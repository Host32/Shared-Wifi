#include "database.h"

// Variaveis de conexao
sqlite3 *conn;
sqlite3_stmt *stmt;
int msg;

// Armazenar mensagem de erro
char *errMsg = 0;

// Variaveis comandos SQL
char *sql_create;
char *sql_insert;
char *sql_update;
char *sql_delete;
char *sql_query_client;
char *sql_query;


int connect_db(){
    return msg = sqlite3_open("banco.db", &conn);
}

int create_table() {
    sql_create = "CREATE TABLE cliente (id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, user_id TEXT NOT NULL, birthday TEXT NOT NULL, link TEXT NOT NULL, name TEXT NOT NULL, location TEXT NOT NULL, gender TEXT NOT NULL, email TEXT NOT NULL);";
    int r = connect_db();
	if (r != SQLITE_OK) {
        
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(conn));
        close_db();
		
        return 0;

    	} else{

        msg = sqlite3_exec(conn, sql_create, callback, 0, &errMsg);

		if (msg != SQLITE_OK ) {
		
            fprintf(stderr, "SQL error: %s\n", errMsg);
            close_db();
		
            return 0;
        } else {
                  fprintf(stdout, "Operation done successfully\n");
        }
		
        close_db();
        return 1;
    }
}

int insert_row(cliente c) {
    sql_insert = "INSERT INTO cliente VALUES(?, ?, ?, ?, ?, ?, ?, ?);";
    int r = connect_db();
    if (r != SQLITE_OK) {

        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(conn));
        close_db();

        return 0;

        } else{

        msg = sqlite3_exec(conn, sql_insert, callback, 0, &errMsg);
        if (msg != SQLITE_OK ) {

            fprintf(stderr, "SQL error: %s\n", errMsg);
            close_db();

            return 0;
        } else {
                  sqlite3_bind_null(stmt, 1);
                  sqlite3_bind_text(stmt, 2, c.user_id, strlen(c.user_id), 0);
                  sqlite3_bind_text(stmt, 3, c.birthday, strlen(c.birthday), 0);
                  sqlite3_bind_text(stmt, 4, c.link, strlen(c.link), 0);
                  sqlite3_bind_text(stmt, 5, c.name, strlen(c.name), 0);
                  sqlite3_bind_text(stmt, 6, c.location, strlen(c.location), 0);
                  sqlite3_bind_text(stmt, 7, c.gender, strlen(c.gender), 0);
                  sqlite3_bind_text(stmt, 8, c.email, strlen(c.email), 0);
        }

        // commit
        sqlite3_step(stmt);
        sqlite3_finalize(stmt);

        close_db();
        return 1;
    }
}

int update_row(cliente c) {
    sql_update = "UPDATE cliente SET birthday = ?, link = ?, name = ?, location = ?, gender = ?, email = ? WHERE user_id = ?;";

    int r = connect_db();
    if (r != SQLITE_OK) {

        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(conn));
        close_db();

        return 0;

        } else{

        msg = sqlite3_exec(conn, sql_update, callback, 0, &errMsg);
        if (msg != SQLITE_OK ) {
            fprintf(stderr, "SQL error: %s\n", errMsg);
            close_db();

            return 0;
        } else {
                    sqlite3_bind_text(stmt, 1, c.birthday, strlen(c.birthday), 0);
                    sqlite3_bind_text(stmt, 2, c.link, strlen(c.link), 0);
                    sqlite3_bind_text(stmt, 3, c.name, strlen(c.name), 0);
                    sqlite3_bind_text(stmt, 4, c.location, strlen(c.location), 0);
                    sqlite3_bind_text(stmt, 5, c.gender, strlen(c.gender), 0);
                    sqlite3_bind_text(stmt, 6, c.email, strlen(c.email), 0);
                    sqlite3_bind_text(stmt, 7, c.user_id, strlen(c.user_id),0);
        }

        // commit
        sqlite3_step(stmt);
        sqlite3_finalize(stmt);

        close_db();
        return 1;
    }
}

int delete_row(int user_id) {
    sql_delete = "DELETE FROM cliente WHERE user_id = ?;";
    int r = connect_db();
    if (r != SQLITE_OK) {

            fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(conn));
            close_db();

            return 0;

    } else if(user_exists(user_id)){
                        msg = sqlite3_prepare_v2(conn, sql_delete, -1, &stmt, 0);
                        if (msg != SQLITE_OK ) {
                            fprintf(stderr, "SQL error: %s\n", errMsg);
                            close_db();

                            return 0;
                        } else {
                            sqlite3_bind_int(stmt, 1, user_id);
                            return 1;
                        }
                        close_db();
    }
    return 1;
}

int user_exists(char user_id[30]) {
    sql_query_client = "SELECT * FROM cliente WHERE user_id = ?;";
    int r = connect_db();
	if (r != SQLITE_OK) {
        
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(conn));
        close_db();
		
        return 0;

    } else{

			r = sqlite3_prepare_v2(conn, sql_query_client, -1, &stmt, 0);
            sqlite3_bind_text(stmt, 1, user_id, strlen(user_id),0);
			    
            int step = sqlite3_step(stmt);
			if (step == SQLITE_ROW) {
                return 1;
			}
		
            close_db();
            return 0;
		}
}

int list_all_rows() {
    sql_query = "SELECT * FROM cliente;";
    int r = connect_db();
	if (r != SQLITE_OK) {
        
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(conn));
        close_db();
		
        return 0;

    	} else{

        msg = sqlite3_exec(conn, sql_query, callback, 0, &errMsg);
		if (msg != SQLITE_OK ) {
		
            fprintf(stderr, "Failed to select data\n");
            fprintf(stderr, "SQL error: %s\n", errMsg);
		
            close_db();
		
            return 0;
        }
		
        close_db();
        return 1;
	}
}

void close_db() {
    sqlite3_free(errMsg);
	sqlite3_close(conn);
}

static int callback(void *NotUsed, int argc, char **argv, char **azColName){
   int i;
   for(i=0; i<argc; i++){
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   printf("\n");
   return 0;
}
