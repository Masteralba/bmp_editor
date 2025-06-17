#include <stdio.h>
#include <stdlib.h>

#include "struct.h"
#include "help_functions.h"


Rgb** function_3(Rgb** arr, BitmapFileHeader* bmfh, BitmapInfoHeader* bmif, unsigned int n, unsigned int m, unsigned int thickness, Rgb color)
{
    unsigned int H = bmif->height;
    unsigned int W = bmif->width;
    int dest_x = (int)W/n+thickness;
    for (int x = dest_x; x < W; x+=dest_x) {
        for (int y = 0; y < H; y++) {
            for (int j = 0; j < thickness; j++) {
                if (H-y >= 0 && x-j >= 0 && x-j < W && H-y < H) {
                    arr[H-y][x-j].r = color.r;
                    arr[H-y][x-j].g = color.g;
                    arr[H-y][x-j].b = color.b;
                }
            }
        } 
    }
    int dest_y = H/m+thickness;
    for (int y = dest_y; y < H; y+=dest_y) {
        for (int x = 0; x < W; x++) {
            for (int j = 0; j < thickness; j++) {
                if (H - y + j >= 0 && x >= 0 && x < W && H - y + j < H)
                {
                    arr[H - y + j][x].r = color.r;
                    arr[H - y + j][x].g = color.g;
                    arr[H - y + j][x].b = color.b;
                }
            }
        } 
    }
    return arr;
}