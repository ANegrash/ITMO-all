#ifndef ASSIGNMENT_IMAGE_ROTATION_STATUS_H
#define ASSIGNMENT_IMAGE_ROTATION_STATUS_H
enum status_type {
    READ = 0,
    WRITE,
    ROTATE
};

enum status_body {
    OK = 0,
    INVALID_HEADER,
    NULL_ERROR,
    CLOSE_ERROR,
    ERROR
};

struct file_status {
    enum status_type type;
    enum status_body body;
};

void print_status(struct file_status status);

#endif
