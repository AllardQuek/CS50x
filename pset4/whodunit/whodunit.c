// Copies a BMP file

#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 3)
    {
        fprintf(stderr, "Usage: copy infile outfile\n");
        return 1;
    }

    // remember filenames
    char *infile = argv[1];
    char *outfile = argv[2];

    // open input file for reading
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL) //if ptr has NULL value, pointing to nth
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // open output file for writing
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }



    //END OF: OPENING FILES




    // START OF: updating header's info for outfile
    // STEP 1: READ from infile first

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

    // STEP 2: WRITE to outfile

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    //END OF: updating header's info for outfile




    // TO DO
    // Change pixels colours as necessary: change white to blue AND red to white (add blue remove red)
    // **WRITE VERDICT'S SCANLINE PIXEL BY PIXEL**
    // padding mentioned

    // determine padding for scanlines
    int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // iterate over infile's scanlines (*Read into scanline for infile pixel by pixel)
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        // iterate over pixels in scanline
        for (int j = 0; j < bi.biWidth; j++)
        {
            // temporary storage
            RGBTRIPLE triple;

            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

            //if white
            if (triple.rgbtBlue == 0xff && triple.rgbtGreen == 0xff && triple.rgbtRed == 0xff)
            {
                //make blue
                triple.rgbtBlue = 0xff;
                triple.rgbtGreen = 0x00;
                triple.rgbtRed = 0x00;
            }

            //if red
            else if (triple.rgbtBlue == 0x00 && triple.rgbtGreen == 0x00 && triple.rgbtRed == 0xff)
            {
                //make white
                triple.rgbtBlue = 0xff;
                triple.rgbtGreen = 0xff;
                triple.rgbtRed = 0xff;
            }



            // write RGB triple to outfile *** write verdict's scanline (pixel by pixel) ***
            fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
        }

        // skip over padding, if any, as padding isn't an RGBTRIPLE hence we won't be reading or writing it
        fseek(inptr, padding, SEEK_CUR);

        // then add it back (to demonstrate how)
        for (int k = 0; k < padding; k++)
        {
            fputc(0x00, outptr);
        }
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}
