#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bitmap.h"


void scale_filter(Bitmap *bmp){

	int new_width;
	int new_height;

    memcpy(&new_width, &bmp->header[BMP_WIDTH_OFFSET], sizeof(int));
    memcpy(&new_height, &bmp->header[BMP_HEIGHT_OFFSET], sizeof(int));


    int scale_factor = new_height / bmp->height;
    
   

    for (int i = 0; i < bmp->height; i++){
    	Pixel *row = malloc(sizeof(Pixel) * new_width);
    	int position = 0;
        for (int j = 0; j < bmp->width; j++){
        	int icounter = 0;
        	

            Pixel *pix = malloc(sizeof(Pixel));
            fread(pix, sizeof(Pixel), 1, stdin);
            while(icounter != scale_factor){
            	memcpy(&row[position], pix, sizeof(Pixel));
            	icounter++;
            	position ++;
            }
            
            free(pix);
        }
        int ocounter = 0;
        while(ocounter != scale_factor){
        	fwrite(row, sizeof(Pixel), new_width, stdout);
        	ocounter++;
        }
        free(row);

    }

}


int main(int argc, char* argv[]) {
    int scale;
    char *ptr;
    scale = strtol(argv[1], &ptr, 10);
    run_filter(scale_filter, scale);
    return 0;
}