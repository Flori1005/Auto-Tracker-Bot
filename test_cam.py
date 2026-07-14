import cv2

cap = cv2.VideoCapture(0) # 0 ist meist die Kamera
if not cap.isOpened():
    print("Kamera konnte nicht geöffnet werden!")
else:
    print("Kamera läuft erfolgreich!")
    cap.release()