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
	int user_id;
    char birthday[12];
	char link[100];
	char name[100];
	char locale[100];
    char gender[10];
	char email[80]; 
} cliente;

int connectDb();
int createTable();
int insertRow(cliente c);
int updateRow(cliente c);
int deleteRow(int user_id);
int userExists(int user_id);
int listAllRows();
void closeDb();
static int callback(void *NotUsed, int argc, char **argv, char **azColName);

#endif
