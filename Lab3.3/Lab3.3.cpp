#include <opencv2/opencv.hpp>
#include <iostream>

class ImageResizer {
private:
    cv::Mat image;

public:
    ImageResizer(std::string path) {
        image = cv::imread(path);
        if (image.empty()) {
            throw std::runtime_error("Error: Could not read image file.");
        }
    }

    void resizeByPixels(int width, int height, std::string windowTitle) {
        cv::Mat resized;
        cv::resize(image, resized, cv::Size(width, height), 0, 0, cv::INTER_LINEAR);
        cv::imshow(windowTitle, resized);
    }

    ~ImageResizer() {
        cv::waitKey(0);
        cv::destroyAllWindows();
    }
};

int main() {
    try {
        ImageResizer resizer("image.jpeg");
        resizer.resizeByPixels(600, 400, "Resized 600x400");
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}