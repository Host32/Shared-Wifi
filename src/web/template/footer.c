#include "footer.h"

int template_footer(char buffer[], int size_buffer, int initial_char_pos){
    return html_reader("web/html/footer.html", buffer, size_buffer, initial_char_pos);
}
