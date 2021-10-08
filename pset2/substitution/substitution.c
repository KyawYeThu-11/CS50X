#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <search.h>
#include <stdlib.h>

int main (int argc, string argv[])
{
    //To ensure the program has only one argument
    if (argc==2)
    {
        //To ensure the argument has 26 letters
        int len=strlen(argv[1]);
        if (len==26)
        {

            char notRepeat[26]={};

            //To ensure the argument is alphabets
            for (int i=0; i<len; i++)
            {
                if (isalpha(argv[1][i])==0)
                {
                    printf("Not all the letters in the argument are alphabets\n");
                    return 1;
                }
                notRepeat[i]=toupper(argv[1][i]);
            }

            //To ensure every alphabet exists
            int count=0;
            for (int j=0; j<len; j++)
            {
                for (int k=0; k<len; k++)
                {
                    if (notRepeat[j]==toupper(argv[1][k]))
                    {
                        count++;
                    }
                }
            }
            if (count>26)
            {
                printf("The argument must contain every alphabet exactly once.\n");
                return 1;
            }

            //***substitution begins*******************************
            else
            {
                string plaintext=get_string("plaintext: ");
                int ascii, link;

                printf("ciphertext: ");

                //iterating the plaintext
                for (int l=0, length=strlen(plaintext); l<length; l++)
                {
                    ascii=(int) toupper(plaintext[l]);
                    link=ascii-65;
                    if (isalpha(plaintext[l]))
                    {
                        if (isupper(plaintext[l]))
                        {
                            printf("%c", toupper(argv[1][link]));
                        }
                        else if (islower(plaintext[l]))
                        {
                            printf("%c", tolower(argv[1][link]));
                        }
                    }
                    else
                    {
                        printf("%c", plaintext[l]);
                    }
                }
                printf("\n");
            }
        }
        else
        {
            printf("The argument must contain 26 alphabetical letters\n");
            return 1;
        }
    }

    //the program has invalid counts of arguments.
    else
    {
        printf("Invalid count(s) of argument\n");
        return 1;
    }
}

