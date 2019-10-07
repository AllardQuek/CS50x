#include <stdio.h>
#include <cs50.h>

//Program should accept exactly 2 cmd-line args: name of input file to open for reading THEN name of output file to open for writing.
//TODO:
//open file #
//update header's info for output file #

//read clue's scanline (pixel by pixel) #
//change pixel's colour as necessary

//write verdict's scanline (pixel by pixel) #

// int main(int argc, char *argv[])
// {
//     //program is executed with < or > than 2 command-line arguments: remind user of correct usage with fprintf (to stderr), and main should return 1.
//     if (argc != 3)
//     {
//         fprintf(stderr, "Usage: whodunit infile outfile\n");
//         return 1;
//     }

//     FILE* ptr = fopen("infile", "r");

//     if ()
//     fprintf(stderr, "Input file cannot be opened for reading!\n");
//     return 2;

//     FILE* ptr1 = ("outfile", "w");

//     fprintf(stderr, "Input file cannot be opened for writing!\n");
//     return 3;

//     fprintf(stderr, "Input file is not a 24-bit uncompressed BMP 4.0\n");
//     return 4;


    //read 1 char at a time from infile
    char ch = fgetc(ptr);


    //fgetc() : read the whole infile, printing out what is being read, file must be opened for READING
    char ch;
    while ((ch = fgetc(ptr)) != EOF)
        printf("%c", ch);


    //fputc() : insert char by char into outfile, file must be opened for WRITING
    fputc(<character>, <file ptr>)

    //fgetc() and fputc() : copy the whole infile into outfile (reading from infile and writing to outfile)
    char ch;
    while((ch = fgetc(ptr)) != EOF)
        fputc(ch, ptr1);

    //fread(<buffer>, <sizeof>, <qty>, <file ptr>) : generic fgetc(), get any amt of info; i.e store whatever is read from file temporarily in buffer (a POINTER)
    //fwrite(<buffer>, <sizeof>, <qty>, <file ptr>) : writing from buffer to a destination file



        //make blue
    RGBTRIPLE triple;
    triple.rgbtBlue = 0xff;
    triple.rgbtGreen = 0x00;
    triple.rgbtRed = 0x00;

    //make white
    RGBTRIPLE triple;
    triple.rgbtBlue = 0xff;
    triple.rgbtGreen = 0xff;
    triple.rgbtRed = 0xff;

    //make red
    triple.rgbtBlue = 0x00;
    triple.rgbtGreen = 0x00;
    triple.rgbtRed = 0xff;




    return 0;
}