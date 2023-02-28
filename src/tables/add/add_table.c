#include <sys/types.h>
#include <sys/stat.h>

#include <stdio.h>
#include <fcntl.h>
#include <malloc.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

#include "add_table.h"
#include "../find/find_table.h"

int add_table(char* table_name, table_col* cols[], size_t len) {
    int ret, fd;

    ret = find_table(table_name);

    if (ret == -1) {
        printf("Не удалось создать таблицу %s\n", table_name);

        return -1;
    } else if (ret == 1) {
        printf("Таблица %s уже существует\n", table_name);

        return -1;
    }

    char* table_path = (char*) malloc(strlen(table_name) + strlen("./tables/") + 1);

    table_path = strcat("./tables/", table_name);

    fd = open(table_path,
              O_RDWR | O_CREAT | O_EXCL | O_SYNC | O_CLOEXEC,
              S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);

    if (fd == -1) {
        if (errno == EEXIST) {
            printf("Таблица с именем %s уже существует\n", table_name);

            return -1;
        } else {
            perror("create table");

            return -1;
        }
    }

    struct stat finfo;
    long block_size;

    ret = fstat(fd, &finfo);

    if (ret == -1) {
        block_size = DEF_BLK_SIZE;
    } else {
        block_size = finfo.st_blksize;
    }

    char table_struct[block_size];

    memset(table_struct, '\0', block_size);

    /* name:type|name:type|...|name:type */
    char* name, *type, *separator = SEP, *separator_col = SEP_COL;

    int i = 0;

    for (int j = 0, len; j < len; j++) {
        name = cols[j]->name;

        len = strlen(name);
        
        copy_data_to_table_struct(&i, name, len, table_struct, block_size, fd);
        copy_data_to_table_struct(&i, separator, SEP_LEN, table_struct, block_size, fd);

        type = cols[j]->type;

        len = strlen(type);

        copy_data_to_table_struct(&i, type, len, table_struct, block_size, fd);
        copy_data_to_table_struct(&i, separator_col, SEP_COL_LEN, table_struct, block_size, fd);
    }

    if (i) {
        write_to_file(table_struct, i, fd);
    }

    return 0;
}

int copy_data_to_table_struct(int * cur_pos, const char* data, int data_len, char* table_struct, int block_size, int fd) {
    int ret;

    if (*cur_pos + data_len > block_size) {
        size_t diff = block_size - *cur_pos;

        strncpy(table_struct + *cur_pos, data, diff);

        ret = write_to_file(table_struct, block_size, fd);

        memset(table_struct, '\0', block_size);

        *cur_pos = 0;

        strncpy(table_struct, data + diff, data_len - diff);

        *cur_pos += data_len - diff;

        if (ret == -1) {
            printf("Ошибка при сохранении таблицы\n");

            return -1;
        }
    } else {
        strcpy(table_struct + *cur_pos, data);

        *cur_pos += data_len;
    }
}

int write_to_file(char* buf, size_t len, int fd) {
    int ret;

    while (len && (ret = write(fd, buf, len))) {
        if (ret == -1) {
            if (errno == EINTR) {
                continue;
            }

            return -1;
        }

        len -= ret;
        buf += ret;
    }

    return 0;
}

