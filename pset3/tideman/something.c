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
pair;

typedef struct
{
    int first;
    int second;
}
memory;

memory memories[1];
pair pairs[5]={{9,4},{6,4},{7,4},{8,4},{5,4}};

int main (void)
{
    memori es[0].first= pairs[2].winner;
    memories[0].second= pairs[2].loser;
    pairs[2].winner=pairs[1].winner;
    pairs[2].loser=pairs[1].loser;
    pairs[1].winner=memories[0].first;
    pairs[1].loser=memories[0].second;

    for(int i=0; i< 5; i++)
    {
        printf("Winner: %i\n", pairs[i].winner);
        printf("Loser: %i\n", pairs[i].loser);
    }
} 