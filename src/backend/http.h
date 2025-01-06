#define HTTP_H
#ifdef HTTP_H

int start_http_server(int port);
int stop_http_server();

int send_http_response(int client_socket, const char *response);
int send_http_response_file(int client_socket, const char *file_path);
#endif // HTTP_H