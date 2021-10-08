#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int height, far, count;
    do
    {
        height=get_int("Height: ");
    }
    while(height<1 || height>8);
    
    
    far= height-1;
    count=0;
    //for height
    for (int i=0; i<height; i++)
    {
        //slope indenting
        for (int j=0; j<far;j++)
        {
            printf(" ");
        }

        //filling hashes
        count++;
        for (int k=0; k<count; k++)
        {
            printf("#");
        }

        //adding spaces
        printf("  ");

        //adding hashes
        for (int l=0; l<count; l++)
        {
            printf("#");
        }

        printf("\n");
        far--;
    }
}