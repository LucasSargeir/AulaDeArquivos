#include<iostream>
using namespace std;

int main(int argc, char** argv){

	char *nome;
	int numBytes = 0;
	int numLinhas = 1;

	if( argc > 2 ){
		
		cout<<"Erro\nNúmero de parametros errado!\n";
		return 1;

	}
	if( argc ==  1 ){

		cout<<"Entre com o nome do arquivo: ";
		nome = new char(100);
		cin>>nome;

	}
	else{
		nome = argv[1];
	}

	FILE *entrada = fopen(nome,"r");
	
	if(entrada){
		char c = fgetc(entrada);
		
		while( c != EOF ){
	
			numBytes++;
			if( c == '\n' ){
				numLinhas++;
			}
			c = fgetc(entrada);
	
		}
	}
	else{
		
		cout<<"Nao foi possivel abrir o arquivo";

	}

	cout<<"\nNumero de linhas: "<<numLinhas<<"\nNumero de Bytes: "<<numBytes<<"\n";

	fclose(entrada);
	return 0;
}
