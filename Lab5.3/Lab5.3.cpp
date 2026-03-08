#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

class ImageRotator {
private:
    Mat image;

public:
    ImageRotator(string path) {
        image = imread(path);
        if (image.empty()) throw runtime_error("Image not found!");
    }

    Mat rotate(double angle, double scale = 1.0) {
        Point2f center((image.cols - 1) / 2.0, (image.rows - 1) / 2.0);
        Mat matrix = getRotationMatrix2D(center, angle, scale);
        Mat rotated;
        warpAffine(image, rotated, matrix, image.size());
        return rotated;
    }

    void showAndSave(const Mat& result, string windowName = "Rotated Image") {
        imshow("Original", image);
        imshow(windowName, result);
        imwrite("rotated_image.jpg", result);
        waitKey(0);
    }
};

int main() {
    try {
        ImageRotator rotator("image.jpg");
        Mat rotated = rotator.rotate(45);
        rotator.showAndSave(rotated);
    }
    catch (const exception& e) {
        cerr << e.what() << endl;
    }
    return 0;
}