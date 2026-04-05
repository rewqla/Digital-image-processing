import cv2
import numpy as np
import matplotlib.pyplot as plt
from IPython.display import display, clear_output

class BackgroundEstimator:
    def __init__(self, video_path):
        self.cap = cv2.VideoCapture(video_path)
        if not self.cap.isOpened():
            raise ValueError("Could not open video file")
        self.median_background = None

    def calculate_background(self, num_samples=25):
        frame_count = int(self.cap.get(cv2.CAP_PROP_FRAME_COUNT))
        frame_ids = np.random.randint(0, frame_count, num_samples)

        frames = []
        for fid in frame_ids:
            self.cap.set(cv2.CAP_PROP_POS_FRAMES, fid)
            ret, frame = self.cap.read()
            if ret:
                frames.append(frame)

        self.median_background = np.median(frames, axis=0).astype(np.uint8)
        return self.median_background

    def detect_objects(self, threshold=30):
        if self.median_background is None:
            self.calculate_background()

        gray_median = cv2.cvtColor(self.median_background, cv2.COLOR_BGR2GRAY)
        self.cap.set(cv2.CAP_PROP_POS_FRAMES, 0)

        try:
            while True:
                ret, frame = self.cap.read()
                if not ret: break

                gray_frame = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
                diff = cv2.absdiff(gray_frame, gray_median)
                _, mask = cv2.threshold(diff, threshold, 255, cv2.THRESH_BINARY)

                clear_output(wait=True)
                plt.imshow(mask, cmap='gray')
                plt.title("Object Detection Mask")
                plt.axis('off')
                plt.show()
        except KeyboardInterrupt:
            pass
        finally:
            self.cap.release()

detector = BackgroundEstimator('Test4.mp4')
detector.detect_objects()