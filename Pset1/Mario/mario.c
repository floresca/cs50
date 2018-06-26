#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int height;


    do
    {
        printf("Enter a height greater than 0 but no greater than 23\n");
        height = get_int("pyramid height: ");
    }
    while (height < 1 || height > 23);

    int width = height;

    for (int i = -1; i < height; i++)
    {
        int hash = height - width;
        for (int space = 0; space < width; space++)
        {
            printf(" ");
        }

        for (int leftPyramid = 0; leftPyramid < hash; leftPyramid++)
        {
            printf("#");
        }

        printf("  ");

        for (int rightPyramid = 0; rightPyramid < hash; rightPyramid++)
        {
            printf("#");
        }

        width--;
        printf("\n");
    }
}