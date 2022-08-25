#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
typedef struct Pixel_Data
{
    int red,green,blue;

}Pixel_Data;

typedef struct PPM_Image_Buffer {

    Pixel_Data* data;
    int row, col;

}PPM_Image_Buffer;

int read_ppm_color_bitmap(const char *filename, PPM_Image_Buffer *buf);
int write_ppm_color_bitmap(char *filename, PPM_Image_Buffer *buf);
void filter_color_component(PPM_Image_Buffer* buf, unsigned int rgb_mask);
void convert_to_grayscale(PPM_Image_Buffer* buf);
void convert_to_grayscale(PPM_Image_Buffer* buf);
