#include <stdio.h>
#include <stdlib.h>

#include "struct.h"
#include "help_functions.h"

Rgb** function_2(Rgb** arr, BitmapFileHeader* bmfh, BitmapInfoHeader* bmif, const char* change_colour, unsigned int value)
{
    unsigned int W = bmif->width;
    unsigned int H = bmif->height;
    char key;
    switch (change_colour[0])
    {
    case 'r':
        for(size_t i=0; i<H; i++)
    {
        for(size_t j=0; j<W; j++)
        {
            arr[i][j].r = value;
        }
    }
        break;
    case 'g':
        for(size_t i=0; i<H; i++)
    {
        for(size_t j=0; j<W; j++)
        {
            arr[i][j].g = value;
        }
    }
        break;
    case 'b':
        for(size_t i=0; i<H; i++)
    {
        for(size_t j=0; j<W; j++)
        {
            arr[i][j].b = value;
        }
    }
        break;
    default:
        error("Error in 'change_component': invalid input value", bmfh, bmif, arr);
        break;
    }
    return arr;
}