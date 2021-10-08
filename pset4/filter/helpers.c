#include "helpers.h"
#include <math.h>
#include <string.h>
#include <stdio.h>
#include <cs50.h>



// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i=0; i< height; i++)
    {
        for(int j=0; j< width; j++)
        {
            int total = image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed;
            float average = (float) total / 3;
            int int_average=(int) round(average);

            image[i][j].rgbtBlue = int_average;
            image[i][j].rgbtGreen = int_average;
            image[i][j].rgbtRed = int_average;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i=0; i< height; i++)
    {
        for(int j=0; j< width; j++)
        {
            float sepiaRed= .189 * image[i][j].rgbtBlue + .769 * image[i][j].rgbtGreen + .393 * image[i][j].rgbtRed;
            float sepiaGreen= .168 * image[i][j].rgbtBlue + .686 * image[i][j].rgbtGreen + .349 * image[i][j].rgbtRed;
            float sepiaBlue= .131 * image[i][j].rgbtBlue + .534 * image[i][j].rgbtGreen + .272 * image[i][j].rgbtRed;

            int int_sepiaRed=(int) round(sepiaRed);
            int int_sepiaGreen=(int) round(sepiaGreen);
            int int_sepiaBlue=(int) round(sepiaBlue);

            if (int_sepiaRed > 255)
            {
                int_sepiaRed = 255;
            }
            if (int_sepiaGreen > 255)
            {
                int_sepiaGreen = 255;
            }
            if (int_sepiaBlue > 255)
            {
                int_sepiaBlue = 255;
            }


            image[i][j].rgbtBlue = int_sepiaBlue;
            image[i][j].rgbtGreen = int_sepiaGreen;
            image[i][j].rgbtRed = int_sepiaRed;

        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i=0; i< height; i++)
    {
        for (int j=0, length=(int) floor((width-1)/2); j<= length; j++)
        {
            int temp1=0;
            int temp2=0;
            int temp3=0;

            temp1=image[i][j].rgbtRed;
            image[i][j].rgbtRed=image[i][(width- 1)-j].rgbtRed;
            image[i][(width- 1)-j].rgbtRed=temp1;

            temp2=image[i][j].rgbtGreen;
            image[i][j].rgbtGreen=image[i][(width- 1)-j].rgbtGreen;
            image[i][(width- 1)-j].rgbtGreen=temp2;

            temp3=image[i][j].rgbtBlue;
            image[i][j].rgbtBlue=image[i][(width- 1)-j].rgbtBlue;
            image[i][(width- 1)-j].rgbtBlue=temp3;

        }
    }
    return;
}

// Blur image
int find_averageRed (int i,int j, int height, int width, RGBTRIPLE image[height][width]);
int find_averageGreen (int i,int j, int height, int width, RGBTRIPLE image[height][width]);
int find_averageBlue (int i,int j, int height, int width, RGBTRIPLE image[height][width]);

void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE clean_image[height][width];

    for(int i=0; i< height; i++)
    {
        for(int j=0; j< width; j++)
        {
            clean_image[i][j].rgbtRed = image[i][j].rgbtRed;
            clean_image[i][j].rgbtGreen = image[i][j].rgbtGreen;
            clean_image[i][j].rgbtBlue = image[i][j].rgbtBlue;
        }
    }

    for(int i=0; i< height; i++)
    {
        for(int j=0; j< width; j++)
        {
            image[i][j].rgbtRed = find_averageRed( i, j, height, width, clean_image);
            image[i][j].rgbtGreen = find_averageGreen( i, j, height, width, clean_image);
            image[i][j].rgbtBlue = find_averageBlue( i, j, height, width, clean_image);
        }
    }
    return;
}

int check (int i, int j, char *a, char *b, int height, int weight, BYTE *ptr, int *pointer);
int find_averageRed (int i,int j, int height, int width, RGBTRIPLE image[height][width])
{
        BYTE *ptr1= &image[i- 1][j - 1].rgbtRed;
        BYTE *ptr2= &image[i- 1][j].rgbtRed;
        BYTE *ptr3= &image[i- 1][j + 1].rgbtRed;
        BYTE *ptr4= &image[i][j - 1].rgbtRed;
        BYTE *ptr5= &image[i][j + 1].rgbtRed;
        BYTE *ptr6= &image[i + 1][j - 1].rgbtRed;
        BYTE *ptr7= &image[i + 1][j].rgbtRed;
        BYTE *ptr8= &image[i + 1][j + 1].rgbtRed;

    int counter=1;
    int *pointer = &counter;


    int total=image[i][j].rgbtRed+check(i, j, "-" ,"-" , height, width, ptr1, pointer)+check(i, j, "-" ,"none" , height, width, ptr2, pointer)+check(i, j, "-" ,"+" , height, width, ptr3, pointer)+check(i, j, "none" ,"-" , height, width, ptr4, pointer)+check(i, j, "none" ,"+" , height, width, ptr5, pointer)+check(i, j, "+" ,"-" , height, width, ptr6, pointer)+check(i, j, "+" ,"none" , height, width, ptr7, pointer)+check(i, j, "+" ,"+" , height, width, ptr8, pointer);
    float average = (float) total/counter;
    int int_average = (int) round(average);

    return int_average;
}

int find_averageGreen (int i,int j, int height, int width, RGBTRIPLE image[height][width])
{
        BYTE *ptr1= &image[i- 1][j - 1].rgbtGreen;
        BYTE *ptr2= &image[i- 1][j].rgbtGreen;
        BYTE *ptr3= &image[i- 1][j + 1].rgbtGreen;
        BYTE *ptr4= &image[i][j - 1].rgbtGreen;
        BYTE *ptr5= &image[i][j + 1].rgbtGreen;
        BYTE *ptr6= &image[i + 1][j - 1].rgbtGreen;
        BYTE *ptr7= &image[i + 1][j].rgbtGreen;
        BYTE *ptr8= &image[i + 1][j + 1].rgbtGreen;

    int counter=1;
    int *pointer = &counter;

    int total=image[i][j].rgbtGreen+check(i, j, "-" ,"-" , height, width, ptr1, pointer)+check(i, j, "-" ,"none" , height, width, ptr2, pointer)+check(i, j, "-" ,"+" , height, width, ptr3, pointer)+check(i, j, "none" ,"-" , height, width, ptr4, pointer)+check(i, j, "none" ,"+" , height, width, ptr5, pointer)+check(i, j, "+" ,"-" , height, width, ptr6, pointer)+check(i, j, "+" ,"none" , height, width, ptr7, pointer)+check(i, j, "+" ,"+" , height, width, ptr8, pointer);
    float average = (float) total/counter;
    int int_average = (int) round(average);

    return int_average;
}

int find_averageBlue (int i,int j, int height, int width, RGBTRIPLE image[height][width])
{
        BYTE *ptr1= &image[i- 1][j - 1].rgbtBlue;
        BYTE *ptr2= &image[i- 1][j].rgbtBlue;
        BYTE *ptr3= &image[i- 1][j + 1].rgbtBlue;
        BYTE *ptr4= &image[i][j - 1].rgbtBlue;
        BYTE *ptr5= &image[i][j + 1].rgbtBlue;
        BYTE *ptr6= &image[i + 1][j - 1].rgbtBlue;
        BYTE *ptr7= &image[i + 1][j].rgbtBlue;
        BYTE *ptr8= &image[i + 1][j + 1].rgbtBlue;

    int counter=1;
    int *pointer = &counter;


    int total=image[i][j].rgbtBlue+check(i, j, "-" ,"-" , height, width, ptr1, pointer)+check(i, j, "-" ,"none" , height, width, ptr2, pointer)+check(i, j, "-" ,"+" , height, width, ptr3, pointer)+check(i, j, "none" ,"-" , height, width, ptr4, pointer)+check(i, j, "none" ,"+" , height, width, ptr5, pointer)+check(i, j, "+" ,"-" , height, width, ptr6, pointer)+check(i, j, "+" ,"none" , height, width, ptr7, pointer)+check(i, j, "+" ,"+" , height, width, ptr8, pointer);
    float average = (float) total/counter;
    int int_average = (int) round(average);

    return int_average;
}

int check (int i, int j, char *a, char *b, int height, int width, BYTE *ptr, int *pointer)
{
    bool check = true;
    if (strcmp(a, "-")==0)
    {
        if (i- 1==-1)
        {
            check = false;
        }
    }
    if (strcmp(b, "-")==0)
    {
        if (j- 1==-1)
        {
            check = false;
        }
    }
    if (strcmp(a, "+")==0)
    {
        if (i+ 1 == height)
        {
            check = false;
        }
    }
    if (strcmp(b, "+")==0)
    {
        if (j+ 1 == width)
        {
            check = false;
        }
    }

    if (check == false)
    {
        return 0;
    }

    BYTE result= *ptr;
    *pointer = *pointer + 1;
    return result;


}
