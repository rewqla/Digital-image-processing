import cv2
import matplotlib.pyplot as plt

class ShapeAnnotator:
    def __init__(self, path):
        self.image = cv2.imread(path)
        if self.image is None:
            raise RuntimeError("Image not found!")

    def draw_shapes(self):
        canvas = self.image.copy()

        cv2.line(canvas, (50, 50), (300, 50), (255, 0, 0), 3)

        cv2.circle(canvas, (100, 220), 50, (0, 255, 0), -1)

        canvas_rgb = cv2.cvtColor(canvas, cv2.COLOR_BGR2RGB)
        plt.figure(figsize=(10, 7))
        plt.imshow(canvas_rgb)
        plt.title("Shape Annotation")
        plt.axis('off')
        plt.show()

try:
    annotator = ShapeAnnotator("images.jpg")
    annotator.draw_shapes()
except Exception as e:
    print(e)