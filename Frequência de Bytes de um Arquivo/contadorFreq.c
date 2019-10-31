#include<stdio.h>
#include<string.h>

int main(int argc, char **argv){

    char nomeArq [200]; 
    int fq[256];  // vetor de frequencia na qual aparecem os caracteres
    int c; 
    FILE *f;

    if(argc > 1){  // entrando o nome do arquivo por comando de linha
        strcpy(nomeArq, argv[1]);
    }else{ // nao entrando o nome do arquivo por comando de linha
        printf("Entre com o nome do arquivo: "); 
        scanf("%s", nomeArq); 
    } 

    f = fopen(nomeArq, "r"); 

    for(int i = 0; i < 256; i++){
        fq[i] = 0; 
    }

    c = fgetc(f); 

    while(fgetc(f) != EOF){
        fq[c]++; 
        c = fgetc(f); 
    }

    for(int i = 0; i < 256; i++){
        //printf("%i\t%d\n", i, fq[i]); // imprimir numeracao
        printf("%c\t%d\n", i, fq[i]);   // imprimir os caracteres correspondentes as posicoes
    }

    return 0; 
    
}
