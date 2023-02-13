#include "project.h"

int main(int argc, char *argv[])
{
    if (argc < 3) 
    {
        printf("Usage: %s input_file output_file [-g] [-f <color component(s)>]\n", argv[0]);
        return 1;
    }

    const char* input_filename = argv[1];
    char* output_filename = argv[2];
    int opt;

    PPM_Image_Buffer* bufer = malloc(sizeof(PPM_Image_Buffer));
    read_ppm_color_bitmap(input_filename, bufer);

    int flag = 0;
    while ((opt = getopt(argc, argv, "gf:")) != -1) 
    {
        switch (opt) 
        {
        case 'g': 
            convert_to_grayscale(bufer);
            flag++;
            write_ppm_color_bitmap(output_filename, bufer);
            return 0;
        case 'f': 
            char color_components[3];
            sscanf(optarg, "%s", color_components); 
            if (strlen(color_components) == 1)
            {
                switch (color_components[0])
                {
                case 'r': filter_color_component(bufer, 1); break;
                case 'g': filter_color_component(bufer, 2); break;
                case 'b': filter_color_component(bufer, 3); break;
                default: 
                    printf("Unknown option\n");
                    break;
                }
            }
            else if (strlen(color_components) == 2)
            {
                if ((color_components[0] == 'r' && color_components[1] == 'g') ||
                    (color_components[0] == 'g' && color_components[1] == 'r')) 
                {
                    filter_color_component(bufer, 3);
                }
                else if ((color_components[0] == 'r' && color_components[1] == 'b') ||
                         (color_components[0] == 'b' && color_components[1] == 'r')) 
                {
                    filter_color_component(bufer, 5);
                }
                else if ((color_components[0] == 'g' && color_components[1] == 'b') ||
                         (color_components[0] == 'b' && color_components[1] == 'g')) 
                {
                    filter_color_component(bufer, 6);
                }
            }
            break; 
        }
    }

    if (!flag)
    {
        write_ppm_color_bitmap(output_filename, bufer);
    }

    return 0;
}
