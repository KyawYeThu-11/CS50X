#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    long number = get_long("Number: ");
    long oneNumber = number;//oneNumber is for first operation
    long twoNumber = number;//twoNumber is for second operation

    long newNumber;
    int lastDigit, newLastDigit, sum, length;
    long firstTwo = number;
    long firstOne = number;
    int sum1=0;
    int sum2=0;

    //finding length
    length=log10(number) + 1;

    //first two digit and first one digit grapping
    while(firstTwo >= 100)
    {
        firstTwo = firstTwo/10;
    }
    firstOne = firstTwo/10;

    //sum of first operation-every other digit from the last digit
    do
    {
       lastDigit=oneNumber%10;
       newNumber=oneNumber/100;
       oneNumber=newNumber;

       sum1+=lastDigit;
    }
    while(newNumber>0);


    //sum of second operation-every other digit, starting with the number’s second-to-last digit
    twoNumber=number/10;
    do
    {
       lastDigit=twoNumber%10;
       newNumber=twoNumber/100;
       twoNumber=newNumber;
       newLastDigit=2*lastDigit;

       //spliting the number greater than ten
       if(newLastDigit>=10)
       {
           newLastDigit=newLastDigit%10+1;
       }
       sum2+=newLastDigit;
    }
    while(newNumber>0);

    //sum
    sum=sum1+sum2;

    if(sum%10==0)
    {

        if(length>=13 && length<=16)
        {
            if(firstTwo==34 || firstTwo==37)
            {
                printf("AMEX\n");
            }
            else if(firstTwo>=51 && firstTwo<=55)
            {
                printf("MASTERCARD\n");
            }
            else if(firstOne==4)
            {
                printf("VISA\n");
            }
            else
            {
                printf("INVALID\n");
            }

        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }

}