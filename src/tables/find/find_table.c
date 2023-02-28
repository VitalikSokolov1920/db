#include <sys/types.h>
#include <sys/stat.h>

#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include "find_table.h"

int find_table(const char* table_name) {
    if (!table_name) {
        return -1;
    }

    char cur_cwd[CWD_LEN];
    getcwd(cur_cwd, CWD_LEN);

    char* tables_dir = strcat(cur_cwd, "/tables");

    DIR* dir = opendir(tables_dir);

    if (!dir) {
        perror("opendir");

        // exit(EXIT_FAILURE);
        return -1;
    }

    struct dirent* file;
    struct stat file_info;

    while (file = readdir(dir)) {
        stat(file->d_name, &file_info);

        if ((file_info.st_mode & S_IFMT) == S_IFREG) {
            if (!strcmp(file->d_name, table_name)) {
                return 1;
            }
        }
    }

    return 0;
}