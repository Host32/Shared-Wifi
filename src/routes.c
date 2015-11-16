#include "routes.h"

static route route_array[MAX_ENTRY_ROUTE_TABLE];

static char path_404[LEN_PREFIX_ROUTE_TABLE];
static int path_404_defined = 0;

static char path_index[LEN_PREFIX_ROUTE_TABLE];
static int path_index_defined = 0;

static int route_to_fill = 0;

/* Registra uma nova rota, recebe o caminhho e a funcao */
void add_route(const char *path, int(*fn) (struct mg_connection *conn)) {
	strncpy(route_array[route_to_fill].prefix, path, LEN_PREFIX_ROUTE_TABLE);
	route_array[route_to_fill].fn = fn;
	route_to_fill++;
}

/* Define qul sera o caminho da pagina 404 */
void set_path_404(const char* path){
	strncpy(path_404, path, LEN_PREFIX_ROUTE_TABLE);
	path_404_defined = 1;
}

/* Define qul sera o caminho da pagina raiz do site */
void set_path_index(const char* path){
	strncpy(path_index, path, LEN_PREFIX_ROUTE_TABLE);
	path_index_defined = 1;
}

/* Inicia a tabela de rotas limpando seus valores */
void init_routes_table() {
	int i;
	for (i = 0; i < MAX_ENTRY_ROUTE_TABLE; i++) {
		strcpy(route_array[i].prefix, "");
		route_array[i].fn = NULL;
	}
}

int exec_route(const char *path, struct mg_connection *conn) {
	int i, rc;
	char prefix[LEN_PREFIX_ROUTE_TABLE];
	route aux, aux2;

	if(path_index_defined && (rc = strcmp("/", path)) == 0){
		strncpy(prefix, path_index, LEN_PREFIX_ROUTE_TABLE);
	} else {
		strncpy(prefix, path, LEN_PREFIX_ROUTE_TABLE);
	}
	
	for (i = 0; i < (route_to_fill - 1); i++) {
		aux = route_array[i];
		if ((rc = strcmp(aux.prefix, prefix)) == 0) {
			return aux.fn(conn);
		}
	}
	
	if(path_404_defined){
		for (i = 0; i < (route_to_fill - 1); i++) {
			aux2 = route_array[i];
			if ((rc = strcmp(aux2.prefix, path_404)) == 0) {
				return aux2.fn(conn);
			}
		}
	}
	
	return 404;
}
