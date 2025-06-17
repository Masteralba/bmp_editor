#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "struct.h"
#include "define.h"

void free_memory(BitmapFileHeader* bmfh, BitmapInfoHeader* bmif, Rgb** pixels)
{
    if (pixels != NULL)
    {
        int H = 0;
        if ( bmif != NULL) H = bmif->height;
        {
            for ( size_t i=0; i < H; i++) free(pixels[i]);
        }
    }
    free(pixels);
    free(bmif);
    free(bmfh);
}

void error(const char* message, BitmapFileHeader* bmfh, BitmapInfoHeader* bmif, Rgb** pixels)
{
    fprintf(stderr, "%s\n", message);
    free_memory(bmfh, bmif, pixels);
    exit(42);
}

void flag_error(const char* message)
{
    fprintf(stderr, "%s\n", message);
    exit(42);
}

void print_help()
{
    puts("Course work for option 4.11, created by Khorchev Gleb");
    puts("ИМЯ КОМАНДЫ:");
    puts("\tИспользуйте имя ./cw, чтобы запустить программу.");
    puts("\tПо-умолчанию последним аргументом утилите должно передаваться имя входного bmp файла.");
    puts("\tИмя выходного файла по умолчанию - out.bmp, однако это возможным переопределить ключом -o, --output.");
    puts("\nСИНТАКСИС:");
    puts("\t./cw [options] [file]");
    puts("\nОПИСАНИЕ:");
    puts("\t, --circle");
    puts("\t\tРисование окружности. Флаги для выполнения команды:");
    puts("\t\t\t-a, --center - координаты центра в формате x.y");
    puts("\t\t\t-r, --radius радиус окружности");
    puts("\t\t\t-t, --thickness толщина окружности");
    puts("\t\t\t-c, --color [rrr.ggg.bbb] - цвет, окружности в формате rgb");
    puts("\t\t\t-f, --fill - необязательный параметр, отвечает за заливку окружности");
    puts("\t\t\t-g, --fill_color [rrr.ggg.bbb] - цвет, в который будет залита окружность в формате rgb");
    puts("\t, --rgbfilter");
    puts("\t\tФильтр rgb-компонент. Флаги для выполнения команды:");
    puts("\t\t\t-e, --component_name [red/blue/green] - название компоненты, которую надо заменить");
    puts("\t\t\t-v, --comopnent_value [rrr.ggg.bbb] - новое значение компоненты для каждого пикселя");
    puts("\t-s, --split");
    puts("\t\tРазделяет изображение на N*M частей. Флаги для выполнения команды:");
    puts("\t\t\t-x, --number_x - число частей по оси X. Должно быть больше 1");
    puts("\t\t\t-y, --number_y - число частей по оси Y. Должно быть больше 1");
    puts("\t\t\t-t, --thickness - толщина линий разбиения. Должна быть больше 0");
    puts("\t\t\t-c, --color [rrr.ggg.bbb] - цвет линии разбиения в формате rgb");
    //puts("\t-i, --input");
    //puts("\t\tФлаг для указания входного файла. В качестве аргумента требует имя файла.");
    puts("\t-o, --output");
    puts("\t\tПереопределяет имя выходного файла. В качестве аргумента требует имя файла.");
    puts("\t-i, --info");
    puts("\t\tВыводит информацию о BMP-файле.");
    puts("\t-h, --help");
    puts("\t\tВыводит данную справку.");
}

void print_file_header(BitmapFileHeader header)
{
    printf("signature:\t%x (%hu)\n", header.signature,header.signature);
    printf("filesize:\t%x (%u)\n", header.filesize,header.filesize);
    printf("reserved1:\t%x (%hu)\n", header.reserved1,header.reserved1);
    printf("reserved2:\t%x (%hu)\n", header.reserved2,header.reserved2);
    printf("pixelArrOffset:\t%x (%u)\n", header.pixelArrOffset, header.pixelArrOffset);
}
void print_info_header(BitmapInfoHeader header)
{
    printf("headerSize:\t%x (%u)\n", header.headerSize,header.headerSize);
    printf("width: \t%x (%u)\n", header.width, header.width); 
    printf("height: \t%x (%u)\n", header.height,header.height);
    printf("planes: \t%x (%hu)\n", header.planes,header.planes);
    printf("bitsPerPixel:\t%x (%hu)\n", header.bitsPerPixel, header.bitsPerPixel);
    printf("compression:\t%x (%u)\n", header.compression, header.compression);
    printf("imageSize:\t%x (%u)\n", header.imageSize,header.imageSize);
    printf("xPixelsPerMeter:\t%x (%u)\n", header.xPixelsPerMeter, header.xPixelsPerMeter);
    printf("yPixelsPerMeter:\t%x (%u)\n", header.yPixelsPerMeter, header.yPixelsPerMeter);
    printf("colorsInColorTable:\t%x (%u)\n", header.colorsInColorTable, header.colorsInColorTable);
    printf("importantColorCount:\t%x (%u)\n", header.importantColorCount, header.importantColorCount);
}


void print_info(BitmapFileHeader* bmfh, BitmapInfoHeader* bmfi)
{
    print_file_header(*bmfh);
    print_info_header(*bmfi);
}

int check_digit(char* string)
{
    for (size_t i =0; i<strlen(string); i++)
    {
        if (!isdigit(string[i])) return 0;
    }
    return 1;
}

void short_flag_argument_check(size_t count, int argc, char** argv, char** optarg, char c)
{
    if (count+2 <= argc)
    {
        *optarg = argv[count];    
    } else
    {
      char str[BUFFER];
      sprintf(str, "No argument for flag %c", c);
      flag_error(str);
    }    
}


void check_opt_arg(char* optarg)
{
  if (strlen(optarg) >= 2)
  {
    if (optarg[0] == '-' && optarg[1] == '-')
    {
      flag_error("");
      exit(42);
    }
  }
}
