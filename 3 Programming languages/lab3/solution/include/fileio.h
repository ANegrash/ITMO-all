#ifndef ASSIGNMENT_IMAGE_ROTATION_FILEIO_H
#define ASSIGNMENT_IMAGE_ROTATION_FILEIO_H
#include "status.h"
#include <stdio.h>


struct file_status open_file(FILE **file, const char *name, const char *mode);
struct file_status close_file(FILE **file);

#endif
