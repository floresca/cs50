#include <cs50.h>
#include <stdio.h>

int main(void)
{

    int Digit;
    int counter = 0;
    long long CardNumber = get_long_long("CreditCard Number: ");
    int LuhnCheck = 0;
    int hold = 0;
    int release = 0;
    int validityAMEX = 0;
    int validityVIMC = 0;
    int validityCheck = 0;

    do
    {
        Digit = CardNumber % 10; // Grab the last digit
        counter++;  //increase coounter by 1 to note the current digit we are working with (starting with the last number)

        //If coutner is 1 then grab the very last number
        if (counter == 1)
        {
            //add the very last number to the sum we will use for the Luhn check
            LuhnCheck = Digit;
        }

        //else if the counter's modulo is 0 grab it so we can work with it (this will grab every other number in the card starting with second to last)
        else if (counter % 2 == 0)
        {
            //check if the product of the number we grabbed, multiplied by 2, is greater than 9
            if ((Digit * 2) > 9)
            {
                //If it IS greater than 9 then we need to loop through it and grab each individual digit (we CANNOT sum a 2 digit number into Luhn's algorithm)
                hold = Digit * 2;
                do
                {
                    //hold has the 2 digit number, now we loop through it and grab each number
                    release = release + (hold % 10);
                    hold = hold / 10;
                }
                while (hold > 0);

                //Add together the individual Digits of the product then add the result to our Luhn number
                LuhnCheck = LuhnCheck + release;
                release = 0; //set release back to 0 in case we find any more 2 digit products
            }
            else
            {
                //If the product of the digit and 2 is less than 9 then just add the product to the Luhn number
                LuhnCheck = LuhnCheck + (Digit * 2);
            }
        }

        //If the modulo equals 1 then grab this digit and add it to the Luhn number
        else if (counter % 2 == 1)
        {
            LuhnCheck = LuhnCheck + Digit;
        }

        //when counter reaches 14 grab the number for a check against AMEX
        if (counter == 14)
        {
            validityAMEX = Digit;
        }

        //when counter reaches 15 grab the number for a check against VISA and MASTER CARD
        else if (counter == 15)
        {
            validityVIMC = Digit;
        }

        //remove the digit we've been working with so far to make room for the next one
        CardNumber = (CardNumber - Digit) / 10;

    }
    while (CardNumber > 0); //Repeat until there are no digits left

//Below we will check if our credit cards work!
    //First step is to see if the number passes the Luhn algorithm check. if it does we go inside
    if (LuhnCheck % 10 == 0 || counter < 13 || counter > 16)
    {
        //We check if the card counter is 13
        if (counter == 13)
        {
            //if the card count is 13 we check wether the last digit taken from the card (the first digit of the card) is a 4
            if (Digit == 4)
            {
                //if all of the above are true then the card is a VISA
                printf("VISA\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }

        //if the card passes Luhn and is 15 digits long
        else if (counter == 15)
        {
            //we cehck the validity of the card by grabbing the 14th digit (saved in validityAMEX) and adding it to the 15th digit
            //For AMEX validityCheck should equal 7 OR 10
            validityCheck = validityAMEX + Digit;
            if (Digit == 3)
            {
                if (validityCheck == 7 || validityCheck == 10)
                {
                    printf("AMEX\n");
                }
                else
                {
                    printf("INVALID\n");
                }
            }
            else
            {
                printf("INVALID\n");
            }
        }

        //is the card length 16 digits after Luhn is good?
        else if (counter == 16)
        {
            //Grab the 15th digit saved in validityVIMC and add it to the 16th
            validityCheck = validityVIMC + Digit;

            //if the first digit is 5 and validityCheck matches then MASTER CARD
            if (Digit == 5 && (validityCheck == 6 || validityCheck == 7 || validityCheck == 8 || validityCheck == 9 || validityCheck == 10))
            {
                printf("MASTERCARD\n");
            }

            //if the Luhn passes, and the card is 16 long, and the first digit is 4 then its VISA
            else if (Digit == 4)
            {
                printf("VISA\n");
            }

            //else all is lost and nothing is true any more and card is INVALID
            else
            {
                printf("INVALID\n");
            }
        }
        else
        {
            printf("INVALID\n");
        }
    }

    //If the Luhn check is failed then don't bother with anything else, the card is INVALID
    else
    {
        printf("INVALID\n");
    }
}