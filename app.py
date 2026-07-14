from flask import Flask, Response
from picamera2 import Picamera2
import cv2

app = Flask(__name__)

# Kamera-Hardware nativ initialisieren
picam2 = Picamera2()
# Auflösung für den Stream definieren (Reduzierung spart Bandbreite)
picam2.configure(picam2.create_preview_configuration(main={"size": (640, 480)}))
picam2.start()

def generate_frames():
    while True:
        # Bild direkt als NumPy-Array abgreifen
        frame = picam2.capture_array()
        
        # --- Hier findet später die KI-Logik / das Tracking statt ---
        
        # Für das Web-Interface als JPEG encodieren
        ret, buffer = cv2.imencode('.jpg', frame)
        frame_bytes = buffer.tobytes()
        yield (b'--frame\r\n'
               b'Content-Type: image/jpeg\r\n\r\n' + frame_bytes + b'\r\n')

@app.route('/video_feed')
def video_feed():
    return Response(generate_frames(), mimetype='multipart/x-mixed-replace; boundary=frame')

@app.route('/')
def index():
    # Eine simple HTML-Ansicht, damit der Browser den Stream verlässlich rendert
    return "<html><body style='background-color: black; text-align: center;'><h1 style='color: white;'>Auto-Tracker Stream</h1><img src='/video_feed'></body></html>"

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000)