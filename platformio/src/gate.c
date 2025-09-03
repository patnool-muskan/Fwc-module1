#include <Arduino.h>

const int Xpin = 2;   // Input X
const int Ypin = 3;   // Input Y
const int Zpin = 13;  // Output LED

void setup() {
  pinMode(Xpin, INPUT_PULLUP); // Internal pull-up enabled
  pinMode(Ypin, INPUT_PULLUP);
  pinMode(Zpin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // Read inputs (invert because of pull-up: LOW=0, HIGH=1)
  int X = !digitalRead(Xpin);
  int Y = !digitalRead(Ypin);

  //STEP1
   int xbar=!X;
   int ybar=!Y;
   //step2
   int nand1= (xbar||Y);
   int nand2= (X||ybar);
   //step3
   int Z = ((X&&ybar)||(xbar&&Y));
  // Drive LED
  digitalWrite(Zpin, Z);

  // Print truth table row
  Serial.print("X=");
  Serial.print(X);
  Serial.print("  Y=");
  Serial.print(Y);
  Serial.print("  Z=");
  Serial.println(Z);

  delay(500);
}
