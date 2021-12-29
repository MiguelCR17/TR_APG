#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void menu();
char *ler_ficheiro();
FILE *fp;
void tabela(char *file);
char file[200];

int main() {
    menu();
    //ler_ficheiro();
    return 0;
}
//***************************************************MENU***************************************************************
void menu(){
    char menu;
    opcao:printf("Digite 1 para ler o ficheiro, 2 para ver a tabela:\n");
    scanf("%d", &menu);

    switch(menu) {
        case 1: //ler ficheiro
            ler_ficheiro();
            goto opcao;
        case 2: //mostrar tabela
            tabela(file);
            goto opcao;
    }
}
//**************************************Ler ficheiro********************* C:\Users\mcrib\OneDrive\Documentos\example.csv
char *ler_ficheiro() {
    printf("Para escolher o ficheiro escreva o diretorio do ficheiro:\n");
    fflush(stdin);                    //o entar fica na memoria entao isto "apaga a memoria" para fazer o if direito
    gets(file);
    printf("%s\n",file);
    fp = fopen(file, "r");
    if (fp != NULL) {
        printf("Ficheiro lido com sucesso!\n");
        fclose(fp);
    } else {
        printf("\nErro na abertura do ficheiro!\n");
    }
return file;
}

void tabela(char *file){
    char buffer[80];
    //abrir ficheiro
    printf("Ficheiro %s lido com sucesso!\n",file);

    fp = fopen(file, "r");

    if(fp == NULL) {
        printf("\nErro na abertura do ficheiro!\n");
    }
    int i=0;

    while( fgets (buffer, 60, fp)!=NULL ) {
        /* writing content to stdout */
        puts(buffer);
        i++;
    }
    printf("%d", i);
    fclose(fp);

    //ler a 1º linha
    //ler 1º coluna
    //fechar ficheiro
    //imprimir












/*
    while (!feof(fp)) {
       // printf("%c", fgetc(fp));                                           //printf("%c", fgetc(fp));
        char token = strtok(buffer, ";");
        while (token) {
            // Just printing each integer here but handle as needed
            printf("%s\n", token);

            token = strtok(NULL, ";");
        }
    }
    */
}