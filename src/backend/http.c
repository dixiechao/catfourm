#include "http.h"
#include <stddef.h>
#include <microhttpd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

static const char *get_base_directory() {
    const char *base_dir = getenv("BASE_DIR");
    if (base_dir == NULL) {
        char cwd[1024];
        if (getcwd(cwd, sizeof(cwd)) != NULL) {
            cwd[sizeof(cwd) - 1] = '\0'; // Ensure null-termination
            base_dir = strdup(cwd); // Use current working directory if BASE_DIR is not set
        } else {
            perror("getcwd() error");
            base_dir = "."; // Fallback to "."
        }
    }
    printf("Base directory: %s\n", base_dir); // Debugging statement
    return base_dir;
}

static int handle_http_request(void *cls, struct MHD_Connection *connection, const char *url, const char *method, const char *upload_data, size_t *upload_data_size, void **con_cls) {
    const char *response_text;
    const char *content_type = "text/html";
    char file_path[1024];
    size_t file_size;
    struct MHD_Response *response;
    int ret;

    const char *base_dir = get_base_directory();

    if (strcmp(url, "/") == 0) {
        snprintf(file_path, sizeof(file_path), "%s/frontend/index.html", base_dir);
    } else {
        snprintf(file_path, sizeof(file_path), "%s%s", base_dir, url);
    }

    printf("Attempting to load file from: %s\n", file_path);

    response_text = http_request_file(file_path);
    if (response_text == NULL) {
        response_text = "File not found";
        response = MHD_create_response_from_buffer(strlen(response_text), (void *)response_text, MHD_RESPMEM_PERSISTENT);
        ret = MHD_queue_response(connection, MHD_HTTP_NOT_FOUND, response);
    } else {
        response = MHD_create_response_from_buffer(strlen(response_text), (void *)response_text, MHD_RESPMEM_MUST_FREE);
        ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    }

    MHD_destroy_response(response);

    return ret;
}

void http_free_data(void *cls) {
    free(cls);
}

int start_http_server(int port) {
    struct MHD_Daemon *daemon;
    daemon = MHD_start_daemon(MHD_USE_EPOLL_INTERNAL_THREAD, port, NULL, NULL, (MHD_AccessHandlerCallback)&handle_http_request, NULL, MHD_OPTION_END);
    if (daemon == NULL) {
        return 1;
    }
    int started = 1;
    while (started == 1) {
        sleep(1);
    }
    return 0;
}

int stop_http_server() {
    return 0;
}

char *http_request_file(const char *file_path) {
    FILE *file = fopen(file_path, "r");
    if (file == NULL) {
        perror("Error opening file");
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *file_content = (char *)malloc(file_size + 1);
    if (file_content == NULL) {
        fclose(file);
        return NULL;
    }

    fread(file_content, 1, file_size, file);
    file_content[file_size] = '\0';

    fclose(file);
    return file_content;
}