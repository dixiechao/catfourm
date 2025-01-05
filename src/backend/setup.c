#include <stdio.h>
#include "setup.h"

int setup_fourm(sqlite3 *db)
{
    const char *sql = 
    "CREATE TABLE IF NOT EXISTS users ("
    "id INTEGER PRIMARY KEY AUTOINCREMENT,"
    "username TEXT NOT NULL UNIQUE,"
    "email TEXT NOT NULL UNIQUE);";

    char* err_msg = 0;

    int rc = sqlite3_exec(db, sql, 0, 0, &err_msg);
    {
        if (rc != SQLITE_OK)
        {
            fprintf(stderr, "SQL error: %s\n", err_msg);
            sqlite3_free(err_msg);
            return 1;
        }
        else
        {
            printf("Table created successfully \n");
        }
    }
    
}