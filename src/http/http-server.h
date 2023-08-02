#ifndef HTTP_SERVER_H
#define HTTP_SERVER_H

#include <stdlib.h>

typedef struct _http_server http_server;

http_server* http_server_create(int port);
void http_server_start(http_server* hs);

int http_server_get_server_socket(http_server* hs);
struct sockaddr_in http_server_get_server_address(http_server* hs);
void http_server_destroy(http_server* hs);

#endif



