#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>

using namespace cv;
using namespace std;

class EdgeDetector {
private:
    Mat sourceImage;
    Mat processedImage;

    void preProcess(int blurSize = 3) {
        Mat gray;
        if (sourceImage.channels() == 3) {
            cvtColor(sourceImage, gray, COLOR_BGR2GRAY);
        }
        else {
            gray = sourceImage.clone();
        }
        GaussianBlur(gray, processedImage, Size(blurSize, blurSize), 0);
    }

public:
    EdgeDetector(string filePath) {
        sourceImage = imread(filePath);
        if (sourceImage.empty()) {
            throw runtime_error("Error: Could not open or find the image: " + filePath);
        }
        preProcess();
    }

    Mat getSobel(int dx, int dy, int kSize = 5) {
        Mat result;
        // Use CV_64F to avoid overflow during gradient calculation
        Sobel(processedImage, result, CV_64F, dx, dy, kSize);
        return result;
    }

    Mat getCanny(double lowThreshold, double highThreshold) {
        Mat result;
        Canny(processedImage, result, lowThreshold, highThreshold);
        return result;
    }

    Mat getSource() const { return sourceImage; }
};

int main() {
    try {
        EdgeDetector detector("test.jpg");

        Mat sobelX = detector.getSobel(1, 0);
        Mat sobelY = detector.getSobel(0, 1);
        Mat sobelXY = detector.getSobel(1, 1);
        Mat cannyEdges = detector.getCanny(100, 200);

        imshow("Original Image", detector.getSource());
        imshow("Sobel X (Vertical edges)", sobelX);
        imshow("Sobel Y (Horizontal edges)", sobelY);
        imshow("Sobel Combined XY", sobelXY);
        imshow("Canny Edge Detection", cannyEdges);

        cout << "Edge detection completed successfully. Press any key to exit." << endl;
        waitKey(0);
        destroyAllWindows();

    }
    catch (const exception& e) {
        cerr << "Exception caught: " << e.what() << endl;
        return -1;
    }

    return 0;
}