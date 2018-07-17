#include "mql.h"

vector<wIdent> make_continuous(vector<wIdent> given_vector){
	 sort (given_vector.begin(), given_vector.begin()+given_vector.size());
	 return given_vector;
}


wIdent lookup(vector<wIdent> vec, wIdent value){
	wIdent j=-1;
	for(unsigned int i=0; i<vec.size(); i++){
		if(vec[i] == value){
			j=i;
			break;
		}
	}
	return j;
}

map<wIdent, intModule*> map_lines_to_modules(intPds* PDS){
	map<wIdent, intModule*> mp;
	
	intModule* m = PDS->modules;
	while(m){
		wSet* v = m->labels;
		while(v){
			if(mp.find(v->ident) != mp.end()){
				cout<< "Error in mapping line numbers to modules  (More than one lines having same Ident) ! \n";
				break;
			}
			mp[v->ident] = m;
			v = v->next;
		}
		m = m->next;
	}
	return mp;
}

int num_locals(intModule* module){
	int num = 0;
	for (intVariable* var = module->vars; var; var = var->next){
		num += (var->type? var->type : 1) * (var->dim? var->dim : 1);
	}
	return num;
}

void set_module_offsets_sizes(intPds* PDS){
	map<wIdent, int> offset_map, size_map;
	size_offset* ret_vars = PDS->ret_vars;
	while(ret_vars){
		offset_map[ret_vars->name] = ret_vars->offset;
		size_map[ret_vars->name] = ret_vars->size;
		ret_vars = ret_vars->next;
	}
	intModule* m = PDS->modules->next;
	while(m){
		if(m->ret_type != (int)IR_VOID){
			size_offset* so = m->so;
			while(so){
				if(offset_map.find(so->name) == offset_map.end() ){
					cout<<"Error ! return: "<<wIdentString(so->name)<<" var not found in map (IR_STRUCT)!"<<endl; break;
				}
				so->offset = offset_map[so->name];
				so->size = size_map[so->name]*(m->ret_dim? m->ret_dim : 1);;
				so = so->next;
			}
		}
		m = m->next;
	}
}



computed_pds wrap_and_compute(intPds* PDS, bool probReach, analysis_mode mode, char entropy){ 

	set_module_offsets_sizes(PDS);

	DdNode** program_variables;
	
	int gcount, lcount, ret_count;
	gcount = PDS->gnum;
	lcount = PDS->lnum;
	ret_count = PDS->ret_num;
	
	char *main = new char[strlen("main"+1)];
	strcpy(main, "main");
	
	program_variables = new DdNode*[3*gcount+3*lcount];

	bdd_index_out_of_domain = bdd_index_out_of_domain + 3 * lcount;
	
	map<wIdent, intModule*> line_module_map = map_lines_to_modules(PDS);
	
	//The cube is a list of abstraction variables (array of DDNode*s to be more precise). The procedure processRules() makes use of 2 arrays of abs. variables for each rule. Currently, both of them (referred to as cube1 and cube2) are assigned the same value (which is the array {g0", g1", g2", g3", g4",..(all global-double-primed variables).....l0", l1", l2", l3",....all local-double-primed variables.........}. However, this might not always work. The parser should send the information regarding the local variables of each function. Hence, every rule must have its own cube1 and cube2 , in which case a common array of DdNode*s is not useful
	
	#ifdef db
	printf("\n%d non-ret-global-bit(s), %d return bit(s), %d local bit(s) \n\n", gcount-ret_count, ret_count, lcount);
	#endif
	
	#ifdef db
	cout<<"Variable details\n";
	intModule* m = PDS->modules;
	while(m){
		cout<<wIdentString(m->name)<<endl;
		intVariable* v = m->vars;
		while(v){
			cout<<wIdentString(v->name)<<" : ";
			cout<<" ("<<v->name<<") "<<endl;
			v = v->next;

		}
		cout<<endl;
		m = m->next;
	}
	
	m = PDS->modules->next;
	cout<<"\nDetails of return Variables:\n";
	while(m){
		cout<<"\nModule: "<<wIdentString(m->name);
		if(m->ret_type == (int)IR_VOID) cout<<" IR_VOID\n\n";
		else{
			size_offset* so = m->so;
			while(so){
				cout<<"\n return type = "<<so->type;
				cout<<"\n bits used = "<<so->size;
				cout<<"\n BDD index = "<<so->offset;
				cout<<endl;
				so = so->next;
			}
		}
		m = m->next;
	}
	
	cout<<"Label details\n";
	m = PDS->modules;
	while(m){
		cout<<wIdentString(m->name)<<endl;
		wSet* v = m->labels;
		while(v){
			cout<<wIdentString(v->ident)<<" :  ("<<v->ident<<") "<<endl;
			v = v->next;
		}
		cout<<endl;
		m = m->next;
	}
	#endif
	
	for(int i=0; i<gcount+lcount; i++){
	
		//For the global variables
		if(i<gcount){
			Cudd_Ref(program_variables[i*3] = PDS->g0[i]);
			Cudd_Ref(program_variables[i*3+1] = PDS->g2[i]);
			Cudd_Ref(program_variables[i*3+2] = PDS->g1[i]);
		}
		
		//For the local variables
		else{
			Cudd_Ref(program_variables[i*3] = PDS->l0[i-gcount]);
			Cudd_Ref(program_variables[i*3+1] = PDS->l2[i-gcount]);
			Cudd_Ref(program_variables[i*3+2] = PDS->l1[i-gcount]);
		}
	}
	
	
	
    DdNode* identityOnGlobals;
    Cudd_Ref(identityOnGlobals = PDS->one);
	DdNode *t1, *t2;
	for(int i=ret_count; i<gcount; i++){
		Cudd_Ref(t1 = Cudd_addApply(PDS->mgr, Cudd_addXnor, PDS->g0[i], PDS->g1[i]));
		Cudd_Ref(t2 = Cudd_addApply(PDS->mgr, Cudd_addTimes, identityOnGlobals, t1));
		Cudd_RecursiveDeref(PDS->mgr, t1);
		Cudd_RecursiveDeref(PDS->mgr, identityOnGlobals);
		Cudd_Ref(identityOnGlobals = t2);
		Cudd_RecursiveDeref(PDS->mgr, t2);
	}
    int main_locals = num_locals(line_module_map[wIdentCreate(main)]);
    #ifdef db
    cout<<endl<<"main locals ="<<main_locals<<endl;
    #endif
    DdNode* init_main_locals_to_zero;
    Cudd_Ref(init_main_locals_to_zero = PDS->one);
    for(int p=0; p<main_locals; p++){
        Cudd_Ref(t1 = Cudd_addCmpl(PDS->mgr, PDS->l1[p]));
        Cudd_Ref(t2 = Cudd_addApply(PDS->mgr, Cudd_addTimes, init_main_locals_to_zero, t1));
        Cudd_RecursiveDeref(PDS->mgr, t1);
        Cudd_RecursiveDeref(PDS->mgr, init_main_locals_to_zero);
        Cudd_Ref(init_main_locals_to_zero = t2);
        Cudd_RecursiveDeref(PDS->mgr, t2);
    }
    DdNode* default_main_rule;
    Cudd_Ref(default_main_rule = Cudd_addApply(PDS->mgr, Cudd_addTimes, identityOnGlobals, init_main_locals_to_zero));
    Cudd_RecursiveDeref(PDS->mgr, init_main_locals_to_zero);
    Cudd_RecursiveDeref(PDS->mgr, identityOnGlobals);
    DdNode** default_main_cube = new DdNode*[gcount + main_locals - ret_count];
    for(int i=ret_count; i<gcount; i++){
        Cudd_Ref(default_main_cube[i-ret_count] = PDS->g2[i]);
    }
    for(int i=0; i<main_locals; i++){
        Cudd_Ref(default_main_cube[i+gcount-ret_count] = PDS->l2[i]);
    }
    
    
    #ifdef db
	cout<<"Pushing all rules in the vector<rules>\n";
	#endif
    
    wIdent x = 0;
	wIdent y = 0;
	
	vector<PDSRule> rules;
	int rule_number = 0;
	vector<wIdent> states;
	vector<wIdent> line_numbers;
	wIdent z = 0;
	states.push_back(z);
	line_numbers.push_back(z);
    
    PDSRule r;
    
    x = wIdentCreate((char*)"q");
    r.previous_state = x;
    if(lookup(states,x)<0) states.push_back(x);
    
    x = wIdentCreate((char*)"0main");
	r.line_number = x;
    if(lookup(line_numbers,x)<0) line_numbers.push_back(x);
    
	Cudd_Ref(r.relation = default_main_rule);
    
    x = wIdentCreate((char*)"q");
	r.next_state = wIdentCreate((char*)"q");
    if(lookup(states,x)<0) states.push_back(x);
    
    x = wIdentCreate(main);
    y = wIdentCreate((char*)"*");
	r.stack = make_pair(x,y);	
    if(lookup(line_numbers,x)<0) line_numbers.push_back(x);
    if(lookup(line_numbers,y)<0) line_numbers.push_back(y);
	r.cube1 = default_main_cube;
	r.nz1 = gcount + main_locals -ret_count;
	r.cube2 = NULL;
	r.nz2 = 0;
	r.cube3 = NULL;
	r.nz3 = 0;
	r.cube_locals = NULL;
	r.line_is_first_line_of_module = true;
    
    rules.push_back(r);
    
    #ifdef db
    cout<<endl;
    cout<<"Rule #"<<rule_number<<endl;
    cout<<"p0 = "<<wIdentString(r.previous_state)<<" ("<<PDS->rules->p0<<")"<<endl;
    cout<<"y0 = "<<wIdentString(r.line_number)<<" ("<<PDS->rules->y0<<")"<<endl;
    cout<<"p1 = "<<wIdentString(r.next_state)<<" ("<<PDS->rules->p1<<")"<<endl;
    cout<<"y1 = "<<wIdentString(r.stack.first)<<" ("<<PDS->rules->y1<<")"<<endl;
    cout<<"y2 = "<<wIdentString(r.stack.second)<<" ("<<PDS->rules->y2<<")"<<endl;
    
    char buffer[50];
    sprintf (buffer, "rule[%d].dot", rule_number);
    FILE* f =fopen(buffer,"w");
    DdNode** out = new DdNode*[1];
    out[0] = r.relation;
    char** name = new char*[1];
    name[0] = wIdentString(r.line_number);
    Cudd_DumpDot(PDS->mgr, 1 ,out ,NULL, name ,f);
    fclose(f);
    #endif
    
    rule_number++;
	
	/*
	#ifdef db
	int rule_cnt = 1;
	pdsRule* pr = PDS->rules;
	while(pr){
		rule_cnt ++;
		pr = pr->next;
	}
	printf("Total %d rules including the additional rule added\n", rule_cnt);
	#endif
	*/
	
	//Now inserting the rules into the vector "rules". The following block also maps the line numbers to [-1,0,1,2...number_of_lines-1]. -1 represents "epsilon" . It maps the state-numbers to [0,1,2...number-of-states-1]. 
	//For the purpose of mapping, each *new* value is pushed into a vector. This vector already contains a "0" in case the vector is for mapping line numbers. The vector is then sorted. The rules are then assigned the (mapped-line-number - 1) and the mapped-state-number. (Note that the parser passes "0" for "epsilon" whereas processRules() assumes "-1" or any other -ve integral value for "epsilon".
	while(PDS->rules){
		PDSRule r;
		
		x = PDS->rules->p0;
		r.previous_state = x;
		if(lookup(states,x)<0) states.push_back(x);
		
		x = PDS->rules->y0;
		r.line_number = x;
		if(lookup(line_numbers,x)<0) line_numbers.push_back(x);
		
		x = PDS->rules->p1;
		r.next_state = x;
		if(lookup(states,x)<0) states.push_back(x);
		
		x = PDS->rules->y1;
		y = PDS->rules->y2;
		r.stack = make_pair(x,y);
		if(lookup(line_numbers,x)<0) line_numbers.push_back(x);
		if(lookup(line_numbers,y)<0) line_numbers.push_back(y);

		#ifdef db
		cout<<endl;
		cout<<"Rule #"<<rule_number<<endl;
		cout<<"p0 = "<<wIdentString(r.previous_state)<<" ("<<PDS->rules->p0<<")"<<endl;
		cout<<"y0 = "<<wIdentString(r.line_number)<<" ("<<PDS->rules->y0<<")"<<endl;
		cout<<"p1 = "<<wIdentString(r.next_state)<<" ("<<PDS->rules->p1<<")"<<endl;
		cout<<"y1 = "<<wIdentString(r.stack.first)<<" ("<<PDS->rules->y1<<")"<<endl;
		cout<<"y2 = "<<wIdentString(r.stack.second)<<" ("<<PDS->rules->y2<<")"<<endl;
		#endif

		Cudd_Ref(r.relation = PDS->rules->bdd);
		
		r.line_is_first_line_of_module = false;

		#ifdef db
		//cout<<"printing rule#"<<rule_number<<endl;		
		char buffer[50];
		sprintf (buffer, "rule[%d].dot", rule_number);
		FILE* f =fopen(buffer,"w");
		DdNode** out = new DdNode*[1];
		out[0] = r.relation;
		char** name = new char*[1];
		name[0] = wIdentString(r.line_number);
		Cudd_DumpDot(PDS->mgr, 1 ,out ,NULL, name ,f);
		fclose(f);
		//cout<<"Rule#"<<rule_number<<" printed !"<<endl;	
		#endif

		#ifdef db
		//cout<<"Calculating number of locals for line: "<<wIdentString(r.line_number)<<endl;
		#endif
		
		int n_locals = 	num_locals(line_module_map[PDS->rules->y0]);

		#ifdef db
		//cout<<"Number of locals for line: "<<wIdentString(r.line_number)<<" is "<<n_locals<<endl;
		#endif
		
		
		if(r.stack.first==0){
			r.cube1 = NULL;
			r.nz1 = 0;
		}
		else{
			DdNode** cube1 = new DdNode*[gcount + n_locals - ret_count];
			for(int i=ret_count; i<gcount; i++){
				Cudd_Ref(cube1[i-ret_count] = PDS->g2[i]);
			}
			for(int i=0; i<n_locals; i++){
				Cudd_Ref(cube1[i+gcount-ret_count] = PDS->l2[i]);
			}
			r.cube1 = cube1;
			r.nz1 = gcount+n_locals-ret_count;
		}
		
		if(r.stack.second==0){
			r.cube2 = NULL;
			r.nz2 = 0;
			r.cube3 = NULL;
			r.nz3 = 0;
			r.cube_locals = NULL;
		}
		else{
			int n_locals_called_module = num_locals(line_module_map[PDS->rules->y1]);
			
			DdNode** cube2 = new DdNode*[gcount + n_locals_called_module - ret_count];
			
			#ifdef db
			cout<<"\nConstructing cube2:"<<endl;
			#endif
			for(int i=ret_count; i<gcount; i++){
				Cudd_Ref(cube2[i-ret_count] = PDS->g2[i]);
				#ifdef db
				printf("\tvariable g2[%d] included\n", i);
				#endif
			}
			for(int i=0; i<n_locals_called_module; i++){
				Cudd_Ref(cube2[i+gcount-ret_count] = PDS->l2[i]);
				#ifdef db
				printf("\tvariable l2[%d] included\n", i);
				#endif
			}
			r.cube2 = cube2;
			r.nz2 = gcount+n_locals_called_module-ret_count;
			
			
			#ifdef db
			cout<<"\nConstructing cube3:"<<endl;
			#endif
			intModule* m = line_module_map[PDS->rules->y1];
			if(m->ret_type==(int)IR_VOID){
				DdNode** cube3 = new DdNode*[gcount + n_locals - ret_count];
				for(int i=ret_count; i<gcount; i++){
					Cudd_Ref(cube3[i-ret_count] = PDS->g2[i]);
					#ifdef db
					printf("\tvariable g2[%d] included\n", i);
					#endif
				}
				for(int i=0; i<n_locals; i++){
					Cudd_Ref(cube3[i+gcount-ret_count] = PDS->l2[i]);
					#ifdef db
					printf("\tvariable l2[%d] included\n", i);
					#endif
				}
				r.cube3 = cube3;
				r.nz3 = gcount + n_locals - ret_count;
			}
			else{
				int n_bits = 0;
				size_offset* so = m->so;
				while(so){
					n_bits += so->size;
					so = so->next;
				}
				DdNode** cube3 = new DdNode*[gcount - ret_count+ n_locals + n_bits];
				
				so = m->so;
				int j = 0;
				while(so){
					for(int nb = so->offset; nb<so->offset+so->size; nb++){
						Cudd_Ref(cube3[j] = PDS->g2[nb]);
						j++;
						#ifdef db
						printf("\tvariable g2[%d] included\n", nb);
						#endif
					}
					so = so->next;
				}
				for(int i=ret_count; i<gcount; i++){
					Cudd_Ref(cube3[j] = PDS->g2[i]);
					j++;
					#ifdef db
					printf("\tvariable g2[%d] included\n", i);
					#endif
				}
				for(int i=0; i<n_locals; i++){
					Cudd_Ref(cube3[j] = PDS->l2[i]);
					j++;
					#ifdef db
					printf("\tvariable l2[%d] included\n", i);
					#endif
				}
				r.cube3 = cube3;
				r.nz3 = j;
				
			}
			
			
			Cudd_Ref(r.cube_locals = PDS->one);
			
			
			
			for(int n=0; n<n_locals; n++)	Cudd_Ref(r.cube_locals = Cudd_addApply(PDS->mgr, Cudd_addTimes, r.cube_locals, PDS->l1[n]));

		}
		
		
		
		rules.push_back(r);
		PDS->rules = PDS->rules->next;
		rule_number++;
	}

	vector<wIdent> map_states = make_continuous(states);
	vector<wIdent> map_line_numbers = make_continuous(line_numbers);
	
	int state_q, state_q_labels;
	
	for(unsigned int i=0; i<rules.size(); i++){
		
		x = rules[i].previous_state;
		x = lookup(map_states,x);
		if(rules[i].previous_state == wIdentCreate((char*)"q")){
			state_q = x - 1;
		}
		rules[i].previous_state = x-1;
		
		x = rules[i].next_state;
		x = lookup(map_states,x);
		if(rules[i].next_state == wIdentCreate((char*)"q_labels")){
			state_q_labels = x - 1;
		}
		rules[i].next_state = x-1;
		
		x = rules[i].line_number;
		x = lookup(map_line_numbers,x);
		rules[i].line_number = x-1;
		
		x = rules[i].stack.first;
		x = lookup(map_line_numbers,x);
		y = rules[i].stack.second;
		y = lookup(map_line_numbers,y);
		
		rules[i].stack = make_pair(x-1,y-1);
	}

	#ifdef db
	cout<<"Finished mapping line-numbers and states to [0, num_lines] and [0, num_states] respectively\n\n";
	#endif
	
	probabilityMatrix pM;

	if(!probReach){
		if(mode==PRE) pM = processRules_pre( PDS->mgr, map_states.size()-1, map_line_numbers.size()-1, rules, 3*(gcount+lcount), 0.00001);
	}
	
	

	//Assigning the names to line-numbers
	char** outNames = new char*[map_line_numbers.size()-1];
	for(unsigned int i=0; i<map_line_numbers.size()-1; i++){
		outNames[i] = wIdentString(map_line_numbers[i+1]);
	}
	
	computed_pds res ;
	res.pM = pM;
	res.number_of_lines = map_line_numbers.size()-1;
	res.number_of_states = map_states.size()-1;
	res.lineNames = outNames;
	res.state_q = state_q;
	res.state_q_labels = state_q_labels;
	res.main_line = lookup(map_line_numbers,wIdentCreate((char*)"0main"))-1;
	/*****Code for Calling the MinEntropy function*****/
	if(!probReach){
	    #ifdef db
	    cout<<"Computing Entropy...\n";
	    #endif
	    DdNode* inputvars = PDS->one;
	    Cudd_Ref(inputvars);
	    DdNode* outputvars = PDS->one;
	    Cudd_Ref(outputvars);

	    for(int i=ret_count; i<gcount; i++){
	    	if(bdd_index_out_of_domain == i) continue;		//This ensures that inputvars and outputvars do not contain the extra out_of_domain variable
		    inputvars = Cudd_addApply(PDS->mgr, Cudd_addTimes, inputvars, program_variables[i*3]);
		    Cudd_Ref(inputvars);
		    outputvars = Cudd_addApply(PDS->mgr, Cudd_addTimes, outputvars, program_variables[i*3+2]);
		    Cudd_Ref(outputvars);
	    }
		
		if(entropy=='m'){
			#ifdef db
			cout<<"Calling Minentropy\n"<<endl;
			#endif
	
			double me = minEntropy(PDS->mgr, pM[0][0][res.main_line], inputvars, gcount, outputvars, gcount, PDS->prob_program);
			cout<<"MinEntropy = "<<me<<endl;
	    }
	    else if(entropy=='s'){
			#ifdef db
			cout<<"Calling Shannon-Entropy\n"<<endl;
			#endif
	
			double sh = shannonEntropy(PDS->mgr, pM[0][0][res.main_line], inputvars, gcount, outputvars, gcount, PDS->prob_program);
			cout<<"Shannon Entropy = "<<sh<<endl;	
	    }
	}
	
	
	
	return res;
}
