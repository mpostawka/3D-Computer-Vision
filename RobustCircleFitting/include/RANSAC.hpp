#pragma once

#include <vector>
#include <opencv2/core/core.hpp>

using namespace std;
using namespace cv;

#include "Model.hpp"

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