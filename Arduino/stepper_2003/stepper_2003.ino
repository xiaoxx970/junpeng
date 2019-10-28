
/*
  Stepper Motor Control - one revolution

  This program drives a unipolar or bipolar stepper motor.
  The motor is attached to digital pins 8 - 11 of the Arduino.

  The motor should revolve one revolution in one direction, then
  one revolution in the other direction.


  Created 11 Mar. 2007
  Modified 30 Nov. 2009
  by Tom Igoe

*/
#include <MPU6050_tockn.h>
#include <Wire.h>
#include <Stepper.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

const int stepsPerRevolution = 2038;  // change this to fit the number of steps per revolution
// for your motor

// initialize the stepper library on pins 8 through 11:
Stepper myStepper(stepsPerRevolution, 8, 10, 9, 11);
// initialize mpu
MPU6050 mpu6050(Wire);

// initilaze oled 12864
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET 4
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2

#define LOGO16_GLCD_HEIGHT 16
#define LOGO16_GLCD_WIDTH  16

int AngleY,motorSpeed,y;

void setup() {
  // set the speed at 60 rpm:
  myStepper.setSpeed(0);
  // initialize the serial port:
  Serial.begin(9600);
  Wire.begin();
  mpu6050.begin();
  mpu6050.calcGyroOffsets(true);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
}

void loop() {
  mpu6050.update();
  AngleY = mpu6050.getAngleY();
  if(AngleY>0){
    motorSpeed = map(AngleY, 0, 90, 0, 100);
    myStepper.setSpeed( Speed);
    myStepper.step(stepsPerRevolution / 100);
    Serial.print("AngleY>0");
  }
  else if (AngleY<0){
    motorSpeed = map(AngleY, 0, -90, 0, 100);
    myStepper.setSpeed(motorSpeed);
    myStepper.step(-stepsPerRevolution / 100);
    Serial.print("AngleY<0");
  }
  else{
    motorSpeed = 0;
    myStepper.setSpeed(motorSpeed);
    myStepper.step(stepsPerRevolution);
    Serial.print("AngleY=0");
  }
  Serial.print("  AngleY:");Serial.print(AngleY);
  Serial.print("  motorSpeed:");Serial.println(motorSpeed);

//  display.clearDisplay();   // clears the screen and buffer
//  display.drawLine(0, 32, 128, 32, WHITE);
//  display.drawLine(64, 0, 64, 64, WHITE);
//  y = map(AngleY, -90, 90, 0, 64);
//  display.fillRect(64 - 3, y - 3, 6, 6, WHITE);
//  display.drawRect(64 - 5, y - 5, 10, 10, WHITE);
//
//  display.display();

}
