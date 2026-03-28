import cv2
import matplotlib.pyplot as plt

class AdvancedResizer:
    def __init__(self, path):
        self.image = cv2.imread(path)
        if self.image is None:
            raise RuntimeError("Error: File not found.")

    def resize_by_scale(self, fx, fy, interp, title):
        result = cv2.resize(self.image, None, fx=fx, fy=fy, interpolation=interp)
        
        result_rgb = cv2.cvtColor(result, cv2.COLOR_BGR2RGB)
        
        plt.figure(figsize=(8, 6))
        plt.imshow(result_rgb)
        plt.title(title)
        plt.axis('off')
        plt.show()

    def __del__(self):
        print("Resources cleared.")

try:
    resizer = AdvancedResizer("image.jpeg")
    
    resizer.resize_by_scale(0.5, 0.5, cv2.INTER_AREA, "Scale 0.5 - Area")
    
    resizer.resize_by_scale(1.5, 1.5, cv2.INTER_CUBIC, "Scale 1.5 - Cubic")

except Exception as e:
    print(e)