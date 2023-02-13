#include "project.h"

int read_ppm_color_bitmap(const char *filename, PPM_Image_Buffer *buf)
{     
    FILE *fp;
    fp = fopen(filename,"rb");
    if (!fp) 
    {
        perror("file not opened");
        return -1;
    }
    
    fseek(fp, 3, SEEK_SET);
    fscanf(fp, "%d", &buf->col);
    fscanf(fp, "%d", &buf->row);
    int size = buf->col*buf->row;

    buf->data = malloc(sizeof(int) * size * 3);
    if(!buf->data)
    {
        perror("data allocation error");
        exit(-1);
    }
    
    fseek(fp, 4, SEEK_CUR);
    for(long int i = 0; i < size; i++)
    {
        fscanf  (fp, "%d %d %d", &(((buf->data) + i)->red),
                                 &(((buf->data) + i)->green),
                                 &(((buf->data) + i)->blue)
                );
    }
    fclose(fp);
    return 0;
}

int write_ppm_color_bitmap(char *filename, PPM_Image_Buffer *buf)
{
    FILE* fp = fopen(filename, "w+");
    int size = buf->col * buf->row;
    if(fp == NULL)
    {
        perror("file open error");
        exit(-1);
    }
    fputs("P3\n", fp);
    fprintf(fp, "%d %d\n", buf->col, buf->row);
    fputs("255\n", fp);
    for(int i = 0; i < size; i++)
        {
            fprintf  (fp, "%d %d %d ",      (((buf->data) + i)->red),
                                            (((buf->data) + i)->green),
                                            (((buf->data) + i)->blue)
                    );
        } 
    fclose(fp);
    return 0;
}

void filter_color_component(PPM_Image_Buffer* buf, unsigned int rgb_mask)
{
    int size = buf->row*buf->col;
    for(int i=0;i < size ; i++)
    {
        if((rgb_mask & (1 << 0)) == 0) ((buf->data) + i)->red = 0;
        if((rgb_mask & (1 << 1)) == 0) ((buf->data) + i)->green = 0;
        if((rgb_mask & (1 << 2)) == 0) ((buf->data) + i)->blue = 0;
    }
}

#define RED_WEIGHT 0.3
#define GREEN_WEIGHT 0.59
#define BLUE_WEIGHT 0.11

void convert_to_grayscale(PPM_Image_Buffer* buf)
{
    int size = buf->col * buf->row; //Calculate size of the image

    for(int i = 0; i < size; i++) // Loop through all pixels
    {
        //Convert the pixel to grayscale by applying the grayscale formula
        (buf->data + i)->red =      (buf->data + i)->red * RED_WEIGHT + (buf->data + i)->green * GREEN_WEIGHT + (buf->data + i)->blue * BLUE_WEIGHT;
        (buf->data + i)->green =    (buf->data + i)->red * RED_WEIGHT + (buf->data + i)->green * GREEN_WEIGHT + (buf->data + i)->blue * BLUE_WEIGHT;
        (buf->data + i)->blue =     (buf->data + i)->red * RED_WEIGHT + (buf->data + i)->green * GREEN_WEIGHT + (buf->data + i)->blue * BLUE_WEIGHT;
    }
}
