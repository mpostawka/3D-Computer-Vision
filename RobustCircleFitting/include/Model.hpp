#pragma once

#include <vector>
#include <opencv2/core/core.hpp>

using namespace std;
using namespace cv;

class Model {
  public:
    Model(){};
    Model(const vector<Point>& points);
    float distance(Point);
};

class Circle : public Model {
  public:
    Circle(){};
};
