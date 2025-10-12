#include <Arduino.h>

#define LED_a 13
#define LED_b 12
#define LED_c 14
#define LED_d 27
#define LED_e 26
#define LED_f 25
#define LED_g 33

int X = 0, Y = 0, Z = 0;

void displayNumber(int num);
void clearDisplay();

void setup() {
  int segs[] = {LED_a, LED_b, LED_c, LED_d, LED_e, LED_f, LED_g};
  for (int i = 0; i < 7; i++) {
    pinMode(segs[i], OUTPUT);
    digitalWrite(segs[i], LOW);
  }

  Serial.begin(115200);
  Serial.println("Logic Function: F = X'Y' + YZ");
  Serial.println("Enter X Y Z (0 or 1 separated by spaces, e.g. 0 1 1):");
}

void loop() {
  if (Serial.available()) {
    X = Serial.parseInt();
    Y = Serial.parseInt();
    Z = Serial.parseInt();
    while (Serial.available()) Serial.read();

    int F = ((!X && !Y) || (Y && Z));

    Serial.print("X="); Serial.print(X);
    Serial.print("  Y="); Serial.print(Y);
    Serial.print("  Z="); Serial.print(Z);
    Serial.print("  =>  F="); Serial.println(F);

    if (F == 1)
      displayNumber(1);  // Show "1" on 7-seg
    else
      displayNumber(0);  // Show "0" on 7-seg
  }
}

void clearDisplay() {
  int segs[] = {LED_a, LED_b, LED_c, LED_d, LED_e, LED_f, LED_g};
  for (int i = 0; i < 7; i++) digitalWrite(segs[i], LOW);
}

void displayNumber(int num) {
  clearDisplay();
  // Segment order: a,b,c,d,e,f,g
  switch (num) {
    case 0:
      digitalWrite(LED_a, HIGH);
      digitalWrite(LED_b, HIGH);
      digitalWrite(LED_c, HIGH);
      digitalWrite(LED_d, HIGH);
      digitalWrite(LED_e, HIGH);
      digitalWrite(LED_f, HIGH);
      break;
    case 1:
      digitalWrite(LED_b, HIGH);
      digitalWrite(LED_c, HIGH);
      break;
  }
}
