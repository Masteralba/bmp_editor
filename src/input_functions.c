#include <stdio.h>
#include <stdlib.h>

#include "help_functions.h"
#include "struct.h"

#define BITS_PER_PIXEl 24
#define PLANES 1
#define SIGNATURE 19778

Rgb **read_bmp(char file_name[], BitmapFileHeader* bmfh, BitmapInfoHeader* bmif)
{
    FILE *f = fopen(file_name, "rb");
    if ( f == NULL )
    {
        error("Error in 'read_bmp': file was not read sucsessfully", bmfh, bmif, NULL);
    }
    unsigned int readed = 0;
    readed += fread(bmfh, 1, sizeof(BitmapFileHeader), f);
    if ( bmfh->signature != SIGNATURE)
    {
        fclose(f);
        error("Error in 'read_bmp': file is not bmp format", bmfh, bmif, NULL);
    }
    readed += fread(bmif, 1, sizeof(BitmapInfoHeader), f);
    if ( bmif->headerSize != 40)
    {
        fclose(f);
        error("Error in 'read_bmp': cant handle this version of bmp", bmfh, bmif, NULL);
    }
    if ( bmif->planes != PLANES)
    {
        fclose(f);
        error("Error in 'read_bmp': planes are not equal to 1", bmfh, bmif, NULL);
    }
    if ( bmif->bitsPerPixel != BITS_PER_PIXEl)
    {
        error("Error in 'read_bmp': bits_per_pixel are not equal to 24", bmfh, bmif, NULL);
    }
    if ( bmif->compression != 0)
    {
        fclose(f);
        error("Error in 'read_bmp': cant handle images with compression", bmfh, bmif, NULL);
    }
    if ( bmif->colorsInColorTable != 0)
    {
        fclose(f);
        error("Error in 'read_bmp': cant handle images with color table", bmfh, bmif, NULL);
    }
    unsigned int H = bmif->height;
    unsigned int W = bmif->width;
    unsigned int padding = (W * sizeof(Rgb)) % 4;
    if ( padding ) padding = 4 - padding;
    size_t total_size = W * sizeof(Rgb) + padding;
    Rgb **arr = (Rgb**)malloc(H * sizeof(Rgb*));
    if ( arr == NULL)
    {
        fclose(f);
        error("Error in 'read_bmp': cannot allocate memory", bmfh, bmif, arr);
    }
    for(int i = 0; i < H; i++)
    {
        arr[i] = (Rgb*)calloc(1, total_size);
        if ( arr[i] == NULL)
        {
            fclose(f);
            error("Error in 'read_bmp': cannot allocate memory", bmfh, bmif, arr);
        }
        readed += fread(arr[i], 1, W * sizeof(Rgb) + padding,f);
    }
    if (readed!= bmfh->filesize)
    {
        
    }
    fclose(f);
    return arr;
}



void write_bmp(char file_name[], Rgb **arr, unsigned int H, unsigned int W, BitmapFileHeader bmfh, BitmapInfoHeader bmif)
{
    FILE *ff = fopen(file_name, "wb");
    if (!ff) error("Error in 'write_bmp': file was not read sucsessfully", &bmfh, &bmif, NULL);    
    fwrite(&bmfh, 1, sizeof(BitmapFileHeader), ff);
    fwrite(&bmif, 1, sizeof(BitmapInfoHeader), ff);
    unsigned int padding = (W * sizeof(Rgb)) % 4;
    if ( padding ) padding = 4 - padding;
    for(int i = 0; i < H; i++)
    {
        fwrite(arr[i], 1, W * sizeof(Rgb) + padding, ff);
    }
    fclose(ff);
}