# Auto Tracker Bot 🚗👁️

Ein autonomes Fahrzeug auf Basis von Raspberry Pi und Arduino, das mittels One-Shot-Learning über eine Kamera nach einem vorgegebenen Referenzbild sucht.

## 🏗️ Systemarchitektur

*   **Arduino (Slave):** Empfängt serielle Steuerbefehle und steuert die Motortreiber (L298N).
*   **Raspberry Pi (Master):** Führt Computer Vision via Kamera aus, berechnet Wegpunkte und sendet Navigationsbefehle an den Arduino.

## 🗺️ Projektphasen & Roadmap

- [ ] **Phase 1: Hardware-Basis**
  - Chassis zusammenbauen, Motoren verkabeln.
  - `arduino/motor_control.ino` schreiben (nimmt serielle Befehle entgegen).
- [ ] **Phase 2: Die Brücke (Kommunikation)**
  - Serielle USB-Verbindung zwischen Pi und Arduino herstellen.
  - Befehle über `notebooks/01_serial_test.ipynb` senden.
- [ ] **Phase 3: Das Sichtfeld (Proof of Concept)**
  - OpenCV einrichten.
  - Simples Color-Tracking oder QR-Code Erkennung in `notebooks/02_color_tracking.ipynb` umsetzen, um Bounding-Box-Logik zu testen.
- [ ] **Phase 4: Die KI (One-Shot Matching)**
  - Feature-Matching (z.B. ORB) für ein Referenzbild in `notebooks/03_one_shot_cv.ipynb` implementieren.
- [ ] **Phase 5: Integration (Der Autopilot)**
  - Algorithmen in `/src` als saubere Module auslagern.
  - State Machine in `src/main.py` schreiben (Idle -> Search -> Track).
- [ ] **Phase 6: Deployment**
  - Web-API für den Bild-Upload hinzufügen.
  - Pi-Umgebung containerisieren (`/docker/docker-compose.yml`).

## 🚀 Setup für die Entwicklung

1. Repository klonen
2. Virtuelle Umgebung erstellen: `python3 -m venv venv`
3. Abhängigkeiten installieren: `pip install -r requirements.txt`
4. Jupyter starten: `jupyter notebook`