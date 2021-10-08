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

int main(void)
{
    for (int i=0; i<5; i++)
    {
        pairs[i].diff=pairs[i].winner-pairs[i].loser;
    }
    
    for (int pointer=0; pointer< 5; pair_count++)
    {
            for(int i=0; i< candidate_count; i++)
            {
                    for(int j=0; j< candidate_count; j++)
                    {
                        if(newnew_prefer[i][j]==0)
                        {
                            continue;
                        }
                        else if (newnew_prefer[i][j]-newnew_prefer[j][i]==pairs[pointer].difference)
                        {
                            locked[i][j]==true;
                            newnew_prefer[j][i]=0;
                        }
                        else if (newnew_prefer[j][i]-newnew_prefer[i][j]==pairs[pointer].difference)
                        {
                            locked[j][i]==true;
                            newnew_prefer[i][j]=0;
                        }
                    }
            }
    }
}
        