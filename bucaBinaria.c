/*#include <stdio.h>
#include <string.h>

typedef struct _Endereco Endereco;

struct _Endereco{

	char logradouro[72];
	char bairro[72];
	char cidade[72];
	char uf[72];
	char sigla[2];
	char cep[8];
	char lixo[2];

};

int main(int argc, char**argv){

	FILE *f;
	Endereco e;
	int qt;
	int c;

	if(argc != 2){

		fprintf(stderr, "USO: %s [CEP]", argv[0]);
		return 1;

	}

    printf("CEP utilizado: %s\n", argv[1]);

	c = 0;
	printf("Tamanho da Estrutura: %ld\n\n", sizeof(Endereco));
	
	f = fopen("cep_ordenado.dat","r");
	qt = fread(&e,sizeof(Endereco),1,f);

	while(qt > 0){

		c++;
		
		if(strncmp(argv[1],e.cep,8)==0){

			printf("%.72s\n%.72s\n%.72s\n%.72s\n%.2s\n%.8s\n",e.logradouro,e.bairro,e.cidade,e.uf,e.sigla,e.cep);
			break;

		}
	
		qt = fread(&e,sizeof(Endereco),1,f);		
	
	}

	printf("Total Lido: %d\n", c);
	fclose(f);
}*/

#include <stdio.h>

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

int main(int argc, char**argv)
{
	FILE *f;
	Endereco e;
	int qt;
	long posicao, primeiro, ultimo, meio;

	if(argc != 2)
	{
		fprintf(stderr, "USO: %s [CEP]", argv[0]);
		return 1;
	}
	f = fopen("cep_ordenado.dat","r");
	fseek(f,0,SEEK_END);
	posicao = ftell(f);
	rewind(f);
	printf("Tamanho do Arquivo: %ld\n", posicao);
	printf("Tamanho do Registro: %ld\n", sizeof(Endereco));
	printf("Tamanho do Arquivo em Registros: %ld\n", posicao/sizeof(Endereco));
	primeiro = 0;
	ultimo = (posicao/sizeof(Endereco))-1;
	meio = (primeiro+ultimo)/2;

	rewind(f);

	return 0;
}

