for (int i = 0; i < strlen(p); i++ ) //for every char in plaintext "hello"
{
    //convert every letter of key into integer no. of places to shift, k
    for (int j = 0; j <= strlen(key); j++) //for every char in key "ABC"/012
    {
        if (isupper(key[j])) //one of the chars in string key
        {
            j = j % strlen(key); //allow wrapping around of key; j=3+1, 4%3=1; j=2+1, 3%3=0
            k = key[j] - 65; //int k can only be x,y,z ; strlen is 3
        }

        else if (islower(key[j]))
        {
            j = j % strlen(key);
            k = key[j] - 97;
        }
    }


    if (islower(p[i]))
    {
        ai = p[i] - 97 + k;
        finalcc = (ai % 26) + 97;
        printf("%c", finalcc);
    }

    else if (isupper(p[i]))
    {
        ai = p[i] - 65 + k;
        finalcc = ai % 26 + 65;
        printf("%c", finalcc);
    }

    else //if char is number, punctuation etc, keep same
    {
        printf("%c", p[i]);
    }

}

