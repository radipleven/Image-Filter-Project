build:
	mkdir build
	gcc -c project.c
	gcc -c main.c
	gcc project.o main.o -o filter_image
	mv project.o  ./build
	mv main.o ./build
	mv filter_image ./build
	
clean:
	rm -rf ./build