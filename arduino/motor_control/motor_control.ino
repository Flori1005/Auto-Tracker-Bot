#include <Servo.h>

// --- Servo für die Lenkung (Vorderachse) ---
Servo steeringServo;
const int servoPin = 3;     // PWM Pin für den Servo
const int centerAngle = 90; // Winkel für Geradeausfahrt
const int leftAngle = 60;   // Einschlagwinkel Links
const int rightAngle = 120; // Einschlagwinkel Rechts

// --- Servos für die Kamera (Pan/Tilt) ---
Servo panServo;
const int panPin = 11;
const int panLeft = 180;
const int panRight = 0;
const int panCenterAngle = 93; // <-- GEUPDATED: Der Offset-Fix für die Mitte

Servo tiltServo;
const int tiltPin = 12;
const int tiltUp = 180;
const int tiltDown = 0;
const int tiltCenterAngle = 90; // <-- GEUPDATED: Die neue physische Mitte nach Umbau

// --- Ultraschallsensor ---
#define TRIG_PIN A0
#define ECHO_PIN A1

// --- L298N Motortreiber (Hinterachse) ---
// Motor A (Hinten Links)
const int enA = 9; // PWM Pin für Geschwindigkeit
const int in1 = 8;
const int in2 = 7;

// Motor B (Hinten Rechts)
const int enB = 10; // PWM Pin für Geschwindigkeit
const int in3 = 5;
const int in4 = 4;

int speed = 255; // Geschwindigkeit (0-255)

void setup() {
  Serial.begin(9600);

  // --- Lenkung initialisieren ---
  steeringServo.attach(servoPin);
  steerCenter();

  // --- Kamera initialisieren ---
  panServo.attach(panPin);
  tiltServo.attach(tiltPin);
  panCenter();
  tiltCenter();

  // --- Ultraschall initialisieren ---
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  // --- Motorpins initialisieren ---
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);

  pinMode(enB, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  stopMotors();
  Serial.println("Arduino bereit. Alle Servos zentriert. Warte auf Test-Befehle...");
}

void loop() {
  if (Serial.available() > 0) {
    char command = Serial.read();

    // Neue Steuerungslogik
    switch (command) {
    // --- Antrieb ---
    case 'F': // Fahren: Vorwärts
      moveForward();
      break;
    case 'B': // Fahren: Rückwärts
      moveBackward();
      break;
    case 'S': // Fahren: Stopp
      stopMotors();
      break;

    // --- Lenkung ---
    case 'L': // Lenken: Links
      steerLeft();
      break;
    case 'R': // Lenken: Rechts
      steerRight();
      break;
    case 'C': // Lenken: Geradeaus (Center)
      steerCenter();
      break;

    // --- Kamera Pan (Links/Rechts) ---
    case 'X': 
      panServo.write(panLeft);
      Serial.println("Kamera: LINKS");
      break;
    case 'Y': 
      panCenter();
      break;
    case 'Z': 
      panServo.write(panRight);
      Serial.println("Kamera: RECHTS");
      break;

    // --- Kamera Tilt (Hoch/Runter) ---
    case 'T': 
      tiltServo.write(tiltUp);
      Serial.println("Kamera: HOCH");
      break;
    case 'G': 
      tiltCenter();
      break;
    case 'V': 
      tiltServo.write(tiltDown);
      Serial.println("Kamera: RUNTER");
      break;

    // --- Ultraschall ---
    case 'D': 
      measureDistance();
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

// --- Lenkfunktionen (Servos) ---

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
}

void panCenter() {
  panServo.write(panCenterAngle); 
  Serial.println("Kamera (Pan): ZENTRIERT (Offset korrigiert)");
}

void tiltCenter() {
  tiltServo.write(tiltCenterAngle); 
  Serial.println("Kamera (Tilt): ZENTRIERT (Physische Mitte)");
}

// --- Ultraschallfunktion ---

void measureDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  
  long dauer = pulseIn(ECHO_PIN, HIGH);
  long distanz_cm = dauer * 0.034 / 2;
  
  Serial.print("Ultraschall Distanz: ");
  Serial.print(distanz_cm);
  Serial.println(" cm");
}