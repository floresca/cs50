#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, string argv[])
{
    //Check if argc is any number other than 2
    if (argc != 2)
    {
        //give an error
        return 1;
    }

    //Turn the key from a string to a character
    int key = atoi(argv[1]);
    //grab the plain text
    string plain = get_string("plaintext: ");

    //print the cypher after the loop
    printf("ciphertext: ");

    //loop through plain
    for (int i = 0, k = strlen(plain); i < k; i++)
    {
        //if its a character
        if (isalpha(plain[i]))
        {
            //check if the character is uppder case
            if (isupper(plain[i]))
            {
                //include the character into the cypher AFTER take away 65 to make A = 0
                //add the key, then modulo 26, then ADD 65 to turn it back into ASCII uppercase
                printf("%c", ((((plain[i] - 65) + key) % 26) + 65));
            }
            //check if it is lowercase instead
            else if (islower(plain[i]))
            {
                //include the character into the cypher AFTER take away 97 to make a = 0
                //add the key, then modulo 26, then ADD 97 to turn it back into ASCII lowercase
                printf("%c", ((((plain[i] - 97) + key) % 26) + 97));
            }
        }
        else
        {
            //if its not a character then add the character directly into the cypher
            printf("%c", plain[i]);
        }

    }
    //add space
    printf("\n");
}