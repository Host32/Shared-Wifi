#include "database.h"

sqlite3 *conn;
sqlite3_stmt *stmt;
int msg;


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
            return 1;
        } else {
            fprintf(stdout, "Erro ao conectar ao banco, erro ao tentar ativar foreign_keys");
            return 0;
        }
	} 

    fprintf(stdout, "Erro ao conectar ao banco, SQLITE_OK false");
    return 0;
}

void close_db() {
	sqlite3_close(conn);
	//fprintf(stderr, "CLOSE - %s\n", sqlite3_errmsg(conn));
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

        fprintf(stdout, "Cannot open database: %s\n", sqlite3_errmsg(conn));
        close_db();
        return 0;

    } else { 
	
        msg = sqlite3_exec(conn, sql_create_client, callback, 0, 0);

		if (msg != SQLITE_OK ) {
            fprintf(stdout, "Cannot exec create_client: %s\n", sqlite3_errmsg(conn));
            close_db();	
            return 0;
        } else {
            msg = sqlite3_exec(conn, sql_create_log, callback, 0, 0);
            if (msg != SQLITE_OK ) {
                fprintf(stdout, "Cannot exec create_log: %s\n", sqlite3_errmsg(conn));
                close_db();
                return 0;
            } else {
                close_db();
                return 1;
            }
        }
    }
}


// TAB : CLIENTE
int insert_client(cliente c) {  
    sql_insert_client = "INSERT INTO cliente VALUES (?, ?, ?, ?, ?, ?, ?, ?);";
    char aux[S_USERID];
    strncpy(aux, c.user_id, S_USERID);
    			
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
			insert_log(aux);
            return 1;
		} 
        else {
            close_db();
            insert_log(aux);
            return 1;
        }
    } else {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(conn));
        
        close_db();
        return 0;
    }
        
}

int update_client(cliente c) {
    sql_update_client = "UPDATE cliente SET birthday = ?, link = ?, name = ?, location = ?, gender = ?, email = ? WHERE user_id = ?;";	
    
    int id = user_exists(c.user_id);
    
    if (connect_db() == 0) {
		if(id != -1){

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

			sqlite3_step(stmt);
			sqlite3_finalize(stmt);

			close_db();
			fprintf(stderr, "Error: %s\n", sqlite3_errmsg(conn));
			return 0;
	
		} else {
			fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(conn));
			close_db();

			return 1;
		}
    } else return 1;
        
}

int delete_client(char user_id[S_USERID]) {   
	int id = user_exists(user_id);
    sql_delete_client = "DELETE FROM cliente WHERE id = ?;";

    if (connect_db() == 0) {
			if(id != -1){
                       msg = sqlite3_prepare_v2(conn, sql_delete_client, -1, &stmt, 0);
                        
                        if (msg != SQLITE_OK ) {
                            close_db();

                            return 1;
                        } else {
                            sqlite3_bind_int(stmt, 1, id);
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

int user_exists(char user_id[S_USERID]) {    
    sql_query_client = "SELECT id FROM cliente WHERE user_id = ?;";

    if (connect_db() == 0) {
        	sqlite3_prepare_v2(conn, sql_query_client, -1, &stmt, NULL);
            sqlite3_bind_text(stmt, 1, user_id, strlen(user_id),0);  
			if (sqlite3_step(stmt) == SQLITE_ROW) {
				int aux = atoi((char*)sqlite3_column_text(stmt, 0));
				sqlite3_finalize(stmt);
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
	int id; 
	sql_query_client = "SELECT * FROM cliente;";
	
	if (connect_db() == 0) {

			sqlite3_prepare_v2(conn, sql_query_client, -1, &stmt, NULL);

			msg = sqlite3_step(stmt);

			while(msg == SQLITE_ROW) {
				id = sqlite3_column_int(stmt, 0);
				user_id = (char*)sqlite3_column_text(stmt, 1);
				birthday = (char*)sqlite3_column_text(stmt, 2);
				link = (char*)sqlite3_column_text(stmt, 3);
				name = (char*)sqlite3_column_text(stmt, 4);
				location = (char*)sqlite3_column_text(stmt, 5);
				gender = (char*)sqlite3_column_text(stmt, 6);
				email = (char*)sqlite3_column_text(stmt, 7); 

				fprintf(stderr, "Row: id = '%d', user_id = '%s', birthday = '%s', link = '%s', name = '%s', location = '%s', gender = '%s', email = '%s'\n", id, user_id, birthday, link, name, location, gender, email);	

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




// TABLE : LOG
int insert_log(char user_id[S_USERID]) { 
    int fk_id = user_exists(user_id);  
    
    sql_insert_log = "INSERT INTO log VALUES (?,datetime('now', 'localtime'),?);";
	
    if (connect_db() == 0) {
		if(fk_id != -1){
			
			sqlite3_prepare_v2(conn, sql_insert_log, -1, &stmt, NULL);
			
			sqlite3_bind_null(stmt,1);					
			sqlite3_bind_int(stmt, 2, fk_id);
			
			sqlite3_step(stmt);	
			sqlite3_finalize(stmt);					
			close_db();
            return 1;
        } else {
            fprintf(stdout, "Usuario nao existe");
            return 0;
        }
    } else {
        fprintf(stdout, "Cannot open database: %s\n", sqlite3_errmsg(conn));
        close_db();
        return 0;
	}       
}

int delete_log(char user_id[S_USERID]) { 
	int id = user_exists(user_id);
    sql_delete_log = "DELETE FROM log WHERE fk_id = ?;";

    if (connect_db() == 0) {
			if(log_exists(id) == 0){
				
                        msg = sqlite3_prepare_v2(conn, sql_delete_log, -1, &stmt, 0);
                        
                        if (msg != SQLITE_OK ) {
                            close_db();

                            return 1;
                        } else {
                            sqlite3_bind_int(stmt, 1, id);
                            sqlite3_step(stmt);
							sqlite3_finalize(stmt);
							
							close_db();
							return 0;
                        }
			} else {
				return 1;			
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
	} else{
		return 1;	
	}

    } else{
			fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(conn));
			close_db();
			return 1;
		}
}

int list_all_logs() {
	const char *created_at;
	int id, fk_id;
	sql_query_log = "SELECT * FROM log;";

	if (connect_db() == 0) {

			sqlite3_prepare_v2(conn, sql_query_log, -1, &stmt, NULL);

			msg = sqlite3_step(stmt);

			while(msg == SQLITE_ROW) {
				id = sqlite3_column_int(stmt, 0);
				created_at = (char*)sqlite3_column_text(stmt, 1);
				fk_id = sqlite3_column_int(stmt, 2);

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
