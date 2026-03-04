#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>

class CameraRecorder {
private:
    cv::VideoCapture cap;
    cv::VideoWriter writer;
    std::string windowName;

public:
    CameraRecorder(int deviceID = 0) : windowName("Webcam Feed") {
        cap.open(deviceID, cv::CAP_DSHOW);

        if (!cap.isOpened()) {
            throw std::runtime_error("Error: Could not open the camera.");
        }

        int frame_width = static_cast<int>(cap.get(cv::CAP_PROP_FRAME_WIDTH));
        int frame_height = static_cast<int>(cap.get(cv::CAP_PROP_FRAME_HEIGHT));
        cv::Size frame_size(frame_width, frame_height);
        double fps = 20.0;

        writer.open("capture_output.mp4", cv::VideoWriter::fourcc('m', 'p', '4', 'v'), fps, frame_size);

        if (!writer.isOpened()) {
            throw std::runtime_error("Error: Could not open the file for writing.");
        }

        std::cout << "Recording started. Press 'q' to stop." << std::endl;
    }

    void run() {
        cv::Mat frame;
        while (true) {
            cap >> frame; 
            if (frame.empty()) break;

            writer.write(frame);       
            cv::imshow(windowName, frame); 

            if (cv::waitKey(1) == 'q') {
                std::cout << "User stopped the recording." << std::endl;
                break;
            }
        }
    }

    ~CameraRecorder() {
        cap.release();
        writer.release();
        cv::destroyAllWindows();
        std::cout << "Resources released and video saved successfully." << std::endl;
    }
};

int main() {
    try {
        CameraRecorder recorder(0); 
        recorder.run();
    }
    catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
        return -1;
    }
    return 0;
}