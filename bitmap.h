#ifndef BITMAP_H_
#define BITMAP_H_

// Use the following offsets to index into the `header`
// field of the Bitmap struct.
#define BMP_FILE_SIZE_OFFSET 2
#define BMP_HEADER_SIZE_OFFSET 10
#define BMP_WIDTH_OFFSET 18
#define BMP_HEIGHT_OFFSET 22

typedef struct {
    unsigned char blue;
    unsigned char green;
    unsigned char red;
} Pixel;

typedef struct {
    int headerSize;          // The size of the header.
    unsigned char *header;   // The contents of the image header.
    int width;               // The width of the image, in pixels.
    int height;              // The height of the image, in pixels.
} Bitmap;


/*
 * The "main" function.
 *
 * Run a given filter function, and apply a scale factor if necessary.
 * You don't need to modify this function to make it work with any of
 * the filters for this assignment.
 */
void run_filter(void (*filter)(Bitmap *), int scale_factor);

// Macros and functions for performing the two multi-row filters.
#define max(a,b) ((a) > (b) ? (a) : (b))
#define min(a,b) ((a) < (b) ? (a) : (b))
#define square(a) ((a) * (a))


/*
 * Functions for the row-buffered filters ("convolutions")
 * -------------------------------------------------------
 *
 * row0, row1, and row2 are interpreted as Pixel arrays of length 3.
 * Together, they represent the three rows of a 3-by-3 pixel grid
 * whose middle pixel is the one being transformed.
 *
 * These functions return the transformed pixel value of the middle pixel
 * when applying the corresponding transformation (a gaussian blur or
 * an edge detection operation), using the pixel values in the 3-by-3 grid.
 *
 * You aren't responsible for the calculations themselves, only for calling
 * these functions properly on pointers representing the 3-by-3 grids.
 *
 * Note that these functions should be called *once per pixel in the image*;
 * the returned Pixel values can be immediately written to stdout.
 */
Pixel apply_gaussian_kernel(Pixel *row0, Pixel *row1, Pixel *row2);
Pixel apply_edge_detection_kernel(Pixel *row0, Pixel *row1, Pixel *row2);

#endif /* BITMAP_H_*/
