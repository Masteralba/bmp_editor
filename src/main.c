#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>
#include <regex.h>

#include "struct.h"
#include "define.h"

#include "function_1.h"
#include "function_2.h"
#include "function_3.h"
#include "help_functions.h"
#include "input_functions.h"


int flag;
int extra_flag = 0;

int
main (int argc, char **argv)
{
  int c;
  static struct option long_options[] =
  {
    {"circle", no_argument,       &flag, CIRLCE},
    {"rgbfilter",   no_argument,       &flag, RGBFILTER},
    {"split", no_argument,       &flag, SPLIT},
    {"help",   no_argument,       &flag, HELP},
    {"info",  no_argument, &flag, INFO},

    {"center",     required_argument,       0, CENTER},
    {"radius",  required_argument,       0, RADIUS},
    {"thickness",  required_argument, 0, THICKNESS},
    {"color",  required_argument, 0, COLOR},
    {"fill",  no_argument, 0, FILL},
    {"fill_color",    required_argument, 0, FILL_COLOR},
    {"component_name",    required_argument, 0, COMPONENT_NAME},
    {"component_value",     required_argument,       0, COMPONENT_VALUE},
    {"number_x",  required_argument,       0, NUMBER_X},
    {"number_y",  required_argument, 0, NUMBER_Y},
    {"output",  required_argument, 0, OUTPUT_NAME},
    {0, 0, 0, 0}
  };

  unsigned int x_coord, y_coord, radius, fill = 0, component_value, thickness, number_x, number_y;
  Rgb fill_color, color;
  char component_name[BUFFER];

  char* regexString_bmp = "(^[a-zA-Z0-9]+\\.bmp$)";
  char* regexString_point = "^([0-9]+)\\.([0-9]+)$";
  char* regexString_color = "^([0-9]+)\\.([0-9]+)\\.([0-9]+)$"; 

  size_t maxGroups_bmp = 1, maxGroups_point = 3, maxGroups_color = 4;
  regex_t regexCompiled_bmp, regexCompiled_point, regexCompiled_color;
  regmatch_t groupArray_bmp[maxGroups_bmp], groupArray_point[maxGroups_point], groupArray_color[maxGroups_color];

  /* getopt_long stores the option index here. */
  int option_index = 0;
  
  int temp; // temp variable needed further
  char filename[BUFFER]; 
  char outputname[BUFFER] = "out.bmp";

  while (1)
  {
    c = getopt_long(argc, argv, "hartcfgevxyoi", long_options, &option_index);
    if ( optarg != NULL )check_opt_arg(optarg);
      /* Detect the end of the options. */
    if (c == -1)
      break;
    switch (c)
      {
      case 0:
        if (extra_flag) flag_error("Error in flags. You have put more then one key flag");
        if ( flag == HELP)
        {
          print_help();
          return 0;
        }
        extra_flag = 1;
        break;
      case 'h':
        print_help();
        return 0;
        break;
      case 'a':
        short_flag_argument_check(optind, argc, argv, &optarg, c);
      case CENTER:
        if (regcomp(&regexCompiled_point, regexString_point, REG_EXTENDED))
        {
          flag_error("Regex compilation porblem");
        }
        if (regexec(&regexCompiled_point, optarg, maxGroups_point, groupArray_point, 0) == 0)
        {
          char buf1[BUFFER];
          char buf2[BUFFER];
          for(size_t i = groupArray_point[1].rm_so; i < groupArray_point[1].rm_eo; i++)
          {
            buf1[i] = optarg[i];
          }
          for(size_t i = groupArray_point[2].rm_so; i < groupArray_point[2].rm_eo; i++)
          {
            buf2[i-groupArray_point[2].rm_so] = optarg[i];
          }
          x_coord = atoi(buf1), y_coord = atoi(buf2); // no need in coord check becouse of regex
        }
        else
        {
          flag_error("regex error in coords");
          exit(42);
        }
        break;
      case 'r':
        short_flag_argument_check(optind, argc, argv, &optarg, c);
      case RADIUS:
        if ( optarg == NULL)
        {
          printf("no argument in radius\n");
          exit(42);
        }
        if (check_digit(optarg))
        {
          temp = atoi(optarg);
          if ( temp > 0)
          {
            radius = temp;
          } else flag_error("Invalid radius argument");
        } else flag_error("Invalid radius argument");
        break;
      case 't':
        short_flag_argument_check(optind, argc, argv, &optarg, c);
      case THICKNESS:
        temp = atoi(optarg);
        if ( temp > 0)
        {
          thickness = temp;
        }
        break;
      case 'c':
        short_flag_argument_check(optind, argc, argv, &optarg, c);
      case COLOR:
        if (regcomp(&regexCompiled_color, regexString_color, REG_EXTENDED))
        {
          flag_error("Regex compilation porblem");
        }
        if (regexec(&regexCompiled_color, optarg, maxGroups_color, groupArray_color, 0) == 0)
        {
          char buf1[BUFFER];
          char buf2[BUFFER];
          char buf3[BUFFER];
          for(size_t i = groupArray_color[1].rm_so; i < groupArray_color[1].rm_eo; i++)
          {
            buf1[i] = optarg[i];
          }
          for(size_t i = groupArray_color[2].rm_so; i < groupArray_color[2].rm_eo; i++)
          {
            buf2[i-groupArray_color[2].rm_so] = optarg[i];
          }
          for(size_t i = groupArray_color[3].rm_so; i < groupArray_color[3].rm_eo; i++)
          {
            buf3[i-groupArray_color[3].rm_so] = optarg[i];
          }
          color.r = atoi(buf1), color.g = atoi(buf2), color.b = atoi(buf3);
          if (color.r >= 256 || color.b >= 256 || color.g >= 256) 
          {
            flag_error("Invalid color value");
          }
        }
        else
        {
          flag_error("Invalid caolor data. Color must be *.*.*.");
        }
        break;
      case 'f':  
      case FILL:
        fill = 1;
        break;
      case 'g':
        short_flag_argument_check(optind, argc, argv, &optarg, c);  
      case FILL_COLOR:
        if (regcomp(&regexCompiled_color, regexString_color, REG_EXTENDED))
        {
          flag_error("Regex compilation porblem");
        }
        if (regexec(&regexCompiled_color, optarg, maxGroups_color, groupArray_color, 0) == 0)
        {
          char buf1[BUFFER];
          char buf2[BUFFER];
          char buf3[BUFFER];
          for(size_t i = groupArray_color[1].rm_so; i < groupArray_color[1].rm_eo; i++)
          {
            buf1[i] = optarg[i];
          }
          for(size_t i = groupArray_color[2].rm_so; i < groupArray_color[2].rm_eo; i++)
          {
            buf2[i-groupArray_color[2].rm_so] = optarg[i];
          }
          for(size_t i = groupArray_color[3].rm_so; i < groupArray_color[3].rm_eo; i++)
          {
            buf3[i-groupArray_color[3].rm_so] = optarg[i];
          }
          fill_color.r = atoi(buf1), fill_color.g = atoi(buf2), fill_color.b = atoi(buf3);
          if (fill_color.r >= 256 || fill_color.b >= 256 || fill_color.g >= 256)
          {
            flag_error("Invalid color value");
          }
        }
        else
        {
          flag_error("Invalid color data. Color must be *.*.*.");
          exit(42);
        }
        break;
      case 'e':
        short_flag_argument_check(optind, argc, argv, &optarg, c);  
      case COMPONENT_NAME:
        if ( !strcmp("red", optarg) || !strcmp("blue", optarg) || !strcmp("green", optarg))
        {
          strncpy(component_name, optarg, sizeof(optarg));
        } else
        {
          flag_error("Invalid component_name argument: it must be 'red', 'green' or 'blue'");
        }
        break;
      case 'v':
        short_flag_argument_check(optind, argc, argv, &optarg, c);  
      case COMPONENT_VALUE:
        if (check_digit(optarg))
        {
          temp = atoi(optarg);
          if ( temp >= 0 && temp < 256)
          {
            component_value = temp;
          } else flag_error("Invalid component_value argument");
        } else flag_error("Invalid component_value argument");
        break;
      case 'x':
        short_flag_argument_check(optind, argc, argv, &optarg, c);  
      case NUMBER_X:
        if (check_digit(optarg))
        {
          temp = atoi(optarg);
          if ( temp >= 1 )
          {
            number_x = temp;
          } else flag_error("Invalid number_x argument");
        } else flag_error("Invalid number_x argument");
        break;
      case 'y':
        short_flag_argument_check(optind, argc, argv, &optarg, c);  
      case NUMBER_Y:
        if (check_digit(optarg))
        {
          temp = atoi(optarg);
          if ( temp >= 1 )
          {
            number_y = temp;
          } else flag_error("Invalid number_y argument");
        } else flag_error("Invalid number_y argument");
        break;
      case 'o':  
      case OUTPUT_NAME:
        if (regcomp(&regexCompiled_bmp, regexString_bmp, REG_EXTENDED))
        {
          flag_error("Regex compilation porblem");
        }
        if (regexec(&regexCompiled_bmp, optarg, maxGroups_bmp, groupArray_bmp, 0) != 0)
        {
          flag_error("Invalid outputfile name");
        }
        strcpy(outputname, optarg);
        break;
      case '?':
        flag_error("Unknown flag");
        /* getopt_long already printed an flag_error message. */
        break;
      case 'i':
        flag = INFO;
        break;
      default:
        flag_error("defalut in case(c): thats strange!");
      }

    }

  /* Print any remaining command line arguments (not options). */
  if (optind < argc)
    {
      strcpy(filename, argv[argc-1]);
      if (regcomp(&regexCompiled_bmp, regexString_bmp, REG_EXTENDED))
        {
          flag_error("Regex compilation porblem");
        }
        if (regexec(&regexCompiled_bmp, filename, maxGroups_bmp, groupArray_bmp, 0) != 0)
        {
          flag_error("Invalid file name");
        }
    }
    else{
      flag_error("No bmp file");
    }

  BitmapFileHeader* fileheader = (BitmapFileHeader*)malloc(sizeof(BitmapFileHeader));
  BitmapInfoHeader* infoheader = (BitmapInfoHeader*)malloc(sizeof(BitmapInfoHeader));
  Rgb** pixels = read_bmp(filename, fileheader, infoheader);
  if ( flag == INFO) print_info(fileheader, infoheader);
  unsigned int H = infoheader->height;
  unsigned int W = infoheader->width;
  switch (flag)
    {
    case CIRLCE:
      if ( argc == 11 || argc == 14 || argc == 16 || argc == 13)
      {
        pixels = function_1(pixels, fileheader, infoheader, x_coord, y_coord, radius, thickness, color, fill, fill_color);
      }
      else{
        flag_error("arguments for --circle are not correct");
        exit(42);
      }
      break;
    case RGBFILTER:
      if ( argc == 7 || argc == 9)
      {
        pixels = function_2(pixels, fileheader, infoheader, component_name, component_value);
      }
      else
      {
        flag_error(" arguments for --rgbfilter are not correct");
      }
      break;
    case SPLIT:
      if (argc == 11 || argc == 13)
      {
        pixels = function_3(pixels, fileheader, infoheader, number_x, number_y, thickness, color);
      }
      else
      {
        flag_error("arguments --split are not correct");
      }
      break;
    }

  write_bmp(outputname, pixels, H, W, *fileheader, *infoheader);
  return 0;
}