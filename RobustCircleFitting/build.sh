g++ -c -g -I./include src/MatrixReaderWriter.cpp
g++ -c -g -Wall -I./include main.cpp
g++ MatrixReaderWriter.o main.o -g -Wall $(pkg-config --cflags --libs opencv) -o main
#g++ MatrixReaderWriter.o panorama.o -L/usr/local/lib -lopencv_core -lopencv_highgui -lopencv_imgproc -o panorama