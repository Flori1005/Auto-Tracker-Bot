import cv2

def main():
    # Kamera öffnen
    cap = cv2.VideoCapture(0)
    
    print("Drücke 'q', um das Programm zu beenden.")
    
    while True:
        ret, frame = cap.read()
        if not ret:
            print("Fehler beim Abrufen des Frames")
            break
            
        cv2.imshow('Kamera Test', frame)
        
        # 'q' zum Beenden drücken
        if cv2.waitKey(1) & 0xFF == ord('q'):
            break
            
    cap.release()
    cv2.destroyAllWindows()

if __name__ == "__main__":
    main()