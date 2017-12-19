/*****************************************************************************/

#include "int.h"

/*****************************************************************************/

/* The following four variables are too tedious to pass around
   in recursive calls. They are used in intTryVars and the
   procedures called by intTryVars (intExprEval, intBuildValues,
   intTryEval, and intTryRecur). They have no meaning outside
   of calls to intTryVars. */
   
static intPds    *ivPds;
static intVarRef *ivChain;
static DdNode    *ivBdd;
static int        ivDivZero;

int intExprEval (intExpr *tree)
{
	switch (tree->type)
	{
	    case EXPR_CONST:
		return tree->value;
	    case EXPR_PROB:
		return (int)tree->prob;
	    case EXPR_QVAR:
		return tree->q->value;
	    case EXPR_VAR:
		return tree->vref->value;
	    case EXPR_PLUS:
		return intExprEval(tree->left) + intExprEval(tree->right);
	    case EXPR_MINUS:
		return intExprEval(tree->left) - intExprEval(tree->right);
	    case EXPR_MULT:
		return intExprEval(tree->left) * intExprEval(tree->right);
	    case EXPR_DIV: {
			int divisor = intExprEval(tree->right);
			if (!divisor) { ivDivZero = 1; return 0; }
			return intExprEval(tree->left) / divisor;
		}
	    case EXPR_SHL:
		return intExprEval(tree->left) << intExprEval(tree->right);
	    case EXPR_SHR:
		return intExprEval(tree->left) >> intExprEval(tree->right);
	    case EXPR_BIT_OR:
		return intExprEval(tree->left) | intExprEval(tree->right);
	    case EXPR_BIT_AND:
		return intExprEval(tree->left) & intExprEval(tree->right);
	    case EXPR_BIT_XOR:
		return intExprEval(tree->left) ^ intExprEval(tree->right);
	    case EXPR_LT:
		return intExprEval(tree->left) < intExprEval(tree->right);
	    case EXPR_LE:
		return intExprEval(tree->left) <= intExprEval(tree->right);
	    case EXPR_EQ:
		return intExprEval(tree->left) == intExprEval(tree->right);
	    case EXPR_NE:
		return intExprEval(tree->left) != intExprEval(tree->right);
	    case EXPR_GE:
		return intExprEval(tree->left) >= intExprEval(tree->right);
	    case EXPR_GT:
		return intExprEval(tree->left) > intExprEval(tree->right);
	    default:
		fprintf(stderr,"unexpected token (%i)", tree->type);
		exit(0);
	}
}

static DdNode* intBuildValues ()
{	/* Evaluate the values of the entries in ivChain,
		and build a BDD expressing that the variables
		in the chain have their respective values. */
	intVarRef *vref;
	DdManager *mgr = ivPds->mgr;
	DdNode *result, *tmp1, *tmp2;
	DdNode **cube;

	Cudd_Ref(result = ivPds->one);
	for (vref = ivChain; vref; vref = vref->next)
	{
		int i, baseindex, value;

		if (vref->index)
		{	/* For arrays, evaluate the index expression
			   and then choose the correct entry. */
			int eval;
			ivDivZero = 0;
			eval = intExprEval(vref->index);

			if (ivDivZero
			      || eval < vref->var->low_index
			      || eval >= vref->var->low_index + vref->var->dim)
			{	/* exceptions lead to 'false' BDDs */
				Cudd_RecursiveDeref(mgr,result);
				Cudd_Ref(ivPds->zero);
				return ivPds->zero;
			}
			baseindex = vref->var->bddindex + vref->var->type
				* (eval - vref->var->low_index);
		}
		else	/* Scalars */
			baseindex = vref->var->bddindex;

		/* Build a cube for the current value. */
		value = vref->value;
		cube = Malloc(vref->var->type * sizeof(DdNode*));

		for (i = vref->var->type-1; i >= 0; i--)
		{
			Cudd_Ref(tmp1 = vref->context[baseindex + i]);
	//		Cudd_Ref(tmp1);	//newly added
			if (!(value & 1)){
				tmp1 = Cudd_addCmpl(mgr,tmp1);
				Cudd_Ref(tmp1);	//newly added
			}
			cube[i] = tmp1;
			Cudd_Ref(cube[i]);	//newly added
			//Cudd_RecursiveDeref(mgr, tmp1);	//newly added
			value >>= 1;
		}

		Cudd_Ref(tmp1 = Cudd_addComputeCube(mgr,cube,NULL,vref->var->type));
		Free(cube);

		/* Conjoin the cube with the rest. */
		Cudd_Ref(tmp2 =  Cudd_addApply(mgr,Cudd_addTimes,result,tmp1));
		Cudd_RecursiveDeref(mgr,result);
		Cudd_RecursiveDeref(mgr,tmp1);
		result = tmp2;	
		Cudd_Ref(result);	//newly added
	}
	return result;
}

static void intTryEval (intExpr *tree, intVarRef *bvar)
{	/* Check if the current valuation satisfies the expression
		and if so, build a BDD for it and disjoin it with ivBdd.
	   If bvar==NULL, then we're evaluating an integer expression.
	   If bvar!=NULL, then we're evaluating the index expression
		of a boolean variable. */

	DdManager *mgr = ivPds->mgr;
	DdNode *tmp0, *tmp1;
	int eval;

	ivDivZero = 0;
	eval = intExprEval(tree);
	if (ivDivZero) return;

	/* If evaluating integer expression, result must be non-zero. */
	if (!bvar && !eval) return;

	/* If evaluating index expression, check if index is admissible. */
	if (bvar && (eval < bvar->var->low_index ||
			eval >= bvar->var->low_index + bvar->var->dim))
		return;

	/* Build a BDD for the variables in ivChain. */
	Cudd_Ref(tmp0 = intBuildValues());

	if (bvar)
	{	/* Conjoin the result with the boolean variable
		   corresponding to the index value. */
		Cudd_Ref(tmp1 = Cudd_addApply(mgr,Cudd_addTimes, tmp0,
		    bvar->context[bvar->var->bddindex
				+ eval - bvar->var->low_index]));
		Cudd_RecursiveDeref(mgr,tmp0);
		Cudd_Ref(tmp0 = tmp1);
		//Cudd_Ref(tmp0);	//newly added
	}

	/* Add the result to ivBdd. */
	Cudd_Ref(tmp1 = Cudd_addApply(mgr,Cudd_addOr,ivBdd,tmp0));
	Cudd_RecursiveDeref(mgr,ivBdd);
	Cudd_RecursiveDeref(mgr,tmp0);
	Cudd_Ref(ivBdd = tmp1);
	//Cudd_Ref(ivBdd); //newly added
}

static void intTryRecur (intExpr *tree, intVarRef *vref, intVarRef *bvar)
{

	if (!vref)
	{
		intTryEval(tree,bvar);
		return;
	}

	for (vref->value = 0; vref->value < vref->maxval; vref->value++)
		intTryRecur(tree,vref->next,bvar);
}

static DdNode* intTryVars (intPds *pds, intExpr *tree,
				intVarRef *vchain, intVarRef *bvar)
{
	ivChain = vchain;
	ivPds = pds;
	Cudd_Ref(ivBdd = ivPds->zero);
	intTryRecur(tree,vchain,bvar);
	return ivBdd;
}

/*****************************************************************************/

static DdNode* intBuildIexpr (intPds *pds, intExpr *tree)
{
	DdManager *mgr = pds->mgr;
	DdNode *tmp1 = NULL, *tmp2, *tmp3, *tmp4, *tmp5, *tmp6;
	DdNode *result;
	intVarRef *vchain;

	/* equality between scalar variables */
	if (tree->type == EXPR_EQ &&
		tree->left->type == EXPR_VAR && tree->right->type == EXPR_VAR)
	{
		intVarRef *vr1 = tree->left->vref;
		intVarRef *vr2 = tree->right->vref;
		intVariable *var1 = vr1->var;
		intVariable *var2 = vr2->var;
		if (!var1->dim && !var2->dim && var1->type == var2->type)
		{
			int i;

			Cudd_Ref(result = pds->one);
			for (i = var1->type-1; i >= 0; i--)
			{
				Cudd_Ref(tmp3 = Cudd_addCmpl(mgr, vr1->context[var1->bddindex + i]));
				Cudd_Ref(tmp4 = Cudd_addCmpl(mgr, vr2->context[var2->bddindex + i]));
				Cudd_Ref(tmp5 = Cudd_addApply(mgr, Cudd_addTimes, vr1->context[var1->bddindex + i], vr2->context[var2->bddindex + i]));
				Cudd_Ref(tmp6 = Cudd_addApply(mgr, Cudd_addTimes, tmp3, tmp4));
				
				Cudd_Ref(tmp1 = Cudd_addApply(mgr, Cudd_addOr, tmp5, tmp6));
				Cudd_RecursiveDeref(mgr, tmp5);
				Cudd_RecursiveDeref(mgr, tmp6);
				Cudd_RecursiveDeref(mgr, tmp3);
				Cudd_RecursiveDeref(mgr, tmp4);
				
				//printf("i=%d\n", i);
				Cudd_Ref(tmp2 = Cudd_addApply(mgr,Cudd_addTimes,result,tmp1));
				Cudd_RecursiveDeref(mgr,tmp1);
				Cudd_RecursiveDeref(mgr,result);
				result = tmp2;
				Cudd_Ref(result);	//newly added
				//Cudd_RecursiveDeref(mgr,tmp2);	//newly added
			}

			return result;
		}
	}

	/* equality between scalar variables and constants */
	if (tree->type == EXPR_EQ &&
		tree->left->type == EXPR_VAR &&
		tree->right->type == EXPR_CONST)
	{
		intVarRef *vref = tree->left->vref;
		intVariable *var = vref->var;
		int number = tree->right->value;

		if (!var->dim)
		{
			int i;

			if (number < 0 || number >= vref->maxval)
			{
				Cudd_Ref(result = pds->zero);
				return result;
			}

			Cudd_Ref(result = pds->one);
			for (i = var->type - 1; i >= 0; i--)
			{
				Cudd_Ref(tmp1 = vref->context[var->bddindex + i]);
			/*	Cudd_Ref(tmp1); //newly added */
				if (!(number & 1)) {
					tmp1 = Cudd_addCmpl(mgr, tmp1);
					Cudd_Ref(tmp1);	//newly added
				}
				Cudd_Ref(tmp2 = Cudd_addApply(mgr,Cudd_addTimes,result,tmp1));
				Cudd_RecursiveDeref(mgr,result);
				result = tmp2;
				Cudd_Ref(result);	//newly added
				number >>= 1;
			}

			return result;
		}
	}
	
	/* comparison (less-than-equal) between scalar variables */
	if (tree->type == EXPR_LE &&
		tree->left->type == EXPR_VAR && tree->right->type == EXPR_VAR)
	{
		intVarRef *vr1 = tree->left->vref;
		intVarRef *vr2 = tree->right->vref;
		intVariable *var1 = vr1->var;
		intVariable *var2 = vr2->var;
		if (!var1->dim && !var2->dim && var1->type == var2->type)
		{
			int i;
			DdNode **n1 = vr1->context+var1->bddindex+var1->type-1;
			DdNode **n2 = vr2->context+var2->bddindex+var1->type-1;

			Cudd_Ref(result =
				Cudd_addCmpl(mgr, Cudd_addApply(mgr, Cudd_addTimes, *n1,Cudd_addCmpl(mgr, *n2))));
			for (i = 1; i < var1->type; i++)
			{
				n1--, n2--;
				Cudd_Ref(tmp1 = Cudd_addApply(mgr,Cudd_addXnor,*n1,*n2));
				Cudd_Ref(tmp2 = Cudd_addApply(mgr, Cudd_addTimes,result,tmp1));
				Cudd_RecursiveDeref(mgr,tmp1);
				Cudd_RecursiveDeref(mgr,result);
				Cudd_Ref(tmp1 =
					Cudd_addApply(mgr,Cudd_addTimes, Cudd_addCmpl(mgr,*n1),*n2));
				Cudd_Ref(result = Cudd_addApply(mgr,Cudd_addOr,tmp1,tmp2));
				Cudd_RecursiveDeref(mgr,tmp1);
				Cudd_RecursiveDeref(mgr,tmp2);
			}

			return result;
		}
	}
	
	/* expression of type X = S | O */
	if (tree->type == EXPR_EQ &&
		tree->left->type == EXPR_VAR && tree->right->type == EXPR_BIT_OR
		&& tree->right->left->type == EXPR_VAR
		&& tree->right->right->type == EXPR_VAR)
	{
		intVarRef *vr1 = tree->left->vref;
		intVarRef *vr2 = tree->right->left->vref;
		intVarRef *vr3 = tree->right->right->vref;
		intVariable *var1 = vr1->var;
		intVariable *var2 = vr2->var;
		intVariable *var3 = vr3->var;
		if (!var1->dim && !var2->dim && !var3->dim
			&& var1->type == var2->type
			&& var1->type == var3->type)
		{
			int i;
			DdNode **n1 = vr1->context + var1->bddindex;
			DdNode **n2 = vr2->context + var2->bddindex;
			DdNode **n3 = vr3->context + var3->bddindex;

			Cudd_Ref(result = pds->one);
			for (i = 0; i < var1->type; i++)
			{
				Cudd_Ref(tmp1 = Cudd_addApply(mgr,Cudd_addOr, *n2,*n3));
				Cudd_Ref(tmp2 = Cudd_addApply(mgr,Cudd_addXnor,*n1,tmp1));
				Cudd_RecursiveDeref(mgr,tmp1);
				Cudd_Ref(tmp1 = Cudd_addApply(mgr,Cudd_addTimes,result,tmp2));
				Cudd_RecursiveDeref(mgr,result);
				Cudd_RecursiveDeref(mgr,tmp2);
				result = tmp1;
				n1++, n2++, n3++;
			}

			return result;
		}
	}
	
		/* expression of type X = S | c (where c is a constant) */
	if (tree->type == EXPR_EQ &&
		tree->left->type == EXPR_VAR && tree->right->type == EXPR_BIT_OR
		&& tree->right->left->type == EXPR_VAR
		&& tree->right->right->type == EXPR_CONST)
	{
		intVarRef *vr1 = tree->left->vref;
		intVarRef *vr2 = tree->right->left->vref;
		intVariable *var1 = vr1->var;
		intVariable *var2 = vr2->var;
		int number = tree->right->right->value;
		if (!var1->dim && !var2->dim && var1->type == var2->type)
		{
			int i;

			Cudd_Ref(result = pds->one);
			for (i = var1->type - 1; i >= 0; i--)
			{
				DdNode **n1 = vr1->context + var1->bddindex + i;
				DdNode **n2 = vr2->context + var2->bddindex + i;

				if (number & 1)
					Cudd_Ref(tmp1 = *n1);
				else
					Cudd_Ref(tmp1 = Cudd_addApply(mgr,Cudd_addXnor,*n1,*n2));

				Cudd_Ref(tmp2 = Cudd_addApply(mgr,Cudd_addTimes,result,tmp1));
				Cudd_RecursiveDeref(mgr,result);
				Cudd_RecursiveDeref(mgr,tmp1);
				result = tmp2;
				number >>= 1;
			}

			return result;
		}
	}
		
	/* all other types of expressions */
	vchain = (intVarRef*) tree->value;
	return intTryVars(pds,tree,vchain,NULL);
}

static DdNode *intBuildRecur (intPds *pds, intExpr *tree)
{
	DdManager *mgr = pds->mgr;
	DD_AOP fn ;
	DdNode *tmp0, *tmp1, *tmp2;
	//DdNode* *tmp3, *tmp4, *tmp5, *tmp6;
	intQuantifier *q;
	intVarRef *vref, *vchain;

	switch (tree->type)
	{
	    case EXPR_OR:
		Cudd_Ref(tmp1 = intBuildRecur(pds,tree->left));
		Cudd_Ref(tmp2 = intBuildRecur(pds,tree->right));
		Cudd_Ref(tmp0 = Cudd_addApply(pds->mgr,Cudd_addOr,tmp1,tmp2));
		Cudd_RecursiveDeref(mgr,tmp1);
		Cudd_RecursiveDeref(mgr,tmp2);
		return tmp0;
	    case EXPR_AND:
		Cudd_Ref(tmp1 = intBuildRecur(pds,tree->left));
		Cudd_Ref(tmp2 = intBuildRecur(pds,tree->right));
		Cudd_Ref(tmp0 = Cudd_addApply(pds->mgr,Cudd_addTimes,tmp1,tmp2));
		Cudd_RecursiveDeref(mgr,tmp1);
		Cudd_RecursiveDeref(mgr,tmp2);
		return tmp0;
		
	    case EXPR_EQV:
		
		/*
		tmp1 = intBuildRecur(pds,tree->left);
		tmp2 = intBuildRecur(pds,tree->right);
		Cudd_Ref(tmp3 = Cudd_addCmpl(pds->mgr, tmp1));
		Cudd_Ref(tmp4 = Cudd_addCmpl(pds->mgr, tmp2));
		Cudd_Ref(tmp5 = Cudd_addApply(pds->mgr, Cudd_addTimes, tmp1, tmp2));
		Cudd_Ref(tmp6 = Cudd_addApply(pds->mgr, Cudd_addTimes, tmp3, tmp4));
		Cudd_RecursiveDeref(mgr,tmp1);
		Cudd_RecursiveDeref(mgr,tmp2);
		Cudd_RecursiveDeref(mgr,tmp3);
		Cudd_RecursiveDeref(mgr,tmp4);
		Cudd_Ref(tmp0 = Cudd_addApply(pds->mgr, Cudd_addOr, tmp5, tmp6));
		Cudd_RecursiveDeref(mgr,tmp5);
		Cudd_RecursiveDeref(mgr,tmp6);
		return tmp0;
		*/
		
		Cudd_Ref(tmp1 = intBuildRecur(pds,tree->left));
		Cudd_Ref(tmp2 = intBuildRecur(pds,tree->right));
		Cudd_Ref(tmp0 = Cudd_addApply(pds->mgr,Cudd_addXnor,tmp1,tmp2));
		Cudd_RecursiveDeref(mgr,tmp1);
		Cudd_RecursiveDeref(mgr,tmp2);
		return tmp0;
		
	    case EXPR_XOR:
		/*
		tmp1 = intBuildRecur(pds,tree->left);
		tmp2 = intBuildRecur(pds,tree->right);
		Cudd_Ref(tmp3 = Cudd_addCmpl(pds->mgr, tmp1));
		Cudd_Ref(tmp4 = Cudd_addCmpl(pds->mgr, tmp2));
		Cudd_Ref(tmp5 = Cudd_addApply(pds->mgr, Cudd_addTimes, tmp1, tmp4));
		Cudd_Ref(tmp6 = Cudd_addApply(pds->mgr, Cudd_addTimes, tmp2, tmp3));
		Cudd_RecursiveDeref(mgr,tmp1);
		Cudd_RecursiveDeref(mgr,tmp2);
		Cudd_RecursiveDeref(mgr,tmp3);
		Cudd_RecursiveDeref(mgr,tmp4);
		Cudd_Ref(tmp0 = Cudd_addApply(pds->mgr, Cudd_addOr, tmp5, tmp6));
		Cudd_RecursiveDeref(mgr,tmp5);
		Cudd_RecursiveDeref(mgr,tmp6);
		return tmp0;
		*/
		
		Cudd_Ref(tmp1 = intBuildRecur(pds,tree->left));
		Cudd_Ref(tmp2 = intBuildRecur(pds,tree->right));
		Cudd_Ref(tmp0 = Cudd_addApply(pds->mgr,Cudd_addXor,tmp1,tmp2));
		Cudd_RecursiveDeref(mgr,tmp1);
		Cudd_RecursiveDeref(mgr,tmp2);
		return tmp0;

	    case EXPR_NOT:
        Cudd_Ref(tmp0=Cudd_addCmpl(pds->mgr, intBuildRecur(pds,tree->left)));
        return tmp0;

	    case EXPR_FORALL:
	    case EXPR_EXISTS:
		fn = (tree->type == EXPR_FORALL)? Cudd_addTimes : Cudd_addOr;
		Cudd_Ref(tmp0 = (tree->type == EXPR_FORALL)?
					pds->one : pds->zero);
		q = tree->q;
		for (q->value = q->lower; q->value <= q->upper; q->value++)
		{
			Cudd_Ref(tmp1 = intBuildRecur(pds,tree->left));
			Cudd_Ref(tmp2 = Cudd_addApply(mgr,fn,tmp0,tmp1));
			Cudd_RecursiveDeref(mgr,tmp0);
			Cudd_RecursiveDeref(mgr,tmp1);
			Cudd_Ref(tmp0 = tmp2);
		}
		return tmp0;

	    case EXPR_VAR:
		vref = tree->vref;
		if (!vref->index)
		{
		    DdNode *bvar;
                     Cudd_Ref(bvar = vref->context[vref->var->bddindex]);
		    return bvar;
		}
		vchain = (intVarRef*) tree->value;
		return intTryVars(pds,vref->index,vchain,vref);
		//return Cudd_BddToAdd(pds->mgr, intTryVars(pds,vref->index,vchain,vref));		//Change made here

        case EXPR_LT: case EXPR_LE: case EXPR_EQ:
        case EXPR_NE: case EXPR_GT: case EXPR_GE:
		Cudd_Ref(tmp0= intBuildIexpr(pds,tree)); /*Rohit*/
        return tmp0;
                 //Cudd_Ref(tmp0 = Cudd_BddToAdd(pds->mgr, intBuildIexpr(pds,tree)));				//Change made here
		//return tmp0;

	    case EXPR_CONST:
		Cudd_Ref(tmp0 = tree->value? pds->one : pds->zero);
		return tmp0;
		
	    case EXPR_PROB:
    	Cudd_Ref(tmp0 = Cudd_addConst(pds->mgr, tree->prob));
    	return tmp0;

	    default:
		fprintf(stderr,"unknown token in intBuild (%i)",tree->type);
		exit(1);
	}
}

/*****************************************************************************/

/* Fill in additional data into intVarRef structs.
   For every integer expression, collect a list of all distinct intVarRef
   structs and hide it in the 'value' field. */

static DdNode** intGetContext (intPds *pds, intVarRef *vref)
{
	intModule *module = vref->var->module;
	if (vref->primes == 0) return module->first;
	if (vref->primes == 1) return module->second;
	if (vref->primes == 2) return module->third;
	fprintf(stderr,"could not set context (%s)\n",
			wIdentString(vref->var->name));
	exit(1);
}

static void intCollectVars (intPds *pds, intExpr *expr, intVarRef **idlist)
{
	intVariable *var;
	intVarRef *vref, *tmp;

	switch (expr->type)
	{
	    case EXPR_LT: case EXPR_LE: case EXPR_EQ:
	    case EXPR_NE: case EXPR_GT: case EXPR_GE:
	    case EXPR_PLUS: case EXPR_MINUS: case EXPR_MULT:
        case EXPR_DIV:  case EXPR_SHL: case EXPR_SHR:
        case EXPR_BIT_OR: case EXPR_BIT_AND: case EXPR_BIT_XOR:
		intCollectVars(pds,expr->left,idlist);
		intCollectVars(pds,expr->right,idlist);
		return;

	    case EXPR_VAR:
		vref = expr->vref;
		var = vref->var;
		vref->context = intGetContext(pds,vref);
		vref->maxval = var->type? (1<<var->type) : 2;
		vref->next = *idlist;
		*idlist = vref;

		if (vref->index)
		{	/* if access to array element, always add to idlist */
			intCollectVars(pds,vref->index,idlist);
			return;
		}

		/* for scalars, remove if already there */
		for (tmp = vref->next; tmp; tmp = tmp->next)
			if (tmp->var == var
				&& tmp->context == vref->context)
			{
				*idlist = vref->next;
				Free(vref);
				expr->vref = tmp;
				break;
			}
		return;

	    case EXPR_QVAR:
	    case EXPR_CONST:
	    case EXPR_PROB:
		return;

	    default:
		fprintf(stderr,"unexpected token (%d)",expr->type);
		exit(1);
	}
}

static void intCheckVars (intPds *pds, intExpr *expr)
{

	if(!expr) printf("In intCheckVars, expr is NULL\n");
	switch (expr->type)
	{
	    case EXPR_OR:  case EXPR_AND:
	    case EXPR_EQV: case EXPR_XOR:
		intCheckVars(pds,expr->left);
		intCheckVars(pds,expr->right);
		return;

	    case EXPR_EXISTS: case EXPR_FORALL:
	    case EXPR_NOT:
		intCheckVars(pds,expr->left);
		return;

           case EXPR_VAR:
		expr->vref->context = intGetContext(pds,expr->vref);
		if (expr->vref->index)
		{
			expr->value = 0;
			intCollectVars(pds,expr->vref->index,
				(intVarRef**)&(expr->value));
		}
		return;

            case EXPR_LT: case EXPR_LE: case EXPR_EQ:
            case EXPR_NE: case EXPR_GT: case EXPR_GE:
		expr->value = 0;
		intCollectVars(pds,expr,(intVarRef**)&(expr->value));
		return;

	    case EXPR_CONST:
	    case EXPR_PROB:
		return;

            default:
                fprintf(stderr,"unexpected token (%d)",expr->type);
                exit(1);
	}
}

/*****************************************************************************/

DdNode* intBuild (intPds *pds, intExpr *expr)
{
	DdNode *result;

	if (!expr)
	{
		fprintf(stderr,"warning: NULL expression, assuming 'true'\n");
		Cudd_Ref(pds->one);
		return pds->one;
	}
	intCheckVars(pds,expr);
	result = intBuildRecur(pds,expr);
	Cudd_Ref(result);	//newly added
	return result;
}

/***************************************************************************/
