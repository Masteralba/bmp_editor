#include <stdio.h>
#include <stdlib.h>

#include "struct.h"

Rgb change_colour(Rgb main_pixel, Rgb color)
{
    main_pixel.r = color.r;
    main_pixel.g = color.g;
    main_pixel.b = color.b;
    return main_pixel;
}

Rgb** draw(Rgb** pixels, unsigned int x0, unsigned int y0, unsigned int x, unsigned int y, Rgb color)
{
    pixels[y0+y][x0+x] = change_colour(pixels[y0+y][x0+x], color);
    pixels[y0+y][x0-x] = change_colour(pixels[y0+y][x0-x], color);
    pixels[y0-y][x0+x] = change_colour(pixels[y0-y][x0+x], color);
    pixels[y0-y][x0-x] = change_colour(pixels[y0-y][x0-x], color);
    pixels[y0+x][x0+y] = change_colour(pixels[y0+x][x0+y], color);
    pixels[y0+x][x0-y] = change_colour(pixels[y0+x][x0-y], color);
    pixels[y0-x][x0+y] = change_colour(pixels[y0-x][x0+y], color);
    pixels[y0-x][x0-y] = change_colour(pixels[y0-x][x0-y], color);
    return pixels;
}

Rgb** draw_circle(Rgb** pixels, unsigned int x0, unsigned int y0, unsigned int r, Rgb color)
{
    int x = 0, y = r;
    int d = 3 - 2*r;
    pixels = draw(pixels, x0, y0, x, y, color);
    while(y>=x)
    {
        x++;
        if ( d > 0 )
        {
            y--;
            d = d + 4 * (x-y) + 10;
        }
        else d = d + 4*x + 6;
        pixels = draw(pixels, x0, y0, x, y, color);
    }
    return pixels;   
}

Rgb** function_1(Rgb** pixels, BitmapFileHeader* bmfh, BitmapInfoHeader* bmif, unsigned int x0, unsigned int y0, unsigned int r, unsigned int t, Rgb color, int flag, Rgb fill_color)
{
    /*if (flag)
    {
        size_t count = 0;
        while (count != t)
        {
            pixels = draw_circle(pixels, x0, y0, r-(count++), color);
        }
        return pixels;
    } else*/
    if (0) {}
    else
    {
        unsigned int H = bmif->height;
        unsigned int W = bmif->width;
        for(size_t y=y0-r; y<y0+r+1; y++)
        {
            for(size_t x=x0-r; x<x0+r+1; x++)
            {
                if ( ( (x-x0)*(x-x0) + (y-y0)*(y-y0) <= r*r) && ((x-x0)*(x-x0) + (y-y0)*(y-y0) >= (r-t)*(r-t) ) ) 
                {
                    pixels[y][x] = change_colour(pixels[y][x], color);
                }
            }
        }
        if (flag)
        {
            r -= t;
            for(size_t y=y0-r; y<y0+r+1; y++)
            {
                for(size_t x=x0-r; x<x0+r+1; x++)
                {
                    if ( ( (x-x0)*(x-x0) + (y-y0)*(y-y0) <= r*r)) 
                    {
                        pixels[y][x] = change_colour(pixels[y][x], fill_color);
                    }
                }
            }
        }
        return pixels;
    }
}

