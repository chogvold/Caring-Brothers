#include <Servo.h>

// initialiserer servoene og knappen til bestemt pin
const int PIN_SERVO1    = 9;   // Servo 1 signal på D9
const int PIN_SERVO2    = 11;  // Servo 2 signal på D11
const int PIN_BUTTON    = 2;

Servo servo1;
Servo servo2;

// 0 = i midtstilling (begge 90°)
// 1 = Servo1 = 180, Servo2 = 0
byte posState = 0;

// Debounce-variabler
int lastButtonState   = HIGH;
int stableButtonState = HIGH;
unsigned long lastDebounceTime = 0;
const unsigned long debounceDelay = 50;

void setup() {
  servo1.attach(PIN_SERVO1);
  servo2.attach(PIN_SERVO2);

  // Start i midt (begge på 90°)
  servo1.write(90);
  servo2.write(90);
  posState = 0;

  pinMode(PIN_BUTTON, INPUT_PULLUP);
}

void loop() {
  int reading = digitalRead(PIN_BUTTON);

  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }
// Passer på at knappen bare endrer verdi når man trykker
  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != stableButtonState) {
      stableButtonState = reading;
      // Når knappen trykkes 
      if (stableButtonState == LOW) {
        if (posState == 0) {
          // Flytt én servo +90 (til 180), andre –90 (til 0)
          servo1.write(180);
          servo2.write(0);
          posState = 1;
        }
        else {
          // Gå tilbake til midt (begge 90°)
          servo1.write(90);
          servo2.write(90);
          posState = 0;
        }
      }
    }
  }

  lastButtonState = reading;
}