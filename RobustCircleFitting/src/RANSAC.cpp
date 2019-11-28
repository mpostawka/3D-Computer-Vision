#include "RANSAC.hpp"
#include "Model.hpp"

template <class Shape>
Shape RANSAC<Shape>::findModel() {
    int bestInlierCount = 0;
    Shape bestModel;
    for(int iter = 0; iter < iterations; iter++) {
        Shape model(measurements); // Get random sample
        int inlierCount = 0;
        for(const auto& point : measurements)
            if(model.distance(point) <= threshold)
                inlierCount++;
        if(inlierCount > bestInlierCount) {
            bestInlierCount = inlierCount;
            bestModel = model;
        }
    }
    return bestModel;
}

template class RANSAC<Circle>;