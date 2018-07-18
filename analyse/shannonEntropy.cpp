#include "mql.h"

double shannonEntropy(
	DdManager* manager,
	DdNode* MTBDD,
	DdNode* inputs,
	int number_of_input_variables,
	DdNode* outputs,
	int number_of_output_variables,
	int prob_program)
{	
	if(number_of_input_variables==0 &&  number_of_output_variables==0) return 0;

	printADD(manager, MTBDD, "Umang_test", "MTBDD", 100, NULL);
	
	if(bdd_index_out_of_domain < 0){
		#ifdef ddb
		char buffer[50];
		sprintf (buffer, "MTBDD-Shannon-entropy.dot");
		FILE* f =fopen(buffer,"w");
		DdNode** out = new DdNode*[1];
		out[0] = MTBDD;
		char** names = new char*[1];
		names[0] = (char*)"MTBDD";
		Cudd_DumpDot(manager, 1 ,out ,NULL, names ,f);
		fclose(f);
		#endif
	
		DdNode *tmp1;
	
		Cudd_Ref(tmp1= Cudd_addExistAbstract(manager, MTBDD, inputs));
	
		#ifdef ddb
		sprintf (buffer, "Step-1-Shannon-entropy.dot");
		f =fopen(buffer,"w");
		out = new DdNode*[1];
		out[0] = tmp1;
		names = new char*[1];
		names[0] = (char*)"Step-1";
		Cudd_DumpDot(manager, 1 ,out ,NULL, names ,f);
		fclose(f);
		#endif
	
		Cudd_Ref(tmp1= Cudd_addApply(manager, Cudd_addDivide, tmp1, Cudd_addConst(manager, ((double)exp2(number_of_input_variables)))));
	
		#ifdef ddb
		sprintf (buffer, "Step-1-a-Shannon-entropy.dot");
		f =fopen(buffer,"w");
		out = new DdNode*[1];
		out[0] = tmp1;
		names = new char*[1];
		names[0] = (char*)"Step-1-a";
		Cudd_DumpDot(manager, 1 ,out ,NULL, names ,f);
		fclose(f);
		#endif
	
		Cudd_Ref(tmp1 = Cudd_addLogExistAbstract(manager, tmp1, outputs));
	
		#ifdef ddb
		sprintf (buffer, "Step-2-Shannon-entropy.dot");
		f =fopen(buffer,"w");
		out = new DdNode*[1];
		out[0] = tmp1;
		names = new char*[1];
		names[0] = (char*)"Step-2";
		Cudd_DumpDot(manager, 1 ,out ,NULL, names ,f);
		fclose(f);
		#endif
	
		if(Cudd_IsNonConstant(tmp1)==1){
			cout<<"The first computed value is not a constant. Please check the inputs."<<endl;
			cout<<"Printing tmp1...\n";
			printADD (manager, tmp1, "tmp1-shannonentropy", "tmp1", 100);
			return -1;
		}
		double val1 = -1 * Cudd_V(tmp1);
	
		#ifdef db
		cout<<"After Exist over inputs followed by LogExist over outputs, constant_node = "<<val1<<endl;
		#endif
	
		//Now compute the contribution for non-termination	in the 1st quantity
		if(prob_program<=0){
			Cudd_Ref(tmp1 = Cudd_addOrAbstract(manager, MTBDD, outputs));
		
			#ifdef ddb
			sprintf (buffer, "Step-3-Shannon-entropy.dot");
			f =fopen(buffer,"w");
			out = new DdNode*[1];
			out[0] = tmp1;
			names = new char*[1];
			names[0] = (char*)"Step-3";
			Cudd_DumpDot(manager, 1 ,out ,NULL, names ,f);
			fclose(f);
			#endif
		
			Cudd_Ref(tmp1 = Cudd_addCmpl(manager, tmp1));
		
			#ifdef ddb
			sprintf (buffer, "Step-4-Shannon-entropy.dot");
			f =fopen(buffer,"w");
			out = new DdNode*[1];
			out[0] = tmp1;
			names = new char*[1];
			names[0] = (char*)"Step-4";
			Cudd_DumpDot(manager, 1 ,out ,NULL, names ,f);
			fclose(f);
			#endif
		
			Cudd_Ref(tmp1 = Cudd_addExistAbstract(manager, tmp1, inputs));
		
			#ifdef ddb
			sprintf (buffer, "Step-5-Shannon-entropy.dot");
			f =fopen(buffer,"w");
			out = new DdNode*[1];
			out[0] = tmp1;
			names = new char*[1];
			names[0] = (char*)"Step-5";
			Cudd_DumpDot(manager, 1 ,out ,NULL, names ,f);
			fclose(f);
			#endif
	
			if(Cudd_IsNonConstant(tmp1)==1){
				cout<<"The second computed value is not a constant. Please check the inputs."<<__LINE__<<endl;
				cout<<"Printing tmp1...\n";
				printADD (manager, tmp1, "tmp1-shannonentropy_non_termination", "tmp1", 100);
				return -1;
			}
			else{
				#ifdef db
				cout<<"val1 before adding the extra component = "<<val1<<endl;
				#endif
				double z = Cudd_V(tmp1)/((double)exp2(number_of_input_variables));
				if(z>0) val1 -= z*log2(z);
			}
		
			#ifdef db
			cout<<"val1 after adding the extra component = "<<val1<<endl;
			#endif
		}
		else{
			//T1_nonterm = abstract(+,G', T_P)
		    //T2_nonterm = abstract(+,G, T1_nonterm)
		    //p1_nonterm = 1 - [ val(T2_nonterm) / 2^n ]
		    //val1_nonterm = -p1_nonterm log p1_nonterm
		    //val1 = val1_term + val1_nonterm
		    //1st quantity I(O)
		    
		    Cudd_Ref(tmp1 = Cudd_addExistAbstract(manager, MTBDD, outputs));
		    
		    #ifdef ddb
			sprintf (buffer, "Step-6-Shannon-entropy.dot");
			f =fopen(buffer,"w");
			out = new DdNode*[1];
			out[0] = tmp1;
			names = new char*[1];
			names[0] = (char*)"Step-3";
			Cudd_DumpDot(manager, 1 ,out ,NULL, names ,f);
			fclose(f);
			#endif
		
		    Cudd_Ref(tmp1 = Cudd_addExistAbstract(manager, tmp1, inputs));
		    
		     #ifdef ddb
			sprintf (buffer, "Step-7-Shannon-entropy.dot");
			f =fopen(buffer,"w");
			out = new DdNode*[1];
			out[0] = tmp1;
			names = new char*[1];
			names[0] = (char*)"Step-3";
			Cudd_DumpDot(manager, 1 ,out ,NULL, names ,f);
			fclose(f);
			#endif
		
			if(Cudd_IsNonConstant(tmp1)==1){
				cout<<"The second computed value is not a constant. Please check the inputs."<<__LINE__<<endl;
				cout<<"Printing tmp1...\n";
				printADD (manager, tmp1, "tmp1-shannonentropy_non_termination", "tmp1", 100);
				return -1;
			}
			else{
				#ifdef db
				cout<<"val1 before adding the extra component = "<<val1<<endl;
				#endif
				double z = 1 - (Cudd_V(tmp1)/((double)exp2(number_of_input_variables)));
				if(z>0) val1 -= z*log2(z);
			}
		
			#ifdef db
			cout<<"val1 after adding the extra component = "<<val1<<endl;
			#endif
		}
	
		double val2 = 0;
	
		if(prob_program>0){ //Computing the 2nd quantity which is non-Zero for probabilistic programs in general
			Cudd_Ref(tmp1 = Cudd_addLogExistAbstract(manager, MTBDD, outputs));
		
			#ifdef ddb
			sprintf (buffer, "Step-8-Shannon-entropy.dot");
			f =fopen(buffer,"w");
			out = new DdNode*[1];
			out[0] = tmp1;
			names = new char*[1];
			names[0] = (char*)"Step-5";
			Cudd_DumpDot(manager, 1 ,out ,NULL, names ,f);
			fclose(f);
			#endif
		
			Cudd_Ref(tmp1 = Cudd_addExistAbstract(manager, tmp1, inputs));
		
			#ifdef ddb
			sprintf (buffer, "Step-9-Shannon-entropy.dot");
			f =fopen(buffer,"w");
			out = new DdNode*[1];
			out[0] = tmp1;
			names = new char*[1];
			names[0] = (char*)"Step-5";
			Cudd_DumpDot(manager, 1 ,out ,NULL, names ,f);
			fclose(f);
			#endif
		
		
			if(Cudd_IsNonConstant(tmp1)==1){
				cout<<"The second computed value is not a constant. Please check the inputs."<<endl;
				cout<<"Printing tmp1...\n";
				printADD (manager, MTBDD, "MTBDD-shannonentropy_non_termination", "MTBDD", 100);
				printADD (manager, tmp1, "tmp1-shannonentropy_non_termination", "tmp1", 100);
				return -1;
			}
			else{
				double z = Cudd_V(tmp1);
			
				#ifdef db
				cout<<"(for prob program) After LogExist over outputs followed by Exist over inputs, constant_node = "<<z<<endl;
				#endif
			
				z /= ((double)exp2(number_of_input_variables));
				val2 += z;
			
			}
		
			//Now compute the value of nontermination in the 2nd component
		
			Cudd_Ref(tmp1 = Cudd_addExistAbstract(manager, MTBDD, outputs));
		    
		    #ifdef ddb
			sprintf (buffer, "Step-10-Shannon-entropy.dot");
			f =fopen(buffer,"w");
			out = new DdNode*[1];
			out[0] = tmp1;
			names = new char*[1];
			names[0] = (char*)"Step-3";
			Cudd_DumpDot(manager, 1 ,out ,NULL, names ,f);
			fclose(f);
			#endif
		
			Cudd_Ref(tmp1 = Cudd_addApply(manager, Cudd_addMinus, Cudd_ReadOne(manager), tmp1));
		
			#ifdef ddb
			sprintf (buffer, "Step-11-Shannon-entropy.dot");
			f =fopen(buffer,"w");
			out = new DdNode*[1];
			out[0] = tmp1;
			names = new char*[1];
			names[0] = (char*)"Step-3";
			Cudd_DumpDot(manager, 1 ,out ,NULL, names ,f);
			fclose(f);
			#endif
		
			Cudd_Ref(tmp1 = Cudd_addLogExistAbstract(manager, tmp1, inputs));
		
			if(Cudd_IsNonConstant(tmp1)==1){
				cout<<"The second computed value is not a constant. Please check the inputs."<<endl;
				cout<<"Printing tmp1...\n";
				printADD (manager, MTBDD, "MTBDD-shannonentropy_non_termination", "MTBDD", 100);
				printADD (manager, tmp1, "tmp1-shannonentropy_non_termination", "tmp1", 100);
				return -1;
			}
			else{
				double z = Cudd_V(tmp1);
			
				#ifdef db
				cout<<"(for prob program) After LogExist over outputs followed by Exist over inputs, constant_node = "<<z<<endl;
				#endif
			
				z /= ((double)exp2(number_of_input_variables));
				val2 += z;
			}
		
		}
		return (val1+val2);
	}
	else {
			
		DdNode *T0,*T1, *T2, *T3, *T4, *tmp;
		
		DdNode *add_out_of_domain;
		Cudd_Ref(add_out_of_domain = Cudd_addIthVar(manager, bdd_index_out_of_domain));
		DdNode *cmpl_out_of_domain;
		Cudd_Ref(cmpl_out_of_domain = Cudd_addCmpl(manager, add_out_of_domain));
		
		DdNode *add_out_of_domain_prime;
		Cudd_Ref(add_out_of_domain_prime = Cudd_addIthVar(manager, bdd_index_out_of_domain+2));
		DdNode *cmpl_out_of_domain_prime;
		Cudd_Ref(cmpl_out_of_domain_prime = Cudd_addCmpl(manager, add_out_of_domain_prime));
		
		Cudd_Ref(T0 = Cudd_addApply(manager, Cudd_addTimes, MTBDD, add_out_of_domain_prime));

		double num_valid_inputs = (double)(exp2(number_of_input_variables)) ;
		
		#ifdef ddb
		cout<<"num_valid_inputs = "<<num_valid_inputs<<endl;
		#endif
		
		DdNode* out_of_domain_and_prime;
		Cudd_Ref(out_of_domain_and_prime = Cudd_addApply(manager, Cudd_addTimes, add_out_of_domain, add_out_of_domain_prime));
		Cudd_Ref(tmp = Cudd_addOrAbstract(manager, T0, out_of_domain_and_prime));	
		Cudd_RecursiveDeref(manager, T0);
		Cudd_Ref(tmp = Cudd_addOrAbstract(manager, tmp, outputs));
		Cudd_Ref(tmp = Cudd_addExistAbstract(manager, tmp, inputs));
		
		if(Cudd_IsNonConstant(tmp)==1){
			cout<<"The first computed value is not a constant. Please check the inputs."<<endl;
			cout<<"Printing tmp...\n";
			printADD (manager, tmp, "MTBDD_copy-shannonentropy", "tmp", 100);
			return -100;
		}
	
		num_valid_inputs -= Cudd_V(tmp);
		Cudd_RecursiveDeref(manager, tmp);
		#ifdef ddb
		cout<<"num_valid_inputs = "<<num_valid_inputs<<endl;
		#endif
	
		// Now computing sum1
		Cudd_Ref(T1 = Cudd_addApply(manager, Cudd_addTimes, MTBDD, cmpl_out_of_domain_prime));
		Cudd_Ref(T2 = Cudd_addOrAbstract(manager, T1, out_of_domain_and_prime));
		Cudd_RecursiveDeref(manager, T1);
		Cudd_Ref(T3 = Cudd_addExistAbstract(manager, T2, inputs));
		Cudd_RecursiveDeref(manager, T2);
		Cudd_Ref(T3 = Cudd_addLogExistAbstract(manager, T3, inputs));	
		if(Cudd_IsNonConstant(T3)==1){
			cout<<"The first computed value is not a constant. Please check the inputs."<<endl;
			cout<<"Printing T3...\n";
			printADD (manager, T3, "MTBDD_copy-shannonentropy", "T3", 100);
			return -1;
		}
		double sum = Cudd_V(T3);
		#ifdef ddb
		cout<<"sum = "<<sum<<endl;
		#endif
		Cudd_RecursiveDeref(manager, T3);
		
		Cudd_Ref(T1 = Cudd_addOrAbstract(manager, MTBDD, out_of_domain_and_prime));
		Cudd_Ref(T2 = Cudd_addOrAbstract(manager, tmp, outputs));
		Cudd_RecursiveDeref(manager, T1);
		Cudd_Ref(T3 = Cudd_addCmpl(manager, T2));
		Cudd_RecursiveDeref(manager, T2);
		Cudd_Ref(T4 = Cudd_addExistAbstract(manager, T3, inputs));
		Cudd_RecursiveDeref(manager, T3);
		
		if(Cudd_IsNonConstant(T4)==1){
			cout<<"The computed value is not a constant. Please check the inputs."<<endl;
			cout<<"Printing T4...\n";
			printADD (manager, T4, "MTBDD_copy-shannonentropy", "T4", 100);
			return -100;
		}
		
		double num_non_term_inputs = Cudd_V(T4);
		#ifdef ddb
		cout<<"num_non_term_inputs = "<<num_non_term_inputs<<endl;
		#endif
		
		if(num_non_term_inputs > 0) sum += num_non_term_inputs*log2(num_non_term_inputs);
		
		return log2(num_valid_inputs) - (sum/num_valid_inputs);
	}
}
