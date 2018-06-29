#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, string argv[])
{
    //Check if argc is any number other than 2 (should only have 1 argument)
    if (argc != 2)
    {
        //tsk tsk
        printf("you've Done Goofed, enter one word\n");
        return 1;
    }

    //if the program gets past the first check do a cehck to make sure its a word
    //the loop grabs the argument being made
    for (int i = 0, k = strlen(argv[1]); i < k; i++)
    {
        //loop goes letter by letter to make sure they are letters and nothing else
        if (isalpha(argv[1][i]) == false)
        {
            printf("Thanks for playing, enter a word next time\n");
            return 1;
        }
    }

    //grab the plain text
    string plain = get_string("plaintext: ");
    //print the cypher after the loop
    printf("ciphertext: ");
    //location integer used for the KEY string array
    int loc = 0;

    //loop through plain string entered by user
    for (int i = 0, k = strlen(plain); i < k; i++)
    {
        //initialize they key to 0
        int key = 0;

        //check if key letter at location X is upper or lower then turn it into alpha
        if (isupper(argv[1][loc]))
        {
            key = argv[1][loc] - 65;
        }
        else
        {
            key = argv[1][loc] - 97;
        }

        //if its a character...
        if (isalpha(plain[i]))
        {
            //...check if the character is uppder case
            if (isupper(plain[i]))
            {
                //include the character into the cypher AFTER take away 65 to make A = 0
                //add the key, then modulo 26, then ADD 65 to turn it back into ASCII uppercase
                printf("%c", ((((plain[i] - 65) + key) % 26) + 65));
                loc++;
            }
            //...its probably lower case
            else
            {
                //include the character into the cypher AFTER take away 97 to make a = 0
                //add the key, then modulo 26, then ADD 97 to turn it back into ASCII lowercase
                printf("%c", ((((plain[i] - 97) + key) % 26) + 97));
                loc++;
            }
        }
        else
        {
            //if its not a letter then add the character directly into the cipher
            printf("%c", plain[i]);
        }


        //if the location counter equals the length of the key string then reset to 0 to go through key again
        if (strlen(argv[1]) == loc)
        {
            loc = 0;
        }

    }
    //add space
    printf("\n");
}