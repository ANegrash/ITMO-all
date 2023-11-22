#include "rotation.h"

//x - num of column, y - num of row
void set_pixel(const struct pixel p, struct image const *img, const uint64_t x, const uint64_t y) {
    (img->data)[y * img->width + x] = p;
}

struct pixel get_pixel(const struct image *img, const uint64_t x, const uint64_t y) {
    return (img->data)[y * img->width + x];
}

//clockwise rotate
struct image rotate(struct image const source) {
    struct image result = create_image(source.height, source.width); // rotate sizes
    for (uint64_t i = 0; i < source.height; ++i) {
        for (uint64_t j = 0; j < source.width; ++j) {
            struct pixel p =get_pixel(&source, j, i);
            set_pixel(p, &result, (source.height-1)-i, j);
        }
    }
    return result;
}
