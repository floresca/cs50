#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>

int main(int numOfArguments, string argValues[])
{
    if (numOfArguments == 2)
    {
        char *file = argValues[1];
        FILE * card = fopen(file, "r");
        if (!card)
        {
            printf("No file/Nothing in file\n");
            return 2;
        }
        //define blockSize
        unsigned char blockSize[512];
        int imgcount = 0;
        int isFileOpen = 0;
        char *FileName = "car.jpg";
        FILE *newFiles = fopen(FileName, "w");

        do
        {
            //if the loop encounters a header file then do the following
            if (blockSize[0] == 0xff && blockSize[1] == 0xd8 && blockSize[2] == 0xff && (blockSize[3] & 0xf0) == 0xe0)
            {
                //increase the image counter
                imgcount++;

                // if (isFileOpen == 0)
                // {
                //     newFiles = fopen(FileName, "w");
                // }
                //if there is a file open then close it and set the open to 0
                if (isFileOpen == 1)
                {
                    fclose(newFiles);
                    isFileOpen = 0;
                    break;
                }

                //make a new file
                // newFiles = fopen(FileName, "w");
                fwrite(blockSize, 512, 1, newFiles);
                //File is now open again
                isFileOpen = 1;
            }
            //if the file is open the write to it
            else if (isFileOpen == 1)
            {
                //write the content to the currently open file
                fwrite(blockSize, 512, 1, newFiles);
            }

        }
        while(fread(blockSize, 512, 1, card) != 0);

        printf("Total number of jpgs is %i\n", imgcount);
        fclose(card);

        // fclose(newFiles);
        return 0;
    }
    else
    {
        printf("Usage: ./getJpg filename\n");
        return 1;
    }
}