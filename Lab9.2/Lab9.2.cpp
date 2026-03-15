#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>
#include <string>

using namespace cv;
using namespace std;

class BlobAnalyzer {
private:
    Mat sourceImage;
    SimpleBlobDetector::Params params;
    vector<KeyPoint> keypoints;

public:
    BlobAnalyzer(string imagePath) {
        sourceImage = imread(imagePath, IMREAD_GRAYSCALE);
        if (sourceImage.empty()) {
            throw runtime_error("Error: Could not open or find the image: " + imagePath);
        }

        params.minThreshold = 10;
        params.maxThreshold = 200;

        params.filterByArea = true;
        params.minArea = 100;

        params.filterByCircularity = true;
        params.minCircularity = 0.1f;

        params.filterByConvexity = true;
        params.minConvexity = 0.87f;

        params.filterByInertia = true;
        params.minInertiaRatio = 0.01f;
    }

    void setAreaFilter(float minArea, float maxArea = 100000.0f) {
        params.filterByArea = true;
        params.minArea = minArea;
        params.maxArea = maxArea;
    }

    void process() {
        Ptr<SimpleBlobDetector> detector = SimpleBlobDetector::create(params);

        keypoints.clear();
        detector->detect(sourceImage, keypoints);

        cout << "Detection finished. Found " << keypoints.size() << " blobs." << endl;
    }

    void displayResults() {
        Mat imageWithKeypoints;

        drawKeypoints(sourceImage, keypoints, imageWithKeypoints,
            Scalar(0, 0, 255), DrawMatchesFlags::DRAW_RICH_KEYPOINTS);

        imshow("Original Image", sourceImage);
        imshow("Detected Blobs", imageWithKeypoints);
        waitKey(0);
    }
};

int main() {
    try {
        BlobAnalyzer analyzer("blob.jpg");

        analyzer.setAreaFilter(500.0f, 5000.0f);

        analyzer.process();
        analyzer.displayResults();

    }
    catch (const exception& e) {
        cerr << "Application Exception: " << e.what() << endl;
        return -1;
    }

    return 0;
}