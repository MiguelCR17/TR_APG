#include <stdlib.h>
#include <stdio.h>

void menu();
void ler_ficheiro();
FILE *fp;
void tabela();

int main() {
    menu();
    //ler_ficheiro();
    return 0;
}
//***************************************************MENU***************************************************************
void menu(){
    char menu;
    printf("Digite 1 para ler o ficheiro, 2 para ver a tabela:\n");
    scanf("%d", &menu);

    switch(menu) {
        case 1: //ler ficheiro
            ler_ficheiro();
            break;
        case 2: //mostrar tabela
            tabela();
            break;
    }
}
//**************************************Ler ficheiro********************* C:\Users\mcrib\OneDrive\Documentos\example.csv
void ler_ficheiro() {
    char file[200];
    char volta;
    printf("Para escolher o ficheiro escreva o diretorio do ficheiro:\n");
    fflush(stdin);                    //o entar fica na memoria entao isto "apaga a memoria" para fazer o if direito
    gets(file);
    fp = fopen(file, "r");
        if (fp != NULL) {
            printf("Ficheiro lido com sucesso!\n");
            while (volta != 1) {
                printf("\nDeseja voltar para o menu? Digite '1'\n");
                scanf("%d", &volta);
                if (volta == 1) {
                    menu();
                }
            }
            fclose(fp);
        } else {
            printf("\nErro na abertura do ficheiro!\n");
        }
}

void tabela(){
    while (!feof(fp)) {
        printf("%c", fgetc(fp));                                           //printf("%c", fgetc(fp));
    }
}