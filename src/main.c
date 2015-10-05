#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../3rdparty/mongoose.h"
#include "../3rdparty/sqlite3.h"
#include "web/template/header.h"
#include "web/template/footer.h"
#include "web/pages/index.h"
#include "web/pages/teste.h"

#define OUTPUT_BUFFER_SIZE 200000

static int ev_handler(struct mg_connection *conn, enum mg_event ev) {
    char buffer[OUTPUT_BUFFER_SIZE];
    int eo_header, eo_body;

    buffer[0] = '\0';

    switch (ev) {
        case MG_AUTH:
            return MG_MORE;
        case MG_REQUEST:
            mg_send_header(conn, "Content-Type", "text/html");

            // Cabecalho do template
            if((eo_header = template_header(buffer, sizeof(buffer), 0)) == 0){
                return MG_FALSE;
            }

            // Switch das urls
            // pagina de teste
            if(strcmp(conn->uri, "/teste") == 0){
                if((eo_body = page_teste(buffer, sizeof(buffer), eo_header)) == 0){
                    return MG_FALSE;
                }
            }
            // Index default
            else {
                if((eo_body = page_index(buffer, sizeof(buffer), eo_header)) == 0){
                    return MG_FALSE;
                }
            }

            // Rodape da pagina
            if(template_footer(buffer, sizeof(buffer), eo_body) == 0){
                return MG_FALSE;
            }

            // Imprime a resposta
            mg_printf_data(conn, buffer);

            return MG_TRUE;
        default:
            return MG_FALSE;
    }
}

int main(void){
	struct mg_server *server;

	// Create and configure the server
	server = mg_create_server(NULL, ev_handler);
	mg_set_option(server, "document_root", ".");
	mg_set_option(server, "listening_port", "8080");

	// Serve request. Hit Ctrl-C to terminate the program
	printf("Starting on port %s\n", mg_get_option(server, "listening_port"));
	for (;;) {
		mg_poll_server(server, 1000);
	}

	// Cleanup, and free server instance
	mg_destroy_server(&server);

    return 0;
}
