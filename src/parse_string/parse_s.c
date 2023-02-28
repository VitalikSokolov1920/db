


#include <malloc.h>
#include <string.h>

#include "parse_s.h"

/*input: <str> <str> <str>*/
char** split(const char* str, size_t len, const char split_by, size_t* res_len) {
    if (!len) {
        return NULL;
    }

    char** res;
    size_t real_len;

    *res_len = (len / 2) + 1;

    res = (char**)malloc(sizeof(char*) * (*res_len));
    for (int i = 0, k = 0, idx = 0; i < len; i++) {
        if ((*(str + i) == split_by) || (i + 1 == len)) {
            *(res + idx) = (char*)malloc(sizeof(char) * ((i - k)) + 1);

            real_len++;

            if (i + 1 == len) {
                strncpy(*(res + idx), str + k, i - k + 1);
            } else {
                strncpy(*(res + idx), str + k, i - k);
            }

            k = i + 1;
            idx++;
        }
    }

    if (real_len < *res_len) {
        res = realloc(res, sizeof(char*) * real_len);

        *res_len = real_len;
    }

    return res;
}

/*
-1 - empty string
0 - ok
*/
char* trim(char* str, size_t len) {
    size_t start_str = 0, end_str = len - 1;

    for (int i = 0, j = len - 1; i < j; i++, j--) {
        if (*(str + i) == ' ') {
            start_str++;
            len--;
        }
        if (*(str + j) == ' ') {
            end_str--;
            len--;
        }
    }

    if (start_str >= end_str) {
        if (*(str + start_str) == ' ') {
            return EMPTY_STRING;
        }
    }

    char* new_str = (char*)malloc(sizeof(char) * len + 1);

    if (!new_str) {
        return EMPTY_STRING;
    }

    strncpy(new_str, str + start_str, len);

    *(new_str + len) = '\0';

    return new_str;
}

char* trim_between(char* str, size_t len) {
    char* new_str;

    new_str = (char*)malloc(sizeof(char) * len + 1);

    if (!new_str) {
        return EMPTY_STRING;
    }

    /*
    i0123456789
    "asd    asd"
    "asd asd"
     012345678901234567
    "String  String asd"
     ++++++++++++++             
    new_str_cur_pos = 14
    word_start = 15
    i = 
    */
    int word_start = 0, new_str_cur_pos = 0;
    for (int i = 0; i < len; i++) {
        if (i + 1 == len) {
            strncpy(new_str + new_str_cur_pos, str + word_start, i - word_start + 1);
        }
        if (*(str + i) == ' ') {
            strncpy(new_str + new_str_cur_pos, str + word_start, i - word_start + 1);

            new_str_cur_pos += i - word_start + 1;

            int space_count = 0;

            while (*(str + i + space_count) == ' ') {
                space_count++;
            }

            word_start = i + space_count;

            i += space_count - 1;
        } else {
            continue;
        }
    }

    *(new_str + len) = '\0';

    return new_str;
}