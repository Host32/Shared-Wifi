#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../3rdparty/mongoose.h"
#include "../3rdparty/sqlite3.h"
#include "web/index.h"
#include "web/teste.h"

#define OUTPUT_BUFFER_SIZE 200000

static int ev_handler(struct mg_connection *conn, enum mg_event ev) {
    char buffer[OUTPUT_BUFFER_SIZE];
    buffer[0] = '\0';

    switch (ev) {
        case MG_AUTH:
            return MG_MORE;
        case MG_REQUEST:

            mg_send_header(conn, "Content-Type", "text/html");

            if(strcmp(conn->uri, "/teste") == 0){ // Switch das urls
                if(page_teste(buffer, sizeof(buffer), 0) == 0){
                    return MG_FALSE;
                }
            } else {  // Entregar o index caso nao encontre a url
                if(page_index(buffer, sizeof(buffer), 0) == 0){
                    return MG_FALSE;
                }
            }

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
