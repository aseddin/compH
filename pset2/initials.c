#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>


int main(int argc, string argv[])
{
    //Input name
    string name = GetString();

    //make sure name is not empty
    if (strlen(name) > 0)
    {
        bool white_space_flag = true;
        int c = 0;
        while(c < strlen(name))
        {
            if(isblank(name[c]))
            {
                white_space_flag = true;
            }
            else if(white_space_flag)
            {
                white_space_flag = false;
                printf("%c", toupper(name[c]));
            }
            c++;

        }
        //print the final new line
        printf("\n");

    }
    return 0;
}
