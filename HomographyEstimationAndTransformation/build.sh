g++ -c -g -I./include src/MatrixReaderWriter.cpp
g++ -c -g -Wall -I./include $(pkg-config --cflags opencv) main.cpp
g++ MatrixReaderWriter.o main.o -g -Wall $(pkg-config --cflags --libs opencv) -o main
