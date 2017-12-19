/*****************************************************************************/

#include <iostream>
#include "mql.h"

set<wIdent> line_set;

void init_line_set(intPds* ipds){
    intModule* m = ipds->modules;
	while(m){
		wSet* v = m->labels;
		while(v){
			
			line_set.insert(v->ident);
			v = v->next;
		}
		m = m->next;
	}
}
			
bool label_exists(wIdent label){
    return (line_set.find(label)!=line_set.end());
}

int main (int argc, char **argv){

	struct timeval tim;  
    gettimeofday(&tim, NULL);  
    double t1=tim.tv_sec*1000+(tim.tv_usec/1000.0);  
    
	if(argc<3){
		printf("Invalid command: Insufficient arguments !\n");
		return 1;
	}
	else{
		if(!(strcmp(argv[1],"-min")==0 || strcmp(argv[1],"-shannon")==0 ) ) {
			printf("Invalid command: Unrecognized option %s\n", argv[1]);
			return 1;
		}
		else{
			intPds *ipds;
			wIdentInit();
			
		    #ifdef db
		    cout<<"Begin parsing...\n";
		    #endif

		    ipds = irReadPds(argv[2]);

		    #ifdef db
		    cout<<"Begin probabilistic Analysis...\n";
		    #endif
			computed_pds res = wrap_and_compute(ipds, false, PRE, argv[1][1]);
			
			#ifdef db
			char buffer [50];
			char command[50];
			FILE *f;
			for(int i=0; i<res.number_of_states; i++){
				for(int j=0; j<res.number_of_states; j++){
					DdNode** out = new DdNode*[res.number_of_lines];
					for(int s=0; s<res.number_of_lines; s++){
						out[s] = res.pM[i][j][s];
					}
					sprintf (buffer, "result[%d][%d].dot", i,j);
					f =fopen(buffer,"w");
					Cudd_DumpDot(ipds->mgr, res.number_of_lines ,out ,NULL, res.lineNames ,f);
					fclose(f);
					sprintf (command, "dot -Tpdf result[%d][%d].dot >result[%d][%d].pdf",i,j,i,j);
					system(command);
				}
			}

			f =fopen("main.dot","w");
			DdNode** main = new DdNode*[1];
			if(res.number_of_states>1) main[0] = res.pM[res.state_q][res.state_q_labels][res.main_line];
			else main[0] = res.pM[res.state_q][res.state_q][res.main_line];
			char** main_name = new char*[1];
			main_name[0] = new char[strlen("main"+1)];
			strcpy(main_name[0], "main");
			Cudd_DumpDot(ipds->mgr, 1 ,main ,NULL, main_name ,f);
			fclose(f);
			system("dot -Tpdf main.dot >main.pdf");
			#endif
				
			
		}
	}
	
	gettimeofday(&tim, NULL);  
    double t2=tim.tv_sec*1000+(tim.tv_usec/1000.0);  
    printf("%.6lf milliseconds elapsed\n", t2-t1); 
	
	return 0;
}
