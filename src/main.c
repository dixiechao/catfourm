#include "backend/setup.h"
#include "backend/register.h"
#include <cstdio>

int main(char* argv[1], int argc) {

    if (argc < 2) {
        printf("Usage: fourm <command> [args]\n");
        return 1;
    }

    if (argv[1] == "setup") {
        sqlite3 *db;
        int rc = sqlite3_open("fourm.db", &db);
        if (rc) {
            fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
            return 1;
        }
        setup_fourm(db);
        sqlite3_close(db);
    }
    else if (argv[1] == "register") {
        register_user(argv[2], argv[3]);
    }
    else {
        printf("Invalid command\n");
    }
}