import cv2
import matplotlib.pyplot as plt
import os

class ImageHandler:
    def __init__(self, file_path):
        self.img = cv2.imread(file_path, cv2.IMREAD_GRAYSCALE)
        
        if self.img is None:
            raise FileNotFoundError(f"Критична помилка: Файл '{file_path}' не знайдено або формат не підтримується.")

    def save(self, new_path):
        cv2.imwrite(new_path, self.img)
        print(f"Зображення збережено як: {new_path}")

    def display(self, title="Grayscale image"):
        plt.figure(figsize=(8, 6))
        plt.imshow(self.img, cmap='gray')
        plt.title(title)
        plt.axis('off') 
        plt.show()

    def __del__(self):
        print("Обробка завершена.")

try:
    input_filename = "image.webp"
    
    my_image = ImageHandler(input_filename)

    my_image.save("image_grayscale.webp")
    my_image.display("Grayscale image")

except Exception as e:
    print(f"Помилка: {e}")