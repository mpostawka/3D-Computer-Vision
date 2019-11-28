#pragma once

#include <vector>
#include <opencv2/core/core.hpp>

using namespace std;
using namespace cv;

class Model {
  public:
    Model();
    Model(const vector<Point>& points);
    virtual float distance(Point);
    virtual void describe();
};

class Circle : public Model {
  public:
    Circle();
    Circle(const Point2f& A, const Point2f& B, const Point2f& C);
    Circle(const vector<Point>& points);
    float distance(Point) override;
    void describe() override;
    Point2f center();
    float size();
    void draw(Mat image);
  private:
    float x, y, radius;
};
