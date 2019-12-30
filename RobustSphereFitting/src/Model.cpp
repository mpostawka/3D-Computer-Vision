#include "Model.hpp"
#include <iostream>
#include <cstdlib>
#include <opencv2/imgproc/imgproc.hpp>

Model::Model() {}

float Model::distance(Point3f) {
    return 0.0f;
} 

void Model::describe() {
    std::cout << "This is an empty model class";
} 

Sphere::Sphere() {
    
}

Sphere::Sphere(const Point3f& A, const Point3f& B, const Point3f& C, const Point3f& D) {
    Mat M = (Mat_<float>(4, 5) << A.x*A.x + A.y*A.y + A.z*A.z, A.x, A.y, A.z, 1,
                                  B.x*B.x + B.y*B.y + B.z*B.z, B.x, B.y, B.z, 1,
                                  C.x*C.x + C.y*C.y + C.z*C.z, C.x, C.y, C.z, 1,
                                  D.x*D.x + D.y*D.y + D.z*D.z, D.x, D.y, D.z, 1);
    float detA = determinant(M.colRange(1, 5));
    Mat tmp;
    hconcat(M.colRange(0, 1), M.colRange(2, 5), tmp);
    float detB = determinant(tmp);
    hconcat(M.colRange(0, 2), M.colRange(3, 5), tmp);
    float detC = determinant(tmp);
    hconcat(M.colRange(0, 3), M.colRange(4, 5), tmp);
    float detD = determinant(tmp);
    x = -detB / detA / 2.0f;
    y = -detC / detA / 2.0f;
    z = -detD / detA / 2.0f;
    radius = 0;
    radius = distance(A);
}

Sphere::Sphere(const vector<Point3f>& points) {
    int el[4] = {0, 0, 0, 0};
    while(el[0] == el[1] || el[0] == el[2] || el[1] == el[2] ||
          el[0] == el[3] || el[1] == el[3] || el[2] == el[3])
        for(auto& e : el)
            e = std::round((points.size() - 1) *
                static_cast<double>(rand()) / static_cast<double>(RAND_MAX));
    new (this) Sphere(points[el[0]], points[el[1]], points[el[2]], points[el[3]]);
}

float Sphere::distance(Point3f p) {
    return abs(radius - sqrtf((p.x - x)*(p.x - x) + (p.y - y)*(p.y - y) + (p.z - x)*(p.z - x)));
} 

void Sphere::describe() {
    std::cout << "Created Sphere in: (" << x << ", " << y << ", " << z << ") of radius: " << radius << "." << std::endl;
}

// Point2f Sphere::center() {
//     return Point3f(x, y, z);
// }

// float Sphere::size() {
//     return radius;
// }