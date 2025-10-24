#include <Arduino.h>
#include <WiFi.h>
#include <esp32PWMUtilities.h>

const char *ssid = "Redmi 12";
const char *password = "12345678";
Motor Motor1;
Motor Motor2;

// Simple settings
int MOTOR_SPEED = 40;
const int TURN_TIME = 300;
const int MOVE_TIME = 100;

// Beacon detection
bool beaconFound = false;
const double BEACON_RSSI = -20.0; // Stop when signal is this strong

void stopMotorsPermanently() {
  Serial.println("*** PERMANENT MOTOR STOP ***");
  
  // Stop motors using the motor library
  Motor1.lockMotor();
  Motor2.lockMotor();
  
  // Also directly control the pins to ensure they stay stopped
  digitalWrite(16, LOW);
  digitalWrite(17, LOW); 
  digitalWrite(18, LOW);
  digitalWrite(19, LOW);
  
  // Stop PWM signals
  ledcDetachPin(14);
  ledcDetachPin(15);
}

void moveForward(int duration) {
  if(beaconFound) return; // Don't move if beacon found
  
  Serial.print("Moving: "); Serial.println(duration);
  Motor1.moveMotor(MOTOR_SPEED);
  Motor2.moveMotor(MOTOR_SPEED);
  delay(duration);
  Motor1.lockMotor();
  Motor2.lockMotor();
}

void turnRight() {
  if(beaconFound) return;
  
  Serial.println("Turn Right");
  Motor1.moveMotor(MOTOR_SPEED);
  Motor2.moveMotor(-MOTOR_SPEED);
  delay(TURN_TIME);
  Motor1.lockMotor();
  Motor2.lockMotor();
}

void turnLeft() {
  if(beaconFound) return;
  
  Serial.println("Turn Left");
  Motor1.moveMotor(-MOTOR_SPEED);
  Motor2.moveMotor(MOTOR_SPEED);
  delay(TURN_TIME);
  Motor1.lockMotor();
  Motor2.lockMotor();
}

double getRSSI() {
  delay(100);
  return WiFi.RSSI();
}

void scanDirections(double &rssiForward, int &bestDir) {
  double rssi[3];
  
  // Forward
  rssi[0] = getRSSI();
  Serial.print("F:"); Serial.print(rssi[0]); Serial.print(" ");
  
  // Right
  turnRight();
  delay(100);
  rssi[1] = getRSSI();
  Serial.print("R:"); Serial.print(rssi[1]); Serial.print(" ");
  
  // Left  
  turnLeft();
  turnLeft();
  delay(100);
  rssi[2] = getRSSI();
  Serial.print("L:"); Serial.println(rssi[2]);
  
  // Back to forward
  turnRight();
  delay(100);
  
  // Find best direction
  bestDir = 0;
  for(int i = 1; i < 3; i++) {
    if(rssi[i] > rssi[bestDir]) {
      bestDir = i;
    }
  }
  
  rssiForward = rssi[0];
}

void setup() { 
  Serial.begin(115200);
  delay(2000);
  Serial.println(" SIMPLE BEACON FINDER ");
  Serial.print("Stop at RSSI: "); Serial.println(BEACON_RSSI);
  
  // Initialize motor pins
  pinMode(16, OUTPUT);
  pinMode(17, OUTPUT);
  pinMode(18, OUTPUT);
  pinMode(19, OUTPUT);
  
  Motor1.attach(14, 16, 17);
  Motor2.attach(15, 18, 19);
  
  // Stop motors initially
  Motor1.lockMotor();
  Motor2.lockMotor();
  
  // Connect to WiFi
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected!");
}

void loop() {
  // IF BEACON ALREADY FOUND - DO NOTHING
  if(beaconFound) {
    Serial.println("*** BEACON FOUND - STAYING STOPPED ***");
    stopMotorsPermanently();
    delay(5000);
    return;
  }
  
  double currentRSSI;
  int bestDirection;
  
  Serial.print("Scan: ");
  scanDirections(currentRSSI, bestDirection);
  
  Serial.print("Best RSSI: "); Serial.println(currentRSSI);
  
  // CHECK FOR BEACON - SIMPLE AND DIRECT
  if(currentRSSI > BEACON_RSSI) {
    Serial.println(" BEACON DETECTED!");
    Serial.println("*** STOPPING ALL MOTORS ***");
    
    beaconFound = true;
    stopMotorsPermanently();
    
    // PERMANENT STOP LOOP
    while(true) {
      Serial.println("*** BEACON FOUND - MISSION COMPLETE ***");
      stopMotorsPermanently(); // Keep stopping motors
      delay(2000);
    }
  }
  
  // If no beacon found, continue searching
  const char* directions[] = {"Forward", "Right", "Left"};
  Serial.print("Moving: "); Serial.println(directions[bestDirection]);
  
  if(bestDirection == 0) {
    moveForward(MOVE_TIME);
  } else if(bestDirection == 1) {
    turnRight();
    moveForward(MOVE_TIME);
  } else if(bestDirection == 2) {
    turnLeft();
    moveForward(MOVE_TIME);
  }
  
  delay(500);
}
