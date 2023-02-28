#include <sys/stat.h>
#include <sys/types.h>

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>

#include "init.h"
#include "../command/command.h"

static char* root_dir = "/var/lib/my-db";

void init() {
    create_db_root_dir();

    change_root_cwd();

    create_tables_dir();
}

static void change_root_cwd() {
    if (chdir(root_dir) == -1) {
        perror("chdir");

        exit(EXIT_FAILURE);
    }
}

/*
-1 - error
0 - ok
1 - exist
2 - exist not dir
*/
int create_dir(char* dir_name, int mode) {
    if (!mode) {
        mode = S_IRUSR | S_IWUSR | S_IWGRP | S_IRGRP;
    }

    if (!mkdir(dir_name, mode)) {
        if (errno == EEXIST) {
            struct stat file_info;

            if (stat(dir_name, &file_info) == -1) {
                perror("stat");

                return -1;
            }

            switch (file_info.st_mode & S_IFMT)
            {
            case S_IFDIR:
                return 1;
                break;
            default:
                return 2;
                break;
            }
        } else {
            return -1;
        }
    }

    return 0;
}

/*
-1 - error
0 - ok
1 - exist
2- exist not dir
*/
static int create_tables_dir() {
    int ret;

    ret = create_dir("./tables", 0);

    if (ret == 2) {
        printf("Не удалось создать директорию базы данных в каталоге %s\n", root_dir);

        exit(EXIT_FAILURE);
    } else if (ret == -1) {
        exit(EXIT_FAILURE);
    }
}

static void create_db_root_dir() { 
    int ret;

    ret = create_dir(root_dir, 0);

    if (ret == 2) {
        printf("Не удалось создать директорию базы данных в каталоге %s\n", root_dir);

        exit(EXIT_FAILURE);
    } else if (ret == -1) {
        printf("Ошибка создания системных директорий\n");

        exit(EXIT_FAILURE);
    }
}

int console_exec() {
    char* input;
    int ret;

    while (1) {
        printf("> ");

        input = (char*)malloc(CMD_INPUT_SIZE);

        fgets(input, CMD_INPUT_SIZE, stdin);

        if (!strlen(input)) {
            printf("Введена пустая команда\n");
            
            break;
        } 

        parse_command(input);
    }
    
    free(input);
}
