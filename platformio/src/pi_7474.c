#include <Arduino.h>

// Inputs
const int Xpin = 2;
const int Ypin = 3;

// Flip-flop pins
const int D1pin = 9;   // D input for FF1
const int D2pin = 6;   // D input for FF2
const int CLKpin = 8;  // shared clock
const int Q1pin = 10;  // Q output FF1
const int Q2pin = 7;   // Q output FF2

// 7447 inputs
const int Apin = 4;  // LSB
const int Bpin = 5;  // MSB
const int Cpin = 12; // tied LOW
const int Dpin = 13; // tied LOW

void setup() {
  pinMode(Xpin, INPUT_PULLUP);
  pinMode(Ypin, INPUT_PULLUP);

  pinMode(D1pin, OUTPUT);
  pinMode(D2pin, OUTPUT);
  pinMode(CLKpin, OUTPUT);

  pinMode(Q1pin, INPUT);
  pinMode(Q2pin, INPUT);

  pinMode(Apin, OUTPUT);
  pinMode(Bpin, OUTPUT);
  pinMode(Cpin, OUTPUT);
  pinMode(Dpin, OUTPUT);

  digitalWrite(Cpin, LOW);
  digitalWrite(Dpin, LOW);

  Serial.begin(9600);
}

void loop() {
  // Read inputs
  int X = !digitalRead(Xpin);
  int Y = !digitalRead(Ypin);

  // Example next-state logic (you can replace with K-map equations)
  int D1 = (X ^ Y);   // FF1 stores XOR
  int D2 = (X && Y);  // FF2 stores AND

  // Send to flip-flops
  digitalWrite(D1pin, D1);
  digitalWrite(D2pin, D2);

  // Clock pulse
  digitalWrite(CLKpin, LOW);
  delayMicroseconds(10);
  digitalWrite(CLKpin, HIGH);
  delayMicroseconds(10);
  digitalWrite(CLKpin, LOW);

  // Read back Q1, Q2
  int Q1 = digitalRead(Q1pin);
  int Q2 = digitalRead(Q2pin);

  // Drive 7447 (A=Q1, B=Q2)
  digitalWrite(Apin, Q1);
  digitalWrite(Bpin, Q2);

  // Debug
  Serial.print("X=");
  Serial.print(X);
  Serial.print(" Y=");
  Serial.print(Y);
  Serial.print(" D1=");
  Serial.print(D1);
  Serial.print(" D2=");
  Serial.print(D2);
  Serial.print(" Q1=");
  Serial.print(Q1);
  Serial.print(" Q2=");
  Serial.println(Q2);

  delay(500);
}
