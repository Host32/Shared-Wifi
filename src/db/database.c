#include "database.h"

sqlite3 *conn;
sqlite3_stmt *stmt;
int msg;

char *errMsg = 0;

const char* sql_pragma;

const char* sql_create_client;
const char* sql_insert_client;
const char* sql_update_client;
const char* sql_delete_client;
const char* sql_query_client;
const char* sql_query_client_id;

const char* sql_create_log;
const char* sql_insert_log;
const char* sql_update_log;
const char* sql_delete_log;
const char* sql_query_log;
const char* sql_query_log_datatime;



// GENERAL
int connect_db(){
    msg = sqlite3_open("banco.db", &conn);
    if (msg == SQLITE_OK){
		sql_pragma = "PRAGMA foreign_keys = ON;";
		msg = sqlite3_exec(conn, sql_pragma, 0, 0, 0);
		if (msg != SQLITE_OK ) {
				sqlite3_close(conn);
				return 1;
		} else return 0;
	} 
    return 1;    
}

void close_db() {
	sqlite3_finalize(stmt);
    sqlite3_free(errMsg);
	sqlite3_close(conn);
}

static int callback(void *data, int argc, char **argv, char **azColName){
  int i;
  fprintf(stderr, "%s: ", (const char*)data);
  for (i = 0; i<argc; i++){
    printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
  }
  printf("\n");
  return 0;
}


// CREATE TABLES
int create_table() {
    sql_create_client = "CREATE TABLE IF NOT EXISTS cliente(id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, user_id TEXT NOT NULL, birthday TEXT NOT NULL, link TEXT NOT NULL, name TEXT NOT NULL, location TEXT NOT NULL, gender TEXT NOT NULL, email TEXT NOT NULL);";
	sql_create_log = "CREATE TABLE IF NOT EXISTS log (id INTEGER NOT NULL PRIMARY KEY, created_at DATETIME NOT NULL, fk_id INTEGER NOT NULL, FOREIGN KEY (fk_id) REFERENCES cliente(id));";

    int r = connect_db();
	if (r != SQLITE_OK) {
        
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(conn));
        close_db();
        return 0;

    } else { 
	
        msg = sqlite3_exec(conn, sql_create_client, callback, 0, &errMsg);

		if (msg != SQLITE_OK ) {
            close_db();	
            return 1;
        } else {
                msg = sqlite3_exec(conn, sql_create_log, callback, 0, &errMsg);
				if (msg != SQLITE_OK ) {
					close_db();
					return 1;
				} else {
						fprintf(stdout, "Operation done successfully\n");
						return 0;
				}
				return 1;	
			}
		
        close_db();
        return 0;
    }
}


// TAB : CLIENTE
int insert_client(cliente c) {  
    sql_insert_client = "INSERT INTO cliente VALUES (?, ?, ?, ?, ?, ?, ?, ?);";
    
    if (connect_db() == SQLITE_OK) {
		if(user_exists(c.user_id) == -1){
			sqlite3_prepare_v2(conn, sql_insert_client, -1, &stmt, NULL);
					
			const char* user_id = c.user_id;
			const char* birthday = c.birthday;
			const char* link = c.link;
			const char* name = c.name;
			const char* location = c.location;
			const char* gender = c.gender;
			const char* email = c.email;
											  
			sqlite3_bind_null(stmt, 1);
			sqlite3_bind_text(stmt, 2, user_id, -1, SQLITE_STATIC);
			sqlite3_bind_text(stmt, 3, birthday, -1, SQLITE_STATIC); 
			sqlite3_bind_text(stmt, 4, link, -1, SQLITE_STATIC); 
			sqlite3_bind_text(stmt, 5, name, -1, SQLITE_STATIC); 
			sqlite3_bind_text(stmt, 6, location, -1, SQLITE_STATIC); 
			sqlite3_bind_text(stmt, 7, gender, -1, SQLITE_STATIC);
			sqlite3_bind_text(stmt, 8, email, -1, SQLITE_STATIC);
					
			sqlite3_step(stmt);
			sqlite3_finalize(stmt);

			close_db();
			
			return 0;
		}

    } else {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(conn));
        
        close_db();
        return 1;
	}
        
}

int update_client(cliente c) {
    sql_update_client = "UPDATE cliente SET birthday = ?, link = ?, name = ?, location = ?, gender = ?, email = ? WHERE user_id = ?;";

    if (connect_db() == 0) {
		if(user_exists(c.user_id) != -1){
			sqlite3_prepare_v2(conn, sql_update_client, -1, &stmt, NULL);
			
			const char* user_id = c.user_id;		
			const char* birthday = c.birthday;
			const char* link = c.link;
			const char* name = c.name;
			const char* location = c.location;
			const char* gender = c.gender;
			const char* email = c.email;
											  
			sqlite3_bind_text(stmt, 1, birthday, -1, SQLITE_STATIC); 
			sqlite3_bind_text(stmt, 2, link, -1, SQLITE_STATIC); 
			sqlite3_bind_text(stmt, 3, name, -1, SQLITE_STATIC); 
			sqlite3_bind_text(stmt, 4, location, -1, SQLITE_STATIC); 
			sqlite3_bind_text(stmt, 5, gender, -1, SQLITE_STATIC);
			sqlite3_bind_text(stmt, 6, email, -1, SQLITE_STATIC);
			sqlite3_bind_text(stmt, 7, user_id, -1, SQLITE_STATIC);
			
			if (sqlite3_step(stmt) == SQLITE_OK){
				sqlite3_finalize(stmt);
				close_db();
				return 0;
			} else {
				fprintf(stderr, "Erro: %s\n", sqlite3_errmsg(conn));
				close_db();
				return 1;		
			}	
		} else {
			fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(conn));
			close_db();

			return 1;
		}
    } 
        
}

int delete_client(char user_id[30]) {   
    sql_delete_client = "DELETE FROM cliente WHERE user_id = ?;";

    if (connect_db() == 0) {
			if(user_exists(user_id) != -1){
                        msg = sqlite3_prepare_v2(conn, sql_delete_client, -1, &stmt, 0);
                        if (msg != SQLITE_OK ) {
                            fprintf(stderr, "SQL error: %s\n", errMsg);
                            close_db();

                            return 1;
                        } else {
                            sqlite3_bind_text(stmt, 1, user_id, -1, SQLITE_STATIC);
                            sqlite3_step(stmt);
							sqlite3_finalize(stmt);

							close_db();
							return 0;
                        }
			} else return 1;

    } else {
            fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(conn));
            close_db();

            return 1;
    }
}

int user_exists(char user_id[30]) {    
    sql_query_client = "SELECT id FROM cliente WHERE user_id = ?;";

    if (connect_db() == 0) {

        	sqlite3_prepare_v2(conn, sql_query_client, -1, &stmt, NULL);
            sqlite3_bind_text(stmt, 1, user_id, strlen(user_id),0);
			    
			if (sqlite3_step(stmt) == SQLITE_ROW) {
				int aux = atoi((char*)sqlite3_column_text(stmt, 0));
				close_db();
				return aux;
			} else return -1;
			
    } else {
			fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(conn));
			return -1;
		}
}

int list_all_clients() {	
	const char *user_id, *birthday, *link, *name, *location, *gender, *email;
	int id, ncols; 
	sql_query_client = "SELECT * FROM cliente;";
	
	if (connect_db() == 0) {

			sqlite3_prepare_v2(conn, sql_query_client, -1, &stmt, NULL);

			ncols = sqlite3_column_count(stmt);
			msg = sqlite3_step(stmt);

			while(msg == SQLITE_ROW) {
				id = sqlite3_column_int(stmt, 0);
				user_id = sqlite3_column_text(stmt, 1);
				birthday = sqlite3_column_text(stmt, 2);
				link = sqlite3_column_text(stmt, 3);
				name = sqlite3_column_text(stmt, 4);
				location = sqlite3_column_text(stmt, 5);
				gender = sqlite3_column_text(stmt, 6);
				email = sqlite3_column_text(stmt, 7); 

				fprintf(stderr, "Row: id = '%d', user_id = '%s', birthday = '%s', link = '%s', name = '%s', location = '%s', gender = '%s', email = '%s'\n", id, user_id, birthday, link, name, location, gender, email);	

				msg = sqlite3_step(stmt);
			}
			
			sqlite3_finalize(stmt);
			sqlite3_reset(stmt);

			close_db();
			return 0;
	} else {
		close_db();
		return 1;
	}
}




// TABLE : LOG
int insert_log(char user_id[30]) { 
    int fk_id = user_exists(user_id);
    sql_insert_log = "INSERT INTO log VALUES (?,datetime('now', 'localtime'),?);";
	
    if (connect_db() == 0) {
			sqlite3_prepare_v2(conn, sql_insert_log, -1, &stmt, NULL);
			
			sqlite3_bind_null(stmt,1);					
			sqlite3_bind_int(stmt, 2, fk_id);
			
			if (sqlite3_step(stmt) != SQLITE_OK) {
				return 1;
			} 					
			
			sqlite3_finalize(stmt);
			close_db();
			return 0;
    } else {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(conn));
        close_db();
        return 1;
	}       
}

int delete_log(char user_id[30]) { 
	int id = user_exists(user_id);
    sql_delete_log = "DELETE FROM log WHERE fk_id = ?;";

    if (connect_db() == 0) {
			if(log_exists(id) == 0){
				
                        msg = sqlite3_prepare_v2(conn, sql_delete_log, -1, &stmt, 0);
                        
		                if (msg != SQLITE_OK ) {
		                    fprintf(stderr, "SQL error: %s\n", errMsg);
		                    close_db();

		                    return 1;
		                } else {
		                    sqlite3_bind_int(stmt, 1, id);
		                    sqlite3_step(stmt);
				    
							sqlite3_finalize(stmt);			
							close_db();
							return 0;
		                }
			}

    } else {
            fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(conn));
            close_db();
            return 1;
    }
}

int log_exists(int fk_id) {
    sql_query_log = "SELECT * FROM log WHERE fk_id = ?;";

    if (connect_db() == 0) {
        	
        	sqlite3_prepare_v2(conn, sql_query_log, -1, &stmt, 0);
            	sqlite3_bind_int(stmt, 1, fk_id);
			    
			if (sqlite3_step(stmt) == SQLITE_ROW) {
                return 0;
			}

    } else{
			fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(conn));
			close_db();
			return 1;
		}
}

int list_all_logs() {
	const char *created_at;
	int i, ncols, id;
	sql_query_log = "SELECT * FROM log;";

	if (connect_db() == 0) {

			sqlite3_prepare_v2(conn, sql_query_log, -1, &stmt, NULL);

			int ncols = sqlite3_column_count(stmt);
			msg = sqlite3_step(stmt);

			while(msg == SQLITE_ROW) {
				id = sqlite3_column_int(stmt, 0);
				created_at = sqlite3_column_text(stmt, 1);
				int fk_id = sqlite3_column_int(stmt, 2);

				fprintf(stderr, "Row: id = '%d', created_at = '%s', fk_id = '%d'\n", id, created_at, fk_id);	
				msg = sqlite3_step(stmt);
			}
			
			sqlite3_finalize(stmt);

			close_db();
			return 0;
	} else {
		close_db();
		return 1;
	}
}
