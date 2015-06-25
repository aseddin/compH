#include <stdio.h>
#include <cs50.h>

/*Print half-pyramid with a a variable height based on user input */

int get_height(void);


int main(void)
{
    
    int pyramid_height, i, whites, hashes;

    //Solicit the user intput for the positive pyramid height
    pyramid_height = get_height();


    for (i = 1; i <= pyramid_height; i++)
    {
        //Generate a pyramid row
        //
        //print white spaces
        for (whites = pyramid_height - i; whites > 0; whites--)
        {
            printf(" ");
        }

        //print the pyramid hashes
        for (hashes = 0 ; hashes <= i; hashes++)
        {
            printf("#");
        }
        
        //new pyramid row
        printf("\n");
    }

    return 0;
}

//Prompt the user for a positve height
int get_height(void)
{
    int height = -1;
    
    //Keep asking for a positive input no greater than 23
    while (height < 0 || height > 23)
    {
        printf("Height: ");
        height = GetInt();
    }
    
    return height;
}


