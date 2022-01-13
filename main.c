#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void menu();
char *ler_ficheiro();
FILE *fp;
void tabela();
char file[1000];
char conteudo[1000][1000][5];
int soma();
int linhas;
int colunas;

int main() {
    menu();
    return 0;
}
//***************************************************MENU***************************************************************
void menu(){
    int menu;
    int operacoes;
    opcao: printf("\nDigite:\n1-> Ler o ficheiro\n2-> Ver o ficheiro\n3-> Aceder ao menu de operacoes\n9-> Sair do programa\n");
    scanf("%d", &menu);

    switch(menu) {
        case 1: //ler ficheiro
            ler_ficheiro();
            goto opcao;
        case 2: //mostrar tabela
            tabela();
            goto opcao;
        case 3:
        operacoes: printf("\nDigite:\n1-> Realizar a soma\n9-> Voltar ao menu principal\n");
            scanf("%d", &operacoes);
            switch(operacoes) {
                case (1):
                    soma();
                    goto operacoes;
                case (9):
                    goto opcao;
                default:
                    printf("Selecione uma opcao disponivel.\n");
                    goto operacoes;
            }
        case (9):
            break;
        default:
            printf("Selecione uma opcao disponivel.\n");
            goto opcao;
    }
}
/**************************************Ler ficheiro******************* C:\Users\mcrib\OneDrive\Documentos\example.csv */
char *ler_ficheiro() {
    char linha[300];
    char *token;
    printf("Para escolher o ficheiro escreva o diretorio do ficheiro:\n");
    fflush(stdin);                    //o enter fica na memoria entao isto "apaga a memoria" para fazer o if direito
    gets(file);
    fp = fopen(file, "r");
    if (fp != NULL) {
        fgets (linha, 300, fp);         //ignorar titulo
        int i=0;        //linhas
        int j= 0;       //colunas
        //Preencher matriz conteudo
        while(fgets (linha, 300, fp)) {       //percorrer os registos
            j= 0;
            token = strtok(linha, ";");
            while( token != NULL ) {                //percorrer os valores
                strcpy(conteudo[i][j], token);
                token = strtok(NULL, ";");
                j++;
            }
            i++;
        }
        linhas = i;
        colunas = j;
        /*
        //IMPRIMIR a Matriz
        int row, columns;
        printf("\n");
        for (row=0; row<i; row++){
            for(columns=0; columns<j; columns++){
                printf("| %s", conteudo[row][columns]);
            }
            printf("|\n");
        }
         */
        printf("\nO Ficheiro tem %d Linhas(sem contar com os Titulos) e %d Colunas\n", i, j);
        printf("Ficheiro\t%s\t lido com sucesso!\n",file);
        fclose(fp);
    } else {
        printf("\nErro na abertura do ficheiro!\n");
    }
    return file;
}
/******************************************* Mostrar Tabela ***********************************************************/
void tabela(){
    int k=0;
    int i;
    char buffer[80];
    //abrir ficheiro
    fp = fopen(file, "r");
    //Verificar se o ficheiro n esta vazio
    if(fp == NULL) {
        printf("\nErro na abertura do ficheiro!\n");
    }
    printf("Quantas linhas que perntende imprimir?\n");
    scanf("%d", &k);
    for(i=0;i<k && fgets(buffer, 300, fp) != NULL;i++) {
        //printa linha a linha do ficheiro
        //while (fgets(buffer, 300, fp) != NULL) {
            puts(buffer);
       // }
    }
    fclose(fp);
}

int soma(){
    int i = 0;
    int k = 0;
    int resultado = 0;
    double fresultado=0;
    printf("Qual a colunas que pertende somar?\n");
    scanf("%d", &k);
    if(k<=colunas) {
        for (i = 0; i < linhas; i++) {
            fresultado = (double) resultado + atoi(conteudo[i][k-1]);
        }
        printf("O resultado final e:%f\n", fresultado);
    }
    else{
        printf("A coluna que digitou nao existe.\n");
    }

    return 0;
}