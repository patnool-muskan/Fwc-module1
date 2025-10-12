#include <Arduino.h>

// BCD output pins (connected to 7447 inputs)
#define A_PIN 13  // LSB
#define B_PIN 12
#define C_PIN 14
#define D_PIN 27  // MSB

void setBCD(int num);
int logicFunction(int X, int Y, int Z);

void setup() {
  Serial.begin(115200);
  pinMode(A_PIN, OUTPUT);
  pinMode(B_PIN, OUTPUT);
  pinMode(C_PIN, OUTPUT);
  pinMode(D_PIN, OUTPUT);

  Serial.println("\n7447 + ESP32 Logic Implementation");
  Serial.println("Function: F = X'Y' + YZ");
  Serial.println("Enter X Y Z (0 or 1 separated by space):");
}

void loop() {
  if (Serial.available()) {
    int X = Serial.parseInt();
    int Y = Serial.parseInt();
    int Z = Serial.parseInt();
    while (Serial.available()) Serial.read(); // clear buffer

    int F = logicFunction(X, Y, Z);
    Serial.print("Inputs: X="); Serial.print(X);
    Serial.print(" Y="); Serial.print(Y);
    Serial.print(" Z="); Serial.print(Z);
    Serial.print("  => F="); Serial.println(F);

    // Send output to 7447 as BCD
    if (F == 1)
      setBCD(1);  // display “1”
    else
      setBCD(0);  // display “0”
  }
}

// Function to compute logic gate output
int logicFunction(int X, int Y, int Z) {
  return ((!X && !Y) || (Y && Z));
}

// Function to set BCD pins for 7447
void setBCD(int num) {
  digitalWrite(A_PIN, num & 0x01);         // Bit0
  digitalWrite(B_PIN, (num >> 1) & 0x01);  // Bit1
  digitalWrite(C_PIN, (num >> 2) & 0x01);  // Bit2
  digitalWrite(D_PIN, (num >> 3) & 0x01);  // Bit3
}
