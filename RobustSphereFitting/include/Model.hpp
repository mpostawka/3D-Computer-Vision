#pragma once

#include <vector>
#include <opencv2/core/core.hpp>

using namespace std;
using namespace cv;

class Model {
  public:
    Model();
    Model(const vector<Point3f>& points);
    virtual float distance(Point3f);
    virtual void describe();
};

class Sphere : public Model {
  public:
    Sphere();
    Sphere(const Point3f& A, const Point3f& B, const Point3f& C, const Point3f& D);
    Sphere(const vector<Point3f>& points);
    float distance(Point3f) override;
    void describe() override;
  private:
    float x, y, z, radius;
};
