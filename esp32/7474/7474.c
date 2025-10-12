#include <Arduino.h>

// Pin Definitions
#define D1 16       // 7474 D input for X
#define D2 17       // 7474 D input for Y
#define CLK 4       // Common clock
#define Z_PIN 18    // Input for Z

// 7447 connections
#define A 21
#define B 22
#define C 23
#define D 25

void setup() {
  Serial.begin(115200);

  // 7474 control pins
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(CLK, OUTPUT);
  pinMode(Z_PIN, OUTPUT);

  // 7447 decoder output pins
  pinMode(A, OUTPUT);
  pinMode(B, OUTPUT);
  pinMode(C, OUTPUT);
  pinMode(D, OUTPUT);

  Serial.println("ESP32 + 7474 + 7447 + 7-Segment Logic Circuit");
  Serial.println("Function: F = X'Y' + YZ");
  Serial.println("------------------------------------------");
}

void loop() {
  int X, Y, Z;
  
  // Input values from Serial
  if (Serial.available()) {
    X = Serial.parseInt();
    Y = Serial.parseInt();
    Z = Serial.parseInt();

    while (Serial.available()) Serial.read();

    Serial.print("Inputs: X="); Serial.print(X);
    Serial.print(" Y="); Serial.print(Y);
    Serial.print(" Z="); Serial.println(Z);

    // Send data to flip-flops
    digitalWrite(D1, X);
    digitalWrite(D2, Y);
    digitalWrite(Z_PIN, Z);

    // Trigger clock
    digitalWrite(CLK, HIGH);
    delay(10);
    digitalWrite(CLK, LOW);

    // Compute Logic Function
    int F = ((!X && !Y) || (Y && Z));

    // Display F on 7-segment (using 7447)
    displayNumber(F);

    Serial.print("Output F = ");
    Serial.println(F);
    delay(1000);
  }
}

// Function to display number on 7-segment through 7447
void displayNumber(int num) {
  digitalWrite(A, num & 0x01);
  digitalWrite(B, (num >> 1) & 0x01);
  digitalWrite(C, (num >> 2) & 0x01);
  digitalWrite(D, (num >> 3) & 0x01);
}
