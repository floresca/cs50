#define _XOPEN_SOURCE
#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, string argv[])
{
    //Check if argc is any number other than 2 (should only have 1 argument)
    if (argc != 2)
    {
        //tsk tsk
        printf("Enter one hash value\n");
        return 1;
    }

    char salt[3] = {argv[1][0], argv[1][1], '\0'};
    char crackers[] = {'a','\0'};
    
    char newA = crackers("%c\n", 'a');
    
    
    
    printf("%s\n", crackers);
}
