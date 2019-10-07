#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)

{
    //declaring variables, change in dollars, min no. of coins, change in cents
    float change;
    int coins;
    int cents;

    //at least once: prompt user for postive change owed
    do
    {
        change = get_float("Change owed: ");
    }
    while (change < 0);

    //set initial no. of coins to 0, and convert change from dollars to cents AND rounding off to nearest integer/penny to account for imprecision of floating-point values
    coins = 0;
    cents = round(change * 100);


    //as long as 25cent coins (largest) can be used, increasing coin count by 1 AND reduce remaining change owed
    while (cents >= 25)
    {
        cents -= 25;
        coins++;
    }

    //once 25cent coins no longer usable, start using 10cent coins.
    while (cents >= 10)
    {
        cents -= 10;
        coins++;
    }


    //using 5cent coins
    while (cents >= 5)
    {
        cents -= 5;
        coins++;
    }

    //using 1cent coins
    while (cents >= 1)
    {
        cents -= 1;
        coins++;
    }


    //print minimum number of coins used to return change
    printf("%i\n", coins);
}