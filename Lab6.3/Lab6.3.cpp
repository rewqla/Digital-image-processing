#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

class ShapeAnnotator {
private:
    Mat image;

public:
    ShapeAnnotator(string path) {
        image = imread(path);
        if (image.empty()) throw runtime_error("Image not found!");
    }

    void drawShapes() {
        Mat canvas = image.clone();

        line(canvas, Point(50, 50), Point(300, 50), Scalar(255, 0, 0), 3);

        circle(canvas, Point(100, 220), 50, Scalar(0, 255, 0), -1);

        imshow("Shape Annotation", canvas);
        waitKey(0);
    }
};

int main() {
    try {
        ShapeAnnotator annotator("images.jpg");
        annotator.drawShapes();
    }
    catch (const exception& e) {
        cerr << e.what() << endl;
    }
    return 0;
}