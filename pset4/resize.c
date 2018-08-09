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
    int size = atoi(argv[1]);
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

    else
    {
        //read the infile and figure out the size of the padding
        int totalOldPadding = bi.biSizeImage - (abs(bi.biWidth * bi.biHeight) * 3);
        int oldPaddingEAline = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
        int newWidth = bi.biWidth * size;
        int newHeight = abs(bi.biHeight * size);
        int newPadding = (4 - (newWidth * sizeof(RGBTRIPLE)) % 4) % 4;
        int newTotalPadding = newPadding * newHeight;
        int newBiSize = ((sizeof(RGBTRIPLE) * newWidth) + newPadding) * abs(newHeight);
        int newBfSize = newBiSize + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

        printf("size is %i, new width is %i, new height is %i\n", size, newWidth, newHeight);
        printf("total padding of original is %i, new total padding is %i\n", totalOldPadding, newTotalPadding);
        printf("padding per line of old image is %i while new image is %i\n", oldPaddingEAline, newPadding);
        printf("original image size is %i but the new image size is %i\n", bi.biSizeImage, newBiSize);
        printf("size of complete old image file %i, new image size is %i\n", bf.bfSize, newBfSize);
        printf("total old image pixels is %i while new image total is %i\n", (bi.biWidth * abs(bi.biHeight)), (newWidth * newHeight));

        //change bi.biWidth and bi.biHeight
        //save it back into bi.Size/bf/size etc

        //Loop through the bmp where i < the qty of structures (bi + bf + RGBtriples + newpadding)
            //if the structure = 14 then push the new bi
            //if the structure = 40 then push the new bf
            //if the structure = 3 then push RGB triple
            //if the structure = 1 then push padding (if the new width is not multiple of 4 then pad + reduce padding)

        for (int i = 0, h = abs(bi.biHeight*size); i < h; i++)
        {
            for (int j = 0, w = bi.biWidth; j < w; j++)
            {
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
                RGBTRIPLE triple;
                for (int k = 0; k < size; k++)
                {
                    fwrite(triple, sizeof(RGBTRIPLE), 1, outptr);
                }
            }
        }



        //loop through the infile
        //if the size of the item is 14 then change
        //if the size of the item is 40 then change biSize, biHeight, biSizeImage
        //if the size is 3 then multiply the pixel by n
        //if new width is not a multiple of 4 then add a padding
        //repeat as long as new width is not a multiple of 4
        //remove 1 from the height and write the same line again

    }

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // determine padding for scanlines
    int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        // iterate over pixels in scanline
        for (int j = 0; j < bi.biWidth; j++)
        {
            // temporary storage
            RGBTRIPLE triple;

            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

            // write RGB triple to outfile
            fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
        }

        // skip over padding, if any
        fseek(inptr, padding, SEEK_CUR);

        // then add it back (to demonstrate how)
        for (int k = 0; k < padding; k++)
        {
            fputc(0x00, outptr);
        }
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}
