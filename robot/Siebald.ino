// Siebald
// Description:	This program is for Siebald, the robot!
// Modified:	2016_1108
// Modified By:	Sky Hoffert

// constants
// sensors
#define sensor_us_trig 7
#define sensor_us_echo 8

// actuators
#define servo_sensor_us 10

// motors
#define motor_L_1 3
#define motor_L_2 5
#define motor_R_1 6
#define motor_R_2 7

// speeds
// servo position
#define servo_sensor_us_center 128
#define servo_sensor_us_left 100
#define servo_sensor_us_right 156

// motor speeds
#define motor_L_full 200
#define motor_L_half 100
#define motor_L_slow 50
#define motor_R_full 200
#define motor_R_half 100
#define motor_R_slow 50
#define motor_stop 0

void setup(){
	pinMode(sensor_us_trig, OUTPUT);
	pinMode(sensor_us_echo, INPUT);

	pinMode(servo_sensor_us, OUTPUT);

	pinMode(motor_L_1, OUTPUT);
	pinMode(motor_L_2, OUTPUT);
	pinMode(motor_R_1, OUTPUT);
	pinMode(motor_R_2, OUTPUT);

	// set the motors with initial values
	// digital pins
	digitalWrite(sensor_us_trig, LOW);

	// analog pins
	analogWrite(servo_sensor_us, servo_sensor_us_center);
	analogWrite(motor_L_1, motor_stop);
	analogWrite(motor_L_2, motor_stop);
	analogWrite(motor_R_1, motor_stop);
	analogWrite(motor_R_2, motor_stop);
}

void loop(){
}
