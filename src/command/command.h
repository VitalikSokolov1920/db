#ifndef COMMAND_H
#define COMMAND_H

#include "command_types.h"

int parse_command(char* command);

int parse_cmd_args(int argc, char* argv[]);

int construct_command(char** cmd_parts, int len);

#endif