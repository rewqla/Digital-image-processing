#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>

class ImageHandler {
private:
    cv::Mat img;
    std::string windowName;

public:
    ImageHandler(std::string filePath) {
        img = cv::imread(filePath, cv::IMREAD_GRAYSCALE);
        if (img.empty()) {
            throw std::runtime_error("Critical Error: File not found or invalid format.");
        }
    }

    void save(std::string newPath) {
        cv::imwrite(newPath, img);
    }

    void display(std::string title) {
        windowName = title;
        cv::namedWindow(windowName, cv::WINDOW_NORMAL);
        cv::imshow(windowName, img);
    }

    ~ImageHandler() {
        std::cout << "Waiting for key press to close..." << std::endl;
        cv::waitKey(0);
        cv::destroyAllWindows();
        std::cout << "Program finished, windows closed." << std::endl;
    }
};

int main() {
    try {
        ImageHandler myImage("image.webp");

        myImage.save("image_grayscale.webp");
        myImage.display("Grayscale image");

    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    return 0;
}