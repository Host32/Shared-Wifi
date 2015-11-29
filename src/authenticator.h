#include <stdio.h>
#include <string.h>
#include "../3rdparty/mongoose.h"
#include "db/database.h" 

#ifndef __REQUEST__
#define __REQUEST__

int authenticate(struct mg_connection *conn); 

#endif
