#ifndef PARSE_S_H
#define PARSE_S_H

#include <stddef.h>

#define EMPTY_STRING (char*)(-1)

char** split(const  char*, size_t len, const char split_by, size_t* res_len);

char* trim(char* str, size_t len);

char* trim_between(char* str, size_t len);

#endif