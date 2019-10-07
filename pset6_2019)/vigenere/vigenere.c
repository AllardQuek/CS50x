#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>

int main(int argc, string argv[])
{
    //ONLY accept if exactly 2 args passed, program and key, AND key does not contain non-alphabetical chars
    string key = argv[1];
    char ai, finalcc;
    int k;

    if (argc != 2) //Number of args must be checked FIRST, before presence of non-alphabetic chars
    {
        printf("Usage: ./vigenere k\n");
        return 1;
    }

    for (int i = 0; i < strlen(key); i++) //for every char in key user passed in { i=0; i<strlen(key); i++ }
    {
        if (isalpha(key[i]) == false)
        {
            printf("Usage: ./vigenere k\n");
            return 1;
        }
    }



    //if main function called properly, prompt user for plaintext
    string p = get_string("plaintext: ");

    printf("ciphertext: ");

    //start enciphering

    //j % strlen(key) is rotating through indexes of key ; key[] is a char of key ; tolower() ensures the char is lowercase ; -97 to get number of places to shift plaintext char by

    for (int i = 0, j = 0; i < strlen(p); i++) //for every char in plaintext "HELLO", IMPT: j initialised to 0 here
    {
        //for (int j = 0; j < strlen(key); j++)  doesn't work, better to split up into lines
        //IMPORTANT: convert every letter of key "ABC" into integer no. of places to shift, k ; MOD allows for wrapping around key
        k = tolower(key[j % strlen(key)]) - 97;

        if (islower(p[i]))
        {
            ai = p[i] - 97 + k;
            finalcc = (ai % 26) + 97;
            printf("%c", finalcc);

            j++; //IMPORTANT: increment j only when used.
        }

        else if (isupper(p[i]))
        {
            ai = p[i] - 65 + k;
            finalcc = ai % 26 + 65;
            printf("%c", finalcc);

            j++;
        }

        else //if char is number, punctuation etc, keep same
        {
            printf("%c", p[i]);
        }

    }


    printf("\n");

    return 0;
}
