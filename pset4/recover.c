#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>

int main(int numOfArguments, string argValues[])
{
    //COmmand line arguments must equal 2
    if (numOfArguments == 2)
    {
        char *file = argValues[1];
        FILE * card = fopen(file, "r");

        //Contents of the card must be readable
        if (!card)
        {
            printf("No file/Nothing in file\n");
            return 2;
        }

        //define blockSize of 512
        unsigned char blockSize[512];

        //We will check if we are currently writing to a file by typing 0 if no, 1 if yes
        int isFileOpen = 0;

        //This will give the pictures a name
        char FileName[] = "000.jpg";

        //We will open the first file here
        FILE *newFiles = fopen(FileName, "w");

        //loop will read through the card.raw, 1 block of size 512 at a time as long as those dont == 0
        while(fread(blockSize, 512, 1, card) != 0)
        {
            //if the loop encounters a header file then do the following
            if (blockSize[0] == 0xff && blockSize[1] == 0xd8 && blockSize[2] == 0xff && (blockSize[3] & 0xf0) == 0xe0)
            {

                //close any open files and prepare the new file's name
                if (isFileOpen == 1)
                {
                    //close file
                    fclose(newFiles);
                    //set the files to 0, closed
                    isFileOpen = 0;

                    //make a new file name by making a counter
                    FileName[2]++;
                    //if the digit in the one's space becomes greater than ASCII 9 then...
                    if (FileName[2] > 57)
                    {
                        //increase digit in tenths space by 1
                        FileName[1]++;
                        //change ASCII on one's space to 0
                        FileName[2] = 48;
                        //if tenths space is greater than ASCII 9 then...
                        if (FileName[1] > 57)
                        {
                            //increase ASCII in hudredths space by 1
                            FileName[0]++;
                            //set ASCII in tenths space to 0
                            FileName[1] = 48;
                        }
                    }

                    //open a new file now that the name has been changed
                    newFiles = fopen(FileName, "w");
                }

                //write the current information to the new file
                fwrite(blockSize, 512, 1, newFiles);
                //Change to file open 1, true so we write to the new file until we encounter another jpg
                isFileOpen = 1;
            }

            //If we encountered a JPG before and have yet to encounter another one then...
            else if (isFileOpen == 1)
            {
                //write the content to the currently open file
                fwrite(blockSize, 512, 1, newFiles);
            }

        }
        //close the card, just in case
        fclose(card);
        //close any ingering open files
        fclose(newFiles);
        return 0;
    }
    //if the number of arguments is not 2 then prompt the user
    else
    {
        printf("Usage: ./getJpg filename\n");
        return 1;
    }
}