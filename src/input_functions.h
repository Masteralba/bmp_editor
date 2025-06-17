#include "struct.h"

Rgb **read_bmp(char file_name[], BitmapFileHeader* bmfh, BitmapInfoHeader* bmif);

void write_bmp(char file_name[], Rgb **arr, unsigned int H, unsigned int W, BitmapFileHeader bmfh, BitmapInfoHeader bmif);