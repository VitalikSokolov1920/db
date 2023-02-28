cmake_minimum_required(VERSION 3.16)

project(main)

add_compile_options(-g -O0 -W)

add_executable(${PROJECT_NAME} 
    main.c
    src/tables/add/add_table.c
    src/tables/add/add_table.h
    src/tables/find/find_table.c
    src/tables/find/find_table.h
    src/init/init.c
    src/init/init.h
    src/parse_string/parse_s.c
    src/parse_string/parse_s.h
    src/command/command_types.h
    src/command/command.c
    src/command/command.h
)
