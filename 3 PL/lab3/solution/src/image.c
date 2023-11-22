#include "image.h"
#include <stdio.h>
#include <stdlib.h>


struct image create_image(const size_t width, const size_t height) {
    struct image result;
    fprintf(stderr,"Creating image: width: %zu , height: %zu\n", width, height);
    if (width * height == 0) {
        result = (struct image) {.height=height, .width=width, .data=NULL};
    } else {
        result = (struct image) {.height=height, .width=width, .data=malloc(sizeof(struct pixel) * width * height)};
        fprintf(stderr,"DataInImage: %" SCNu64 "\n", (uint64_t) result.data);
    }
    return result;
}

//Clear memory from "image"
void delete_image(struct image *img) {
    if(img){
        if(img->data){
            free(img->data);
        }
    }
}
