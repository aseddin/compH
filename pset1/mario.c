#include <stdio.h>
#include <cs50.h>

/*Print half-pyramid with a a variable height based on user input */

int get_height(void);
void print_block(char character, int block_size);

int main(void)
{
    int pyramid_height;

    //Solicit the user intput for the positive pyramid height
    pyramid_height = get_height();

    for (int i = 1; i <= pyramid_height; i++)
    {
        //Generate a pyramid row (both sides and white spaces in between)

        print_block(' ', pyramid_height - i);
        print_block('#', i);
        print_block(' ', 2);
        print_block('#', i);
        print_block(' ', pyramid_height - i);
        
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

//print a character "block_size" times
void print_block(char character, int block_size)
{
    for(int i = 0; i < block_size; i++)
        printf("%c", character);
}
