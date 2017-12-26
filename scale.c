#include <stdio.h>
#include <stdlib.h>
#include "bitmap.h"
#include <string.h>

/*
 * Main filter loop.
 */
void scale_filter(Bitmap *bmp) {

    Pixel *pix;
    Pixel row[bmp->width];

    for (int i = 0; i < bmp->height * bmp->scaleFactor; i++) {
	//
	if (i % bmp->scaleFactor == 0) {
	    fread(row, sizeof(Pixel), bmp->width, stdin);
	}

	for (int j = 0; j < bmp->width * bmp->scaleFactor; j++) {
	    pix = &(row[j / bmp->scaleFactor]);
	    fwrite(pix, sizeof(Pixel), 1, stdout);
	}
    }

    bmp->width *= bmp->scaleFactor;
    bmp->height *= bmp->scaleFactor;
}

int main(int argc, char **argv) {

    int scale_factor = strtol(argv[1], NULL, 10);
    run_filter(scale_filter, scale_factor);
    return 0;
}
