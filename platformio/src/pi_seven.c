// XOR Display on Seven-Segment (without 7447)

// Inputs
const int Xpin = 2; // Input X
const int Ypin = 3; // Input Y

// Seven-segment pins (a-g)
const int A = 4;
const int B = 5;
const int C = 6;
const int D = 7;
const int E = 8;
const int F = 9;
const int G = 10;

void setup() {
  // Inputs with pull-ups
  pinMode(Xpin, INPUT_PULLUP);
  pinMode(Ypin, INPUT_PULLUP);

  // Set all segment pins as output
  pinMode(A, OUTPUT);
  pinMode(B, OUTPUT);
  pinMode(C, OUTPUT);
  pinMode(D, OUTPUT);
  pinMode(E, OUTPUT);
  pinMode(F, OUTPUT);
  pinMode(G, OUTPUT);

  Serial.begin(9600);
}

// Function to display 0 or 1 on seven-segment (common anode)
void displayNumber(int num) {
  if (num == 0) {
    digitalWrite(A, LOW);
    digitalWrite(B, LOW);
    digitalWrite(C, LOW);
    digitalWrite(D, LOW);
    digitalWrite(E, LOW);
    digitalWrite(F, LOW);
    digitalWrite(G, HIGH);
  } else if (num == 1) {
    digitalWrite(A, HIGH);
    digitalWrite(B, LOW);
    digitalWrite(C, LOW);
    digitalWrite(D, HIGH);
    digitalWrite(E, HIGH);
    digitalWrite(F, HIGH);
    digitalWrite(G, HIGH);
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
