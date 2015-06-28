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
        printf("%c", toupper(name[0]));
        int c = 1;
        do
        {
            if(name[c] == ' ')
            {
                printf("%c", toupper(name[c+1]));
            }
            c++;
        }while(c < strlen(name));

        //print the final new line
        printf("\n");

    }
    return 0;
}
