#include <opencv2/opencv.hpp>

using namespace cv;

class TextAnnotator {
private:
    Mat image;

public:
    TextAnnotator(std::string path) {
        image = imread(path);
    }

    void addLabel(std::string text, Point pos, Scalar color) {
        Mat canvas = image.clone();
        putText(canvas, text, pos, FONT_HERSHEY_SIMPLEX, 1.0, color, 2);
        imshow("Text Annotation", canvas);
        waitKey(0);
    }
};

int main() {
    TextAnnotator annotator("images.jpg");
    annotator.addLabel("Creation", Point(50, 50), Scalar(100, 255, 0));
    return 0;
}