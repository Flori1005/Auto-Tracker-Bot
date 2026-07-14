#include <Servo.h>

// --- Servo für die Lenkung (Vorderachse) ---
Servo steeringServo;
const int servoPin = 3;     // PWM Pin für den Servo (z.B. Pin 3)
const int centerAngle = 90; // Winkel für Geradeausfahrt
const int leftAngle = 60;   // Einschlagwinkel Links 
const int rightAngle = 120; // Einschlagwinkel Rechts 
// Hinweis: Die Winkel (60 und 120) musst du eventuell etwas anpassen, 
// je nachdem wie das Lenkgestänge mechanisch am Servo montiert ist.

// --- L298N Motortreiber (Hinterachse) ---
// Motor A (Hinten Links)
const int enA = 9;  // PWM Pin für Geschwindigkeit
const int in1 = 8;
const int in2 = 7;

// Motor B (Hinten Rechts)
const int enB = 10; // PWM Pin für Geschwindigkeit
const int in3 = 5;
const int in4 = 4;

int speed = 150; // Geschwindigkeit (0-255)

void setup() {
  Serial.begin(9600);
  
  // Servo initialisieren und zentrieren
  steeringServo.attach(servoPin);
  steerCenter();
  
  // Motorpins initialisieren
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  
  pinMode(enB, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  
  stopMotors();
  Serial.println("Arduino bereit. Servo zentriert, warte auf Befehle...");
}

void loop() {
  if (Serial.available() > 0) {
    char command = Serial.read();
    
    // Neue Steuerungslogik
    switch(command) {
      case 'F': // Fahren: Vorwärts
        moveForward();
        break;
      case 'B': // Fahren: Rückwärts
        moveBackward();
        break;
      case 'S': // Fahren: Stopp
        stopMotors();
        break;
      case 'L': // Lenken: Links
        steerLeft();
        break;
      case 'R': // Lenken: Rechts
        steerRight();
        break;
      case 'C': // Lenken: Geradeaus (Center)
        steerCenter();
        break;
    }
  }
}

// --- Bewegungsfunktionen (Antrieb) ---

void moveForward() {
  analogWrite(enA, speed);
  analogWrite(enB, speed);
  // Beide Motoren drehen vorwärts
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  Serial.println("Antrieb: VORWAERTS");
}

void moveBackward() {
  analogWrite(enA, speed);
  analogWrite(enB, speed);
  // Beide Motoren drehen rückwärts
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  Serial.println("Antrieb: RUECKWAERTS");
}

void stopMotors() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  analogWrite(enA, 0);
  analogWrite(enB, 0);
  Serial.println("Antrieb: STOPP");
}

// --- Lenkfunktionen (Servo) ---

void steerLeft() {
  steeringServo.write(leftAngle);
  Serial.println("Lenkung: LINKS");
}

void steerRight() {
  steeringServo.write(rightAngle);
  Serial.println("Lenkung: RECHTS");
}

void steerCenter() {
  steeringServo.write(centerAngle);
  Serial.println("Lenkung: ZENTRIERT");
}// Phase 1: C++ Skript für Motorsteuerung
