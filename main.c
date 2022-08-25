#include "project.h"

int main(int argc, char *argv[])
{

    int opt;
    PPM_Image_Buffer* bufer = malloc(sizeof(PPM_Image_Buffer)); 
    read_ppm_color_bitmap(argv[1],bufer);
    char args[2];
    int flag =0;
    
    
    while ((opt = getopt(argc, argv, "gf:")) != -1) 
    {
        switch (opt) 
        {
         case 'g': convert_to_grayscale(bufer);flag++;write_ppm_color_bitmap(argv[2], bufer);return 0;
         case 'f': sscanf(optarg,"%s",args); break; 
        }
    }
    

    //printf("flag= %d\n", flag);
    //printf("args[0] = %c \n", args[0]);
    //printf("args[1] = %c \n", args[1]);
    if (args[1]=='\0' && flag ==0)
    { 
        printf("argasddsa \n");
        switch (args[0])
        {
        case 'r':filter_color_component(bufer, 1);break;
        case 'g':filter_color_component(bufer, 2);break;
        case 'b':filter_color_component(bufer, 3);break;
        default: printf("unknown option\n");break;
        }
    }else if (args[1]!='\0' && flag ==0)
    { 
        if (args[0]=='r' && args[1]=='g') filter_color_component(bufer, 3);
        if (args[0]=='g' && args[1]=='r') filter_color_component(bufer, 3);
        if (args[0]=='r' && args[1]=='b') filter_color_component(bufer, 5);
        if (args[0]=='b' && args[1]=='r') filter_color_component(bufer, 5);
        if (args[0]=='g' && args[1]=='b') filter_color_component(bufer, 6);
        if (args[0]=='b' && args[1]=='g') filter_color_component(bufer, 6);
        
    }
    
    write_ppm_color_bitmap(argv[2], bufer);
    

    return 0;
}