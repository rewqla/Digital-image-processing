#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

class ImageTranslator {
private:
    Mat image;

public:
    ImageTranslator(string path) {
        image = imread(path);
        if (image.empty()) throw runtime_error("Image not found!");
    }

    Mat translate(float tx, float ty) {
        float warp_values[] = { 1.0, 0.0, tx, 0.0, 1.0, ty };
        Mat matrix = Mat(2, 3, CV_32F, warp_values);
        Mat translated;
        warpAffine(image, translated, matrix, image.size());
        return translated;
    }

    void showAndSave(const Mat& result) {
        imshow("Original", image);
        imshow("Translated", result);
        imwrite("translated_image.jpg", result);
        waitKey(0);
    }

    Size getSize() { return image.size(); }
};

int main() {
    try {
        ImageTranslator translator("image.jpg");
        Size s = translator.getSize();
        Mat translated = translator.translate(s.width / 4.0f, s.height / 4.0f);
        translator.showAndSave(translated);
    }
    catch (const exception& e) {
        cerr << e.what() << endl;
    }
    return 0;
}