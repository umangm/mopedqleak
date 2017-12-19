#include<iostream>
#include<cstdio>
using namespace std;

#define N 32
#define N_by_2 16

int main(){

	for(int i=0; i<N; i++) printf("bool S%d, O%d, X%d;\n", i, i, i);

	printf("module void main(){\nbool le;\nbool done;\n");

	for(int i = 0; i<N; i++){
		printf("O%d = false;\n", i);
	}
	
	cout<<endl;
	
	for(int i = N-1; i>=N_by_2; i--){
		for(int j = 0; j<N; j++){
			if(j==i) printf("X%d = true;\n", j);
			else printf("X%d = O%d;\n", j, j);
		}
		
		printf("\nle = true;\ndone = false;\n\n");
		
		for(int j = N-1; j>=0; j--){
			printf("if\n::\t!done && !X%d && S%d -> done = true ;\n::\telse ->\n\tif\n\t::\t!done && X%d && !S%d -> done = true; le = false;\n\t::\telse -> skip;\n\tfi\nfi\n\n", j, j, j,j);
		}
		
		
		printf("if\n::\t le -> O%d = true;\n", i);
		printf("::\telse -> skip;\nfi\n\n\n");
	}
	
	for(int i = 0; i<N; i++){
		printf("S%d = false;\n", i);
	}
	
	cout<<endl;
	
	for(int i = 0; i<N; i++){
		printf("X%d = false;\n", i);
	}
	
	cout<<"}";
	
	return 0;
}
