# image-filtering
Build a simple pipeline for manipulating bitmap image files by applying a set of common filters on images.
Read in pixel data from bitmap files and perform necessary transformations on the RBG values and write out the pixel data to an output file.
Use fork() and exec() to handle the filter in a new child process.
Pipe data into child process using pipe() calls.

Usage:
- Type "make" on command line to compile files.
- > ./image_filter [input_image.bmp] [output_image.bmp] [filter]
- > ./image_filter dog.bmp dog_grey.bmp greyscale
