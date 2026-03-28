import cv2
import time
from IPython.display import display, clear_output
import matplotlib.pyplot as plt

class VideoPlayer:
    def __init__(self, file_path):
        self.cap = cv2.VideoCapture(file_path)
        self.window_name = "Video Playback"
        
        if not self.cap.isOpened():
            raise RuntimeError(f"Помилка: Не вдалося відкрити відеофайл: {file_path}")

        self.fps = self.cap.get(cv2.CAP_PROP_FPS)
        self.frame_count = self.cap.get(cv2.CAP_PROP_FRAME_COUNT)
        print(f"Файл: {file_path}\nFPS: {self.fps}\nВсього кадрів: {self.frame_count}")

    def play(self):
        try:
            while self.cap.isOpened():
                ret, frame = self.cap.read()
                if not ret:
                    print("Відео завершилося або кадр не зчитано.")
                    break

                frame_rgb = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)

                clear_output(wait=True)
                plt.figure(figsize=(10, 6))
                plt.imshow(frame_rgb)
                plt.axis('off')
                plt.title(self.window_name)
                plt.show()

                time.sleep(1 / (self.fps * 2)) 

        except KeyboardInterrupt:
            print("Відтворення зупинено користувачем.")

    def __del__(self):
        if hasattr(self, 'cap'):
            self.cap.release()
        print("Ресурси звільнено.")

try:
    video_path = "Test.mp4"
    player = VideoPlayer(video_path)
    player.play()

except Exception as e:
    print(f"Виняток: {e}")