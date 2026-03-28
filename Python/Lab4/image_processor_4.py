import cv2
import os
import matplotlib.pyplot as plt

class ImageTiler:
    def __init__(self, path):
        self.image = cv2.imread(path)
        if self.image is None:
            raise RuntimeError("Error: Could not open or find the image!")
        
        if not os.path.exists('saved_patches'):
            os.makedirs('saved_patches')

    def split_into_tiles(self, tile_height, tile_width):
        canvas = self.image.copy()
        rows, cols = self.image.shape[:2]

        for y in range(0, rows - tile_height + 1, tile_height):
            for x in range(0, cols - tile_width + 1, tile_width):
                
                tile = self.image[y:y + tile_height, x:x + tile_width]

                file_name = f"saved_patches/tile_{y}_{x}.jpg"
                cv2.imwrite(file_name, tile)

                cv2.rectangle(canvas, (x, y), (x + tile_width, y + tile_height), (0, 255, 0), 2)

        canvas_rgb = cv2.cvtColor(canvas, cv2.COLOR_BGR2RGB)
        plt.figure(figsize=(12, 8))
        plt.imshow(canvas_rgb)
        plt.title("Tiling Result (Grid)")
        plt.axis('off')
        plt.show()
        
        print("Tiling complete. Check 'saved_patches' folder.")

    def __del__(self):
        print("Resources cleared.")

try:
    tiler = ImageTiler("test.jpg")
    tiler.split_into_tiles(75, 100)
except Exception as e:
    print(e)