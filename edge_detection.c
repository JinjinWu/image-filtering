#include <stdio.h>
#include <stdlib.h>
#include "bitmap.h"

/*
 * Main filter loop.
 */
void edge_detection_filter(Bitmap *bmp) {

    Pixel pix;
    Pixel row0[bmp->width];
    Pixel row1[bmp->width];
    Pixel row2[bmp->width];

    fread(row0, sizeof(Pixel), bmp->width, stdin);
    fread(row1, sizeof(Pixel), bmp->width, stdin);
    fread(row2, sizeof(Pixel), bmp->width, stdin);

    Pixel *a;
    Pixel *b;
    Pixel *c;
    Pixel *temp;

    a = row0;
    b = row1;
    c = row2;

    int k;

    for (int i = 0; i < bmp->height; i++) {

	for (int j = 0; j < bmp->width; j++) {
	    if (j == 0) {
		k = 1;
	    } else if (j == (bmp->width - 1)) {
		k = bmp->width - 2;
	    } else {
		k = j;
	    }
	    pix = apply_edge_detection_kernel(a + k - 1, b + k - 1, c + k - 1);
	    fwrite(&pix, sizeof(Pixel), 1, stdout);
	}

	if (i == 0 || i >= bmp->width - 2) {
	    continue;
	}

	temp = a;
	a = b;
	b = c;
	fread(temp, sizeof(Pixel), bmp->width, stdin);
	c = temp;

    }
}

int main() {
    // Run the filter program with copy_filter to process the pixels.
    // You shouldn't need to change this implementation.
    run_filter(edge_detection_filter, 1);
    return 0;
}
