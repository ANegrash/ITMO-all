#ifndef IMAGE_H
#define IMAGE_H

#include <inttypes.h>
#include <stddef.h>

struct __attribute__((packed)) pixel{
uint8_t b, g, r;
};

struct image {
    uint64_t width, height;
    struct pixel *data;
};

struct image create_image(size_t width, size_t height);

void delete_image(struct image *img);

#endif
