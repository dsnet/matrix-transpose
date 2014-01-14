// Written in 2012 by Joe Tsai <joetsai@digital-static.net>
//
// ===================================================================
// The contents of this file are dedicated to the public domain. To
// the extent that dedication to the public domain is not available,
// everyone is granted a worldwide, perpetual, royalty-free,
// non-exclusive license to exercise all rights associated with the
// contents of this file for any purpose whatsoever.
// No rights are reserved.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
// EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
// NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
// BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
// ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
// CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
// ===================================================================

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>


#if COLOR
    #define CODE1   "\033[1;33m"
    #define CODE0   "\033[1;30m"
    #define RESET   "\033[0m"
#else
    #define CODE1   ""
    #define CODE0   ""
    #define RESET   ""
#endif


#if BIT_WIDTH == 8
    typedef uint8_t uintX;
#elif BIT_WIDTH == 16
    typedef uint16_t uintX;
#elif BIT_WIDTH == 32
    typedef uint32_t uintX;
#elif BIT_WIDTH == 64
    typedef uint64_t uintX;
#endif
uintX bit_matrix[BIT_WIDTH];


void matrix_transpose(uintX* matrix);
void matrix_swap(uintX matrix[], int width, uintX mask);
void matrix_print(uintX matrix[]);


int main() {
    // Get random data for the bit matrix
    int scan;
    srand(time(NULL));
    for (scan = 0; scan < sizeof(uintX)*sizeof(uintX)*8; scan++) {
        ((uint8_t*)bit_matrix)[scan] = rand();
    }

    // Perform bit transpose
    printf("Before tranpose:\n");
    matrix_print(bit_matrix);

    matrix_transpose(bit_matrix);

    printf("After tranpose:\n");
    matrix_print(bit_matrix);

    return 0;
}


// Perform a bit matrix tranpose along the upper-right to lower-left diagonal.
void matrix_transpose(uintX matrix[]) {
    int swap_width = sizeof(uintX)*8;
    uintX swap_mask = ((uintX)(-1));
    while (swap_width != 1) {
        swap_width >>= 1;
        swap_mask = swap_mask ^ (swap_mask >> swap_width);
        matrix_swap(matrix, swap_width, swap_mask);
    }
}


// Swap blocks within the bit matrix.
void matrix_swap(uintX matrix[], int width, uintX mask) {
    int inner, outer;
    for (outer = 0; outer < (sizeof(uintX)*8)/(width*2); outer++) {
        for (inner = 0; inner < width; inner++)         {
            uintX* x = &matrix[(inner) + (outer*width*2)];
            uintX* y = &matrix[(inner+width) + (outer*width*2)];

            *x = ((*y << width) & mask) ^ *x;
            *y = ((*x & mask) >> width) ^ *y;
            *x = ((*y << width) & mask) ^ *x;
        }
    }
}


// Pretty print the bit matrix in binary form.
void matrix_print(uintX matrix[]) {
    int inner, outer;
    uintX sig_mask = (uintX)1 << ((sizeof(uintX)*8)-1);
    for (outer = 0; outer < sizeof(uintX)*8; outer++) {
        uintX pattern = matrix[outer];
        for (inner = 0; inner < sizeof(uintX)*8; inner++) {
            if (pattern & sig_mask)
            { printf("%s1 ",CODE1); }
            else
            { printf("%s0 ",CODE0); }
            pattern <<= 1;
        }
        printf("%s\n",RESET);
    }
    printf("\n");
}
