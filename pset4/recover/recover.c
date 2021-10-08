#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <cs50.h>
#include <stdint.h>


typedef uint8_t BYTE;


int main(int argc, char *argv[])
{
    if (argc !=2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }


    FILE *input = fopen(argv[1], "r");
    if( input == NULL)
    {
        printf("Could not open %s\n", argv[1]);
        return 1;
    }

    BYTE buffer[512];
    int counter=0;
    bool found = false;
    char filename[8];
    while(fread(buffer, sizeof(BYTE), 512, input))
    {

        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            sprintf(filename, "%03i.jpg", counter);
            counter++;

            FILE *output = fopen(filename, "w");
            fwrite(buffer, sizeof(BYTE), 512, output);
            fclose(output);

            found = true;
        }
        else if (found == true)
        {
            FILE *output = fopen(filename, "a");
            fwrite(buffer, sizeof(BYTE), 512, output);
            fclose(output);
        }
    }
    fclose(input);
}
