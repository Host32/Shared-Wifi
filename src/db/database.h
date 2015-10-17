#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include "../../3rdparty/sqlite3.h"

#ifndef __DATABASE__
#define __DATABASE__

typedef struct{
	int id;
    char user_id[30];
    char birthday[12];
	char link[100];
	char name[100];
    char location[100];
    char gender[10];
	char email[80]; 
} cliente;

int connect_db();
int create_table();
int insert_row(cliente c);
int update_row(cliente c);
int delete_row(int user_id);
int user_exists(char user_id[]);
int list_all_rows();
void close_db();
static int callback(void *NotUsed, int argc, char **argv, char **azColName);

#endif
