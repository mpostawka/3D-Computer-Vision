#pragma once

#include <vector>
#include <opencv2/core/core.hpp>

using namespace std;
using namespace cv;

template <class Shape>
class RANSAC {
  public:
    RANSAC(vector<Point3f> &data) :
      iterations(1000), threshold(12.0f) {
        measurements = data;
    };
    Shape findModel();
  private:
    int iterations;
    float threshold;
    vector<Point3f> measurements;
};