# Bit-Matrix Transpose #

## Introduction ##

![matrix-transpose-intro](http://code.digital-static.net/matrix-transpose/raw/tip/doc/matrix-transpose-intro.png)

This code was written to test an algorithm to perform transpose on a bit-matrix.
In this example, the transpose is performed by swapping all bits in a square
bit-matrix across the top-right to bottom-left diagonal.

The application of this is in embedded applications to take advantage of a
modulation technique called
[Binary Code Modulation](http://www.batsocks.co.uk/readme/art_bcm_1.htm). This
technique allows the value of a register to control the duty-cycle and only
requires a single hardware timer to control multiple outputs.

Thus in BCM usage, imagine that 8x 8-bit registers contains the values of the
intended output duty-cycle for 8x output pins. The problem is that when
outputting the values, the lowest bit of each register should be written
together to the output, followed by the second lowest bit, and so on.
The naive way of doing this by masking and shifting one bit at a time would be
far too inefficient. Thus, by coming up with an efficient way to do bit-matrix
transposes, we can transform the values in the registers such that the first
register now contains the lowest bit of all outputs, the second register
contains the second lowest bit of all outputs, and so on. Now, all that needs
to be done is to write each register to the output whenever the hardware timer
triggers an interrupt.

## Theory ##

This technique exploits the fact that an 8-bit microcontroller almost always has
an 8-bit ALU. Rather than using bit-shifts and bit-masks to transpose one bit
at a time, the ALU is used to shift 8-bits at a time. Note that the number of
swap operation does not go down, but rather this method exploits a form of
parallelism by utilizing the properties of the hardware.

The code example commited is generalized to operate on any n-bit matrix. Since
modern processors are now 64-bit, this allows efficient transposing of 8b, 16b,
32b, and 64b square bit-matrices. The operational complexity to perform a
transpose is _O(n\*log(n))_ as opposed to _O(n\*n)_ without this method.

![matrix-transpose-method](http://code.digital-static.net/matrix-transpose/raw/tip/doc/matrix-transpose-method.png)

## References ##

* [Binary code modulation](http://www.batsocks.co.uk/readme/art_bcm_1.htm)
