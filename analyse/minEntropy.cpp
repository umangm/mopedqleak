#include "mql.h"

double minEntropy(
	DdManager* manager,
	DdNode* MTBDD,
	DdNode* inputs,
	int number_of_input_variables,
	DdNode* outputs,
	int number_of_output_variables,
	int prob_program)
{
	
	#ifdef ddb
	cout<<"OUT_OF_DOMAIN = "<<bdd_index_out_of_domain<<endl;
	#endif
	
	//exists_out_of_domain(manager);
	
	if(number_of_input_variables==0 &&  number_of_output_variables==0) return 0;
	
	#ifdef ddb
	char buffer[50];
	sprintf (buffer, "MTBDD-min-entropy.dot");
	FILE* f =fopen(buffer,"w");
	DdNode** out = new DdNode*[1];
	out[0] = MTBDD;
	char** names = new char*[1];
	names[0] = (char*)"MTBDD";
	Cudd_DumpDot(manager, 1 ,out ,NULL, names ,f);
	fclose(f);
	#endif
	
	DdNode* MTBDD_copy;
	Cudd_Ref(MTBDD_copy = MTBDD);
		
	if(bdd_index_out_of_domain >= 0){
		DdNode *add_out_of_domain;
		Cudd_Ref(add_out_of_domain = Cudd_addIthVar(manager, 3*bdd_index_out_of_domain));
		DdNode *add_out_of_domain_prime;
		Cudd_Ref(add_out_of_domain_prime = Cudd_addIthVar(manager, 3*bdd_index_out_of_domain+2));
	
		DdNode *cmpl_out_of_domain;
		Cudd_Ref(cmpl_out_of_domain = Cudd_addCmpl(manager, add_out_of_domain));
		DdNode *cmpl_out_of_domain_prime;
		Cudd_Ref(cmpl_out_of_domain_prime = Cudd_addCmpl(manager, add_out_of_domain_prime));
	
		Cudd_Ref(MTBDD = Cudd_addApply(manager, Cudd_addTimes, MTBDD, cmpl_out_of_domain));
		Cudd_Ref(MTBDD_copy = Cudd_addApply(manager, Cudd_addTimes, MTBDD, cmpl_out_of_domain));
	
		Cudd_Ref(MTBDD = Cudd_addApply(manager, Cudd_addTimes, MTBDD, cmpl_out_of_domain_prime));
	
		DdNode* out_of_domain_and_prime;
		Cudd_Ref(out_of_domain_and_prime = Cudd_addApply(manager, Cudd_addTimes, add_out_of_domain, add_out_of_domain_prime));
		Cudd_Ref(MTBDD = Cudd_addExistAbstract(manager, MTBDD, out_of_domain_and_prime));	

	    number_of_input_variables --;
		number_of_output_variables --;
	}
	
	DdNode *tmp1;
	
	if(prob_program<=0){
		tmp1= Cudd_addOrAbstract(manager, MTBDD, inputs);
		Cudd_Ref(tmp1);
	}
	else{
		tmp1= Cudd_addMaxAbstract(manager, MTBDD, inputs);
		Cudd_Ref(tmp1);
	}
	
	#ifdef ddb
	sprintf (buffer, "STEP-1-min-entropy.dot");
	f =fopen(buffer,"w");
	out = new DdNode*[1];
	out[0] = tmp1;
	names = new char*[1];
	names[0] = (char*)"Step-1";
	Cudd_DumpDot(manager, 1 ,out ,NULL, names ,f);
	fclose(f);
	#endif
	
	tmp1 = Cudd_addExistAbstract(manager, tmp1, outputs);
	Cudd_Ref(tmp1);
	if(Cudd_IsNonConstant(tmp1)==1){
		cout<<"The first computed value is not a constant. Please check the inputs."<<endl;
		cout<<"Printing tmp1...\n";
		printADD (manager, tmp1, "tmp1-minentropy", "tmp1", 100);
		return -100;
	}
	
	#ifdef ddb
	sprintf (buffer, "STEP-2-min-entropy.dot");
	f =fopen(buffer,"w");
	out = new DdNode*[1];
	out[0] = tmp1;
	names = new char*[1];
	names[0] = (char*)"Step-2";
	Cudd_DumpDot(manager, 1 ,out ,NULL, names ,f);
	fclose(f);
	#endif
	
	double val = Cudd_V(tmp1);
	
	//Now compute the value for non-termination	
	if(prob_program<=0){
	//T4= orabstract (T1, g_prime, out_domian_prime)
	//T5= existabstract (T1, g, out_of_domain)
	//N_terminates = value(T5)
		
		Cudd_Ref(tmp1 = Cudd_addOrAbstract(manager, MTBDD_copy, outputs));
		if(bdd_index_out_of_domain >= 0){
			DdNode *add_out_of_domain_prime;
			Cudd_Ref(add_out_of_domain_prime = Cudd_addIthVar(manager, 3*bdd_index_out_of_domain + 2));
			Cudd_Ref(tmp1 = Cudd_addOrAbstract(manager, tmp1, add_out_of_domain_prime));
		}
		
		Cudd_Ref(tmp1 = Cudd_addExistAbstract(manager, tmp1, inputs)); 
		if(bdd_index_out_of_domain >= 0){
			DdNode *add_out_of_domain;
			Cudd_Ref(add_out_of_domain = Cudd_addIthVar(manager, 3*bdd_index_out_of_domain));
			Cudd_Ref(tmp1 = Cudd_addOrAbstract(manager, tmp1, add_out_of_domain));
		}
		
		#ifdef ddb
		sprintf (buffer, "STEP-3-min-entropy.dot");
		f =fopen(buffer,"w");
		out = new DdNode*[1];
		out[0] = tmp1;
		names = new char*[1];
		names[0] = (char*)"Step-3";
		Cudd_DumpDot(manager, 1 ,out ,NULL, names ,f);
		fclose(f);
		#endif
		
		#ifdef db
		cout<<"val before adding the extra component = "<<val<<endl;
		#endif
	
		if(Cudd_IsNonConstant(tmp1)==1){
			val += 1;
		}
		else if(Cudd_V(tmp1)==0){
			val += 1;
		}
		
		#ifdef db
		cout<<"val after adding the extra component = "<<val<<endl;
		#endif
	}
	else{
		tmp1 = Cudd_addExistAbstract(manager, MTBDD, outputs);
		Cudd_Ref(tmp1);
		if(bdd_index_out_of_domain >= 0){
			DdNode *add_out_of_domain_prime;
			Cudd_Ref(add_out_of_domain_prime = Cudd_addIthVar(manager, 3*bdd_index_out_of_domain + 2));
			Cudd_Ref(tmp1 = Cudd_addExistAbstract(manager, tmp1, add_out_of_domain_prime));
		}
		
		tmp1= Cudd_addMinAbstract(manager, tmp1, inputs);
		Cudd_Ref(tmp1);
		if(bdd_index_out_of_domain >= 0){
			DdNode *add_out_of_domain;
			Cudd_Ref(add_out_of_domain = Cudd_addIthVar(manager, 3*bdd_index_out_of_domain));
			Cudd_Ref(tmp1 = Cudd_addMinAbstract(manager, tmp1, add_out_of_domain));
		}
		if(Cudd_IsNonConstant(tmp1)==1){
			cout<<"The second computed value is not a constant. Please check the inputs."<<endl;
			return -1;
		}
		#ifdef db
		cout<<"val before adding the extra component = "<<val<<endl;
		#endif
	
		val += (1-Cudd_V(tmp1));
	
		#ifdef db
		cout<<"val after adding the extra component = "<<val<<endl;
		#endif
	}
	return log2(val);
	
}
