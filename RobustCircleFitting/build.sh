g++ -c -g -I./include src/MatrixReaderWriter.cpp
g++ -c -g -Wall -I./include src/Model.cpp
g++ -c -g -Wall -I./include src/RANSAC.cpp
g++ -c -g -Wall -I./include main.cpp
g++ MatrixReaderWriter.o Model.o RANSAC.o main.o -g -Wall $(pkg-config --cflags --libs opencv) -o main