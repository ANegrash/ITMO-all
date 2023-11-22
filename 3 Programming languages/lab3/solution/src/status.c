#include "../include/status.h"
#include <stdio.h>
#include <stdlib.h>


static const char *const error_message_read_status[] = {
        [OK] = "Read successfully",
        [INVALID_HEADER] = "Invalid Header",
        [NULL_ERROR] = "Read Null",
        [ERROR] = "Error read file"
};
static const char *const error_message_write_status[] = {
        [OK] = "Write successfully",
        [INVALID_HEADER] = "Invalid Header",
        [NULL_ERROR] = "Write Null",
        [CLOSE_ERROR] = "Error close file",
        [ERROR] = "Error write file"
};
static const char *const error_message_rotate_status[] = {
        [OK] = "Image rotated",
        [ERROR] = "Function not found"
};

void print_status(struct file_status status) {
    const char *message;
    switch (status.type) {
        case READ:
            message = error_message_read_status[status.body];
            break;
        case WRITE:
            message = error_message_write_status[status.body];
            break;
        case ROTATE:
            message = error_message_rotate_status[status.body];
            break;
        default:
            message = error_message_read_status[status.body];
            break;
    }
    if (status.body) {
        fprintf(stderr, "%s\n", message);
        exit(1);
    }
    fprintf(stdout, "%s\n", message);
}
