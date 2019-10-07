#include <stdio.h>
#include <cs50.h>

int main(void)
{
    //declare height of pyramid, n
    int n;


    //at least once: prompt user input for pyramid height
    do
    {
        n = get_int("Height:");
    }
    while (n < 0 || n > 23);

    //for each row...
    for (int i = 0; i < n; i++)
    {
        //print spaces (-- per row)
        for (int j = i; j < n - 1; j++)
        {
            printf(" ");
        }
        //print hashes (++ per row)
        for (int k = n - 2 - i; k < n; k++)
        {
            printf("#");
        }
        //print newline
        printf("\n");
    }
}