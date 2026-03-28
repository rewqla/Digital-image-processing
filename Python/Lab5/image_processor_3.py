import cv2
import matplotlib.pyplot as plt

class ImageRotator:
    def __init__(self, path):
        self.image = cv2.imread(path)
        if self.image is None:
            raise RuntimeError("Image not found!")

    def rotate(self, angle, scale=1.0):
        h, w = self.image.shape[:2]
        center = ((w - 1) / 2.0, (h - 1) / 2.0)
        matrix = cv2.getRotationMatrix2D(center, angle, scale)
        rotated = cv2.warpAffine(self.image, matrix, (w, h))
        return rotated

    def show_and_save(self, result, window_name="Rotated Image"):
        fig, axes = plt.subplots(1, 2, figsize=(12, 6))
        
        orig_rgb = cv2.cvtColor(self.image, cv2.COLOR_BGR2RGB)
        axes[0].imshow(orig_rgb)
        axes[0].set_title("Original")
        axes[0].axis('off')

        res_rgb = cv2.cvtColor(result, cv2.COLOR_BGR2RGB)
        axes[1].imshow(res_rgb)
        axes[1].set_title(window_name)
        axes[1].axis('off')

        plt.show()
        cv2.imwrite("rotated_image.jpg", result)

try:
    rotator = ImageRotator("image.jpg")
    rotated_mat = rotator.rotate(45)
    rotator.show_and_save(rotated_mat)
except Exception as e:
    print(e)