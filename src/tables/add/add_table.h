#ifndef ADD_TABLE_H
#define ADD_TABLE_H

#include <stddef.h>

#define SEP_LEN 1
#define SEP_COL_LEN 1
#define SEP ":"
#define SEP_COL "|"

typedef struct table_col table_col;
struct table_col {
    char* name;
    char* type;
};

int add_table(char*, table_col*[], size_t);

int write_to_file(char* buf, size_t len, int fd);

int copy_data_to_table_struct(int * i, const char* data, int data_len, char* table_struct, int block_size, int fd);

#endif