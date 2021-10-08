#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int startSize, endSize, bornSize, dieSize;
    int year=0;

    do
    {
        startSize=get_int("Start Size: ");
    }
    while (startSize<9);

    do
    {
        endSize=get_int("End Size: ");
    }
    while (endSize<startSize);

    while(startSize<endSize)
    {
         bornSize=startSize/3;
         dieSize=startSize/4;
         startSize=startSize+bornSize-dieSize;
         year++;
    }

    printf("Years: %i\n", year);
}
