#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#include <map>
#include <set>
#include <sys/time.h> 
#include "cudd.h" 

using namespace std;

#define number_iterations 50

extern "C"{
	#include "../parse/ir.h"
	#include "../parse/wpdsInt.h"
	#include "../parse/int.h"
}

extern int bdd_index_out_of_domain;

/********************************************************************************************
PDSRule:
	<previous_state,line_number> ⇒⇒relation→⇒ <next_state,(stack.first,stack.second)>
********************************************************************************************/
struct PDSRule{
	wIdent previous_state;
	wIdent line_number;
	DdNode *relation;
	wIdent next_state;
	pair <wIdent,wIdent> stack;		//<x,-1> for no change in stack ht, <x,y> for increase in stack ht by 1, <-1,-1> for a pop  ; x,y>=0
	DdNode** cube1;					//Represents the variables to be abstracted away in matrix-multiply operation of sequential statements. NULL if stack = <-1,-1>
	int nz1;						//0 if stack = <-1,-1> or when cube1 = ONE
	DdNode** cube2;					//Represents the variables to be abstracted away in 1st matrix-multiply operation of function call statement. NULL if stack = <x,-1>, x is any integer.
	int nz2;						//0 if stack = <x,-1>, x is an integer or when cube2 = ONE.
	DdNode** cube3;					//Represents the variables to be abstracted away in 2nd matrix-multiply operation of function call statement. NULL if stack = <x,-1>, x is any integer.
	int nz3;						//0 if stack = <x,-1>, x is an integer or when cube3 = ONE
	DdNode* cube_locals;
	bool line_is_first_line_of_module;
	
	PDSRule(){
		previous_state = -1;
		line_number = -1;
		relation = NULL;
		next_state = -1;
		stack = make_pair(-1,-1);
		cube1 = NULL;
		nz1 = 0;
		cube2 = NULL;
		nz2 = 0;
		cube3 = NULL;
		nz3 = 0;
		cube_locals = NULL;
		line_is_first_line_of_module = false;
	}
};

typedef vector<DdNode*> vd;
typedef vector<vd> vvd;
typedef vector<vvd> probabilityMatrix;

//A wrapper struct that includes the computed probabilities as well as the information related to the PDS (might be needed for printing the output on stdout).
struct computed_pds{
	probabilityMatrix pM;
	wIdent number_of_lines;
	wIdent number_of_states;
	char** lineNames;
	wIdent main_line;
	int state_q;	//Mapping of wIdentCreate("q") in [0, num_states]
	int state_q_labels;
	
	computed_pds(){
		//pM = NULL;
		number_of_lines = 0;
		number_of_states = 0;
		lineNames = NULL;
		main_line = -1;
		state_q = -1;	//Mapping of wIdentCreate("q") in [0, num_states]
		state_q_labels = -1;
	}
};

enum analysis_mode {PRE, POST};

/********************************************************************************************
	Input: A pair of (number of lines "number_of_lines", vector of PDSRule(s) "vec_PDSRules")
	Output: Vector of MTBDDs "final_variables"
********************************************************************************************/
probabilityMatrix processRules_pre (DdManager *manager,
								wIdent number_of_states,
								wIdent number_of_lines,
								vector<PDSRule> rules,
								int number_of_variables,
								CUDD_VALUE_TYPE tolerance);
								
struct probabilityMatrix_post{
	probabilityMatrix pM;
	DdNode* ret;
	probabilityMatrix_post(){}
	probabilityMatrix_post(probabilityMatrix pM1, DdNode* ret1){
		pM = pM1;
		Cudd_Ref(ret = ret1);
	}
	probabilityMatrix_post(const probabilityMatrix_post& p){
		pM = p.pM;
		Cudd_Ref(ret = p.ret);
	}
};
								
//given a vector "given_vector", this function sorts it to give another vector.
vector<wIdent> make_continuous(vector<wIdent> given_vector);

//Given a vector "vec" and a value "val", it gves the index (starting from 0) of "val" in "vec". Returns -1 if "val" not found.
wIdent lookup(vector<wIdent> vec, wIdent value);

//The wrapper function that takes in a intpds* and forms the rules so as to make it usable for the function processRules. Returns the computed probabilities alongwith the number of lines, number of states and the names of the lines.
computed_pds wrap_and_compute(intPds* PDS, bool reachAnalysis, analysis_mode, char entropy);


void set_module_offsets_sizes(intPds* PDS);

void printADD (DdManager* manager, DdNode* MTBDD, string name_of_file, string name_of_output, int number_of_input_variables, char** inputNames = NULL);

//Function for calculation of min-entropy for a given DdNode*. The Ddnode* is supposed to be comprised of 2 and only 2 kind of variables: 1. the inputs, 2. the outputs
double minEntropy(
	DdManager* manager,
	DdNode* MTBDD,
	DdNode* inputs,
	int number_of_input_variables,
	DdNode* outputs,
	int number_of_output_variables,
	int prob_program
	);
	
//Function for calculation of Shannon-entropy for a given DdNode*. The Ddnode* is supposed to be comprised of 2 and only 2 kind of variables: 1. the inputs, 2. the outputs
double shannonEntropy(
	DdManager* manager,
	DdNode* MTBDD,
	DdNode* inputs,
	int number_of_input_variables,
	DdNode* outputs,
	int number_of_output_variables,
	int prob_program
	);
	
	
int num_locals(intModule* module);
map<wIdent, intModule*> map_lines_to_modules(intPds* PDS);

enum {
	IR_BOOL, IR_INT, IR_SGNINT/*, IR_FLOAT*/, IR_ENUM, IR_STRUCT, IR_VOID
};

