#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/socket.h>
#include <sys/types.h>

#include <netinet/in.h>
#include <unistd.h>

char* build_response(const char* http_header, const char* http_body) {
    size_t http_header_length = strlen(http_header);
    size_t http_body_length = strlen(http_body);

    char* http_response = (char*)malloc(http_header_length + http_body_length);

    if (http_response == NULL) {
        perror("Memory allocation error");
        return NULL;
    }

    strcpy(http_response, http_header);
    strcat(http_response, http_body);

    printf("%s", http_response);
    return http_response;
}

void add_cool(int client_socket, const char* http_response) {
    size_t http_response_size = strlen(http_response);

    char cool[] = "cool";
    size_t cool_size = sizeof(cool);

    char* new_http_response = (char*)malloc(http_response_size + cool_size + 1);

    strcpy(new_http_response, http_response);
    strcat(new_http_response, cool);


    send(client_socket, new_http_response, strlen(new_http_response), 0);

    free(new_http_response);
}

int main() {
    const char http_body[] = "hello world";
    size_t http_header_length = strlen("HTTP/1.1 200 OK\r\n\n");

    char* http_header = (char *)malloc(http_header_length + 1); // Add 1 for the null terminator

    if (http_header == NULL) {
        perror("Memory allocation error");
        return 1;
    }

    strcpy(http_header, "HTTP/1.1 200 OK\r\n\n");

    char* http_response = build_response(http_header, http_body);

    int server_socket;
    server_socket = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in server_address;

    server_address.sin_port = htons(9002);
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;


    int bind_socket_status = bind(server_socket, (struct sockaddr *) &server_address, sizeof(server_address));
    if (bind_socket_status == -1) {
        perror("bind");
        return 1;
    }

    listen(server_socket, 5);

    int client_socket;

    while(1) {
        client_socket = accept(server_socket, NULL, NULL);
        add_cool(client_socket, http_response);
        close(client_socket);
    }

    return 0;
}







