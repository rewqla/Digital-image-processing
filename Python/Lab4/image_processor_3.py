import cv2
import matplotlib.pyplot as plt

class ImageCropper:
    def __init__(self, path):
        self.image = cv2.imread(path)
        if self.image is None:
            raise RuntimeError("Error: Could not open or find the image!")

    def crop_and_save(self, start_row, end_row, start_col, end_col, save_path):
        height, width = self.image.shape[:2]

        if end_row > height or end_col > width:
            print("Warning: Crop dimensions exceed image size. Adjusting...")
            end_row = min(end_row, height)
            end_col = min(end_col, width)

        # У Python обрізка виконується як зріз списку: [рядок_від:рядок_до, колонка_від:колонка_до]
        cropped = self.image[start_row:end_row, start_col:end_col]

        # Відображення обох варіантів через matplotlib
        fig, axes = plt.subplots(1, 2, figsize=(12, 6))
        
        # Оригінал
        image_rgb = cv2.cvtColor(self.image, cv2.COLOR_BGR2RGB)
        axes[0].imshow(image_rgb)
        axes[0].set_title("Original Image")
        axes[0].axis('off')

        # Обрізаний фрагмент
        cropped_rgb = cv2.cvtColor(cropped, cv2.COLOR_BGR2RGB)
        axes[1].imshow(cropped_rgb)
        axes[1].set_title("Cropped Fragment")
        axes[1].axis('off')

        plt.show()

        # Збереження
        cv2.imwrite(save_path, cropped)
        print(f"Fragment saved to: {save_path}")

    def __del__(self):
        print("Resources cleared.")

# --- Запуск ---
try:
    # Завантажте файл test.jpg у Colab перед запуском
    processor = ImageCropper("test.jpg")
    processor.crop_and_save(80, 280, 150, 330, "crop.jpg")
except Exception as e:
    print(e)