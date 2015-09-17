#include "header.h"

int template_header(char buffer[], int size_buffer, int initial_char_pos){
    return html_reader("web/html/header.html", buffer, size_buffer, initial_char_pos);
}
