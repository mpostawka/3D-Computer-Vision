#include <iostream>
#include <string>
#include <vector>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <MatrixReaderWriter.h>

using namespace std;
using namespace cv;

const char *window_name = "floating";

cv::Mat normTransform( vector<Point2f> points ) {
    Point2f mean(0.0f, 0.0f);
    for(const auto& p : points)
        mean += p;
    mean /= static_cast<float>(points.size());
    Point2f variance(0.0f, 0.0f);
    for(const auto& p : points) {
        variance.x += (p.x - mean.x) * (p.x - mean.x);
        variance.y += (p.y - mean.y) * (p.y - mean.y);
    }
    variance /= static_cast<float>(points.size());
    Point2f std(sqrtf(variance.x), sqrtf(variance.y));

    Mat translate = Mat::eye(3, 3, CV_32F);
	translate.at<float>(0, 2) = -mean.x;
	translate.at<float>(1, 2) = -mean.y;

	Mat scale = Mat::eye(3, 3, CV_32F);
	scale.at<float>(0, 0) = sqrtf(2) / std.x;
	scale.at<float>(1, 1) = sqrtf(2) / std.y;

    return scale * translate; // Maybe clone?
}

cv::Mat hommTransform(vector<Point2f> first, vector<Point2f> second) {
    cv::Mat A(0, 9, CV_32F);
    for(int i=0; i<first.size(); i++) {
        auto& p1 = first[i];
        auto& p2 = second[i];
        Mat row = (Mat_<float>(2, 9) << p1.x, p1.y, 1, 0, 0, 0, -p1.x*p2.x, -p1.y*p2.x, -p2.x,
                                        0, 0, 0, p1.x, p1.y, 1, -p1.x*p2.y, -p1.y*p2.y, -p2.y);
        vconcat(A,row, A);
    }
    Mat eigenvalues, eigenvector;
    eigen(A.t() * A, eigenvalues, eigenvector);
    Mat H(3, 3, CV_32F);
    for (int i=0;i<9;i++)
        H.at<float>(i/3, i%3) = eigenvector.at<float>(8,i);
    H *= 1.0 / H.at<float>(2, 2);
    return H;
}

void transformImage(Mat origImg, Mat& newImage, Mat tr, bool isPerspective) {
    Mat invTr=tr.inv();
    const int WIDTH=origImg.cols;
    const int HEIGHT=origImg.rows;

    const int newWIDTH=newImage.cols;
    const int newHEIGHT=newImage.rows;

    for (int x=0;x<newWIDTH;x++) {
        for (int y=0;y<newHEIGHT;y++){
        Mat pt(3,1,CV_32F);
        pt.at<float>(0,0)=x;
        pt.at<float>(1,0)=y;
        pt.at<float>(2,0)=1.0;

        Mat ptTransformed=invTr*pt;
        if (isPerspective) {
            ptTransformed=(1.0/ptTransformed.at<float>(2,0))*ptTransformed;
        }

        int newX=round(ptTransformed.at<float>(0,0));
        int newY=round(ptTransformed.at<float>(1,0));

        if ((newX>=0)&&(newX<WIDTH)&&(newY>=0)&&(newY<HEIGHT))
            newImage.at<Vec3b>(y,x)=origImg.at<Vec3b>(newY,newX);
        }
    }
}

int main(int argc, char **argv) {
    if (argc < 2)
        return -1;
    string image1Filename = "data/" + static_cast<string>(argv[1]) + "1.jpg";
    string image2Filename = "data/" + static_cast<string>(argv[1]) + "2.jpg";
    vector<Point2f> features1;
    vector<Point2f> features2;

    string featuresFilename = "data/" + static_cast<string>(argv[1]) + ".txt";
    MatrixReaderWriter matrix(featuresFilename.c_str());
    int c = matrix.columnNum;
    for (int i = 0; i < 4; i++) {
        Point2f first, second;
        first =  Point2f(matrix.data[i], matrix.data[c+i]);
        second = Point2f(matrix.data[2*c+i], matrix.data[3*c+i]);
        features1.push_back(first);
        features2.push_back(second);
    }

    Mat image1 = imread(image1Filename);
    Mat image2 = imread(image2Filename);
    for(int i=0; i<features1.size(); i++) {
        std::cout << "(" << features1[i].x << ", " << features1[i].y << ") <==> ("
                         << features2[i].x << ", " << features2[i].y << ")" << std::endl;
    }
    vector<Point2f> normalized1, normalized2;
    Mat T1 = normTransform(features1);
    Mat T2 = normTransform(features2);
    perspectiveTransform(features1, normalized1, T1);
    perspectiveTransform(features2, normalized2, T2);
    Mat Hnorm = hommTransform(normalized1, normalized2);
    Mat H = T2.inv() * Hnorm * T1;

    std::cout << "#################################\n";
    for(int i=0; i<features1.size(); i++) {
        Mat trPoint = (H*(Mat_<float>(3, 1) << features1[i].x, features1[i].y, 1.0f));
        trPoint /= trPoint.at<float>(2, 0);
        std::cout << "(" << trPoint.at<float>(0, 0) << ", " << trPoint.at<float>(1, 0) << ") <==> (";
        std::cout << features2[i].x << ", " << features2[i].y << ")" << std::endl;
    }

    Mat image3 = Mat(image2.size(), image2.type());
    transformImage(image1, image3, H, true);
    imwrite("data/" + static_cast<string>(argv[1])  + "3.jpg", image3);

    namedWindow(window_name, WINDOW_AUTOSIZE);
    resize(image1, image1, Size(), 0.25, 0.25);
    imshow(window_name, image1);
    waitKey(0);
    resize(image2, image2, Size(), 0.25, 0.25);
    imshow(window_name, image2);
    waitKey(0);
    resize(image3, image3, Size(), 0.25, 0.25);
    imshow(window_name, image3);
    waitKey(0);
}