#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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

int compara(const void* c1, const void* c2){
    
    return strncmp(((Endereco*)c1)->cep,((Endereco*)c2)->cep,8);

}

int main(int argc, char**argv){

    FILE *f, *saida;
	Endereco *e;
	long posicao, qtd, parte, qtd2;


	f = fopen("cep.dat","r");

	fseek(f,0,SEEK_END);
	posicao = ftell(f);
	qtd = posicao/sizeof(Endereco);
	parte = (qtd/8);

    int i = 1;
    rewind(f);

//__________________________[DIVIDINDO ARQUIVOS]__________________________
    printf("______________________[DIVIDIR E ORDENAR]______________________\n");

    while(i++ < 9){
        
        printf("Dividindo...\t");

        qtd2 = (i < 9)?parte:(qtd - (parte*7));

        e = (Endereco*) malloc(qtd2*sizeof(Endereco));
        
        if(!fread(e,sizeof(Endereco),qtd2,f) == qtd2){
            printf("Erro na leitura do arquivo!!!");
        }

	    qsort(e,qtd2,sizeof(Endereco),compara);
        printf("Ordenando particao %d\n",i-1);
        char fileName[200];
        sprintf(fileName,"cep_%d.dat",i-1);
        saida = fopen(fileName,"w");
	    printf("Gerando arquivo %s...\n",fileName);
        fwrite(e,sizeof(Endereco),qtd2,saida);
	    
        fclose(saida); //add condição
	    free(e);
        
    }
    i--;	
    fclose(f);        

//__________________________[INTERCALANDO ARQUIVOS]__________________________
    
    printf("______________________[CONCATENACAO]______________________\n");

    FILE *a1, *a2, *a3;
    int j = 1;
    Endereco ea1,ea2;

    while(i < 16){
        
        char fileName1[200];
        char fileName2[200];
        char fileName3[200];

        sprintf(fileName1,"cep_%d.dat",j++);
        printf("Concatenando: %s\t",fileName1);
        sprintf(fileName2,"cep_%d.dat",j++);
        printf("%s...\n",fileName2);
        sprintf(fileName3,"cep_%d.dat",i++);
        printf("Gerando: %s...\n\n",fileName3);

        a1 = fopen(fileName1,"r");
        a2 = fopen(fileName2,"r");
        a3 = fopen(fileName3,"w");

        
        fread(&ea1,sizeof(Endereco),1,a1);
	    fread(&ea2,sizeof(Endereco),1,a2);

        while(!feof(a1) && !feof(a2)){
		
            if(compara(&ea1,&ea2) < 0){

                fwrite(&ea1,sizeof(Endereco),1,a3);
                fread(&ea1,sizeof(Endereco),1,a1);

            }
            else{

                fwrite(&ea2,sizeof(Endereco),1,a3);
                fread(&ea2,sizeof(Endereco),1,a2);

            }
	    }

        while(!feof(a1)){

            fwrite(&ea1,sizeof(Endereco),1,a3);
            fread(&ea1,sizeof(Endereco),1,a1);		

        }
        while(!feof(a2)){

            fwrite(&ea2,sizeof(Endereco),1,a3);
            fread(&ea2,sizeof(Endereco),1,a2);		

        }

        fclose(a1);
	    fclose(a2);
	    fclose(a3);

    }

	return 0;
}