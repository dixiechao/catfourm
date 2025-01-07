#include "backend/setup.h"
#include "backend/register.h"
#include "backend/http.h"
#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[1]) {

    if (argc < 2) {
        printf("Usage: fourm <command> [args]\n");
        return 1;
    }

    if (strcmp(argv[1], "setup") == 0) {
        sqlite3 *db;
        int rc = sqlite3_open("fourm.db", &db);
        if (rc) {
            fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
            return 1;
        }
        setup_fourm(db);
        sqlite3_close(db);
    }
    else if (strcmp(argv[1], "register") == 0) {
        register_user(argv[2], argv[3]);
    }
    else {
        printf("Running Server! at localhost:8080\n");
        start_http_server(8080);
    }
}