#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "MatrixReaderWriter.h"
#include "Model.hpp"
#include "RANSAC.hpp"

using namespace std;
using namespace cv;

const char *window_name = "floating";
const bool show_input = false;

int main(int argc, char **argv) {
    if (argc < 2)
        return -1;
    srand(time(nullptr));
    string number = static_cast<string>(argv[1]);
    MatrixReaderWriter matrix("data/points" + number + ".txt");
    Mat image = imread("data/image" + number + ".png");
    if (!image.data) {
        return -1;
    };
    vector<Point> points;
    for (int i = 0; i < matrix.rowNum; i++) {
        Point point;
        point.x = matrix.data[2 * i + 0];
        point.y = matrix.data[2 * i + 1];
        point.y = matrix.data[2 * i + 2];
        points.push_back(point);
    }
    if(show_input)
        for (const auto &point : points)
            circle(image, point, 3, Scalar(255, 0, 0), 8);

    RANSAC<Circle> ransac(points);
    Circle model = ransac.findModel();
    model.draw(image);
    
    namedWindow(window_name, WINDOW_AUTOSIZE);
    Mat view;
    resize(image, view, Size(0, 0), 0.25f, 0.25f);
    imshow(window_name, view);
    waitKey(0);
}