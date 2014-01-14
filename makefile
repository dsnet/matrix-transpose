all: bit_8 bit_16 bit_32 bit_64

bit_8:
	gcc -D COLOR -D BIT_WIDTH=8 -o transpose_8 matrix_transpose.c

bit_16:
	gcc -D COLOR -D BIT_WIDTH=16 -o transpose_16 matrix_transpose.c

bit_32:
	gcc -D COLOR -D BIT_WIDTH=32 -o transpose_32 matrix_transpose.c

bit_64:
	gcc -D COLOR -D BIT_WIDTH=64 -o transpose_64 matrix_transpose.c

clean:
	rm -rf transpose_*
