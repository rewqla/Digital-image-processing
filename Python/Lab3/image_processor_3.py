import cv2
import matplotlib.pyplot as plt

class ImageResizer:
    def __init__(self, path):
        self.image = cv2.imread(path)
        if self.image is None:
            raise RuntimeError("Error: Could not read image file.")

    def resize_by_pixels(self, width, height, window_title):
        resized = cv2.resize(self.image, (width, height), interpolation=cv2.INTER_LINEAR)
        
        resized_rgb = cv2.cvtColor(resized, cv2.COLOR_BGR2RGB)
        
        plt.figure(figsize=(10, 7))
        plt.imshow(resized_rgb)
        plt.title(window_title)
        plt.axis('off')
        plt.show()

    def __del__(self):
        print("Processing finished.")

try:
    resizer = ImageResizer("image.jpeg")
    resizer.resize_by_pixels(600, 400, "Resized 600x400")
except Exception as e:
    print(e)