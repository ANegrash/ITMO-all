#include "fileio.h"
#include "image.h"
#include "status.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

struct file_status from_bmp(FILE *in, struct image *img);

struct file_status to_bmp(FILE *out, struct image const *img);
