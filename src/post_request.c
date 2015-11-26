#include "post_request.h"

int handle_post_request(struct mg_connection *conn) {

	cliente c;

    char name[S_NAME], link[S_LINK], user_id[S_USERID], email[S_EMAIL], birthday[S_BIRTHDAY], location[S_LOCATION], gender[S_GENDER];
		
	mg_get_header(conn, "text/html; charset=utf-8");

	mg_get_var(conn, "name", name, S_NAME);
	mg_get_var(conn, "link", link, S_LINK);
	mg_get_var(conn, "user_id", user_id, S_USERID);
	mg_get_var(conn, "email", email, S_EMAIL);
	mg_get_var(conn, "birthday", birthday, S_BIRTHDAY);
	mg_get_var(conn, "location", location, S_LOCATION);
	mg_get_var(conn, "gender", gender, S_GENDER);				   		   
					   
	strncpy(c.name, name, S_NAME);
	strncpy(c.user_id, user_id, S_USERID);
	strncpy(c.birthday, birthday, S_BIRTHDAY);
	strncpy(c.email, email, S_EMAIL);
	strncpy(c.location, location, S_LOCATION);
	strncpy(c.link, link, S_LINK);
	strncpy(c.gender, gender, S_GENDER);
	
	//create_table();
    insert_client(c);
			
	return 1;
}
