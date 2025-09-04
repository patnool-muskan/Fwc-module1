#include <Arduino.h>

// Inputs
const int Xpin = 2;   // X
const int Ypin = 3;   // Y

// 7447 inputs
const int Apin = 4;   // A (LSB)
const int Bpin = 5;   // B
const int Cpin = 6;   // C
const int Dpin = 7;   // D

void setup() {
  pinMode(Xpin, INPUT_PULLUP);
  pinMode(Ypin, INPUT_PULLUP);

  pinMode(Apin, OUTPUT);
  pinMode(Bpin, OUTPUT);
  pinMode(Cpin, OUTPUT);
  pinMode(Dpin, OUTPUT);

  // Tie higher inputs low
  digitalWrite(Bpin, LOW);
  digitalWrite(Cpin, LOW);
  digitalWrite(Dpin, LOW);

  Serial.begin(9600);
}

void loop() {
  // Read inputs (invert because of pull-up)
  int X = !digitalRead(Xpin);
  int Y = !digitalRead(Ypin);

  // Step 1: get complements
  int Xbar = !X;
  int Ybar = !Y;

  // Step 2: form product terms
  int term1 = Xbar && Y; // X'Y
  int term2 = X && Ybar; // XY'

  // Step 3: OR the terms
  int Z = term1 || term2;

  // Drive 7447 (only A matters)
  digitalWrite(Apin, Z);

  // Debug
  Serial.print("X="); Serial.print(X);
  Serial.print(" Y="); Serial.print(Y);
  Serial.print(" Z="); Serial.println(Z);

  delay(500);
}
\
