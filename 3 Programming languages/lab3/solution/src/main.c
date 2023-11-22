#include "bmp.h"
#include "fileio.h"
#include "rotation.h"
#include <stdio.h>


int main(int argc, char **argv) {
    if (argc != 3) {
        fprintf(stderr, "./program <source> <destination>");
        return 0;
    }
    if (argc < 3) fprintf(stderr, "Not enough arguments \n");
    if (argc > 3) fprintf(stderr, "Too many arguments \n");

    printf("Input: %s\n", argv[1]);
    printf("Output: %s\n", argv[2]);

    struct image img;
    FILE *in = NULL;
    FILE *out = NULL;

    print_status(open_file(&in, argv[1], "rb"));
    print_status(open_file(&out, argv[2], "wb"));
    print_status(from_bmp(in, &img));
    print_status(close_file(&in));

    struct image res = rotate(img);
    delete_image(&img);

    print_status(to_bmp(out, &res));
    print_status(close_file(&out));
    delete_image(&res);


    return 0;
}
