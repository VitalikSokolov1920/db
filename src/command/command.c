


#include <string.h>
#include <stdio.h>

#include "../parse_string/parse_s.h"
#include "command.h"

int parse_command(char* cmd) {
    size_t len;
    int ret;

    len = strlen(cmd);

    char* trim_cmd = trim(cmd, len);

    if (trim_cmd == EMPTY_STRING) {
        return -1;
    }

    len = strlen(trim_cmd);

    char* trim_all_cmd = trim_between(cmd, len);

    if (trim_all_cmd == EMPTY_STRING) {
        return -1;
    }

    len = strlen(trim_all_cmd);

    size_t parts_amount = 0;

    char** cmd_parts = split(trim_all_cmd, len, ' ', &parts_amount);

    if (!cmd_parts) {
        return -1;
    }

    construct_command(cmd_parts, parts_amount);

    return 0;
}
// "create table my_table ()"
int construct_command(char** cmd_parts, int len) {
    
}

int parse_cmd_args(int argc, char* argv[]) {

}