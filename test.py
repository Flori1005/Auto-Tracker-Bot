import cv2

print("1. Verbinde mit Kamera...")
# Der Zusatz cv2.CAP_V4L2 zwingt den Pi, den nativen Linux-Videotreiber zu nutzen.
# Das löst auf dem Raspberry Pi sehr oft diese "Hänger".
cap = cv2.VideoCapture(0, cv2.CAP_V4L2)

print("2. Versuche ein Bild zu lesen...")
ret, frame = cap.read()

if ret:
    cv2.imwrite("test_bild.jpg", frame)
    print("3. ERFOLG! Bild wurde als test_bild.jpg gespeichert.")
else:
    print("3. FEHLER: Kamera hat kein Bild geliefert.")

cap.release()