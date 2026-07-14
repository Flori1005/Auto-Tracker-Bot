import cv2
import ipywidgets as widgets
from IPython.display import display

# Kamera initialisieren
cap = cv2.VideoCapture(0)
image_widget = widgets.Image(format='jpeg', width=640, height=480)
display(image_widget)

try:
    while True:
        ret, frame = cap.read()
        if not ret: break
        
        # In JPEG konvertieren für das Widget
        _, encoded_image = cv2.imencode('.jpg', frame)
        image_widget.value = encoded_image.tobytes()
except KeyboardInterrupt:
    cap.release()