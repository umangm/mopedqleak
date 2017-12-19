
#include "mql.h"

bool is_smaller(int i1, int j1, int k1, int i2, int j2, int k2){
	bool is_sml = false;
	if(i1<i2) is_sml = true;
	else if(i1==i2 && j1<j2) is_sml = true;
	else if(i1==i2 && j1==j2 && k1>k2) is_sml = true;
	return is_sml;
} 


//Gauss-Seidel Implementation
probabilityMatrix processRules_pre (DdManager *manager,
								wIdent number_of_states,
								wIdent number_of_lines,
								vector<PDSRule> rules,
								int number_of_variables,
								CUDD_VALUE_TYPE tolerance)
{

	#ifdef db
	//-- debugging mode..
	cout<<"In Process rules..."<<endl;
	cout<<"number of lines = "<<number_of_lines<<endl;
	cout<<"number of states = "<<number_of_states<<endl;
	cout<<"number of variables = "<<number_of_variables<<endl<<endl;
	
	
	for(unsigned int i=0; i<rules.size(); i++){
		cout<<"Rule "<<i<<endl;
		cout<<"Current state = "<<rules[i].previous_state<<endl;
		cout<<"Next state = "<<rules[i].next_state<<endl;
		cout<<"Line Number = "<<rules[i].line_number<<endl;
		cout<<"stack = <"<<rules[i].stack.first<<","<<rules[i].stack.second<<">"<<endl;
		cout<<"nz1 = "<<rules[i].nz1<<endl;
		cout<<"nz2 = "<<rules[i].nz2<<endl;
		cout<<"nz3 = "<<rules[i].nz3<<endl;
		cout<<endl;
	}
	#endif
	

	DdNode *Zero = Cudd_addConst(manager,0);
	Cudd_Ref(Zero);
	
	int permut1[number_of_variables];	//{0,2,1} for permuting (x,x') to (x,x")
	int permut2[number_of_variables];	//{1,0,2} for permuting (x,x') to (x",x')
	//***CAUTION*** : the variable ordering should be x,x",x' .It is also a more efficient ordering than any other as discussed.
	
	//Creating the 2 permutation arrays
	
	#ifdef db
	cout<<"Creating the 2 permutation arrays"<<endl;
	#endif
	
	for(int i=0; i<number_of_variables; i++){
		if(i%3==0){
			permut1[i]=i;
			permut2[i]=i+1;
		}
		if(i%3==1){
			permut1[i]=i+1;
			permut2[i]=i-1;
		}
		if(i%3==2){
			permut1[i]=i-1;
			permut2[i]=i;
		}
	}
	
	//The variables of the form [pXq]: new_variables[p][q][X] and old_variables[p][q][X]
	probabilityMatrix new_variables (number_of_states, vector<vd> (number_of_states, vector<DdNode*> (number_of_lines,Zero)));
	probabilityMatrix old_variables (number_of_states, vector<vd> (number_of_states, vector<DdNode*> (number_of_lines,Zero)));
	
	//initialization
	
	#ifdef db
	cout<<"Initialization"<<endl;
	#endif
	
	for(wIdent i=0; i<number_of_states; i++){
		for(wIdent j=0; j<number_of_states; j++){
			for(wIdent k=0; k<number_of_lines; k++){
				Cudd_Ref(old_variables[i][j][k] = Zero);				
			}
		}
	}
	
	//Auxillary variables used to update the old_variables and new_variables.
	//In order to perform var1*var2, where var1 and var2 are ADDs, we need to permute var1 according to permut1 and var2 according to permut2
	DdNode *tmp_permute1; 	//the temporary variable that stores the add for the pre-term after permuted according to permut1 array.
	DdNode *tmp_permute2; 	//the temporary variable that stores the add for the post-term after permuted according to permut2 array.
							//tmp_permute2 also stores the permuted ADD of var3 whenever there is a operation involving var1*var2*var3. Such multiplications are performed by first multiplying var1*var2, storing the result in tmp_addend. tmp_addend is multiplied by anothe ADD (id_on_locals) which ensures that the local variables of the caller functions retain their values.
	DdNode *tmp_permute3; 	//the temporary variable for the first term. Will permute [the product of 1st two terms in a cubic expression, multiplied with id_on_locals]
	DdNode *tmp_addend; 	//the variable for addition. tmp_addend is added to new_variables each time
	//DdNode *tmp_addend_new;	//the variable that stores tmp_addend+new_variables[i][j][k].
	
	
	//The iterations commence here....
	int itr = 0;
	while(1){
	
		#ifdef db
		cout<<"Iteration #"<<itr<<endl;
		#endif
		
		//Initializing new_variables[i][j][k] to Zero before each iteration	
		#ifdef db
		cout<<"Initializing new_variables[i][j][k] to Zero before each iteration	"<<endl;
		#endif
		for(wIdent i=0; i<number_of_states; i++){
			for(wIdent j=0; j<number_of_states; j++){
				for(wIdent k=0; k<number_of_lines; k++){
					Cudd_Ref(new_variables[i][j][k] = Zero);
				}
			}
		}
		
		for(int i=0; i<number_of_states; i++){
			for(int j=0; j<number_of_states; j++){
				for(int k=number_of_lines-1; k>=0; k--){
				
					for(int r = rules.size()-1; r>=0; r--){
						
						if(rules[r].previous_state==i && rules[r].next_state==j && rules[r].line_number==k && rules[r].stack.first<0 && rules[r].stack.second<0){
							Cudd_Ref(new_variables[i][j][k] = Cudd_addApply(manager, Cudd_addPlus, new_variables[i][j][k], rules[r].relation));
						}
						
						else if(rules[r].previous_state==i && rules[r].line_number==k && rules[r].stack.first>=0 && rules[r].stack.second<0){
						
							Cudd_Ref(tmp_permute1 = Cudd_addPermute(manager, rules[r].relation, permut1));
							
							if(is_smaller(rules[r].next_state, j, rules[r].stack.first, i, j, k)){
								Cudd_Ref(tmp_permute2 = Cudd_addPermute(manager, new_variables[rules[r].next_state][j][rules[r].stack.first], permut2));
							}
							else{
								Cudd_Ref(tmp_permute2 = Cudd_addPermute(manager, old_variables[rules[r].next_state][j][rules[r].stack.first], permut2));
							}
							
							Cudd_Ref(tmp_addend = Cudd_addMatrixMultiply(manager, tmp_permute1, tmp_permute2, rules[r].cube1, rules[r].nz1));
							Cudd_RecursiveDeref(manager, tmp_permute1);
							Cudd_RecursiveDeref(manager, tmp_permute2);
						
							Cudd_Ref(new_variables[i][j][k] = Cudd_addApply(manager, Cudd_addPlus, new_variables[i][j][k], tmp_addend));
							Cudd_RecursiveDeref(manager, tmp_addend);
						}
						else if(rules[r].previous_state==i && rules[r].line_number==k && rules[r].stack.first>=0 && rules[r].stack.second>=0){
						
							Cudd_Ref(tmp_permute1 = Cudd_addPermute(manager, rules[r].relation, permut1));
							
							for(int q2 = 0; q2<number_of_states; q2++){
								if(is_smaller(rules[r].next_state, q2, rules[r].stack.first, i, j, k)){
									Cudd_Ref(tmp_permute2 = Cudd_addPermute(manager, new_variables[rules[r].next_state][q2][rules[r].stack.first], permut2));
								}
								else{
									Cudd_Ref(tmp_permute2 = Cudd_addPermute(manager, old_variables[rules[r].next_state][q2][rules[r].stack.first], permut2));	
								}
								
								Cudd_Ref(tmp_addend = Cudd_addMatrixMultiply(manager, tmp_permute1, tmp_permute2, rules[r].cube2, rules[r].nz2));
								Cudd_RecursiveDeref( manager, tmp_permute2);
								
								Cudd_Ref(tmp_permute3 = Cudd_addPermute(manager, tmp_addend, permut1));
								Cudd_RecursiveDeref(manager, tmp_addend);
								
								if(is_smaller(q2, j, rules[r].stack.second, i, j, k)){
									Cudd_Ref(tmp_permute2 = Cudd_addPermute(manager, new_variables[q2][j][rules[r].stack.second], permut2));
								}
								else{
									Cudd_Ref(tmp_permute2 = Cudd_addPermute(manager, old_variables[q2][j][rules[r].stack.second], permut2));	
								}
								
								Cudd_Ref(tmp_addend = Cudd_addMatrixMultiply(manager, tmp_permute3, tmp_permute2, rules[r].cube3, rules[r].nz3));
								Cudd_RecursiveDeref( manager, tmp_permute2);
								Cudd_RecursiveDeref( manager, tmp_permute3);
								
								Cudd_Ref(new_variables[i][j][k] = Cudd_addApply(manager, Cudd_addPlus, new_variables[i][j][k], tmp_addend));
								Cudd_RecursiveDeref(manager, tmp_addend);
							}
							Cudd_RecursiveDeref(manager, tmp_permute1);
						}
						else{
							//Not an important rule :P
						}
						
					} 
				}
			}
		}
		
		//Now checking for termination
		#ifdef db
		cout<<"Checking for termination"<<endl;
		#endif
		//match remains true only if all old_variables and all new_variables match
		bool match=true;
		for(int i=0; i<number_of_states; i++){
			for(int j=0; j<number_of_states; j++){
				for(int k=0; k<number_of_lines; k++){
					if(Cudd_EqualSupNorm(manager, old_variables[i][j][k], new_variables[i][j][k], tolerance, -1) == 0){
						match = false;
						break;
					}
				}
			}
		}
		
		if(match) {
			cout<<"Termination after "<<itr+1<<" iterations."<<endl;
			break;
		}
		
		//Changing old_variables to new_variables
		for(int i=0; i<number_of_states; i++){
			for(int j=0; j<number_of_states; j++){
				for(int k=0; k<number_of_lines; k++){
					Cudd_RecursiveDeref(manager,old_variables[i][j][k]);
					old_variables[i][j][k] = new_variables[i][j][k];
					Cudd_Ref(old_variables[i][j][k]);
				}
			}
		}
		
		itr++;
		
	}
	
	#ifdef db
	cout<<"Exiting processRules\n"<<endl;
	#endif
	
	Cudd_RecursiveDeref(manager,Zero);
	
	return new_variables;
}
