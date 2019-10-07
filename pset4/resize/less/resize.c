// Copies a BMP file

#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: copy infile outfile\n");
        return 1;
    }

    // remember filenames
    char *factor = argv[1];
    char *infile = argv[2];
    char *outfile = argv[3];
    int n = atoi(argv[1]); //where n is the factor

    if (n <= 0 || n > 100)
    {
        fprintf(stderr, "Factor n must be a postive integer AND less than or equal to 100.\n");
        return 1;
    }

    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    //update outfile header info
    //FILE--> file size: bfSize (size in bytes of bitmap file, NOT biSize which is no. of bytes req by STRUCTURE)
    //total size of file in bytes: bf.bfSize = bi.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER); i.e fileheader + infoheader + wholeimage

    //INFO--> image size: biSizeImage, width: biWidth, height: biHeight)
    //size of image in bytes including pixels AND padding: bi.biSizeImage = ((sizeof(RGBTRIPLE) * bi.biWidth) + padding) * abs(bi.biHeight) ; i.e hori x vert

    int oldbiWidth = bi.biWidth;
    int oldbiHeight = bi.biHeight;

    // NEW: update width and height
    bi.biWidth *= n;
    bi.biHeight *= n;

    // determine padding for scanlines
    int oldpadding = (4 - (oldbiWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int newpadding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    bi.biSizeImage = ((sizeof(RGBTRIPLE) * bi.biWidth) + newpadding) * abs(bi.biHeight);
    bf.bfSize = bi.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);




    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);


    //DONE: open files for r/w, update header's info for outfile


    //create array of type RGBTRIPLE so that pixels can be stored in it temporarily first before finally writing the contents to the outfiles
    RGBTRIPLE *array = malloc(bi.biWidth * sizeof(RGBTRIPLE));
    //check if pointer returned is NULL, if true exit program
    if (array == NULL)
    {
        fprintf(stderr, "pointer array assigned NULL pointer, i.e pointing to nothing");
        return 5;
    }

    //for EACH ROW
    for (int i = 0, biHeight = abs(oldbiHeight); i < biHeight; i++)
    {
        int t = 0;
        //for EACH PIXEL in infile, i.e oldwidth
        for (int j = 0; j < oldbiWidth; j++)
        {
            RGBTRIPLE triple;

            // READ RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

            //WRITE each pixel to array n times
            for (int k = 0; k < n; k++)
            {
                *(array + t) = triple;
                t++;
            }
            // IMPORTANT: tracker is a must !! because t must keep incrementing from 0 ... all the way to 100 and beyond!
            // if tracker t is replaced by k, then for e.g, after the 1st row, k will be reset to ZERO ; thus *(array + k) goes back to prev values
            // hence program will try to store the new pixels at locations where pixels from the 1st row are already stored.
        }

        //with that, I finish resizing horizontally all pixels of 1st row

        //write row from array to outfile n times, each time adding padding
        for (int l = 0; l < n; l++)
        {
            fwrite(array, sizeof(RGBTRIPLE), bi.biWidth, outptr); //QTY is bi.biWidth!! NOT 1
            //add OUTfile's PADDING (NEW padding)
            for (int m = 0; m < newpadding; m++)
            {
                fputc(0x00, outptr);
            }
        }

        // skip over INfile's padding, if any
        fseek(inptr, oldpadding, SEEK_CUR);
        // then move on to next row
    }

    //malloc memory used must be RETURNED once all work is done
    free(array);

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}