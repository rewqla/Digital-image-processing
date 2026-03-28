import cv2
import numpy as np
import matplotlib.pyplot as plt

class ImageTranslator:
    def __init__(self, path):
        self.image = cv2.imread(path)
        if self.image is None:
            raise RuntimeError("Image not found!")

    def translate(self, tx, ty):
        matrix = np.array([[1.0, 0.0, tx], 
                           [0.0, 1.0, ty]], dtype=np.float32)
        h, w = self.image.shape[:2]
        translated = cv2.warpAffine(self.image, matrix, (w, h))
        return translated

    def show_and_save(self, result):
        fig, axes = plt.subplots(1, 2, figsize=(12, 6))
        
        orig_rgb = cv2.cvtColor(self.image, cv2.COLOR_BGR2RGB)
        axes[0].imshow(orig_rgb)
        axes[0].set_title("Original")
        axes[0].axis('off')

        res_rgb = cv2.cvtColor(result, cv2.COLOR_BGR2RGB)
        axes[1].imshow(res_rgb)
        axes[1].set_title("Translated")
        axes[1].axis('off')

        plt.show()
        cv2.imwrite("translated_image.jpg", result)

    def get_size(self):
        h, w = self.image.shape[:2]
        return w, h

try:
    translator = ImageTranslator("image.jpg")
    width, height = translator.get_size()
    translated_mat = translator.translate(width / 4.0, height / 4.0)
    translator.show_and_save(translated_mat)
except Exception as e:
    print(e)