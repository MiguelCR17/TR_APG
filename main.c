#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <time.h>

void menu();
void historico();
char *ler_ficheiro();
FILE *fp;
FILE *history;
void tabela();
void fic();
char file[1000];
char conteudo[1000][100][20];
int soma();
int linhas;
int colunas;
int media();
void dp();
void maxmin();
void mediana();
void quartis();
char* printTime();

int main() {
    menu();
    return 0;

}
//***************************************************MENU***************************************************************
void menu(){
    int menu;
    int tf;
    int operacoes;
    opcao: printf("\nDigite:\n1-> Ler o ficheiro\n2-> Ver tabela / ficheiro\n3-> Aceder ao menu de operacoes\n9-> Sair do programa\n");
    scanf("%d", &menu);

    switch(menu) {
        case 1: //ler ficheiro
        historico();
        ler_ficheiro();
            goto opcao;
        case 2: //mostrar tabela
        tf:printf("1-> Ver tabela\n2-> Ver ficheiro\n9-> Voltar para o menu principal\n");
        scanf("%d", &tf);
            switch(tf) {
                case (1):
                    tabela();
                    goto tf;
                case (2):
                    fic();
                    goto tf;
                case (9):
                    goto opcao;
                default:
                    printf("Selecione uma opcao disponivel.\n");
                    goto tf;
            }
        case 3:
        operacoes: printf("\nDigite:\n1-> Realizar a soma\n2-> Calcular a media\n3-> Calcular o desvio padrao\n4-> Saber o maximo e minimo\n5-> Saber a mediana\n6-> Calcular Q1 e Q3\n9-> Voltar ao menu principal\n");
            scanf("%d", &operacoes);
            switch(operacoes) {
                case (1):
                    soma();
                    goto operacoes;
                case (2):
                    media();
                    goto operacoes;
                case (3):
                    dp();
                    goto operacoes;
                case (4):
                    maxmin();
                    goto operacoes;
                case (5):
                    mediana();
                    goto operacoes;
                case (6):
                    quartis();
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
        for (row=0; row<linhas; row++){
            for(columns=0; columns<colunas; columns++){
                printf("|%s", conteudo[row][columns]);
            }
            printf("|\n");
        }
*/
        printf("\nO Ficheiro tem %d Linhas(sem contar com os Titulos) e %d Colunas\n", linhas, colunas);
        printf("Ficheiro\t%s\t lido com sucesso!\n",file);
        fclose(fp);
    } else {
        printf("\nErro na abertura do ficheiro!\n");
    }
    return file;
}
/******************************************* Mostrar Tabela ***********************************************************/
void tabela(){
    //IMPRIMIR a Matriz
    int row, columns;
    printf("\n");
    for (row=0; row<linhas; row++){
        for(columns=0; columns<colunas; columns++){
            printf("|%s", conteudo[row][columns]);
        }
        printf("|\n");
    }
}

/**********************TIME****************/

char* printTime(){

    time_t now = time(NULL) ;
    struct tm tm_now ;
    //localtime_r(&now, &tm_now) ;
    char buff[100] ;
    strftime(buff, sizeof(buff), "%Y-%m-%d %H:%M", &tm_now) ;
    printf("'%s'\n", buff) ;

    return 0;
}


/******************************************* Mostrar Ficheiro ***********************************************************/
void fic(){
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

/********************************* Subestituir "," por "." para poder usar fun????es ************************************/
char* replace_char(char* str, char find, char replace){
    char *current_pos = strchr(str,find);
    while (current_pos) {
        *current_pos = replace;
        current_pos = strchr(current_pos,find);
    }
    return str;
}

/********************************* Remover os espa??os nos numeros para poder fazer as contas **************************/
char* remover_espacos_strings(char* str){
    static char str1[99];
    int j, k;

    // Putting string into another
    // string variable after
    // removing leading white spaces
    for (j = 0, k = 0 ; str[j] != '\0'; j++, k++) {
        if(str[j]==' ') {
            k--;
        }
        else{
            str1[k] = str[j];
        }
    }
    str1[k] = '\0';

    return str1;
}
/***************************************************** SOMA ***********************************************************/
int soma(){
    int i;
    int k = 0;
    float fresultado=0.0;
    printf("Qual a coluna que pertende somar?\n");
    scanf("%d", &k);
    if(k<=colunas) {
        for (i = 0; i < linhas; i++) {

            strcpy(conteudo[i][k - 1],remover_espacos_strings(conteudo[i][k-1]));
            if (strstr(conteudo[i][k - 1], ",")) {
                strcpy(conteudo[i][k - 1], replace_char(conteudo[i][k - 1], ',', '.'));
            }
            else strcat(conteudo[i][k - 1],".0");
            fresultado += atof(conteudo[i][k - 1]);
        }
        fprintf(history, "O resultado final: %f\n", fresultado);
        printf("O resultado final: %f\n", fresultado);
        //fprintf(history, printTime());

    }
    else{
        printf("A coluna que digitou nao existe.\n");
    }
    return 0;
}
/**************************************************** Media ***********************************************************/
int media(){
    int i;
    int k = 0;
    float fresultado=0.0;
    printf("Qual a coluna que pertende calcular a media?\n");
    scanf("%d", &k);
    if(k<=colunas) {
        for (i = 0; i < linhas; i++) {

            strcpy(conteudo[i][k - 1],remover_espacos_strings(conteudo[i][k-1]));
            if (strstr(conteudo[i][k - 1], ",")) {
                strcpy(conteudo[i][k - 1], replace_char(conteudo[i][k - 1], ',', '.'));
            }
            else strcat(conteudo[i][k - 1],".0");
            fresultado += atof(conteudo[i][k - 1]);
        }
        fresultado/=linhas;
        fprintf(history, "O resultado final: %f\n", fresultado);
        printf("O resultado final: %f\n", fresultado);
    }
    else{
        printf("A coluna que digitou nao existe.\n");
    }
    return 0;
}
/*********************************************** Desvio Padrao ********************************************************/
void dp(){
    int i;
    int k = 0;
    float media=0.0;
    float sum=0.0;
    float fresultado;
    printf("Qual a coluna que pertende calcular o desvio padrao?\n");
    scanf("%d", &k);
    if(k<=colunas) {
        for (i = 0; i < linhas; i++) {
            strcpy(conteudo[i][k - 1],remover_espacos_strings(conteudo[i][k-1]));
            if (strstr(conteudo[i][k - 1], ",")) {
                strcpy(conteudo[i][k - 1], replace_char(conteudo[i][k - 1], ',', '.'));
            }
            else strcat(conteudo[i][k - 1],".0");
            media += (float) atof(conteudo[i][k - 1]);
        }
        media/=linhas;
        for (i = 0; i < linhas; i++) {
            sum += pow((atof(conteudo[i][k-1]) - media), 2);
        }
        fresultado = sqrt(sum / linhas);
        fprintf(history, "O resultado final: %f\n", fresultado);
        printf("O resultado final: %f\n", fresultado);
    }
    else{
        printf("A coluna que digitou nao existe.\n");
    }
}

/********************************************** Val MIN E MAX *********************************************************/
void maxmin() {
    int i;
    int k = 0;
    float max=0;
    float min=999999999999;
    printf("Qual a coluna que pertende saber o maximo e o minimo?\n");
    scanf("%d", &k);
    if (k <= colunas) {
        for (i = 0; i < linhas; i++) {
            if(min>atof(conteudo[i][k-1])){
                min=atof(conteudo[i][k-1]);
            }
            if(max<atof(conteudo[i][k-1])){
                max=atof(conteudo[i][k-1]);
            }
        }
    } else {
        printf("A coluna que digitou nao existe.\n");
    }
    fprintf(history, "O maximo e: %.2f\nO minimo e: %.2f", max, min);

    printf("O maximo e: %.2f\nO minimo e: %.2f", max, min);
}
/******************************************** Mediana *****************************************************************/
float median(float *valuesList){

    int i = 0,j = 0;
    float t=0.0, median=0;
    int k=0;
    // Organizar dados
    for(i=0 ; i<linhas-1 ; i++) {
        for (j = i+1; j < linhas; j++) {
            if (valuesList[i] > valuesList[j]) { // Interchanging values
                t = valuesList[i];
                valuesList[i] = valuesList[j];
                valuesList[j] = t;
            } else
                continue;
        }
    }
    //sorting ends
    // calculation of median
    if ( linhas % 2 == 0)
        median = (valuesList[(linhas - 1)/2] + valuesList[linhas/2])/2.0 ;
    else
        median = valuesList[linhas/2];

    return median;
}

void mediana(){
        int i;
        int k = 0;
        float tempList[linhas];
        printf("Qual a coluna que pretende saber a mediana?\n");
        scanf("%d", &k);
        if (k <= colunas) {
            for (i = 0; i < linhas; i++) {
                strcpy(conteudo[i][k - 1],remover_espacos_strings(conteudo[i][k-1]));
                if (strstr(conteudo[i][k - 1], ",")) {
                    strcpy(conteudo[i][k - 1], replace_char(conteudo[i][k - 1], ',', '.'));
                }
                else strcat(conteudo[i][k - 1],".0");

                tempList[i] = (float) atof(conteudo[i][k-1]);
            }
        } else {
            printf("A coluna que digitou nao existe.\n");
        }
    fprintf(history, "A mediana e: %.2f", median(tempList));
    printf("A mediana e: %.2f", median(tempList));
}
/************************************************* Organizar variaveis ************************************************/
float *ordenar(float *valuesList){
    int i = 0, j = 0;
    float t = 0.0;
    int k = 0;
    // Organizar dados
    for (i = 0; i < linhas - 1; i++) {
        for (j = i + 1; j < linhas; j++) {
            //printf("Valores i, j, t: %f, %f, %f\n", valuesList[i], valuesList[j], t);
            if (valuesList[i] > valuesList[j]) { // Interchanging values
                t = valuesList[i];
                valuesList[i] = valuesList[j];
                valuesList[j] = t;
            } else
                continue;
        }
    }
    return valuesList;
}
/************************************************* Quartil 1 e 3 ******************************************************/
void quartis() {
    int i;
    int k = 0;
    int quartil1 = 0, quartil3 = 0;
    float median = 0;
    float tempList[linhas];
    printf("Qual a coluna que pretende saber a mediana?\n");
    scanf("%d", &k);
    if (k <= colunas) {
        for (i = 0; i < linhas; i++) {
            strcpy(conteudo[i][k - 1], remover_espacos_strings(conteudo[i][k - 1]));
            if (strstr(conteudo[i][k - 1], ",")) {
                strcpy(conteudo[i][k - 1], replace_char(conteudo[i][k - 1], ',', '.'));
            } else strcat(conteudo[i][k - 1], ".0");

            tempList[i] = (float) atof(conteudo[i][k - 1]);
        }
        quartil1 = ((linhas + 1) * 0.25) + 0.5;
        quartil3 = ((linhas + 1) * 0.75) + 0.5;

        //tempList = ordenar(tempList);
        fprintf(history, "O Quartil 1 e: %f\nO Quartil 3 e: %f\n", ordenar(tempList)[quartil1 - 1],ordenar(tempList)[quartil3 - 1]);
        printf("O Quartil 1 e: %f\nO Quartil 3 e: %f\n", ordenar(tempList)[quartil1 - 1],ordenar(tempList)[quartil3 - 1]);

    }
}
/************************************************** Historico *********************************************************/
void historico(){
    history = fopen("historico.csv", "w+");
}