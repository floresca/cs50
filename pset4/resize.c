// Copies a BMP file

#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: Enter 3 arguments, a size, oldFileName.etc newFileName.etc\n");
        return 1;
    }

    // remember filenames int resizeBy = argv[1]
    int newSize = atoi(argv[1]);
    char *infile = argv[2];
    char *outfile = argv[3];

    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);


    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    //hold the old width and height
    long oldWidth = bi.biWidth;
    long oldHeight = abs(bi.biHeight);

    //New Width and Height parameters are calculated
    bi.biWidth = bi.biWidth * newSize;
    bi.biHeight = bi.biHeight * newSize;

    //New padding is put together
    int newPadding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    //New Image size and new total file size are calculated
    bi.biSizeImage = ((sizeof(RGBTRIPLE) * bi.biWidth) + newPadding) * abs(bi.biHeight);
    bf.bfSize = bi.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

    // write outfile's NEW BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's NEW BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    //Determine the old padding for each scanline
    int padding = (4 - (oldWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // iterate over infile's scanlines one at a time
    for (int i = 0; i < oldHeight; i++)
    {
        //loop through the scan line as many times as the image needs to be tall
        for (int tallness = 0; tallness < newSize; tallness++)
        {
            // iterate over each pixel in the old scanline
            for (int j = 0; j < oldWidth; j++)
            {
                // temporary storage
                RGBTRIPLE triple;

                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

                // write RGB triple to outfile
                for (int l = 1; l <= newSize; l++)
                {
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }
            }

            //skip over any padding from infile
            fseek(inptr, padding, SEEK_CUR);

            //Move back to the beggining of the scanline
            fseek(inptr, -(padding + (sizeof(RGBTRIPLE) * oldWidth)), SEEK_CUR);

            //add any necessary padding
            for (int k = 0; k < newPadding; k++)
            {
                fputc(0x00, outptr);
            }
        }

        //move cursor to the beggining of the next scanline
        fseek(inptr, (padding + (oldWidth * sizeof(RGBTRIPLE))), SEEK_CUR);
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}