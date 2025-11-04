// ShieldBot SumBot  - Written by Yousef 2024.10.10

#include <Servo.h> //include servo library
// Declare left and right servos
Servo servoLeft;
Servo servoRight;

// declare constants for QTI sensor pins

const int Right_QTI_PIN = 2;
const int Left_QTI_PIN = 3;

// declare constants for IR sensor pins
const int Right_IR_LED_PIN = 4;
const int Right_IR_REC_PIN = 5;
const int Left_IR_LED_PIN = 9;
const int Left_IR_REC_PIN = 10;


// declare constants for UltraSonic Sensor
const int TRIGGER_PIN = 8;
const int ECHO_PIN = 7;

float duration;
float distance;

bool Last_Detection_Right = false; 
bool Last_Detection_Left = true; //start with one as true so robot can turn in the left direction while scanning for opponents using IR


void setup() {
  Serial.begin(9600); // start serial communication

  randomSeed(analogRead(0));

  //attach servos
  servoLeft.attach(12);
  servoRight.attach(13);

  // set the QTI pins as an input:
  pinMode(Left_QTI_PIN, INPUT);
  pinMode(Right_QTI_PIN, INPUT);

  //set the IR sensor pins as inout/output
  pinMode(Right_IR_LED_PIN, OUTPUT);
  pinMode(Right_IR_REC_PIN, INPUT);
  pinMode(Left_IR_LED_PIN, OUTPUT);
  pinMode(Left_IR_REC_PIN, INPUT);


  // set the Ultrasonic sensor pins as input/output
  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

}

void loop() {
  //read QTI values
  bool Left_QTI_sensorValue = digitalRead(Left_QTI_PIN);
  bool Right_QTI_sensorValue = digitalRead(Right_QTI_PIN);

   /************ Start IR Detection Section ***********/
  tone(Left_IR_LED_PIN, 38000, 8);
  delay(1);
  int Left_ir = digitalRead(Left_IR_REC_PIN);
  delay(1);
  tone(Right_IR_LED_PIN, 38000, 8);
  delay(1);
  int Right_ir = digitalRead(Right_IR_REC_PIN);
  delay(1);
  /************ End IR Detection Section ***********/


    /************ Start US Measurement Section ***********/
  digitalWrite(TRIGGER_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN, LOW);
  duration = pulseIn(ECHO_PIN, HIGH);
  distance = duration * 0.034 / 2;
  /************** End US Measurement Section ***********/


  //QTI MASTER CONTROL
  if (Left_QTI_sensorValue == 1 && Right_QTI_sensorValue == 1)  { //if both QTI detects black, move forward
    servoLeft.writeMicroseconds(1470); //left motor forward
    servoRight.writeMicroseconds(1530); //right motor forward
    if (Left_ir == 0) { //if left ir sensors detects an object, turn left
      servoLeft.writeMicroseconds(1500);
      servoRight.writeMicroseconds(1565);
      Last_Detection_Right = false; 
      Last_Detection_Left = true; 
    } else if (Right_ir == 0) { //if right ir sensors detects an object, turn right
      servoLeft.writeMicroseconds(1435);
      servoRight.writeMicroseconds(1500);
      Last_Detection_Right = true; 
      Last_Detection_Left = false; 
    }

    //if US sensor detects another robot, go full speed
    if (distance <= 50) {
      servoLeft.writeMicroseconds(1300);
      servoRight.writeMicroseconds(1700);
    }
  } else if (Left_QTI_sensorValue == 0 || Right_QTI_sensorValue == 0 && Last_Detection_Left == true; ) { // if one QTI detect white (boundary) then reverse and turn around
    //reverse
    servoLeft.writeMicroseconds(1600);
    servoRight.writeMicroseconds(1400);
    delay(500);
    //turn around
    servoLeft.writeMicroseconds(1600); //left motor backward
    servoRight.writeMicroseconds(1600); //right motor forward
    delay(550);
  } else if (Left_QTI_sensorValue == 0 || Right_QTI_sensorValue == 0 && Last_Detection_Right == true; ) { // if one QTI detect white (boundary) then reverse and turn around
    //reverse
    servoLeft.writeMicroseconds(1600);
    servoRight.writeMicroseconds(1400);
    delay(500);
    //turn around
    servoLeft.writeMicroseconds(1400); //left motor forward
    servoRight.writeMicroseconds(1300); //right motor backward
    delay(550);
  } 
}