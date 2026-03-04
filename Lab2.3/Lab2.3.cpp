#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>

class VideoPlayer {
private:
    cv::VideoCapture cap;
    std::string windowName;

public:
    VideoPlayer(std::string filePath) : windowName("Video Playback") {
        cap.open(filePath);
        if (!cap.isOpened()) {
            throw std::runtime_error("Error: Could not open video file: " + filePath);
        }

        double fps = cap.get(cv::CAP_PROP_FPS);
        double count = cap.get(cv::CAP_PROP_FRAME_COUNT);
        std::cout << "File: " << filePath << "\nFPS: " << fps << "\nTotal Frames: " << count << std::endl;
    }

    void play() {
        cv::Mat frame;
        while (cap.read(frame)) {
            cv::imshow(windowName, frame);

            if (cv::waitKey(25) == 'q') {
                std::cout << "Playback stopped by user." << std::endl;
                break;
            }
        }
    }

    ~VideoPlayer() {
        cap.release();
        cv::destroyAllWindows();
        std::cout << "Resources released and windows closed." << std::endl;
    }
};

int main() {
    try {
        VideoPlayer player("Test.mp4");
        player.play();
    }
    catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
        return -1;
    }
    return 0;
}