#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE * AbrirArquivo(char modo, char carac[30]){
    FILE * arquivo;
    switch(modo){
        case 'w':
            arquivo = fopen(carac, "w");
        break;
        case 'r':
            arquivo = fopen(carac, "r");
        break;
        case 'a':
            arquivo = fopen(carac, "a");
        break;
        case 'rb':
            arquivo = fopen(carac, "rb");
        break;
    }
    if(arquivo == NULL){
        printf("Impossivel abrir o arquivo");
    }
    return arquivo;
}

void FecharArquivo(FILE * arquivo){
    fclose(arquivo);
}

void Registrar(char carac[30], int num){
    FILE * arquivo;
    arquivo = AbrirArquivo('a', "agenda.txt");
    fprintf(arquivo, "%s %d\n", carac, num);

    FecharArquivo(arquivo);
}

void Consulta(){
    FILE * arquivo;
    char carac[30];
    int linha = 0, num;

    arquivo = AbrirArquivo('r', "agenda.txt");

   while(!feof(arquivo)){
       fscanf(arquivo, "%s %d ", &carac, &num);
       printf("Numero da linha: %d Nome: %s - Telefone: %d\n", linha++, carac, num);
   }
   FecharArquivo(arquivo);
}

void Apagar(FILE * arquivo, FILE * arquivo2){
    int deletar;
    int linha = 0;
    arquivo = AbrirArquivo('r', "agenda.txt");

    if(arquivo == NULL){
        printf("ERROR");
        return 1;
    }

    printf("Digite a linha que deseja deletar: ");
    scanf("%d", &deletar);

    arquivo2 = AbrirArquivo('w', "arquivo2.txt");

    char carac[30];

    while(fgets(carac, 29, arquivo) != NULL){
        linha++;
        if(linha != deletar){
            fputs(carac, arquivo2);
            printf("Copia feita con sucesso!\n");
        }
    }
    fclose(arquivo);
    fclose(arquivo2);
    remove("agenda.txt");
    rename("arquivo2.txt", "agenda.txt");
}

void Pesquisa(char carac[30]){
    int done = 1;
    char palavra[100];

    FILE * arquivo;
    arquivo = AbrirArquivo('r', "agenda.txt");

    printf("Digite o nome do contato: ");
    gets(carac);

    while(fgets(palavra, 100, arquivo) !=NULL){
        if(strstr(palavra, carac) !=NULL){
            printf("%s", palavra);
            done = 0;
        }
    }
}

int main(){
    FILE *arquivo;
    FILE *arquivo2;
    char carac[30];
    int num;
    char modo;

    do{

    printf("MENU:\n");
    printf("\n1 - para registar um contato\n\n2 - para consultar contato\n\n3 - para apagar contato\n\n4 - para pesquisar contato\n\n5 - Sair\n");

    scanf("%s", &modo);
    system("cls");

    switch(modo){
        case '1':
            printf("Digite o nome: ");
            setbuf(stdin, NULL);
            gets(carac);
            printf("Digite o numero: ");
            scanf("%d", &num);
            Registrar(carac, num);
            getchar();
        break;
        case '2':
            Consulta();
            getchar();
        break;
        case '3':
            Apagar(arquivo, arquivo2);
        break;
             break;
        case '4':
            Pesquisa(carac);
            getchar();
        break;
        case '5':
            printf("finalizando...\n");
            getchar();
            exit(0);
        break;
        }
    }while(modo != 3);
}
