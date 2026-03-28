import cv2
import numpy as np
import matplotlib.pyplot as plt

class ImageFilter:
    def __init__(self, path):
        self.image = cv2.imread(path)
        if self.image is None:
            raise RuntimeError(f"Error: Image not found at {path}")

    def apply_custom_blur(self):
        kernel = np.ones((5, 5), np.float64) / 25.0
        result = cv2.filter2D(self.image, -1, kernel)
        return result

    def apply_sharpening(self):
        kernel = np.array([[0, -1, 0],
                           [-1, 5, -1],
                           [0, -1, 0]], dtype=np.float64)
        result = cv2.filter2D(self.image, -1, kernel)
        return result

    def apply_gaussian_blur(self, k_size=5):
        result = cv2.GaussianBlur(self.image, (k_size, k_size), 0)
        return result

    def apply_median_blur(self, k_size=5):
        result = cv2.medianBlur(self.image, k_size)
        return result

    def apply_bilateral(self, d=9, sigma_color=75, sigma_space=75):
        result = cv2.bilateralFilter(self.image, d, sigma_color, sigma_space)
        return result

    def display_all(self, results_dict):
        num_images = len(results_dict) + 1
        plt.figure(figsize=(20, 10))
        
        orig_rgb = cv2.cvtColor(self.image, cv2.COLOR_BGR2RGB)
        plt.subplot(2, 3, 1)
        plt.imshow(orig_rgb)
        plt.title("Original Image")
        plt.axis('off')

        for i, (title, img) in enumerate(results_dict.items(), 2):
            img_rgb = cv2.cvtColor(img, cv2.COLOR_BGR2RGB)
            plt.subplot(2, 3, i)
            plt.imshow(img_rgb)
            plt.title(title)
            plt.axis('off')
        
        plt.tight_layout()
        plt.show()

try:
    processor = ImageFilter("test.jpg")

    results = {
        "1. Custom Kernel Blur": processor.apply_custom_blur(),
        "2. Sharpened Image": processor.apply_sharpening(),
        "3. Gaussian Blur": processor.apply_gaussian_blur(9),
        "4. Median Blur": processor.apply_median_blur(5),
        "5. Bilateral Filter": processor.apply_bilateral()
    }

    processor.display_all(results)

except Exception as e:
    print(f"Exception: {e}")