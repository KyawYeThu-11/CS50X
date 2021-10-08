#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

typedef struct
{
    int winner;
    int loser;
}
pairs;
pairs pair[3]={};
int preferences[3][3]={{0,3,1}, {1,0,2}, {3,2,0}};
void add_pairs(void);

int main (void)
{
    add_pairs();
}

void add_pairs(void)
{
    int pointer=0;
    int count=pointer;
    for(int i=0; i< 3; i++)
    {
        for(int j=0; j< 3; j++)
        {
            if(preferences[i][j]==0)
            {
                continue;
            }
            else if (preferences[i][j]>preferences[j][i])
            {
                pair[pointer].winner=i;
                pair[pointer].loser=j;
                pointer++;
                preferences[j][i]=0;
            }
            else if (preferences[i][j]<preferences[j][i])
            {
                pair[pointer].winner=j;
                pair[pointer].loser=i;
                pointer++;
                preferences[j][i]=0;
            }
            else if (preferences[i][j]==preferences[j][i])
            {
                pair[pointer].winner=69;
                pair[pointer].loser=69;
                pointer++;
                preferences[j][i]=0;
            }
        }
    }
    for(int i=0; i< 3; i++)
    {
        printf("Winner: %i\n", pair[i].winner);
        printf("Loser: %i\n", pair[i].loser);
    }
    return;
}

