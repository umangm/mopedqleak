#include<iostream>
#include<cstdio>
using namespace std;

#define N 32
#define N_by_2 16

int main(){

	for(int i=0; i<N; i++) printf("bool S%d, O%d;\n", i, i, i);

	printf("module void main(){\n\n");

	for(int i = 0; i<N_by_2; i++){
		printf("O%d = S%d ^^ S%d;\n", i, i+16, i);
	}
	
	cout<<endl;
	
	for(int i = N_by_2; i<N; i++){
		printf("O%d = S%d ;\n", i, i);
	}
	
	cout<<endl;
	
	for(int i = N_by_2 ; i< N; i++){
		printf("O%d = O%d || O%d ;\n", i, i-16, i);
	}
	
	cout<<endl;
	
	for(int i = 0 ; i< N_by_2; i++){
		printf("O%d = O%d;\n", i,  i);
	}
	
	cout<<endl;
	
	for(int i = 0; i<N; i++){
		printf("S%d = false;\n", i);
	}
	
	cout<<endl;
	
	cout<<"}";
	
	return 0;
}
