#include <stdio.h>
#include <stdlib.h>
#include "bitmap.h"


/*
 * Main filter loop.
 * This function is responsible for doing the following:
 *   1. Read in pixels one at a time.
 *   2. Immediately write out each pixel.
 *
 * Note that this function should allocate space only for a single Pixel;
 * do *not* store more than one Pixel at a time, it isn't necessary here!
 */
void greyscale_filter(Bitmap *bmp) {
    // TODO: Complete this function.
    Pixel pix;
    unsigned char avg;

    for (int i = 0; i < bmp->height; i++) {
	for (int j = 0; j < bmp->width; j++) {
	    fread(&pix, sizeof(Pixel), 1, stdin);
	    avg = (pix.blue + pix.green + pix.red) / 3;
	    pix.blue = avg;
	    pix.green = avg;
	    pix.red = avg;
	    fwrite(&pix, sizeof(Pixel), 1, stdout);
	}
    }
}

int main() {
    // Run the filter program with copy_filter to process the pixels.
    // You shouldn't need to change this implementation.
    run_filter(greyscale_filter, 1);
    return 0;
}
