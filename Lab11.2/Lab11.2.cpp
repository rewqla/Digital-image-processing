#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>

using namespace cv;
using namespace std;

class ImageEditor {
private:
    Mat originalImage;
    Mat currentDisplay;
    string windowName;
    Point topLeft, bottomRight;
    int scaleValue;
    const int maxScale = 100;

public:
    ImageEditor(string filePath, string winName = "Image Editor") {
        originalImage = imread(filePath);
        if (originalImage.empty()) {
            throw runtime_error("Could not open image: " + filePath);
        }
        currentDisplay = originalImage.clone();
        windowName = winName;
        scaleValue = 0; // Default: 1.0 scale

        namedWindow(windowName, WINDOW_AUTOSIZE);
    }

    static void onMouse(int event, int x, int y, int flags, void* userdata) {
        ImageEditor* editor = reinterpret_cast<ImageEditor*>(userdata);

        if (event == EVENT_LBUTTONDOWN) {
            editor->topLeft = Point(x, y);
        }
        else if (event == EVENT_LBUTTONUP) {
            editor->bottomRight = Point(x, y);
            // Draw green rectangle
            rectangle(editor->currentDisplay, editor->topLeft, editor->bottomRight,
                Scalar(0, 255, 0), 2, 8);
            editor->refresh();
        }
    }

    static void onTrackbar(int pos, void* userdata) {
        ImageEditor* editor = reinterpret_cast<ImageEditor*>(userdata);
        double factor = 1.0 + (pos / 100.0);

        Mat scaled;
        resize(editor->originalImage, scaled, Size(), factor, factor, INTER_LINEAR);
        editor->currentDisplay = scaled;
        editor->refresh();
    }

    void refresh() {
        imshow(windowName, currentDisplay);
    }

    void run() {
        setMouseCallback(windowName, onMouse, this);
        createTrackbar("Scale %", windowName, &scaleValue, maxScale, onTrackbar, this);

        cout << "Instructions:\n- Drag Mouse: Draw Rectangles\n- Trackbar: Zoom In\n- Press 'c': Clear\n- Press 'q': Exit" << endl;

        int key = 0;
        while (key != 'q' && key != 27) { 
            refresh();
            key = waitKey(0);

            if (key == 'c') { // Clear annotations
                currentDisplay = originalImage.clone();
                scaleValue = 0; // Reset scale tracker
                setTrackbarPos("Scale %", windowName, 0);
                cout << "Canvas cleared." << endl;
            }
        }
        destroyAllWindows();
    }
};

int main() {
    try {
        ImageEditor editor("sample.png");
        editor.run();
    }
    catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        return -1;
    }
    return 0;
}