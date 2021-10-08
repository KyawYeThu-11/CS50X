#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX 9
int preferences[MAX][MAX];
int array[MAX][MAX];

    int candidates[]={3,0,4,1,2};
void record_preferences(int ranks[]);
bool lookup (int k, int length, int finished_candidate[]);

int main(void)
{
    record_preferences(candidates);
}

void record_preferences(int ranks[])
{
    int finished_candidate[4]={};
    int number_finished=0;

    for (int i=0; i< 5; i++)
    {
        for (int j=0; j < 5; j++)
        {
            for (int k=0; k < 5; k++)
            {
                if (j!=ranks[i])
                {
                    printf("%i", preferences[ranks[j]][ranks[k]]);
                    continue;
                }
                else if (j==ranks[i] && k==ranks[i])
                {
                    printf("%i", preferences[ranks[j]][ranks[k]]);
                    continue;
                }
                else if (j==ranks[i] && lookup(k, number_finished, finished_candidate)==true)
                {
                    printf("%i", preferences[ranks[j]][ranks[k]]);
                    continue;
                }
                else
                {
                    preferences[ranks[j]][ranks[k]]++;
                    printf("%i", preferences[ranks[j]][ranks[k]]);
                }
            }
         printf("\n");

         }
         printf("\n");
         finished_candidate[i]=ranks[i];
         number_finished++;


    }
    for (int a=0; a< 5; a++)
    {
        for(int b=0; b<5; b++)
        {
            array[a][b]=preferences[ranks[a]][ranks[b]];
        }
    }
    printf("New array!");
    for (int a=0; a< 5; a++)
    {
        for(int b=0; b<5; b++)
        {
            printf("%i",array[a][b]);
        }
        printf("\n");
    }


    return;
}

bool lookup (int k, int length, int finished_candidate[])
{
    for (int i=0; i< length; i++)
    {
        if(k==candidates[i])
        {
            return true;
        }
    }
    return false;
}
