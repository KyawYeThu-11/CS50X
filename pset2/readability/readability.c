#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int count_letters(string ptext);
int count_words(string ptext);
int count_sentences(string ptext);
float finding_L(int pletters, float pwords);
float finding_S(int psentences, float pwords);

int main(void)
{
    string text = get_string("Text: ");
    int letters = count_letters(text);
    int words = count_words(text);
    int sentences = count_sentences(text);

    int L = finding_L(letters, words);
    int S = finding_S(sentences, words);
    float index = 0.0588 * L - 0.296 * S - 15.8;
    int integer_index=round(index);

    if(integer_index>=16)
    {
        printf("Grade 16+\n");
    }
    else if (integer_index<1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %i\n", integer_index);
    }


}

int count_letters(string ptext)
{
    int count=0;
    for (int i=0, len=strlen(ptext); i<len; i++)
    {
        if (ptext[i]>='A' && ptext[i]<='z')
        {
            count++;
        }
    }
    return count;
}

int count_words(string ptext)
{
    int count=0;
    for (int i=0, len=strlen(ptext); i<len; i++)
    {
        if (ptext[i]==' ')
        {
            count++;
        }
    }
     return count+1;
}

int count_sentences(string ptext)
{
    int count=0;
    for (int i=0, len=strlen(ptext); i<len; i++)
    {
        if (ptext[i]=='.' || ptext[i]=='!' || ptext[i]=='?')
        {
            count++;
        }
    }
    return count;
}

float finding_L(int pletters, float pwords)
{
    int result;
    result=(100/pwords) * pletters;
    return result;
}

float finding_S(int psentences, float pwords)
{
    int result;
    result=(100/pwords) * psentences;
    return result;
}