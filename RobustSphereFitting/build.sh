g++ -c -g -I./include src/MatrixReaderWriter.cpp
g++ -c -g -Wall -I./include $(pkg-config --cflags opencv4) src/Model.cpp
g++ -c -g -Wall -I./include $(pkg-config --cflags opencv4) src/RANSAC.cpp
g++ -c -g -Wall -I./include $(pkg-config --cflags opencv4) main.cpp
g++ MatrixReaderWriter.o Model.o RANSAC.o main.o -g -Wall $(pkg-config --cflags --libs opencv4) -o main
