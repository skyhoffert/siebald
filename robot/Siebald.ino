// Siebald
// Description:  This program is for Siebald, the robot!
// Modified:  2016_1108
// Modified By: Sky Hoffert

#include <Servo.h>

// constants
// sensors
#define sensor_us_trig 2
#define sensor_us_echo 4

// actuators
#define servo_sensor_us 3

// motors
#define motor_L_1 5
#define motor_L_2 6
#define motor_R_1 9
#define motor_R_2 10

// speeds
// servo position
#define servo_sensor_us_center 90
#define servo_sensor_us_left 50
#define servo_sensor_us_right 140

// motor speeds
#define motor_L_full 255
#define motor_L_half 100
#define motor_L_slow 50
#define motor_R_full 255
#define motor_R_half 100
#define motor_R_slow 75
#define motor_stop 0

Servo servo_us;

void setup(){
  // set pin modes
  // ultrasonic sensor
  pinMode(sensor_us_trig, OUTPUT);
  pinMode(sensor_us_echo, INPUT);

  // servo
  servo_us.attach(3);

  // motors
  pinMode(motor_L_1, OUTPUT);
  pinMode(motor_L_2, OUTPUT);
  pinMode(motor_R_1, OUTPUT);
  pinMode(motor_R_2, OUTPUT);

  // set the motors with initial values
  // digital pins
  digitalWrite(sensor_us_trig, LOW);

  // other
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin (9600);
  
  // analog pins
  analogWrite(motor_L_1, motor_stop);
  analogWrite(motor_L_2, motor_stop);
  analogWrite(motor_R_1, motor_stop);
  analogWrite(motor_R_2, motor_stop);

  // servos
  servo_us.write(90);
}

void loop(){
  // do stuff

  // sample code for the US sensor
   long duration, distance;
  digitalWrite(sensor_us_trig, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(sensor_us_trig, HIGH);
//  delayMicroseconds(1000); - Removed this line
  delayMicroseconds(10); // Added this line
  digitalWrite(sensor_us_trig, LOW);
  duration = pulseIn(sensor_us_echo, HIGH);
  distance = (duration/2) / 29.1;
  if (distance < 10) {  // This is where the LED On/Off happens
    digitalWrite(LED_BUILTIN,HIGH); // When the Red condition is met, the Green LED should turn off
}
  else {
    digitalWrite(LED_BUILTIN,LOW);
  }
  if (distance >= 200 || distance <= 0){
    Serial.println("Out of range");

    // testing
    analogWrite(motor_R_1, 250);
    analogWrite(motor_R_2, motor_stop);
  }
  else {
    Serial.print(distance);
    Serial.println(" cm");

    // testing
    analogWrite(motor_R_1, motor_stop);
    analogWrite(motor_R_2, motor_stop);
  }
  delay(100);
}

