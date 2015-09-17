#include "teste.h"

int page_teste(char buffer[], int size_buffer, int initial_char_pos){
    return html_reader("web/teste.html", buffer, size_buffer, initial_char_pos);
}
