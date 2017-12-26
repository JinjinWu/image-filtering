FLAGS = -Wall -std=gnu99 -g

all: copy greyscale gaussian_blur edge_detection scale image_filter

copy: copy.o bitmap.o
	gcc ${FLAGS} -o $@ $^ -lm

greyscale: greyscale.o bitmap.o
	gcc ${FLAGS} -o $@ $^ -lm

gaussian_blur: gaussian_blur.o bitmap.o
	gcc ${FLAGS} -o $@ $^ -lm

edge_detection: edge_detection.o bitmap.o
	gcc ${FLAGS} -o $@ $^ -lm

scale: scale.o bitmap.o
	gcc ${FLAGS} -o $@ $^ -lm

image_filter: image_filter.o
	gcc ${FLAGS} -o $@ $^ -lm

%.o: %.c bitmap.h
	gcc ${FLAGS} -c $<

clean:
	rm *.o image_filter copy greyscale gaussian_blur edge_detection scale

test:
	mkdir images -p
	./copy < dog.bmp > images/dog_copy.bmp

test2:
	mkdir images -p
	./greyscale < dog.bmp > images/dog_grey.bmp

test3:
	mkdir images -p
	./gaussian_blur < dog.bmp > images/dog_blur.bmp

test4:
	mkdir images -p
	./edge_detection < dog.bmp > images/dog_edges.bmp

test5:
	mkdir images -p
	./scale 2 < dog.bmp > images/dog_big.bmp
