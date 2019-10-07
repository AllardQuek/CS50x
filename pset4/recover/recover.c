#include <stdio.h>
#include <stdint.h> //to write typedef

int main(int argc, char *argv[])
{
    //ensure proper usage
    if (argc != 2)
    {
        fprintf(stderr, "Only ONE command-line argument will be accepted!");
        return 1;
    }

    //what are the argument(s)?
    char *rawfile = argv[1]; //argv[1] is a char*, string

    //open rawfile for READING
    FILE *file = fopen(rawfile, "r");
    if (file == NULL)
    {
        fprintf(stderr, "File %s cannot be opened.\n", argv[1]);
        return 2;
    }

    //create outfile for image
    FILE *img = NULL;

    //create 1st array for file names "###.jpg" total EIGHT chars including \0!
    char filename[8];

    //create 2nd array for bytes;  //https://www.tutorialspoint.com/cprogramming/c_data_types.htm
    //can use: unsigned char buffer[512]; UNSIGNED is CRUCIAL!! else "comparison of constant 255 with expression of type 'char' is always false"
    //no need to multiply by anything because I'm only doing things 512 bytes at a time, no need for more memory

    typedef uint8_t BYTE;
    BYTE buffer[512];
    // Repeat until END OF CARD

    //counter for filenames; 001, 002, etc.
    int count = 0;

    while (!feof(file)) //(fread(buffer, 1, 512, file) == 512) //number of bytes return = 512, keep reading next 512 bytes

    {
        //check first 4 bytes for jpeg header 0xff 0xd8 0xff ; e = 1110 , f = 1111
        // result must be e0 1110 0000 when comparing e1 1110 0001 to f0 1111 0000 (last 4 digits ALWAYS return 0, hence only comparing 1st 4 matters)
        // e.g compare 0xea 1110 1010 to 0xef 1110 0000, results 1110 0000 which is 0xe0 (https://www.programiz.com/c-programming/bitwise-operators#and)
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            if (img != NULL) //jpeg alr open; OR if (img) , tells you whether file was successfully opened
            {
                //close current jpg file
                fclose(img);
            }

            //create new jpg file
            sprintf(filename, "%03i.jpg", count);
            count++;

            //open new file
            img = fopen(filename, "w");
        }

        //else not a jpeg header
        //jpeg alr open
        if (img != NULL)
        {
            //writing to jpeg file
            fwrite(buffer, 1, 512, img);
        }

        //return to top of loop and continue reading 512 bytes at a time; DONT WRITE
        fread(buffer, 1, 512, file); //must read BEFORE checking the while condition!
    }

    //reached EOF: stop reading, close files
    fclose(img);
    fclose(file);


    return 0;

}