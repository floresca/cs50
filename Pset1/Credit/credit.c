#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{

    int Digit;
    int counter = 0;
    long long CardNumber = get_long_long("CreditCard Number: ");
    int totalCards = 0;
    int hold = 0;
    int release = 0;
    int validityBucket = 0;
    int validityCheck = 0;

    do
    {
        Digit = CardNumber % 10; // Grab the last digit
        counter++;  //increase coounter by 1

        //If coutner is 1 then grab the very first number
        if (counter == 1)
        {
            totalCards = Digit;
        }

        //else if the counter's modulo is 0 grab it so we can work with it
        else if (counter % 2 == 0)
        {
            //check if the product of the number multiplied by 2 is greater than 9
            if ((Digit * 2) > 9)
            {
                //If it IS greater than 9 then we need to loop through it and grab each individual digit
                hold = Digit * 2;
                do
                {
                    release = release + (hold % 10);
                    hold = hold / 10;
                }
                while (hold > 0);

                //Add together the individual Digits of the product then add the result to our TOTAL SUM
                totalCards = totalCards + release;
                release = 0;
            }
            else {
                //If the product of the digit and 2 is less than 9 then just add the product to the TOTAL SUM
                totalCards = totalCards + (Digit * 2);
            }
        }
        //If the modulo equals 1 then grab this digit and add it to the TOTAL SUM
        else if (counter % 2 == 1)
        {
            totalCards = totalCards + Digit;
        }


        if (counter == 14)
        {
            validityBucket = Digit;
        }

        else if (counter == 15 && totalCards % 10 == 0)
        {
            validityCheck = validityBucket + Digit;
            if (Digit == 3 && (validityCheck == 7 || validityCheck == 10))
            printf("AMEX\n");
        }

        else if (counter == 15)
        {
            validityBucket = Digit;
        }

        else if (counter == 16 && totalCards % 10 == 0)
        {
            validityCheck = validityBucket + Digit;
            if (Digit == 5 && (validityCheck == 6 || validityCheck == 7 || validityCheck == 8 || validityCheck == 9 || validityCheck == 10))
            {
                printf("MASTER CARD\n");
            }
            else if (Digit == 4)
            {
                printf("VISA\n");
            }
        }

        //remove the digit we've been working with so far
        CardNumber = (CardNumber - Digit)/10;

    }
    while (CardNumber > 0); //Repeat until there are no digits left

    if (counter == 13)
    {
        if (Digit == 4 && totalCards % 10 == 0)
        {
            printf("VISA\n");
        }
    }
    // else
    // {
    //     printf("INVALID\n");
    // }
}