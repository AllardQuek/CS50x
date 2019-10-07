# Questions

## What's `stdint.h`?

A library

## What's the point of using `uint8_t`, `uint32_t`, `int32_t`, and `uint16_t` in a program?

uint means unsigned integer. Tells program the number of bits the datatype takes up.

## How many bytes is a `BYTE`, a `DWORD`, a `LONG`, and a `WORD`, respectively?

1byte, 4bytes, 4bytes, 2bytes

## What (in ASCII, decimal, or hexadecimal) must the first two bytes of any BMP file be? Leading bytes used to identify file formats (with high probability) are generally called "magic numbers."

0x4d42 (WORD bfType)

## What's the difference between `bfSize` and `biSize`?

bfSize is the size, in bytes, of the bitmap file whereas biSize is the number of bytes required by the structure, such as BITMAPINFOHEADER

## What does it mean if `biHeight` is negative?

biHeight is the height of the bitmap in pixels. If biHeight is negative, the bitmap is a top-down DIB and its origin is the upper-left corner.

## What field in `BITMAPINFOHEADER` specifies the BMP's color depth (i.e., bits per pixel)?

biBitCount

## Why might `fopen` return `NULL` in lines 24 and 32 of `copy.c`?

When a pointer is created and its value is not assigned immediately, or is assigned NULL, hence it points to nothing.

## Why is the third argument to `fread` always `1` in our code?

We are reading only a quantity of 1 thing at a time and storing it temporarily in an address.

## What value does line 65 of `copy.c` assign to `padding` if `bi.biWidth` is `3`?

(4 - 3 * 3 % 4) % 4 = 3 % 4 = 3

## What does `fseek` do?

Allows you to rewind or fastforward your position (byte you're at) in a file.

## What is `SEEK_CUR`?

Your current position in the file.

## Whodunit?

It was
Professor Plum
with the candlestick
in the library.
