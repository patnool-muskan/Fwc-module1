// XOR Display on Seven-Segment (without 7447)

// Inputs
const int Xpin = 2; // Input X
const int Ypin = 3; // Input Y

// Seven-segment pins (a-g)
const int segA = 4;
const int segB = 5;
const int segC = 6;
const int segD = 7;
const int segE = 8;
const int segF = 9;
const int segG = 10;

void setup() {
  // Inputs with pull-ups
  pinMode(Xpin, INPUT_PULLUP);
  pinMode(Ypin, INPUT_PULLUP);

  // Set all segment pins as output
  pinMode(segA, OUTPUT);
  pinMode(segB, OUTPUT);
  pinMode(segC, OUTPUT);
  pinMode(segD, OUTPUT);
  pinMode(segE, OUTPUT);
  pinMode(segF, OUTPUT);
  pinMode(segG, OUTPUT);

  Serial.begin(9600);
}

// Function to display 0 or 1 on seven-segment (common anode)
void displayNumber(int num) {
  if (num == 0) {
    digitalWrite(segA, LOW);
    digitalWrite(segB, LOW);
    digitalWrite(segC, LOW);
    digitalWrite(segD, LOW);
    digitalWrite(segE, LOW);
    digitalWrite(segF, LOW);
    digitalWrite(segG, HIGH);
  } else if (num == 1) {
    digitalWrite(segA, HIGH);
    digitalWrite(segB, LOW);
    digitalWrite(segC, LOW);
    digitalWrite(segD, HIGH);
    digitalWrite(segE, HIGH);
    digitalWrite(segF, HIGH);
    digitalWrite(segG, HIGH);
  }
}

void loop() {
  // Read inputs
  int X = !digitalRead(Xpin); // invert because of pull-up
  int Y = !digitalRead(Ypin);

  // XOR logic
  int Z = (X && !Y) || (!X && Y);

  // Display XOR output
  displayNumber(Z);

  // Debug
  Serial.print("X=");
  Serial.print(X);
  Serial.print("  Y=");
  Serial.print(Y);
  Serial.print("  XOR=");
  Serial.println(Z);

  delay(500);
}
