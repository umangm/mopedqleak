/***************************************************************************/

#include "int.h"

/***************************************************************************/

extern int bdd_index_out_of_domain;

static int intBitsInModule (intModule *module)
{
	/* Find out how many bits are needed to represent the variables
	   in a given module. */
	int index = 0;
	intVariable *var;

	for (var = module->vars; var; var = var->next)
		index += (var->type? var->type : 1) * (var->dim? var->dim : 1);
	return module->numvars = index;
}

static void intSetIndices (intModule *module)
{
	intVariable *var;
	int index = module->numvars;
	for (var = module->vars; var; var = var->next)
	{
		index -= (var->type? var->type : 1) * (var->dim? var->dim : 1);
		var->bddindex = index;
		if(var->name == wIdentCreate("out_of_domain") && module->name == wIdentCreate("*")) {
			bdd_index_out_of_domain = index;
		}
	}
}

static void intGenBit (int *i, int *shuffle, int bit, intModule *module)
{
	intVariable *var;
	for (var = module->vars; var; var = var->next)
	{
		if (var->type == 0 && bit > 0) continue;
		if (var->type > 0 && bit >= var->type) continue;

		int pos = var->bddindex + bit;
		shuffle[pos] = (*i)++;
		if (var->dim == 0) continue;
		int j, type = var->type? var->type : 1;
		for (j = 1; j < var->dim; j++)
			shuffle[pos += type] = (*i)++;
	}
}

static void intGenShuffle (int *shuffle, intModule *module)
{

        int i;
	for (i = 0; i < module->numvars; i++)
		shuffle[i] = i;
	
      /*  int bit = 0, n = 0;
	while (n < module->numvars)
	{
		intGenBit(&n,shuffle,bit,module);
		bit++;
	}*/
}

static DdNode** intApplyShuffle (int n, DdNode **vars, int *shuffle)
{
	DdNode **new = malloc(n * sizeof(DdNode**));
	while (n-- > 0) new[n] = vars[shuffle[n]];
	return new;
}

static void intSetShuffle (intModule *module,
				DdNode **v1, DdNode **v2, DdNode **v3)
{
	int *shuffle = malloc(module->numvars * sizeof(int));
	intSetIndices(module);
	intGenShuffle(shuffle,module);
	module->first = intApplyShuffle(module->numvars,v1,shuffle);
	module->second = intApplyShuffle(module->numvars,v2,shuffle);
	module->third = intApplyShuffle(module->numvars,v3,shuffle);
	free(shuffle);
}

static void intSetModule (intModule *module)
{
	intVariable *var;
	for (var = module->vars; var; var = var->next)
		var->module = module;
}

extern intPds* intPdsCreate (intModule *modules)
{
	intPds *pds = Malloc(sizeof(struct intPds));
	int global_vars = 0, local_vars = 0;
	intModule *proc;
	int i;

	/* Set the BDD indices for all variables, find out how
	   many global and local variables are needed. */
	pds->modules = modules;
	intSetModule(modules);
	global_vars = intBitsInModule(modules);

	for (proc = pds->modules->next; proc; proc = proc->next)
	{
		intSetModule(proc);
		int num = intBitsInModule(proc);
		if (num > local_vars) local_vars = num;
	}

	pds->rules = NULL;
	pds->mgr = Cudd_Init(0,0,CUDD_UNIQUE_SLOTS,CUDD_CACHE_SLOTS,0);
        
	Cudd_Ref(pds->one = Cudd_addConst(pds->mgr, 1));
	Cudd_Ref(pds->zero = Cudd_addConst(pds->mgr, 0));

	#ifdef db
	printf("globals = %d, locals = %d\n",global_vars,local_vars);
	#endif
	
	pds->gnum = global_vars;
	pds->lnum = local_vars;

	if (global_vars > 0)
	{
		pds->g0 = malloc(global_vars * sizeof(DdNode*));
		pds->g1 = malloc(global_vars * sizeof(DdNode*));
		pds->g2 = malloc(global_vars * sizeof(DdNode*));
	}
	else
		pds->g0 = pds->g1 = pds->g2 = NULL;

	if (local_vars > 0)
	{
		pds->l0 = malloc(local_vars * sizeof(DdNode*));
		pds->l1 = malloc(local_vars * sizeof(DdNode*));
		pds->l2 = malloc(local_vars * sizeof(DdNode*));
	}
	else
		pds->l0 = pds->l1 = pds->l2 = NULL;

	for (i = 0; i < local_vars; i++)
	{
		Cudd_Ref(pds->l0[i] = Cudd_addNewVar(pds->mgr));
		Cudd_Ref(pds->l2[i] = Cudd_addNewVar(pds->mgr));
		Cudd_Ref(pds->l1[i] = Cudd_addNewVar(pds->mgr));
	}

	for (i = 0; i < global_vars; i++)
	{
		Cudd_Ref(pds->g0[i] = Cudd_addNewVar(pds->mgr));
		Cudd_Ref(pds->g2[i] = Cudd_addNewVar(pds->mgr));
		Cudd_Ref(pds->g1[i] = Cudd_addNewVar(pds->mgr));
	}

	// Find the right variable shuffle for all procedures
	intSetShuffle(pds->modules,pds->g0,pds->g1,pds->g2);
	for (proc = pds->modules->next; proc; proc = proc->next)
		intSetShuffle(proc,pds->l0,pds->l1,pds->l2);

	return pds;
}

/***************************************************************************/

extern pdsRule* intPdsInsert (intPds *pds, wIdent p0, wIdent y0,
			wIdent p1, wIdent y1, wIdent y2, intExpr *expr, int type, float probability)
{

	pdsRule *r = malloc(sizeof(pdsRule));
	r->p0 = p0;
	r->p1 = p1;
	r->y0 = y0;
	r->y1 = y1;
	r->y2 = y2;
	r->bdd = intBuild(pds,expr);
	r->type = type;
	r->probability = probability;
	r->next = pds->rules;
	pds->rules = r;

	return r;
}

/**************************************************************************

extern void intPdsDelete (intPds *pds)
{
	bddPdsDelete(pds->pds);
	while (pds->modules)
	{
		intModule *tmp = pds->modules->next;
		while (pds->modules->vars)
		{
			intVariable *tmp = pds->modules->vars->next;
			Free(pds->modules->vars);
			pds->modules->vars = tmp;
		}
		wSetDelete(pds->modules->labels);
		Free(pds->modules);
		pds->modules = tmp;
	}
	Free(pds);
}

**************************************************************************/
