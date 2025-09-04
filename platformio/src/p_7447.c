#include <Arduino.h>

// Inputs
const int Xpin = 2;   // Input X
const int Ypin = 3;   // Input Y

// 7447 inputs
const int Apin = 4;   // A
const int Bpin = 5;   // B
const int Cpin = 6;   // C
const int Dpin = 7;   // D

void setup() {
  // Inputs with pull-ups
  pinMode(Xpin, INPUT_PULLUP);
  pinMode(Ypin, INPUT_PULLUP);

  // 7447 inputs as outputs
  pinMode(Apin, OUTPUT);
  pinMode(Bpin, OUTPUT);
  pinMode(Cpin, OUTPUT);
  pinMode(Dpin, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  // 1. Read inputs
  int X = !digitalRead(Xpin);  // invert because of pull-up
  int Y = !digitalRead(Ypin);

  // 2. Logic: Z = X'Y + XY'
  int xbar = !X;
  int ybar = !Y;
  int Z = (X&&ybar)||(xbar&&Y);  // OR

  // 3. Drive 7447
  digitalWrite(Apin, Z);   // Only A is used
  digitalWrite(Bpin, LOW);
  digitalWrite(Cpin, LOW);
  digitalWrite(Dpin, LOW);

  // 4. Debug
  Serial.print("X=");
  Serial.print(X);
  Serial.print("  Y=");
  Serial.print(Y);
  Serial.print("  Z=");
  Serial.println(Z);

  delay(500);
}
