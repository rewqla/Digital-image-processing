#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>

using namespace cv;
using namespace std;

class ThresholdManager {
private:
    Mat sourceImage;
    double thresholdValue;
    double maxValue;

public:
    ThresholdManager(string filePath, double thresh = 127, double maxVal = 255) {
        sourceImage = imread(filePath, IMREAD_GRAYSCALE);
        if (sourceImage.empty()) {
            throw runtime_error("Error: Could not load image at: " + filePath);
        }
        thresholdValue = thresh;
        maxValue = maxVal;
    }

    void setParams(double thresh, double maxVal) {
        thresholdValue = thresh;
        maxValue = maxVal;
    }

    Mat applyThreshold(int type) {
        Mat result;
        threshold(sourceImage, result, thresholdValue, maxValue, type);
        return result;
    }

    Mat getSource() const {
        return sourceImage;
    }

    ~ThresholdManager() {
        sourceImage.release();
    }
};

int main() {
    try {
        ThresholdManager tm("test.jpg", 127, 255);


        Mat bin = tm.applyThreshold(THRESH_BINARY);
        Mat binInv = tm.applyThreshold(THRESH_BINARY_INV);
        Mat trunc = tm.applyThreshold(THRESH_TRUNC);
        Mat toZero = tm.applyThreshold(THRESH_TOZERO);
        Mat toZeroInv = tm.applyThreshold(THRESH_TOZERO_INV);

        imshow("Binary Threshold", bin);
        imshow("Binary Inverse Threshold", binInv);
        imshow("Truncate Threshold", trunc);
        imshow("To Zero Threshold", toZero);
        imshow("To Zero Inverse Threshold", toZeroInv);

        cout << "Processing complete. Press any key to exit..." << endl;
        waitKey(0);
        destroyAllWindows();

    }
    catch (const exception& e) {
        cerr << "Application Error: " << e.what() << endl;
        return -1;
    }

    return 0;
}