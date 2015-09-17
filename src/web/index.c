#include "index.h"

int page_index(char buffer[], int size_buffer, int initial_char_pos){
    return html_reader("web/index.html", buffer, size_buffer, initial_char_pos);
}
