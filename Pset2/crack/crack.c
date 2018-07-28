// #define _XOPEN_SOURCE
#define _GNU_SOURCE
#include <cs50.h>
#include <crypt.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include <unistd.h>

int main(int argc, string argv[])
{
    //Check if argc is any number other than 2 (should only have 1 argument)
    if (argc != 2)
    {
        //tsk tsk
        printf("Enter only one hash value\n");
        return 1;
    }

    char salt[3] = {argv[1][0], argv[1][1], '\0'};
    int crackerCount = 0;
    char crackers[6] = {'a'};
    memset(crackers, 0, crackerCount*sizeof(int));
    char *hashbrown = salt;
    // int crackerJack = (sizeof(crackers) / sizeof (crackers[0])) - 1;
    // size_t manyCrackers = crackerJack + 1;
    // string caramel = crackers;
    char *caramelized;

    do
    {
        caramelized = crypt(crackers, hashbrown);
        if (strcmp(caramelized, argv[1]) == 0)
        {
            break;
        }

        else if (strcmp(caramelized, argv[1]) != 0)
        {

            //If there is only one letter in the chracters we need to crack then update those letters
            if (crackerCount == 0)
            {
                crackers[crackerCount]++;
                if (crackers[crackerCount] == 122)
                {
                    crackers[crackerCount] = 65;
                }
                else if (crackers[crackerCount] == 90)
                {
                    crackerCount++;
                    crackers[crackerCount] = 'a';
                    crackers[crackerCount - 1] = 'a';
                    crackers[crackerCount + 1] = '\0';
                    continue;
                }
            }

            //If there are two letters in the cracker
            if (crackerCount == 1)
            {
                crackers[crackerCount]++;
                if (crackers[crackerCount] == 122){
                    crackers[crackerCount] = 65;
                }
                else if (crackers[crackerCount] == 90 && crackers[crackerCount - 1] != 90)
                {
                    crackers[crackerCount] = 'a';
                    crackers[crackerCount - 1]++;
                    if (crackers[crackerCount - 1] == 122)
                    {
                        crackers[crackerCount - 1] = 65;
                    }
                }
                else if (crackers[crackerCount] == 90 && crackers[crackerCount - 1] == 90)
                {
                    crackerCount++;
                    crackers[crackerCount] = 'a';
                    crackers[crackerCount - 1] = 'a';
                    crackers[crackerCount - 2] = 'a';
                    crackers[crackerCount + 1] = '\0';
                    continue;
                }
            }

            //If there are three letters in the cracker
            if (crackerCount == 2)
            {
                crackers[crackerCount]++;
                if (crackers[crackerCount] == 122){
                    crackers[crackerCount] = 65;
                }
                else if (crackers[crackerCount] == 90 && crackers[crackerCount - 1] != 90)
                {
                    crackers[crackerCount] = 'a';
                    crackers[crackerCount - 1]++;
                    if (crackers[crackerCount - 1] == 122)
                    {
                        crackers[crackerCount - 1] = 65;
                    }
                }
                else if (crackers[crackerCount] == 90 && crackers[crackerCount - 1] == 90 && crackers[crackerCount - 2] != 90)
                {
                    crackers[crackerCount] = 'a';
                    crackers[crackerCount - 1] = 'a';
                    crackers[crackerCount - 2]++;
                    if (crackers[crackerCount - 2] == 122)
                    {
                        crackers[crackerCount - 2] = 65;
                    }
                }
                else if (crackers[crackerCount] == 90 && crackers[crackerCount - 1] == 90 && crackers[crackerCount - 2] == 90)
                {
                    crackerCount++;
                    crackers[crackerCount] = 'a';
                    crackers[crackerCount - 1] = 'a';
                    crackers[crackerCount - 2] = 'a';
                    crackers[crackerCount - 3] = 'a';
                    crackers[crackerCount + 1] = '\0';
                    continue;
                }
            }

            //If there are four letters in the cracker
            // if (crackerCount == 3)
            //If there are five letters in the cracker
            // if (crackerCount == 4)

        }


        //If none of the answers up there worked then turn all characters in the answer string back to "a" and add a new character
        // else
        // {
        //     for (int i = 0, k = strlen(answer); i < k; i++)
        //     {
        //         answer[i] = "a";
        //         answer("%c", "a");
        //     }
        // }

    }
    while (strcmp(caramelized, argv[1]) != 0);

    //null terminator added to the end of the character array
    crackerCount++;
    crackers[crackerCount] = '\0';

    //print the password
    printf("%s\n", crackers);

    // printf("%i\n", crackerJack);
    printf("%s\n", hashbrown);
}

// 50JGnXUgaafgc