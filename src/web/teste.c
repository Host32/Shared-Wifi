#include "teste.h"

int page_teste(char buffer[], int size_buffer){
    char index[] = "web/teste.html";
    char ch;
    int x;
    FILE *arq;

    buffer[0] = '\x0';

    arq = fopen(index, "r");

    if ( arq == NULL ) {
        printf("[Erro]: nao foi possivel abrir o arquivo web/teste.html\n");
        return 0;
    } else {
        for ( x = 0; (ch = fgetc(arq)) != EOF && x < size_buffer ; x++ ) {
            buffer[x] = ch;
        }

        if(fclose(arq) == EOF){
            printf("[Erro]: nao foi possivel fechar o arquivo web/teste.html\n");
            return 0;
        }
    }

    return 1;
}
