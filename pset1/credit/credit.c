#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int firstsum;
    int secsum;
    int sum;
    int count;
    long long n, n1, n2;
    //Prompt user for credit card number
    do
    {
        n = get_long_long("Number:");
    }
    while (n <= 0);

    // STEP 1
    // double every other digit starting w/ 2nd to last
    // then sum the individual digits of these products
    for (n1 = n / 10, firstsum = 0; n1 > 0; n1 /= 100)
        //divide by 10 to remove last digit and 'get to' 2nd last digit, keeping in mind n1 is an INTEGER ; divide by 100 to remove last 2 digits, ie. get to every other digit from 2nd last digit.
    {
        //n1 % 10 will now actually get the 2nd last digit, if when multiplied by 2 (following algorithm) value is 2 digits, ie. 10 and above,
        if (2 * (n1 % 10) > 9)
        {
            //THEN divide by 10 to get the first digit, keeping in mind the number is an INTEGER and will be rounded. Add the 1st digit to firstsum
            firstsum += (2 * (n1 % 10)) / 10;
            //THEN get the second digit (last digit in ones place). Add 2nd digit to firstsum.
            firstsum += (2 * (n1 % 10)) % 10;
        }
        else
        {
            firstsum += 2 * (n1 % 10);
        }
        //if after multiplying by 2 value is between 0 and 9 inclusive, THEN add that value (a single digit) to first sums

    }

    // STEP 2
    // sum every other digit starting w/ the the last
    for (n2 = n, secsum = 0;
         n2 > 0;
         n2 /= 100)
        //divide by 100 to remove last 2 digits, ie. get to every other digit, keeping in mind n2 is an INTEGER
    {
        secsum += n2 % 10; //adding the last digit to sum
    }

    // FINAL STEP
    sum = firstsum + secsum;
    // AMEX: 34/37, 15-digit ; MASTERCARD: 51, 52, 53, 54, or 55, 16-digit ; VISA: 4, 13/16-digit
    // Check and print credit card brand; ie. AMEX\n or MASTERCARD\n or VISA\n or INVALID\n
    if (sum % 10 == 0) // check if last digit is equal to 0
    {
        if ((n >= 340000000000000 && n < 350000000000000) || (n >= 370000000000000
                && n < 380000000000000)) // AMEX: either 34/37 AND 15-digit. MUST split into two inequalities, no combining using C syntax.
        {
            printf("AMEX\n");
        }

        else if (n >= 5100000000000000 && n < 5600000000000000)
        {
            printf("MASTERCARD\n");
        }
        else if ((n >= 4000000000000 && n < 5000000000000) || (n >= 4000000000000000 && n < 5000000000000000))
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }

    return 0;
}