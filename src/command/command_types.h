#ifndef COMMAND_TYPES_H
#define COMMAND_TYPES_H

#include "../tables/add/add_table.h"

typedef void*(*create_handler_t)(char*, table_col*, size_t);

/*
CREATE, ALTER, DROP
*/
typedef struct DDL DDL;
struct DDL {
    create_handler_t create_handler;
};

/*
SELECT, INSERT, UPDATE, DELETE
*/
typedef struct DML DML;
struct DML {

};

typedef struct DCL DCL;
struct DCL {

};

typedef struct command command;
struct command {
    DDL ddl_family;
    DML dml_family;
    DCL dcl_family;
};

#endif