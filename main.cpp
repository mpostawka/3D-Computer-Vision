#include "MatrixReaderWriter.h"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <opencv2/core/core.hpp>
#include <string>
#include <vector>

using namespace std;
using namespace cv;

const char *window_name = "floating";

class Model {
  public:
    Model(){};
    Model(vector<Point> points);
    float distance(Point);
};

class Circle : public Model {
  public:
    Circle(){};
};

class RANSAC {
  public:
    RANSAC(vector<Point> &data) :
      iterations(1000), threshold(12.0f) {
        measurements = data;
    };
    Model findModel();
  private:
    int iterations;
    float threshold;
    vector<Point> measurements;
};

Model RANSAC::findModel() {
    int bestInlierCount = 0;
    for(int iter = 0; iter < iterations; iter++) {
        Model model = Model(measurements); // Get random sample
        for(const auto& point : measurements) {
            int inlierCount = 0;
            if(model.distance(point) <= threshold) {
                inlierCount++;
            }
        }
    }
}

int main(int argc, char **argv) {
    if (argc < 2)
        return -1;
    string number = static_cast<string>(argv[1]);
    MatrixReaderWriter matrix("data/points" + number + ".txt");
    Mat image = imread("data/image" + number + ".png");
    if (!image.data) {
        return -1;
    };
    vector<Point2f> points;
    for (int i = 0; i < matrix.rowNum; i++) {
        Point2f point;
        point.x = matrix.data[2 * i + 0];
        point.y = matrix.data[2 * i + 1];
        points.push_back(point);
    }

    RANSAC ransac(points);
    ransac

        namedWindow(window_name, WINDOW_AUTOSIZE);
    for (const auto &point : points) {
        circle(image, point, 3, Scalar(255, 0, 0), 8);
    }
    Mat view;
    resize(image, view, Size(0, 0), 0.25f, 0.25f);
    imshow(window_name, view);
    waitKey(0);
}