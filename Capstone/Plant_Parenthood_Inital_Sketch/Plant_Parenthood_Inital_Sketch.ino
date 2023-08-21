// Plant Parenthood Initial Code

//Import Necesssary Libraries
#include <AFMotor.h>
#include <Servo.h>

// Defining Motor & Sensor Pins
#define senPin A0
#define s1Pin 9
#define s2Pin 10

// Creating Motor Objects
AF_DCMotor gear1(1);
AF_DCMotor gear2(2);
AF_DCMotor pump(3);
Servo rServo;
Servo zServo;

// Important Motor Constants
const int rServoDelay = 1500;   //ADJUST
const int rServoSpd = 10;       //ADJUST
const int zServoDelay = 2000;   //ADJUST
const int zServoSpd = 10;       //ADJUST
const int gearSpd = 50;        //ADJUST
const int pumpSpeed = 250;      //ADJUST
const int pumpDelayMin = 2000;  //ADJUST
const int pumpDelayMax = 10000;  //ADJUST

// Important Sensor Constants
const int sensorDelay = 2000;   //ADJUST
const int h2oMin = 0;          //ADJUST
const int h2oMax = 100;         //ADJUST

void setup() {
  //Initiate Sensor Pin Function
  pinMode(senPin, INPUT);

  //Initialize Motors
  gear1.setSpeed(0);
  gear1.run(RELEASE);
  gear2.setSpeed(0);
  gear2.run(RELEASE);
  pump.setSpeed(0);
  pump.setSpeed(RELEASE);
  rServo.attach(s1Pin);
  rServo.write(90);
  zServo.attach(s2Pin);
  zServo.write(90);
  Serial.begin(9600);

  //Wait to start
  delay(10000);

  //Pump to initialize water
  water(1020);
  delay(5000);
}

void loop() {
  // Move Cart to New Position
  motion(1500);     //ADJUST
  delay(500);

  // Insert Probe and Water as Necessary
  sense();
  delay(500);
  
  // Radially Extend Probe and Repeat
  extend();

  //Wait to Change Locations
  delay(4000);    //ADJUST
}

void extend(){
  // Move Servo to Extend Probe
  rServo.write(90 - rServoSpd);    //ADJUST DIRECTION
  delay(rServoDelay);
  rServo.write(90);

  // Perform Probing and Watering
  delay(500);
  sense();
  delay(500);

  // Move Servo to Retract Probe
  rServo.write(90 + rServoSpd);    //ADJUST DIRECTION
  delay(rServoDelay);
  rServo.write(90); 
}

void motion(int t){
  // Accelerate Cart to Top Speed
  gear1.run(BACKWARD);
  gear2.run(BACKWARD);
  for(int i = 0; i <= gearSpd; i++){
    gear1.setSpeed(i);
    gear2.setSpeed(i); 
    delay(5);   
  }

  // Run at Speed for Set Time
  delay(t);
  
  // Decelerate Cart to Stop
  for(int i = gearSpd; i >= 0; i--){
    gear1.setSpeed(i);
    gear2.setSpeed(i); 
    delay(5);   
  }

  // Remove Any Current to Motors
  gear1.run(RELEASE);
  gear2.run(RELEASE);
}

void sense(){
  // Move Servo to Insert Probe
  zServo.write(90 + zServoSpd);    //ADJUST DIRECTION
  delay(zServoDelay);
  zServo.write(90);

  // Wait to Take Moisture Reading
  delay(sensorDelay);
  int h2o = 0;
  h2o = analogRead(senPin);
  Serial.println(h2o);
  // Move Servo to Retract Probe
  zServo.write(90 - zServoSpd);     //ADJUST DIRECTION
  delay(zServoDelay);
  zServo.write(90);

  // Send Reading to Water Function
  water(h2o);
}

void water(int h2o){
  // Map Analog Reading to Watering Percentage
  int p = map(h2o, 0, 1020, 0, h2oMax);

  // Check if Watering is Necessary
  if(p >= h2oMin){
    // Map Percentage to Time
    int t = map(p, 20, 100, pumpDelayMin, pumpDelayMax);

    // Turn on Pump Only For Specified Time
    pump.setSpeed(pumpSpeed);
    pump.run(BACKWARD);
    delay(t);
    pump.run(RELEASE);
  }
}
