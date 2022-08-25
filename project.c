#include "project.h"

int read_ppm_color_bitmap(const char *filename, PPM_Image_Buffer *buf)
{     
    FILE *fp;
    int rgb,size;
    fp = fopen(filename,"rb");//open file
    if (!fp) 
    {
        perror("file not opened \n");
        return -1;
    }
    

    
    fseek(fp, 3, SEEK_SET);//next line
    
    
    fscanf(fp, "%d", &buf->col);//iamge size 
    fscanf(fp, "%d", &buf->row);
    size = buf->col*buf->row;
    //printf("col= %d\n", buf->col);
    //printf("row= %d\n", buf->row);
    
    
    buf->data = malloc(sizeof(int) * size * 3);//mlloc for data
    if(!buf->data)
    {
        perror("data alloc err");
        exit(-1);
    }
    
    fseek(fp, 4, SEEK_CUR);//read data 
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
    int size = buf->col * buf->row; //image size
    if(fp == NULL)
    {
        perror("file open err\n");
        exit(-1);
    }
    fputs("P3\n", fp);
    fprintf(fp, "%d %d\n", buf->col, buf->row);
    fputs("255\n", fp);//write first 3 rows
    for(int i = 0; i < size; i++)//write rest of the rows
        {
            fprintf  (fp, "%d %d %d ",      (((buf->data) + i)->red),
                                            (((buf->data) + i)->green),
                                            (((buf->data) + i)->blue)
                    );
        } 
}

void filter_color_component(PPM_Image_Buffer* buf, unsigned int rgb_mask)
{
   int size = buf->row*buf->col;//image size
    for(int i=0;i < size ; i++)//edit pixels
    {
        if((rgb_mask & (1 << 0)) == 0) ((buf->data) + i)->red = 0;
        if((rgb_mask & (1 << 1)) == 0) ((buf->data) + i)->green = 0;
        if((rgb_mask & (1 << 2)) == 0) ((buf->data) + i)->blue = 0;
        
    }
        
}

void convert_to_grayscale(PPM_Image_Buffer* buf)
{
    int size = buf->col * buf->row;//image size

    for(int i = 0; i < size; i++)//edit pixels
    {
        (buf->data + i)->red =      (buf->data + i)->red * 0.3 + (buf->data + i)->green * 0.59 + (buf->data + i)->blue * 0.11;
        (buf->data + i)->green =    (buf->data + i)->red * 0.3 + (buf->data + i)->green * 0.59 + (buf->data + i)->blue * 0.11;
        (buf->data + i)->blue =     (buf->data + i)->red * 0.3 + (buf->data + i)->green * 0.59 + (buf->data + i)->blue * 0.11;

       if( ((buf->data + i)->red   != (buf->data + i)->green)    || 
            ((buf->data + i)->red   != (buf->data + i)->blue)       ||
            ((buf->data + i)->blue  != (buf->data + i)->green))   --i;
    }
}