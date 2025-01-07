#include <stddef.h>
#define HTTP_H
#ifdef HTTP_H
#include <microhttpd.h>


int start_http_server(int port);
int stop_http_server();
void http_free_data(void *cls);
static int handle_http_request(void *cls, struct MHD_Connection *connection, const char *url, const char *method, const char *upload_data, size_t *upload_data_size, void **con_cls);

char *http_request_file(const char *file_path);
#endif // HTTP_H