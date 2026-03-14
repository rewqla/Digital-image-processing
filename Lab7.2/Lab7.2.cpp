#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>

using namespace cv;
using namespace std;

class ImageFilter {
private:
    Mat image; 

public:
    ImageFilter(string path) {
        image = imread(path);
        if (image.empty()) throw runtime_error("Error: Image not found at " + path);
    }

    Mat applyCustomBlur() {
        Mat result;
        Mat kernel = Mat::ones(5, 5, CV_64F) / 25.0;
        filter2D(image, result, -1, kernel);
        return result;
    }

    Mat applySharpening() {
        Mat result;
        Mat kernel = (Mat_<double>(3, 3) <<
            0, -1, 0,
            -1, 5, -1,
            0, -1, 0);
        filter2D(image, result, -1, kernel);
        return result;
    }

    Mat applyGaussianBlur(int kSize = 5) {
        Mat result;
        GaussianBlur(image, result, Size(kSize, kSize), 0);
        return result;
    }

    Mat applyMedianBlur(int kSize = 5) {
        Mat result;
        medianBlur(image, result, kSize);
        return result;
    }

    Mat applyBilateral(int d = 9, double sigmaColor = 75, double sigmaSpace = 75) {
        Mat result;
        bilateralFilter(image, result, d, sigmaColor, sigmaSpace);
        return result;
    }

    void showOriginal() {
        imshow("Original Image", image);
    }
};

int main() {
    try {
        ImageFilter filter("test.jpg"); 

        filter.showOriginal();

        Mat blurred = filter.applyCustomBlur();
        imshow("1. Custom Kernel Blur", blurred);

        Mat sharp = filter.applySharpening();
        imshow("2. Sharpened Image", sharp);

        Mat gaussian = filter.applyGaussianBlur(9);
        imshow("3. Gaussian Blur", gaussian);

        Mat median = filter.applyMedianBlur(5);
        imshow("4. Median Blur", median);

        Mat bilateral = filter.applyBilateral();
        imshow("5. Bilateral Filter", bilateral);

        waitKey(0);
        destroyAllWindows();

    }
    catch (const exception& e) {
        cerr << "Exception: " << e.what() << endl;
        return -1;
    }
    return 0;
}