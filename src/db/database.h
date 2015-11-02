#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include "../3rdparty/sqlite3.h"

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
void close_db();
static int callback(void *NotUsed, int argc, char **argv, char **azColName);

int create_table();

int insert_client(cliente c);
int update_client(cliente c);
int delete_client(char user_id[30]);
int user_exists(char user_id[30]);
int list_all_clients();

int insert_log(char user_id[30]);
int delete_log(char user_id[30]);
int log_exists(int fk_id);
int list_all_logs();

#endif
