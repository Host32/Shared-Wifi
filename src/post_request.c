#include "post_request.h"

cliente c;

int handle_post_request(struct mg_connection *conn) {

    char name[S_NAME], link[S_LINK], user_id[S_USERID], email[S_EMAIL], birthday[S_BIRTHDAY], location[S_LOCATION], gender[S_GENDER];
		
		mg_get_header(conn, "text/html; charset=utf-8");

		fprintf(stdout, "Entrou: %s\n", conn->request_method);
		
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
		
		mg_printf_data(stdout, 
		               "Submitted data: [%.*s]\n"
					   "Submitted data length: %d bytes\n"
					   "name: [%s]\n"
					   "link: [%s]\n"
					   "user_id: [%s]\n"
					   "email: [%s]\n"
					   "birthday: [%s]\n"
					   "location: [%s]\n"
					   "gender: [%s]\n",
					   conn->content_len, conn->content,
					   conn->content_len, c.name, c.link, 
					   c.user_id, c.email, c.birthday, 
					   c.location, c.gender);
		
		if(insert_client(c)) 
			return 0;
			
		return 1;
}
