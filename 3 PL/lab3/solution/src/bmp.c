#include "bmp.h"

#define BMP_TYPE 0x4D42
#define BMP_SIZE 40
#define BMP_PLANES 1
#define BMP_BIT_COUNT 24

typedef struct __attribute__((packed)) {
    uint16_t bfType;
    uint32_t bfileSize;
    uint32_t bfReserved;
    uint32_t bOffBits;
    uint32_t biSize;
    uint32_t biWidth;
    uint32_t biHeight;
    uint16_t biPlanes;
    uint16_t biBitCount;
    uint32_t biCompression;
    uint32_t biSizeImage;
    uint32_t biXPelsPerMeter;
    uint32_t biYPelsPerMeter;
    uint32_t biClrUsed;
    uint32_t biClrImportant;
} bmp_header;


static void bmp_header_print(const bmp_header *header, FILE *f) {
    fprintf(f, "File size: %d\n", header->bfileSize);
    fprintf(f, "Width: %d\n", header->biWidth);
    fprintf(f, "Height: %d\n", header->biHeight);
}

static bool bmp_header_write_to_file(const bmp_header *header, FILE *f) {
    if (f) {
        size_t s = fwrite(header, sizeof(bmp_header), 1, f);
        fprintf(stderr, "%zu\n", s);
        if (s == 1) {
            fprintf(stderr, "Succes write header\n");
            return true;
        }
    }
    return false;
}

static bool read_header(FILE *f, bmp_header *header) {
    return fread(header, sizeof(bmp_header), 1, f);
}

static bool bmp_header_read_from_file(FILE *f, bmp_header *header) {
    if (!f) return false;
    if (read_header(f, header)) {
        return true;
    }
    return false;
}

static bmp_header bmp_header_create(struct image const *img) {
    printf("Header created\n");
    bmp_header Header = (bmp_header) {0};
    Header.bfType = BMP_TYPE;
    Header.biWidth = img->width;
    Header.biHeight = img->height;
    Header.bfileSize = Header.biWidth * Header.biHeight * sizeof(struct pixel) + sizeof(Header);
    Header.biSize = BMP_SIZE;
    Header.bOffBits = sizeof(bmp_header);
    Header.biPlanes = BMP_PLANES;
    Header.biBitCount = BMP_BIT_COUNT;
    Header.bfReserved = 0;
    Header.biCompression = 0;
    Header.biSizeImage = Header.biWidth * Header.biHeight * sizeof(struct pixel);
    Header.biXPelsPerMeter = 0;
    Header.biYPelsPerMeter = 0;
    Header.biClrUsed = 0;
    Header.biClrImportant = 0;
    return Header;
}

static size_t calc_padding(size_t width) {
    const size_t p = 4 - width * sizeof(struct pixel) % 4;
    if (p == 4) return 0;
    return p;
}

static bool
bmp_pixel_read_from_file(size_t *readed, struct pixel *pix, FILE *in, struct image *img, size_t i, size_t j) {
    size_t r = fread(pix, sizeof(struct pixel), 1, in);
    if (!r) {
        return false;
    }
    *readed = *readed + r;
    img->data[i * (img->width) + j] = *pix;
    return true;
}

struct file_status from_bmp(FILE *in, struct image *img) {
    if (!in) {
        return (struct file_status) {.type = READ, .body = NULL_ERROR};
    }
    bmp_header h = {0};
    if (bmp_header_read_from_file(in, &h)) {
        bmp_header_print(&h, stderr);
    } else {
        return (struct file_status) {.type=READ, .body=INVALID_HEADER};
    }

    *img = create_image(h.biWidth, h.biHeight);

    size_t width_padding = calc_padding(img->width);
    fprintf(stderr, "Padding read: %zu\n", width_padding);
    for (uint64_t i = 0; i < img->height; ++i) {
        size_t readed = 0;
        struct pixel *pix = &(struct pixel) {0};
        for (int j = 0; j < img->width; ++j) {
            bool b = bmp_pixel_read_from_file(&readed, pix, in, img, i, j);
            if (!b) {
                return (struct file_status) {.type=READ, .body=ERROR};
            }
        }
        if (width_padding) {
            size_t r = fread(&h, 1, width_padding, in); // Not the best variant, but i didn't need here and after bmp header
            if (!r) {
                return (struct file_status) {.type=READ, .body=ERROR};
            }
        }
    }
    fprintf(stderr, "Read end\n");
    return (struct file_status) {.type=READ, .body=OK};
}

static bool bmp_pixel_write_to_file(FILE *out, struct pixel p) {
    size_t s = fwrite(&p, sizeof(struct pixel), 1, out);
    if (s == 1) {
        return true;
    }
    return false;
}

struct file_status to_bmp(FILE *out, struct image const *img) {
    bmp_header b_h = bmp_header_create(img);
    bmp_header_print(&b_h, stderr);
    if (!bmp_header_write_to_file(&b_h, out)) {
        return (struct file_status) {.type=WRITE, .body=ERROR};
    }

    size_t width_padding = calc_padding(img->width);
    fprintf(stderr, "Padding: %zu\n", width_padding);
    for (size_t i = 0; i < img->height; ++i) {
        for (size_t j = 0; j < img->width; ++j) {
            bool b = bmp_pixel_write_to_file(out, img->data[i * (img->width) + j]);
            if (!b) {
                return (struct file_status) {.type=WRITE, .body=ERROR};
            }
        }
        size_t s = fwrite(&i, 1, width_padding, out);
        if (s != width_padding) {
            return (struct file_status) {.type=WRITE, .body=ERROR};
        }
    }
    return (struct file_status) {.type=WRITE, .body=OK};
}
