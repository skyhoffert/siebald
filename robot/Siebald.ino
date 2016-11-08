// Skylar Hoffert
// January 22, 2016
// S1EBALD is a robot with a personality!
// Significant Iteration 1 of Emotionally Built Autonomous Learning Droids

#include <Servo.h>
#include "pitches.h"

// notes in the melody:
int melody[] = {
NOTE_C4, NOTE_G3,NOTE_G3, NOTE_A3, NOTE_G3,0, NOTE_B3, NOTE_C4};
// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {8,8,8,8,8,8,8,8};

// pins
int motorRight1 = 1, motorRight2 = 2;
int motorLeft1 = 7, motorLeft2 = 8;
int headYaw = 9, headPitch = 10;
int armLeft = 3, armRight = 5;
int trig = 12, echo = 11;
int speaker = 6;
// variables
double duration = 0, distance = 0;
// Servo stuff
// *********ALL NEED TO BE MODIFIED******** 
Servo hyaw;
int hyawLeft = 35, hyawRight = 145;
Servo hpitch;
int hpitchDown = 135, hpitchUp = 30;
Servo armL;
int armLDown = 70, armLUp = 160;
Servo armR;
int armRDown = 110, armRUp = 20;
// US sensor distance
const int MOVE_RANGE = 20;

// for searching
bool isRight = true, isMiddle = true;
// timer stuff - every second for rate
unsigned long timeLast = 0, timeNow = 0;
unsigned const int TIME_RATE = 400;

// runs once at beginning
void setup() {
  // set up Servo and pins
  hyaw.attach(headYaw);
  hpitch.attach(headPitch);
  armL.attach(armLeft);
  armR.attach(armRight);
  // center all servos
  hyaw.write(90);
  hpitch.write(90);
  armL.write(90);
  armR.write(90);
  
  // set up the motors
  pinMode(motorRight1, OUTPUT);
  pinMode(motorRight2, OUTPUT);
  pinMode(motorLeft1, OUTPUT);
  pinMode(motorLeft2, OUTPUT);
  pinMode(speaker, OUTPUT);
  
  // stop all motors just because
  digitalWrite(motorRight1, LOW);
  digitalWrite(motorRight2, LOW);
  digitalWrite(motorLeft1, LOW);
  digitalWrite(motorLeft2, LOW);
  
  // set up sensors
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  //clear the signal on the pin
  digitalWrite(trig, LOW);
  
  // pause
  delay(1000);
  
  // play start up melody
  // iterate over the notes of the melody:
  for (int thisNote = 0; thisNote < 8; thisNote++) {
    // to calculate the note duration, take one second
    // divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000/noteDurations[thisNote];
    tone(speaker, melody[thisNote],noteDuration);
    
    // to distinguish the notes, set a minimum time between them
    int pauseBetweenNotes = noteDuration * .5;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(speaker);
  }
  
  // set timer stuff
  timeLast = millis();
  timeNow = millis();
}

// main code functions
void loop() {
  // delay the loop
  delayMicroseconds(250);
  
  // read distance
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  
  duration = pulseIn(echo, HIGH);
  // distance in centimeters
  distance = duration / 58;
  
  // brief delay
  delayMicroseconds(100);
  
  //if there is room
  if (distance > MOVE_RANGE){
    forward();
  } else {
    tone(speaker, NOTE_C4, 1000/8);
    //decide what to do depending on current stuff
    if (isMiddle){
      //basically if it is turning left
      if (isRight){
        rotateRight();
      } else {
        rotateLeft();
      }
    } else {
      //if its facing right
      if (isRight){
        rotateLeft();
      } else {
        rotateRight();
      }
    }
  }
  delayMicroseconds(100); 
  
  //decide where eyes should look
  //get time stuff
  timeNow = millis();
  if (distance > MOVE_RANGE){
      if (timeNow - timeLast >= TIME_RATE){
        //if eyes are looking straight
        if (isMiddle){
          //last position was right
          if (isRight){
            //turn the eyes left
            isRight = false;
            hyaw.write(hyawLeft);
          //it was last looking left
          } else {
            //turn eyes right
            isRight = true;
            hyaw.write(hyawRight);
          }
          //this will always go false
          isMiddle = false;
        //eyes are looking elsewhere
        } else {
          //look middle
          isMiddle = true;
          hyaw.write(90);
        }
    }
    //reset timer
    timeLast = millis();
  }
}

void forward(){
    //make motors go forward
    digitalWrite(motorRight1, HIGH);
    digitalWrite(motorRight2, LOW);
    digitalWrite(motorLeft1, HIGH);
    digitalWrite(motorLeft2, LOW);
}

void rotateRight(){
    //make it spin
    digitalWrite(motorRight1, HIGH);
    digitalWrite(motorRight2, LOW);
    digitalWrite(motorLeft1, LOW);
    digitalWrite(motorLeft2, HIGH);
}

void rotateLeft(){
    //make it spin
    digitalWrite(motorRight1, LOW);
    digitalWrite(motorRight2, HIGH);
    digitalWrite(motorLeft1, HIGH);
    digitalWrite(motorLeft2, LOW);
}
