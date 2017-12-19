#include "mql.h"

//Function to print a DdNode*
void printADD (DdManager* manager, DdNode* MTBDD, string name_of_file, string name_of_output, int number_of_input_variables, char** inputNames){
	DdNode** out = new DdNode*[1];
	out[0] = MTBDD;
	char buffer [100];
	if(inputNames==NULL){
		char** inNames = new char*[number_of_input_variables];
		for(int i=0; i<number_of_input_variables; i++){
			sprintf (buffer, "variable[%d]", i);
			inNames[i] = buffer;
		}
		char** outNames = new char*[1];
		outNames[0] = new char[name_of_output.length()+1];
		outNames[0][name_of_output.length()]=0;
		memcpy(outNames[0],name_of_output.c_str(),name_of_output.length());
		char* a = new char[name_of_file.length()+1];
		a[name_of_file.length()]=0;
		memcpy(a,name_of_file.c_str(),name_of_file.length());
		sprintf(buffer,"%s.dot",a);
		FILE* f =fopen(buffer,"w");
		Cudd_DumpDot(manager, 1 ,out ,inNames, outNames,f);
		fclose(f);
	}
	else{
		char** outNames = new char*[1];
		outNames[0] = new char[name_of_output.length()+1];
		outNames[0][name_of_output.length()]=0;
		memcpy(outNames[0],name_of_output.c_str(),name_of_output.length());
		char* a = new char[name_of_file.length()+1];
		a[name_of_file.length()]=0;
		memcpy(a,name_of_file.c_str(),name_of_file.length());
		sprintf(buffer,"%s.dot",a);
		FILE* f =fopen(buffer,"w");
		Cudd_DumpDot(manager, 1 ,out ,inputNames, outNames ,f);
		fclose(f);
	}
}
