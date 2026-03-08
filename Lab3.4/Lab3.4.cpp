#include <opencv2/opencv.hpp>
#include <iostream>

class AdvancedResizer {
private:
    cv::Mat image;

public:
    AdvancedResizer(std::string path) {
        image = cv::imread(path);
        if (image.empty()) throw std::runtime_error("Error: File not found.");
    }

    void resizeByScale(double fx, double fy, int interp, std::string title) {
        cv::Mat result;
        cv::resize(image, result, cv::Size(), fx, fy, interp);
        cv::imshow(title, result);
    }

    ~AdvancedResizer() {
        cv::waitKey(0);
        cv::destroyAllWindows();
    }
};

int main() {
    try {
        AdvancedResizer resizer("image.jpeg");
        resizer.resizeByScale(0.5, 0.5, cv::INTER_AREA, "Scale 0.5 - Area");
        resizer.resizeByScale(1.5, 1.5, cv::INTER_CUBIC, "Scale 1.5 - Cubic");
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}