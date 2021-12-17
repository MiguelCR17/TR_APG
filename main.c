#include <stdlib.h>
#include <stdio.h>

void menu();
void ler_ficheiro();
void mostrar_tabela();


int main() {
    menu();
    //ler_ficheiro();
    return 0;
}
//***************************************************MENU***************************************************************
void menu(){
    char menu;
    printf("Digite 1 para ler o ficheiro:\n");
    scanf("%d", &menu);

    switch(menu) {
        case 1: //ler ficheiro
            ler_ficheiro();
            break;

        case 2: //ver tabela
            mostrar_tabela();
            break;
    }
}
//**************************************Ler ficheiro********************* C:\Users\mcrib\OneDrive\Documentos\example.csv
void ler_ficheiro() {
        char file[200];
        char volta;
        printf("\nPara escolher o ficheiro escreva o diretorio do ficheiro:\n");
        fflush(stdin);//o entar fica na memoria entao isto "apaga a memoria" para fazer o if direito
        gets(file);
        FILE *fp = fopen(file, "r");
        if (fp != NULL) {
            while (!feof(fp)) {
                printf("%c", fgetc(fp));              //printf("%c", fgetc(fp));
            }

                printf("\n Deseja voltar para o menu? Digite 'B'\n");
                scanf("%d", &volta);
            while(volta != 'V') {
                if(volta == 'V'){
                    menu();
                }
            }
            fclose(fp);
        }
        else {
            printf("\nErro na abertura do ficheiro!\n");
        }


}

void mostrar_tabela(){

}