#include <stdio.h>
#include <string.h>
#include "../3rdparty/mongoose.h"
#include "db/database.h" 

#ifndef __REQUEST__
#define __REQUEST__

int handle_post_request(struct mg_connection *conn); 

#endif
