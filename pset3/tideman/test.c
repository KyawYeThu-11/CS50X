#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

typedef struct
{
    int winner;
    int loser;
    int diff;
}
pair;
pair pairs[5]={{9,4,0},{6,4,0},{7,4,0},{8,4,0},{5,4,0}};

typedef struct
{
    int winner;
    int loser;
    int diff;
}
memory;
memory memories[1]={};

void sort_pairs(void);

int main (void)
{
    sort_pairs();
}

void sort_pairs(void)
{
    for (int i=0; i<5; i++)
    {
        pairs[i].diff=pairs[i].winner-pairs[i].loser;
    }

    //sorting from strongest to weakest
    while(true)
    {
        int indicator=0;
        for (int i=0; i< 4; i++)
        {
            if (pairs[i].diff<pairs[i+ 1].diff)
            {
                memories[0].winner=pairs[i+ 1].winner;
                memories[0].loser=pairs[i+ 1].loser;
                memories[0].diff=pairs[i+ 1].diff;

                pairs[i+ 1].winner=pairs[i].winner;
                pairs[i+ 1].loser=pairs[i].loser;
                pairs[i+ 1].diff=pairs[i].diff;

                pairs[i].winner=memories[0].winner;
                pairs[i].loser=memories[0].loser;
                pairs[i].diff=memories[0].diff;
            }
        }

        for (int i=0; i< 4; i++)
        {
            if (pairs[i].diff>pairs[i+ 1].diff)
            {
                indicator++;
                continue;
            }
        }

        if(indicator==4)
        {
            break;
        }
    }

    for(int i=0; i< 5; i++)
    {
        printf("Winner: %i\n", pairs[i].winner);
        printf("Loser: %i\n", pairs[i].loser);
    }
    return;
}
