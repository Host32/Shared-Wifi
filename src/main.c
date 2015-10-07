#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../3rdparty/mongoose.h"
#include "../3rdparty/sqlite3.h"
#include "routes.h"
#include "resources.h"

static int ev_handler(struct mg_connection *conn, enum mg_event ev) {
	int exec_result;

    switch (ev) {
        case MG_AUTH:
            return MG_MORE;
        case MG_REQUEST:
			fprintf(stdout, "Processing %s\n", conn->uri);
            
			exec_result = exec_route(conn->uri, conn);

			if (exec_result == 404) {
				return MG_FALSE;
			}
			else if (!exec_result) {
				return MG_FALSE;
			}

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

	init_routes_table();
	init_resources_table();

	// Serve request. Hit Ctrl-C to terminate the program
	printf("Starting on port %s\n", mg_get_option(server, "listening_port"));
	for (;;) {
		mg_poll_server(server, 1000);
	}

	// Cleanup, and free server instance
	mg_destroy_server(&server);

    return 0;
}
