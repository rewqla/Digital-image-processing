import cv2
import matplotlib.pyplot as plt

class TextAnnotator:
    def __init__(self, path):
        self.image = cv2.imread(path)
        if self.image is None:
            raise RuntimeError("Image not found!")

    def add_label(self, text, pos, color):
        canvas = self.image.copy()
        cv2.putText(canvas, text, pos, cv2.FONT_HERSHEY_SIMPLEX, 1.0, color, 2)
        
        canvas_rgb = cv2.cvtColor(canvas, cv2.COLOR_BGR2RGB)
        plt.figure(figsize=(10, 7))
        plt.imshow(canvas_rgb)
        plt.title("Text Annotation")
        plt.axis('off')
        plt.show()

try:
    annotator = TextAnnotator("images.jpg")
    annotator.add_label("Creation", (50, 50), (100, 255, 0))
except Exception as e:
    print(e)