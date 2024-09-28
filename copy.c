#include <stdio.h>
#include <stdlib.h>
#include "bitmap.h"


/*
 * Main filter loop.
 * This function is responsible for doing the following:
 *   1. Read in pixels one at a time (because copy is a pixel-by-pixel transformation).
 *   2. Immediately write out each pixel.
 *
 * Note that this function should allocate space only for a single Pixel;
 * do *not* store more than one Pixel at a time, it isn't necessary here!
 */
void copy_filter(Bitmap *bmp) {
    
    

    for (int i = 0; i < bmp->height; i++){
        for (int j = 0; j < bmp->width; j++){

            Pixel *pix = malloc(sizeof(Pixel));
            fread(pix, sizeof(Pixel), 1, stdin);
            fwrite(pix, sizeof(Pixel), 1, stdout);
            free(pix);
        }
    }
    
}

int main() {
    // Run the filter program with copy_filter to process the pixels.
    // You shouldn't need to change this implementation.
    run_filter(copy_filter, 1);
    return 0;
}