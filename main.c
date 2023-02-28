#include <unistd.h>
#include <stdio.h>
#include <string.h>

#include "src/init/init.h"

#include "src/tables/add/add_table.h"
#include "src/command/command.h"
#include "src/command/command_types.h"

#define DEBUG 0

void f() {    //012345678901234567
    printf("%lu\n", sizeof(void*));
}

int main(int agrc, char* argv[]) {
#if DEBUG
    f();
#endif
#if !DEBUG
    init();

    int ret;

    if (agrc < 2) {
        ret = console_exec();
    } else {
        ret = parse_cmd_args(agrc - 1, argv + 1);
    }
#endif
    
    return 0;
}