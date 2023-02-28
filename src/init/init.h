#ifndef INIT_H
#define INIT_H

#define CMD_INPUT_SIZE 256

typedef struct config config;
struct config {
    char* root_cwd;
    char* tables_cwd;
};

void init();

static void change_root_cwd();

static void create_db_root_dir();

static int create_tables_dir();

int create_dir(char* dir_name,  int mode);

int console_exec();

#endif