#include "RANSAC.hpp"

Model RANSAC::findModel() {
    int bestInlierCount = 0;
    Model bestModel;
    for(int iter = 0; iter < iterations; iter++) {
        Model model = Model(measurements); // Get random sample
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