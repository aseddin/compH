#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

char cipher(char c, int k);

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
        string p, c;
        int current_key;

        string k = argv[1]; //get the key
        int key_length = strlen(k);

        //make sure the key is alphabetical only
        for(int i = 0; i < key_length; i++)
        {
            if(!isalpha(k[i]))
            {
                printf("Keyword must only contain letters A-Z and a-z\n");
                return 1; //exit the program with error code 1
            }
        }

        //Get the original message to encrypt
        p = GetString();

        //copy the original to the cipher to keep the non-alpha chars
        c = p;

        //Encrypt the message
        for(int i = 0, j = 0, n = strlen(p); i < n; i++)
        {
            if(isalpha(p[i]))
            {
                //get the key number
                current_key = tolower(k[j]) - 'a';
                c[i] = cipher(p[i], current_key);

                //advance the key's index only for characters in p and repeat the key
                j = (j + 1) % key_length;
            }
        }

        //Display the cipher message
        printf("%s\n", p);

        return 0;
    }
}


//Encrypt a character c using a key k
char cipher(char c, int k)
{
    char output = ' ';

    if(isalpha(c))
    {
        //Move the numbers to range [0 to 25] then back up based on capitalization
        if(isupper(c))
            output = (k + c - 'A') % 26 + 'A';
        else
            output = (k + c - 'a') % 26 + 'a';
    }

    return output;
}
