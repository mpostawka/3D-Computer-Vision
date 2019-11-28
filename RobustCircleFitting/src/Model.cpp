#include "Model.hpp"
#include <iostream>
#include <cstdlib>
#include <opencv2/imgproc/imgproc.hpp>

Model::Model() {}

float Model::distance(Point) {
    return 0.0f;
} 

void Model::describe() {
    std::cout << "This is an empty model class";
} 

Circle::Circle() {
    
}

Circle::Circle(const Point2f& A, const Point2f& B, const Point2f& C) {
    Point2f orgA((A.x + B.x)/2.0f, (A.y + B.y)/2.0f);
    Point2f orgB((B.x + C.x)/2.0f, (B.y + C.y)/2.0f);
    Point2f dirA(B.y - A.y, A.x - B.x);
    Point2f dirB(C.y - B.y, B.x - C.x);
    Mat IT = (Mat_<float>(2, 2) << dirA.x, -dirB.x,
                                   dirA.y, -dirB.y);
    Mat tu = IT.inv() * (Mat_<float>(2, 1) << orgB.x - orgA.x,
                                              orgB.y - orgA.y);
    float t = tu.at<float>(0, 0);
    x = orgA.x + t * dirA.x;
    y = orgA.y + t * dirA.y;
    radius = sqrtf((A.x - x)*(A.x - x) + (A.y - y)*(A.y - y));
}

Circle::Circle(const vector<Point>& points) {
    int el[3] = {0, 0, 0};
    while(el[0] == el[1] || el[0] == el[2] || el[1] == el[2])
        for(auto& e : el)
            e = std::round((points.size() - 1) *
                static_cast<double>(rand()) / static_cast<double>(RAND_MAX));
    new (this) Circle(points[el[0]], points[el[1]], points[el[2]]);
}

float Circle::distance(Point p) {
    return abs(radius - sqrtf((p.x - x)*(p.x - x) + (p.y - y)*(p.y - y)));
} 

Point2f Circle::center() {
    return Point2f(x, y);
}

float Circle::size() {
    return radius;
}

void Circle::draw(Mat image) {
    circle(image, center(), 3, Scalar(0, 0, 255), 8);
    circle(image, center(), radius, Scalar(0, 255, 0), 8);
}

void Circle::describe() {
    std::cout << "Created Circle in: (" << x << ", " << y << ") of radius: " << radius << "." << std::endl;
}