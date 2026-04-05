#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

class BackgroundEstimator {
private:
    cv::VideoCapture cap;
    cv::Mat medianBackground;

    uchar getMedian(std::vector<uchar>& tokens) {
        size_t n = tokens.size() / 2;
        std::nth_element(tokens.begin(), tokens.begin() + n, tokens.end());
        return tokens[n];
    }

public:
    BackgroundEstimator(std::string videoPath) {
        cap.open(videoPath);
        if (!cap.isOpened()) {
            throw std::runtime_error("Could not open video file");
        }
    }

    cv::Mat calculateBackground(int numSamples = 25) {
        int frameCount = static_cast<int>(cap.get(cv::CAP_PROP_FRAME_COUNT));
        std::vector<cv::Mat> frames;
        
        std::default_random_engine generator;
        std::uniform_int_distribution<int> distribution(0, frameCount - 1);

        for (int i = 0; i < numSamples; i++) {
            int fid = distribution(generator);
            cap.set(cv::CAP_PROP_POS_FRAMES, fid);
            cv::Mat frame;
            cap >> frame;
            if (!frame.empty()) {
                frames.push_back(frame);
            }
        }

        if (frames.empty()) throw std::runtime_error("No frames captured");

        medianBackground = cv::Mat(frames[0].rows, frames[0].cols, CV_8UC3);

        for (int r = 0; r < frames[0].rows; r++) {
            for (int c = 0; c < frames[0].cols; c++) {
                for (int ch = 0; ch < 3; ch++) {
                    std::vector<uchar> pixels;
                    for (int i = 0; i < frames.size(); i++) {
                        pixels.push_back(frames[i].at<cv::Vec3b>(r, c)[ch]);
                    }
                    medianBackground.at<cv::Vec3b>(r, c)[ch] = getMedian(pixels);
                }
            }
        }
        return medianBackground;
    }

    void detectObjects(int thresholdVal = 30) {
        if (medianBackground.empty()) {
            calculateBackground();
        }

        cv::Mat grayMedian;
        cv::cvtColor(medianBackground, grayMedian, cv::COLOR_BGR2GRAY);
        cap.set(cv::CAP_PROP_POS_FRAMES, 0);

        cv::Mat frame, grayFrame, diff, mask;

        while (true) {
            cap >> frame;
            if (frame.empty()) break;

            cv::cvtColor(frame, grayFrame, cv::COLOR_BGR2GRAY);
            
            cv::absdiff(grayFrame, grayMedian, diff);
            
            cv::threshold(diff, mask, thresholdVal, 255, cv::THRESH_BINARY);

            cv::imshow("Object Detection Mask", mask);
            
            char key = (char)cv::waitKey(30);
            if (key == 'q' || key == 27) break;
        }

        cap.release();
        cv::destroyAllWindows();
    }
};

int main() {
    try {
        BackgroundEstimator detector("Test4.mp4");
        detector.detectObjects(30);
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return -1;
    }
    return 0;
}