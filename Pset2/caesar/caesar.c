#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>


int main(int argc, string argv[])
{
    if (argc != 2)
    {
        return 1;
    }

    int key = atoi(argv[1]);
    string plain = get_string("plaintext: ");

    for (int i = 0, k = strlen(plain); i < k; i++)
    {

    }


    //when all that is done ask for the plaintext using get_string
    //grab each character in the plain text and run it against the key
        //For each character run the key
        //turn the character into its ASCII code (or check that its good)
        //if the character doesnt fall in the capital letters or the lower case letters then print it as is
        //if the character key takes it over the last ASCII (Z) then loop to A
    //when loop is done print the cypher text

    //isalpha('') will return true is character is a letter
    //isupper('') checks whether its upper case
    //islower('') checks whether its lower case
    //strlen() gives the string length per character

    //if the ASCII is capital then -65
    //if ASCII lowercase then -97
    //alphabetical index loop
        //(value + key) % 26
    //bring result back to ASCII

    eprintf("%i\n", key);
}


//+++check that argc is no more and no less than 2
    //+++turn the string number in argv[] into an integer using atoi (check the library)
        //+++what if its not all numbers? cehck library