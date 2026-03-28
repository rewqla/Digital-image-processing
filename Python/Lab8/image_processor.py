import cv2
import matplotlib.pyplot as plt

class ThresholdManager:
    def __init__(self, file_path, thresh=127, max_val=255):
        self.source_image = cv2.imread(file_path, cv2.IMREAD_GRAYSCALE)
        if self.source_image is None:
            raise RuntimeError(f"Error: Could not load image at: {file_path}")
        self.threshold_value = thresh
        self.max_value = max_val

    def set_params(self, thresh, max_val):
        self.threshold_value = thresh
        self.max_value = max_val

    def apply_threshold(self, threshold_type):
        _, result = cv2.threshold(self.source_image, self.threshold_value, self.max_value, threshold_type)
        return result

    def get_source(self):
        return self.source_image

    def __del__(self):
        print("Resources released.")

def display_results(images_dict):
    plt.figure(figsize=(15, 10))
    for i, (title, img) in enumerate(images_dict.items(), 1):
        plt.subplot(2, 3, i)
        plt.imshow(img, cmap='gray')
        plt.title(title)
        plt.axis('off')
    plt.tight_layout()
    plt.show()

try:
    tm = ThresholdManager("test.jpg", 127, 255)

    results = {
        "Original Grayscale": tm.get_source(),
        "Binary Threshold": tm.apply_threshold(cv2.THRESH_BINARY),
        "Binary Inverse": tm.apply_threshold(cv2.THRESH_BINARY_INV),
        "Truncate": tm.apply_threshold(cv2.THRESH_TRUNC),
        "To Zero": tm.apply_threshold(cv2.THRESH_TOZERO),
        "To Zero Inverse": tm.apply_threshold(cv2.THRESH_TOZERO_INV)
    }

    display_results(results)

except Exception as e:
    print(f"Application Error: {e}")