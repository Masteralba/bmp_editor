#pragma once

#include "struct.h"

void free_memory(BitmapFileHeader* bmfh, BitmapInfoHeader* bmif, Rgb** pixels);

void error(const char* message, BitmapFileHeader* bmfh, BitmapInfoHeader* bmif, Rgb** pixels);

void flag_error(const char* message);

void print_help();

void print_file_header(BitmapFileHeader header);

void print_info_header(BitmapInfoHeader header);

void print_info(BitmapFileHeader* bmfh, BitmapInfoHeader* bmfi);

int check_digit(char* string);

void short_flag_argument_check(size_t count, int argc, char** argv, char** optarg, char c);

void check_opt_arg(char* optarg);