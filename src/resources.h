#ifndef __RESOURCES__
#define __RESOURCES__

#include <stdio.h>
#include <stdlib.h>
#include "../3rdparty/mongoose.h"
#include "routes.h"

void init_resources_table();

int _404_html(struct mg_connection *conn);

int _index_html(struct mg_connection *conn);

#endif
