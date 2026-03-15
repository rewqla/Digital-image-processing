#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>
#include <string>

using namespace cv;
using namespace std;

class ContourProcessor {
private:
    Mat srcImage;     
    Mat grayImage;      
    Mat binaryImage;    

    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;

public:
    ContourProcessor(const string& filename) {
        srcImage = imread(filename);
        if (srcImage.empty()) {
            throw runtime_error("Error: Could not load image at " + filename);
        }
        cvtColor(srcImage, grayImage, COLOR_BGR2GRAY);
    }

    void process(int thresholdValue = 127, int retrievalMode = RETR_TREE) {
        threshold(grayImage, binaryImage, thresholdValue, 255, THRESH_BINARY);

        contours.clear();
        hierarchy.clear();

        findContours(binaryImage, contours, hierarchy, retrievalMode, CHAIN_APPROX_SIMPLE);

        cout << "Successfully detected " << contours.size() << " contour(s)." << endl;
    }

    void displayResults(const string& winName = "Contour Detection Result") {
        Mat output = srcImage.clone();

        drawContours(output, contours, -1, Scalar(0, 255, 0), 2);

        imshow("Original Image", srcImage);
        imshow("Binary Mask", binaryImage);
        imshow(winName, output);

        cout << "Press any key to exit..." << endl;
        waitKey(0);
        destroyAllWindows();
    }

    const vector<vector<Point>>& getContours() const {
        return contours;
    }
};

int main() {
    try {
        ContourProcessor processor("test.jpg");

        processor.process(150, RETR_TREE);

        processor.displayResults();

    }
    catch (const exception& e) {
        cerr << "Exception caught: " << e.what() << endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}