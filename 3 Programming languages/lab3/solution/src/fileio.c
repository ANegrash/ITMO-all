#include "../include/fileio.h"

struct file_status open_file(FILE **file, const char *name, const char *mode) {
    if (file != NULL) {
        *file = fopen(name, mode);
        if(*file == NULL) return (struct file_status){.type = READ, .body = NULL_ERROR};
    }
    return (struct file_status){.type = READ, .body = OK};
}

struct file_status close_file(FILE **file) {
    if (*file) {
        if (fclose(*file) == 0) return (struct file_status) {.type = WRITE, .body = OK};
    }
    return (struct file_status) {.type = WRITE, .body = CLOSE_ERROR};
}
