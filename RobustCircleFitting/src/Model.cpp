#include "Model.hpp"
#include<iostream>

Model::Model() {}

float Model::distance(Point) {
    return 0.0f;
} 

Circle::Circle() {
    
}

Circle::Circle(const Point2f& A, const Point2f& B, const Point2f& C) {
    float ma = (B.y / A.y) / (B.x - A.x);
    float mb = (C.y / B.y) / (C.x - B.x);
    Point AB((A.x + B.x)/2.0f, (A.y + B.y)/2.0f);
    Point BC((B.x + C.x)/2.0f, (B.y + C.y)/2.0f);
    x = ma*mb*(A.y - C.y)/2.0f + mb*AB.x + ma*BC.x;
    x /= (mb - ma);
    y = -(1.0f / ma) * (x - AB.x) + AB.y;
    radius = sqrtf((A.x - x)*(A.x - x) + (B.x - x)*(B.x - x));
    std::cout << "Created Circle in: (" << x << ", " << y << ") of radius: " << radius << "." << std::endl;
}

Circle::Circle(const vector<Point>& points) {
    
}


float Circle::distance(Point) {
    return 0.0f;
} 
