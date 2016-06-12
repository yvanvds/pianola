/*
*  each motor has 3 channels
*  - led color
*  - servo color
*  - servo position
* 
*  Serial: 0xFF id cmd_id cmd_data
*
*/
#include "MeccaBrain.h"

// My ID, only commands for me are processed
#define MY_ID 1
#define CMD_LENGTH 3
#define DEBUG

// variables
bool isCapturing = false;
uint8_t index = 0;
char inData[3]; // ID + cmd ID + value

// MECCANOID PINS //
//Pins to connect Meccanoids' servos, where chain 1 is left arm, chain 2 is head and chain 3 is right arm
//pins can be any digital pins, not necessary PWM
const int chainPin1 = 22;
const int chainPin2 = 23;
const int chainPin3 = 24;

//pins to set speed on motor driver
const int leftSpeedPin = 10;
const int rightSpeedPin = 11;

//pins to set direction on motor driver
const int leftDirPin = 12;
const int rightDirPin = 13;

//Joints mapping:
//Chain 1 - Left Arm. 1.0 is Arm Pitch, 1.1 is Arm Roll, 1.2 is Elbow
//Chain 2 - Head. 2.0 is Head Yaw, 2.1 is Head Roll, 2.2 is LEDs
//Chain 3 - Right Arm. 3.0 is Arm Pitch, 3.1 is Arm Roll 3.2 is Elbow

const byte LEFT_ARM_PITCH=0; 
const byte LEFT_ARM_ROLL=1; 
const byte LEFT_ARM_ELBOW=2;
const byte HEAD_YAW=3; 
const byte HEAD_ROLL=4;
const byte RIGHT_ARM_PITCH=5; 
const byte RIGHT_ARM_ROLL=6; 
const byte RIGHT_ARM_ELBOW=7;

const byte CMD_GO_FORWARD=1;
const byte CMD_GO_BACKWARD=2;
const byte CMD_ROTATE_LEFT=3;
const byte CMD_ROTATE_RIGHT=4;
const byte CMD_HEAD_ROLL=5;
const byte CMD_HEAD_YAW=6;
const byte CMD_LEFT_ARM_ROLL=7;
const byte CMD_RIGHT_ARM_ROLL=8;
const byte CMD_LEFT_ARM_ELBOW=9;
const byte CMD_RIGHT_ARM_ELBOW=10;

MeccaBrain chain1(chainPin1); //each chain allows to plug up to 4 smart modules
MeccaBrain chain2(chainPin2);
MeccaBrain chain3(chainPin3);

//Commands for driving robots' motors
void turnLeft(int speed)
{
  analogWrite(leftSpeedPin, speed);
  analogWrite(rightSpeedPin, 0);
  digitalWrite(leftDirPin, LOW);
  digitalWrite(rightDirPin, HIGH);
}

void turnRight(int speed)
{
  analogWrite(leftSpeedPin, 0);
  analogWrite(rightSpeedPin, speed);
  digitalWrite(leftDirPin, HIGH);
  digitalWrite(rightDirPin, LOW);
}

void rotateLeft(int speed)
{
  analogWrite(leftSpeedPin, speed);
  analogWrite(rightSpeedPin, speed);
  digitalWrite(leftDirPin, LOW);
  digitalWrite(rightDirPin, HIGH);
}

void rotateRight(int speed)
{
  analogWrite(leftSpeedPin, speed);
  analogWrite(rightSpeedPin, speed);
  digitalWrite(leftDirPin, HIGH);
  digitalWrite(rightDirPin, LOW);
}

void goForward(int speed)
{
  analogWrite(leftSpeedPin, speed);
  analogWrite(rightSpeedPin, speed);
  digitalWrite(leftDirPin, HIGH);
  digitalWrite(rightDirPin, HIGH);
}

void goBackward(int speed)
{
  analogWrite(leftSpeedPin, speed);
  analogWrite(rightSpeedPin, speed);
  digitalWrite(leftDirPin, LOW);
  digitalWrite(rightDirPin, LOW);
}

void stay()
{
  analogWrite(leftSpeedPin, 0);
  analogWrite(rightSpeedPin, 0);
}

void parseSerial()
{
  uint8_t id     = inData[0];
  uint8_t cmd    = inData[1];
  uint8_t value  = inData[2];
 
#ifdef DEBUG
  Serial.print("ID: ");
  Serial.print(id);
  Serial.print(" CMD: ");
  Serial.print(cmd);
  Serial.print(" VALUE: ");
  Serial.println(value);
#endif

  if (id == MY_ID)
  {
    switch (cmd)
    {
      case CMD_GO_FORWARD: goForward(value); break;
      case CMD_GO_BACKWARD: goBackward(value); break;
      case CMD_ROTATE_LEFT: rotateLeft(value); break;
      case CMD_ROTATE_RIGHT: rotateRight(value); break;
      case CMD_HEAD_ROLL: setJoint(HEAD_ROLL, value); break;
      case CMD_HEAD_YAW: setJoint(HEAD_YAW, value); break;
      case CMD_LEFT_ARM_ROLL: setJoint(LEFT_ARM_ROLL, value); break;
      case CMD_RIGHT_ARM_ROLL: setJoint(RIGHT_ARM_ROLL, value); break;
      case CMD_LEFT_ARM_ELBOW: setJoint(LEFT_ARM_ELBOW, value); break;
      case CMD_RIGHT_ARM_ELBOW: setJoint(RIGHT_ARM_ELBOW, value); break;
       
      default:
        break;
    }
  }
}

//jointName is LEFT_ARM_ROLL etc
//pos is 0...255
void setJoint(byte jointName, byte pos)
{
  switch(jointName){
    case LEFT_ARM_PITCH:
      chain1.setServoPosition(0, pos);
      chain1.communicate();
      break;
    case LEFT_ARM_ROLL:
      chain1.setServoPosition(1, pos);
      chain1.communicate();
      break;
    case LEFT_ARM_ELBOW:
      chain1.setServoPosition(2, pos);
      chain1.communicate();
      break;
    case HEAD_YAW:
      chain2.setServoPosition(0, pos);
      chain2.communicate();
      break;
    case HEAD_ROLL:
      chain2.setServoPosition(1, pos);
      chain2.communicate();
      break;      
    case RIGHT_ARM_PITCH:
      chain3.setServoPosition(0, pos);
      chain3.communicate();
      break;
    case RIGHT_ARM_ROLL:
      chain3.setServoPosition(1, pos);
      chain3.communicate();
      break;
    case RIGHT_ARM_ELBOW:
      chain3.setServoPosition(2, pos);
      chain3.communicate();
      break;
  }
}

//Set the color of eye LEDS. red, green and blue are from 0 to 7 (0 - no color, 7 - max color). 
//fadetime is from 0 to 7 and means the speed of color change (0 - immediate change, 7 - longest change)
//example: setColor(7,0,0,3) means change color to red with average speed
void setEyesColor(byte red, byte green, byte blue, byte fadetime)
{
  chain2.setLEDColor(red, green, blue, fadetime);
  chain2.communicate();
}

//Servo colors
const byte JOINT_BLACK=0xF0;  
const byte JOINT_RED=0xF1; 
const byte JOINT_GREEN=0xF2; 
const byte JOINT_BROWN=0xF3; 
const byte JOINT_BLUE=0xF4; 
const byte JOINT_VIOLET=0xF5; 
const byte JOINT_SEA=0xF6; 
const byte JOINT_WHITE=0xF7;

//set the servo color
//for example, setJointColor(RIGHT_ARM_ELBOW, JOINT_VIOLET)
void setJointColor(byte jointName, byte color)
{
  switch(jointName){
    case LEFT_ARM_PITCH:
      chain1.setServoColor(0, color);
      chain1.communicate();
      break;
    case LEFT_ARM_ROLL:
      chain1.setServoColor(1, color);
      chain1.communicate();
      break;
    case LEFT_ARM_ELBOW:
      chain1.setServoColor(2, color);
      chain1.communicate();
      break;
    case HEAD_YAW:
      chain2.setServoColor(0, color);
      chain2.communicate();
      break;
    case HEAD_ROLL:
      chain2.setServoColor(1, color);
      chain2.communicate();
      break;      
    case RIGHT_ARM_PITCH:
      chain3.setServoColor(0, color);
      chain3.communicate();
      break;
    case RIGHT_ARM_ROLL:
      chain3.setServoColor(1, color);
      chain3.communicate();
      break;
    case RIGHT_ARM_ELBOW:
      chain3.setServoColor(2, color);
      chain3.communicate();
      break;
  }
}

void setup() {
  pinMode(chainPin1, OUTPUT);
  pinMode(chainPin2, OUTPUT);
  pinMode(chainPin3, OUTPUT);
  pinMode(leftSpeedPin, OUTPUT);
  pinMode(rightSpeedPin, OUTPUT);
  pinMode(leftDirPin, OUTPUT);
  pinMode(rightDirPin, OUTPUT);
  
  Serial.begin(115200);
  Serial.println("done");

  //"Discover" all the modules (make them blue-colored instead of green-colored)
  //for some unknown reason, I have to repeat it from time to time
  for (int i = 0; i < 50; i++)
  {
    chain1.communicate();
    chain2.communicate();
    chain3.communicate();
  }
  //delay to be sure that all modules are ready
  //if some module is "not discovered" than it will remain green and later this module will behave strangely
  delay(2000);
}

void loop() 
{
  while(Serial.available() > 0) 
  {
    char inChar = Serial.read();
    // scan for begin of command character
    // start capturing, we only capture 2 following bytes (id, val)
    if ( (uint8_t)inChar == 0xFF && index == 0) { isCapturing = true; continue; }
    if (isCapturing)
    {
      switch ( (uint8_t)inChar )
      {
        // received start code in middle of message 
        // discard what we've captured so far  
        case 0xFF:
        {
           isCapturing = false;
           index = 0;
        } 
        // received a valid character
        default:
        { 
            inData[index] = inChar; // Store it
            index++; 
            
            // check if we're at end of command
            if (index > CMD_LENGTH-1) {
              isCapturing = false;
              // reset for next command
              index = 0;
              // parse command
              parseSerial();
            }
        }
      }
    }
  } // end serial while
}
