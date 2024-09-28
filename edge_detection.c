#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bitmap.h"




void edge_detection_filter(Bitmap *bmp) {
    
    
    
    Pixel *row0 = malloc(sizeof(Pixel) * bmp->width);
    Pixel *row1 = malloc(sizeof(Pixel) * bmp->width);
    Pixel *row2 = malloc(sizeof(Pixel) * bmp->width);
    Pixel *pix = malloc(sizeof(Pixel));
    Pixel *new_row = malloc(sizeof(Pixel) * bmp->width);
    Pixel *new = malloc(sizeof(Pixel));
    Pixel *r0 = malloc(sizeof(Pixel) * 3);
    Pixel *r1 = malloc(sizeof(Pixel) * 3);
    Pixel *r2 = malloc(sizeof(Pixel) * 3);

    for(int i = 0; i < bmp->height; i++){

        if (i == 0){
            
            // row 0 
            int position = 0;
        
            for (int a = 0; a < bmp->width; a++){
                fread(pix, sizeof(Pixel), 1, stdin);
                memcpy(&row0[position], pix, sizeof(Pixel));
                position ++;
            }
        
            // row 1
            position = 0;
        
            for (int b = 0; b < bmp->width; b++){
                fread(pix, sizeof(Pixel), 1, stdin);
                memcpy(&row1[position], pix, sizeof(Pixel));
                position ++;
            }

            // row 2
            position = 0;
        
            for (int c = 0; c < bmp->width; c++){
                fread(pix, sizeof(Pixel), 1, stdin);
                memcpy(&row2[position], pix, sizeof(Pixel));
                position ++;
            }
        }

        else if (i != 1 || i != bmp->height - 2){
            memcpy(row0, row1, sizeof(Pixel) * bmp->width);
            memcpy(row1, row2, sizeof(Pixel) * bmp->width);

            int position = 0;
        
            for (int d = 0; d < bmp->width; d++){
                fread(pix, sizeof(Pixel), 1, stdin);
                memcpy(&row2[position], pix, sizeof(Pixel));
                position ++;
            }
        }

        
        int pos = 0;
        for (int j = 1; j < bmp->width - 1; j++){
            
            memcpy(r0, &row0[j - 1], sizeof(Pixel) * 3);
            memcpy(r1, &row1[j - 1], sizeof(Pixel) * 3);
            memcpy(r2, &row2[j - 1], sizeof(Pixel) * 3);

            *new = apply_edge_detection_kernel(r0, r1, r2);

            if(j == 1 || j == bmp->width - 2) {
                memcpy(&new_row[pos], new, sizeof(Pixel));
                pos ++;
                
            }
            memcpy(&new_row[pos], new, sizeof(Pixel));
            pos ++;
           
        }

        fwrite(new_row, sizeof(Pixel) * bmp->width, 1, stdout);
        if (i == 1 || i == bmp->height - 2){
            fwrite(new_row, sizeof(Pixel) * bmp->width, 1, stdout);
            i++;
        }

    }
    free(pix);
    free(row0);
    free(row1);
    free(row2);
    free(new_row);
    free(new);
    free(r0);
    free(r1);
    free(r2);
    
}

int main() {
    
    run_filter(edge_detection_filter, 1);
    return 0;
}