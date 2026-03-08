#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>

using namespace std;
using namespace cv;

class ImageCropper {
private:
    Mat image;

public:
    ImageCropper(string path) {
        image = imread(path);
        if (image.empty()) {
            throw runtime_error("Error: Could not open or find the image!");
        }
    }

    void cropAndSave(int startRow, int endRow, int startCol, int endCol, string savePath) {
        if (endRow > image.rows || endCol > image.cols) {
            cout << "Warning: Crop dimensions exceed image size. Adjusting..." << endl;
            endRow = min(endRow, image.rows);
            endCol = min(endCol, image.cols);
        }

        Mat cropped = image(Range(startRow, endRow), Range(startCol, endCol));

        imshow("Original Image", image);
        imshow("Cropped Fragment", cropped);

        imwrite(savePath, cropped);
        cout << "Fragment saved to: " << savePath << endl;

        waitKey(0);
        destroyAllWindows();
    }
};

int main() {
    try {
        ImageCropper processor("test.jpg");
        processor.cropAndSave(80, 280, 150, 330, "crop.jpg");
    }
    catch (const exception& e) {
        cerr << e.what() << endl;
    }
    return 0;
}