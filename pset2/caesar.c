#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>


int main(int argc, string argv[])
{
    //Ascertain 2 command line arguments
    if(argc != 2)
    {
        printf("Usage: %s <key>\n", argv[0]);
        return 1;
    }
    else
    {
        //convert the string k to integer
        int k =  atoi(argv[1]);
        
        //Ascertain k is positive
        if(k < 0)
        {
            printf("Key must be a non-negative integer.\n");
            return 1;
        }
        else
        {
            string p, c;
            
            //Get the original message to encrypt
            p = GetString();

            //copy the original to the cipher to keep the non-alpha chars
            c = p;

            //Encrypt the message
            for(int i = 0, n = strlen(p); i < n; i++)
            {
                if(isalpha(p[i]))
                {
                    //Move the numbers to range [0 to 25] then back up based on capitalization
                    if(isupper(p[i]))
                        c[i] = (k + p[i] - 'A') % 26 + 'A';
                    else
                        c[i] = (k + p[i] - 'a') % 26 + 'a';
                }
            }

            //Display the cipher message
            printf("%s\n", p);

            return 0;
        }
    }
}
