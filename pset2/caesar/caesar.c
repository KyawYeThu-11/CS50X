#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <stdlib.h>

int main (int argc, string argv[])
{
    //To ensure the program has only one argument
    if (argc==2)
    {
        //To ensure the argument is decimal digit
        for (int i=0, len=strlen(argv[1]); i<len; i++)
        {
            if (isdigit(argv[1][i])==0)
            {
                printf("Usage: ./caesar key\n");
                return 1;
            }
        }


        int key=atoi(argv[1]);
        string plaintext=get_string("plaintext: ");
        char cipherletter;
        int ascii, ascii2, ascii3;

        printf("ciphertext: ");

        //iterating each letter in the plaintext
        for (int j=0, length=strlen(plaintext); j<length; j++)
        {
            ascii=(int) plaintext[j];

            //if uppercase,
            if (ascii >= (int) 'A' && ascii <= (int) 'Z')
            {
                ascii2=((ascii-64)+key)%26;
                ascii3=ascii2+64;
                cipherletter=(char) ascii3;
                printf("%c", cipherletter);
            }
            //if lower case,
            else if (ascii >= (int) 'a' && ascii <= (int) 'z')
            {
                ascii2=((ascii-96)+key)%26;
                ascii3=ascii2+96;
                cipherletter=(char) ascii3;
                printf("%c", cipherletter);
            }
            else
            {
                printf("%c", plaintext[j]);
            }
        }
        printf("\n");
    }

    //the program has invalid counts of arguments.
    else
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

}

