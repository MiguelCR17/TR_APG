#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void menu();
char *ler_ficheiro();
FILE *fp;
//void tabela(char *file);
char file[200];
char conteudo[1000][1000][5];

int main() {
    menu();
    //ler_ficheiro();
    return 0;
}
//***************************************************MENU***************************************************************
void menu(){
    int menu;
    opcao:printf("\nDigite 1 para ler o ficheiro, 2 para ver a tabela:\n");
    scanf("%d", &menu);

    switch(menu) {
        case 1: //ler ficheiro
            ler_ficheiro();
            goto opcao;
            break;
        case 2: //mostrar tabela
            //tabela(file);
            goto opcao;
            break;
        case 3:
            break;
        default:
            printf("Selecione uma opcao disponivel em cima.\n");
            goto opcao;
            break;
    }
}
//**************************************Ler ficheiro********************* C:\Users\mcrib\OneDrive\Documentos\example.csv
char *ler_ficheiro() {
    char linha[300];
    char *token;
    printf("Para escolher o ficheiro escreva o diretorio do ficheiro:\n");
    fflush(stdin);                    //o enter fica na memoria entao isto "apaga a memoria" para fazer o if direito
    gets(file);
    fp = fopen(file, "r");
    if (fp != NULL) {
        fgets (linha, 80, fp);         //ignorar titulo
        int i=0;
        int j= 0;
        //Preencher matriz conteudo
        while(fgets (linha, 80, fp)) {       //percorrer os registos
            j= 0;
            token = strtok(linha, ";");
            while( token != NULL ) {                //percorrer os valores
                strcpy(conteudo[i][j], token);
                token = strtok(NULL, ";");
                j++;
            }
            i++;
        }
        //IMPRIMIR
        int row, columns,length;
        printf("\n");
        for (row=0; row<i; row++){
            for(columns=0; columns<j; columns++){
                printf("| %s", conteudo[row][columns]);
            }
            printf("|\n");
        }
        printf("Ficheiro\t%s\t lido com sucesso!\n",file);
        fclose(fp);
    } else {
        printf("\nErro na abertura do ficheiro!\n");
    }
    return file;
}
/*
void tabela(char *file){
    char buffer[80];
    //abrir ficheiro
    fp = fopen(file, "r");
    if(fp == NULL) {
        printf("\nErro na abertura do ficheiro!\n");
    }
    int i=0;    //i conta o nº de linhas

    while( fgets (buffer, 80, fp)!=NULL ) {

        puts(buffer);
        i++;
    }
    printf("\nO Ficheiro contem %d colunas.\n", i);
    fclose(fp);
*/
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

} */