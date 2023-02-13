# Filter Image

Filter Image is a command line tool that can be used to filter and convert the color image files in PPM format. It is implemented in C programming language and can be compiled and run on most of the platforms.

## Prerequisites

To compile and run the code, the following tools are required:

* GCC (GNU Compiler Collection)
* Make

## Compilation
The code can be compiled by using the following command in the terminal:
```
make build
```
This will create a build folder and compile the main.c, project.c and project.h files into a binary named filter_image.

## Usage
The compiled binary can be used by providing the input and output file names as command line arguments. The following is the usage format:
```
./filter_image input_file output_file [-g] [-f <color component(s)>]
```

* ```input_file``` is the path to the input PPM format image file.
* ```output_file``` is the path to the output PPM format image file.
* ```-g``` is an optional argument that can be used to convert the image to grayscale.
* ```-f``` is an optional argument that can be used to filter the color components. The value of this argument can be ```r``` for red, ```g``` for green &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;and ```b``` for blue. Multiple color components can be filtered by providing the combination of ```r``` and ```g``` or ```g``` and ```b``` or ```r``` and ```b```.

## Cleaning up

To remove the build folder and the binary, use the following command:
```
make clean
```

## License
This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
