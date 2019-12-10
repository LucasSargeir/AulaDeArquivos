#include <stdio.h>
#include <string.h>

int main(int argc, char** argv)
{
	char linha[2048];
	char nis[15];
	int n = 0;
	int coluna = 0;
	long posicao;
	char* campo;
	FILE *f = fopen("bolsa.csv", "r");
	fgets(linha, 2048, f);
	posicao = ftell(f);
	fgets(linha, 2048, f);
	while(!feof(f)) 
	{
		coluna = 0;
		campo = strtok(linha,"\t");
		while(campo)
		{
			if(coluna == 7)
			{
				strcpy(nis, campo);
				printf("NIS => %s esta em %ld\n", nis, posicao);
			}
			coluna++;
			// printf("%s\n",campo);
			campo = strtok(NULL,"\t");
		}
		printf("---------------------------------------\n");
		posicao = ftell(f);
		fgets(linha, 2048, f);
		n++;
		if(n == 10)
		{
			break;
		}
	}
	fclose(f);
	return 0;
}
