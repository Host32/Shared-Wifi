#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include "../3rdparty/sqlite3.h"

#ifndef __DATABASE__
#define __DATABASE__

#define S_USERID 30
#define S_BIRTHDAY 12
#define S_LINK 100
#define S_NAME 100
#define S_LOCATION 100
#define S_GENDER 10
#define S_EMAIL 80

typedef struct{
	int id;
    char user_id[S_USERID];
    char birthday[S_BIRTHDAY];
	char link[S_LINK];
	char name[S_NAME];
    char location[S_LOCATION];
    char gender[S_GENDER];
	char email[S_EMAIL]; 
} cliente;


int connect_db();
void close_db();
static int callback(void *NotUsed, int argc, char **argv, char **azColName);

int create_table();

int insert_client(cliente c);
int update_client(cliente c);
int delete_client(char user_id[S_USERID]);
int user_exists(char user_id[S_USERID]);
int list_all_clients();

int insert_log(char user_id[S_USERID]);
int delete_log(char user_id[S_USERID]);
int log_exists(int fk_id);
int list_all_logs();

#endif
