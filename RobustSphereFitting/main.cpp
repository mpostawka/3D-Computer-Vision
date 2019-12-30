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

int main(int argc, char **argv) {
    if (argc < 2)
        return -1;
    srand(time(nullptr));
    string filename = static_cast<string>(argv[1]);
    MatrixReaderWriter matrix("data/" + filename);

    vector<Point3f> points;
    for (int i = 0; i < matrix.rowNum; i++) {
        Point3f point;
        point.x = matrix.data[3 * i + 0];
        point.y = matrix.data[3 * i + 1];
        point.z = matrix.data[3 * i + 2];
        points.push_back(point);
    }

    RANSAC<Sphere> ransac(points);
    Sphere model = ransac.findModel();
    // Sphere model(Point3f(1.0f, 1.0f, 0.0f),
    //              Point3f(0.0f, 1.0f, 1.0f),
    //              Point3f(0.0f, 2.0f, 0.0f),
    //              Point3f(-1.0f, 1.0f, 0.0f));
    model.describe();
    
    waitKey(0);
}