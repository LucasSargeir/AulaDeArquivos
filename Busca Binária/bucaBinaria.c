#include <stdio.h>
#include <string.h>

typedef struct _Endereco Endereco;

struct _Endereco
{
	char logradouro[72];
	char bairro[72];
	char cidade[72];
	char uf[72];
	char sigla[2];
	char cep[8];
	char lixo[2];
};

/*
	SEEK_SET = Posição inicial	
	SEEK_CUR = Posição atual
	SEEK_END = Posição final

*/


int buscaBinaria(FILE *f, char *bCep,long ini,long fim,int cont){  // Retorna o numero de iterações (cont)

	Endereco e;
	long meio;
	rewind(f);												// Volta ao começo do arquivo
	if(ini <= fim){

		int qt;	// Testa se foi possivel ler

		cont++;

		meio = (ini+fim)/2;

		//printf("\nINICIO: %ld\tMEIO: %ld\tFINAL: %ld\n",ini,meio,fim);

		fseek(f,(meio*sizeof(Endereco)),SEEK_SET);

		qt = fread(&e, sizeof(Endereco), 1, f);
		//printf("\n\nLogradouro: %.72s\nBairro: %.72s\nCidade: %.72s\nUF: %.72s\nSigla: %.2s\nCEP: %.8s\n",e.logradouro,e.bairro,e.cidade,e.uf,e.sigla,e.cep);

		if(strncmp(bCep,e.cep,8) == 0){
			printf("\nLogradouro: %.72s\nBairro: %.72s\nCidade: %.72s\nUF: %.72s\nSigla: %.2s\nCEP: %.8s\n\n",e.logradouro,e.bairro,e.cidade,e.uf,e.sigla,e.cep);
			return cont;
		}
		else{
			if(strncmp(bCep,e.cep,8) > 0){
				buscaBinaria(f,bCep,meio+1,fim,cont);
			}
			else if(strncmp(bCep,e.cep,8) < 0){
				buscaBinaria(f,bCep,ini,meio-1,cont);
			}

		}

	}
	else{
		
		printf("Não foi possivel encontrar o CEP\n");
		return cont;

	}

}

int buscaNaoBinaria(FILE *f, char *bCep,int cont){

	rewind(f);												// Volta ao começo do arquivo
	Endereco e;
	int qt;		// (qt) Armazena quantos foram lidos
	qt = fread(&e,sizeof(Endereco),1,f);

	while(qt > 0){

		cont++;
		if(strncmp(bCep,e.cep,8) == 0){
			printf("\n\nLogradouro: %.72s\nBairro: %.72s\nCidade: %.72s\nUF: %.72s\nSigla: %.2s\nCEP: %.8s\n\n",e.logradouro,e.bairro,e.cidade,e.uf,e.sigla,e.cep);
			break;

		}
	
		qt = fread(&e,sizeof(Endereco),1,f);		
	
	}

	return cont;

}

int main(int argc, char**argv){
	
	FILE *f;								
	long posicao, primeiro, ultimo, meio;
	char bCep[8];

	if(argc != 2){											// Verifica passagem de parâmetro
		printf("Entre com o CEP que deseja pesquisar:\n");
		int i = 0;
		while(i < 8){
			bCep[i++] = getchar();
		}
	}
	else{

		strncpy(bCep,argv[1],8);

	}

	f = fopen("cep_ordenado.dat","r");						// Abertura de arquivo


	fseek(f,0,SEEK_END);									// Navega até o final do arquivo
	posicao = ftell(f);										// Descobre o tamanho do arquivo
	


	printf("________________________[INFO]________________________\n\n");
	printf("Tamanho do Arquivo: %ldBytes\n", posicao);
	printf("Tamanho do Registro: %ld\n", sizeof(Endereco));
	printf("Tamanho do Arquivo em Registros: %ld\n", posicao/sizeof(Endereco));
	
	primeiro = 0;
	ultimo = (posicao/sizeof(Endereco))-1;

	
	printf("\n___________________[BUSCA BINÁRIA]____________________\n\n");
	printf("Numero de iterações: %d\n",buscaBinaria(f, bCep,primeiro, ultimo,0));
	

	printf("\n_________________[BUSCA NÃO BINÁRIA]__________________\n\n");
	printf("Numero de iterações: %d\n",buscaNaoBinaria(f, bCep,0));
	printf("______________________________________________________\n\n");

	return 0;
}
