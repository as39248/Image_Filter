#include <stdio.h>
#include <stdlib.h>
#include "bitmap.h"




void greyscale_filter(Bitmap *bmp) {
   
    


    for (int i = 0; i < bmp->height; i++){
        for (int j = 0; j < bmp->width; j++){


            int grey;
            Pixel *pix = malloc(sizeof(Pixel));
            fread(pix, sizeof(Pixel), 1, stdin);
            grey = (pix->blue + pix->green + pix->red) / 3;
            pix->blue = grey;
            pix->green = grey;
            pix->red = grey;
            fwrite(pix, sizeof(Pixel), 1, stdout);
            free(pix);
        }
    }
    

    
}

int main() {
    
    run_filter(greyscale_filter, 1);
    return 0;
}