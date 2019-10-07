#include <stdio.h>
#include <cs50.h>
#include <stdlib.h> //for function atoi
#include <string.h> //for strlen()
#include <ctype.h> //for characters, check isupper(), islower(), isalpha()

int main(int argc, string argv[])
{
    char ASCIIcc, ai, finalcc;
    int k;

    //check if user passes 2 args, ie. whether the key exists; if it does then use argv indexing to get it. Use = for assignment, == for equality

    if (argc != 2)
    {
        printf("Usage: ./caesar k\n");
        return 1;
    }

    string key = argv[1]; //get key from cmd line arg
    k = atoi(key); //convert key (string) to integer

    ////int k = atoi(argv[1]);
    //user provides more than one command-line argument at the prompt, argc could be greater than 2, in which case, again, your program should print an error and return 1.

    //prompt user for plaintext
    string p = get_string("plaintext:");

    //Now with key k and plaintext p, start encrypting p with k. Iterate over chars in a string, printing 1 at a time:
    //for each CHAR in plaintext str, for ONLY alphabets: preserve upper/lower case AND shift char by key, collecting all the cipher characters in ciphertext
    //start: ASCII values, encipher: alphabetical index, print: ASCII values
    printf("ciphertext: ");
    for (int i = 0; i < strlen(p); i++)
    {
        if (isalpha(p[i])) //if char is letter/alphabet
        {
            if (islower(p[i])) //if lowercase shift using some way
            {
                ai = p[i] - 97 + k; //ai helps us wrap around, single quotes on p[i] NOT needed as it will alr return a string!
                finalcc = (ai % 26) + 97;
                printf("%c", finalcc);
                //ciphert[i] = finalcc;
            }
            //if uppercase shift using another way, more detailed (ASCII not necessary, can simplify to lowercase's method)
            else if (isupper(p[i]))
            {
                ASCIIcc = p[i] + k;
                ai = ASCIIcc - 65; //ai helps us wrap around
                finalcc = ai % 26 + 65;
                printf("%c", finalcc);
                //ciphert[i] = finalcc;
            }
        }

        else //if char is number, punctuation etc, keep same
        {
            printf("%c", p[i]);
        }
    }

    printf("\n");

    return 0;
}
