#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{

    int Digit;
    int placeCheck = 0;
    long long CardNumber = get_long_long("CreditCard Number: ");
    int totalCards = 0;
    int hold = 0;
    int release = 0;

        do
        {
            Digit = CardNumber % 10;
            placeCheck++;

            if (placeCheck == 1)
            {
                totalCards = Digit;
            }
            else if (placeCheck % 2 == 0)
            {
                if ((Digit * 2) > 9)
                {
                    hold = Digit * 2;
                    do
                    {
                        release = release + (hold % 10);
                        hold = hold / 10;
                    }
                    while (hold > 0);

                    totalCards = totalCards + release;
                    release = 0;
                }
                else {
                totalCards = totalCards + (Digit * 2);
                }
            }
            else if (placeCheck % 2 == 1)
            {
                totalCards = totalCards + Digit;
            }

            CardNumber = (CardNumber - Digit)/10;

        }
        while (CardNumber > 0);

    if (placeCheck != 13 && placeCheck != 15 && placeCheck != 16)
    {
        printf("Not a valid card number!\n");
    } else {
        printf("Thank you!\n");
    }
}

//Check if when the card is at 13, 15 or 16 it is a Visa, MasterCard or Amex
//We can check this by when place holder == X number && The first number is 3 etc