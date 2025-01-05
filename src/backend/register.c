#include <stdio.h>
#include <sqlite3.h>
#include <string.h>
#include "register.h"

int register_user(const char *username, const char *email) {
    sqlite3 *db;
    char *err_msg = 0;

    // attempt to open the database
    int rc = sqlite3_open("fourm.db", &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    // prepare the SQL statement
    char *sql[256];
    snprintf(sql, sizeof(sql), "INSERT INTO users (username, email) VALUES ('%s', '%s');", username, email);

    // execute the SQL statement
    rc = sqlite3_exec(db, sql, 0, 0, &err_msg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(db);
        return 1;
    }

    printf("User registered successfully\n");

    // close the database
    sqlite3_close(db);
    return 0;
}