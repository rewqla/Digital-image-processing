#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
#include <filesystem>

using namespace std;
using namespace cv;

class ImageTiler {
private:
    Mat image;

public:
    ImageTiler(string path) {
        image = imread(path);
        if (image.empty()) {
            throw runtime_error("Error: Could not open or find the image!");
        }
    }

    void splitIntoTiles(int tileHeight, int tileWidth) {
        Mat canvas = image.clone();
        int rows = image.rows;
        int cols = image.cols;

        for (int y = 0; y <= rows - tileHeight; y += tileHeight) {
            for (int x = 0; x <= cols - tileWidth; x += tileWidth) {

                Mat tile = image(Range(y, y + tileHeight), Range(x, x + tileWidth));

                string fileName = "saved_patches/tile_" + to_string(y) + "_" + to_string(x) + ".jpg";
                imwrite(fileName, tile);

                rectangle(canvas, Point(x, y), Point(x + tileWidth, y + tileHeight), Scalar(0, 255, 0), 1);
            }
        }

        imshow("Tiling Result (Grid)", canvas);
        cout << "Tiling complete. Check 'saved_patches' folder." << endl;
        waitKey(0);
        destroyAllWindows();
    }
};

int main() {
    try {
        ImageTiler tiler("test.jpg");
        tiler.splitIntoTiles(75, 100); 
    }
    catch (const exception& e) {
        cerr << e.what() << endl;
    }
    return 0;
}