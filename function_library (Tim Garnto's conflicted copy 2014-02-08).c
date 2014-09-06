#pragma systemFile

#include "rdpartyrobotcdr-3.3.1/drivers/hitechnic-sensormux.h"     //Drivers for IR Beacon
#include "rdpartyrobotcdr-3.3.1/drivers/hitechnic-irseeker-v2.h"

//there was a declaration of speed as 1200 if that's important.
#define TURN_LEFT 			true           //defines TURN_LEFT as true in a boolean
#define TURN_RIGHT 			false          //defines TURN_RIGHT as false in a boolean
#define MOVE_SERVO1 		1
//#define MOVE_SERVO2 		2
#define MOVE_SERVRO_BOTH 	3
#define SPEED 				50
#define SPEED2 				55
#define CONVO_RATE_DIST 	31.9
#define CONVO_RATE_DEG 		.56
#define BEGINNING_POINT 	45
#define SLOW_MOTORS			20

// Give Joystick Buttons Good Names
#define	JOY_BUTTON_X		01
#define	JOY_BUTTON_A		02
#define	JOY_BUTTON_B		03
#define	JOY_BUTTON_Y		04
#define	JOY_BUTTON_LB		05
#define JOY_BUTTON_LT		07
#define	JOY_BUTTON_RB		06
#define JOY_BUTTON_RT		08

// Define the block servo values
#define BLOCK_INIT				255		// Block Servo Setting for Start
#define BLOCK_FLING				80		// Block Servo Setting for Block Fling
#define BLOCK_REST				255		// Block Servo Setting when not in use
#define MAX_MOTOR_CLICKS 7000
#define FORWARD true
#define BACK false



void stops() {                   //Stops motors from any movement
	motor[motor_right] = 0;
	motor[motor_left] = 0;
}
void shincapit(int time, int motorSpeed, int waitTime, bool dir) { //Moves the Flag and Flag Adjust
		if(dir == FORWARD){
			servo[servoFlagAdjust] = 0; //Moves the servo
		}
		else{
			servo[servoFlagAdjust] = 256; //moves the servo in
		}
		wait1Msec(2000);
		servo[servoFlagAdjust] = 127; //Stops the continous servo
		motor[motorFlag] = motorSpeed;
		wait1Msec(time);
		stops();
}
void move(int speed, int time) { //Makes robot move up or down in the specified direction
	motor[motor_right] = speed;
	motor[motor_left] = speed;
	wait1Msec (time);
	stops ();
}

void liftMove(int speed, int time){ //moves the lift automatically and stops it.
	motor[motorLift] = speed;
	wait1Msec(time);
	motor[motorLift] = 0;
}

/*void liftEncoded(int speed, int time, int distance){ //lifts the arm a certain number of clicks
	nMotorEncoder[motorLift] = 0  WIP  */



void turn(int speed, int time, bool direction) { //Makes robot turn in the specified direction
	if (direction == TURN_RIGHT) { //Turns left
		motor [motor_left] = speed;
		motor [motor_right] = -speed;
		wait1Msec (time);
	}
	else {                       //Turns Right
		motor [motor_left] = -speed;
		motor [motor_right] = speed;
		wait1Msec (time);
	}
	stops();
}

int convertDistClick(int dist){
	int clicks = dist * CONVO_RATE_DIST;
	return clicks;
}

int getIRReading(tSensors ir_seeker)
{
  wait1Msec(1);                              // Wait 1 ms
  int ir = HTIRS2readACDir(ir_seeker);      // IR receiver -> ir variable
  wait1Msec(1);                              // Down time before recheck
  return ir;
}

void tossBlock() {
	servoChangeRate[servoBlock] = 0;
	servo[servoBlock] = BLOCK_FLING;
	wait1Msec(1000);
	servo[servoBlock] = BLOCK_REST;
	wait1Msec(1000);
}

void drive2Encoder(int iEncoder, int power, bool direction)
{
	if(direction == FORWARD){
		while(abs(nMotorEncoder[motor_right]) < iEncoder && abs(nMotorEncoder[motor_left]) < iEncoder ){
			motor [motor_left] = power;
			motor [motor_right] = power;
			wait1Msec(50);
		}
	}
	else{
		while(abs(nMotorEncoder[motor_right]) > iEncoder && abs(nMotorEncoder[motor_left]) > iEncoder ){
			motor [motor_left] = -power;
			motor [motor_right] = -power;
			wait1Msec(50);
		}
	}
	stops();
	wait1Msec(500);
}

void locateIR (tSensors ir_seeker)
{ //Locates IR Beacon
//3400 6800
//2100 5500

	nMotorEncoder[motor_right] = 0;
	nMotorEncoder[motor_left] = 0;

	drive2Encoder(2100, SLOW_MOTORS, FORWARD);
	if( getIRReading(ir_seeker) < 7 )
		drive2Encoder(3400, SLOW_MOTORS, FORWARD);
		if( getIRReading(ir_seeker) < 7 )
			drive2Encoder(5500, SLOW_MOTORS, FORWARD);
			if( getIRReading(ir_seeker) < 7 )
				drive2Encoder(6800, SLOW_MOTORS, FORWARD);
}

void forward(int power){
	motor[motor_right] = power;
	motor[motor_left] = power;
}

void dropAutoBucket(int time){
	servo[servoBucket] = 180;
	wait1Msec(time);
	servo[servoBucket] = 0;
}

void moveDist(int dist, int waitTime, int speed){
	int clicks = convertDistClick(dist);
	int power = 0;
	int targetPower = speed;
	int beginning = 200;
	int shortDist = 400;
	int slowMotion = 4;
	nMotorEncoder[motor_right] = 0;
	nMotorEncoder[motor_left] = 0;
	while(nMotorEncoder[motor_right] < clicks){
		if(abs(clicks) > shortDist){
			if(nMotorEncoder[motor_right] < beginning && power < targetPower){
				power += 2;
			}
			if(clicks - nMotorEncoder[motor_right] < beginning && power > slowMotion){
				power -= 2;
			}
		}
		if(clicks > 0 && clicks <= shortDist){
			power = slowMotion;
		}
		if(abs(clicks) > shortDist && clicks < 0){
			if(abs(nMotorEncoder[motor_right]) < abs(beginning) && abs(power) < abs(targetPower)){
				power -= 2;
			}
			if(abs(clicks - nMotorEncoder[motor_right]) < abs(beginning) && power < slowMotion){
				power += 2;
			}
		}
		if(clicks < 0 && abs(clicks) < abs(shortDist)){
			power = -slowMotion;
		}
		motor[motor_right] = power;
		motor[motor_left] = power;
	}
	stops();
	wait1Msec(waitTime);
}

int convertDegDist(int degrees){
	int distance = degrees * CONVO_RATE_DEG;
	return distance;
}

void turnDeg(int deg, bool direction, int waitTime, int speed){
	int distance = convertDegDist(deg);
	int clicks = convertDistClick(distance);
	int power = 0;
	int minimumPower = 40;
	int targetPower = speed;
	nMotorEncoder[motor_right] = 0;
	nMotorEncoder[motor_left] = 0;
	if(direction == TURN_RIGHT){
		while(abs(nMotorEncoder[motor_left]) < abs(clicks) ){//&& abs(nMotorEncoder[motor_right]) < abs(clicks)){
			if( abs(nMotorEncoder[motor_left]) < clicks / 2 && power < targetPower ){
				power += 1;
			}
			if( abs(nMotorEncoder[motor_left]) >= clicks / 1.5 && power > minimumPower ){
				power -= 1;
			}
			motor [motor_right] = -power;
			motor [motor_left] = power;
		}
	}
	else{
		while(abs(nMotorEncoder[motor_right]) < abs(clicks) ){//&& abs(nMotorEncoder[motor_right]) < abs(clicks)){
			if( abs(nMotorEncoder[motor_right]) < clicks / 2 && abs(power) < targetPower ){
				power += 1;
			}
			if( abs(nMotorEncoder[motor_right]) > clicks / 2 && abs(power) > minimumPower ){
				power -= 1;
			}
			motor [motor_right] = power;
			motor [motor_left] = -power;
		}
	}
	stops();
	wait1Msec(waitTime);
}

#ifdef IR_SENSOR1
void locateIR () { //Locates IR Beacon
	int slowMovement = 25;
	while(HTIRS2readACDir(IR_SENSOR1) != 4 && HTIRS2readACDir(IR_SENSOR1) != 6){ //Moves until IR Sensor gets inbetween IR fields 4 and 6
		motor [motor_left] = slowMovement;
		motor [motor_right] = slowMovement;
	}
	stops(); //Stops movement
}
#endif

void dropBucketAndUndo(){
	servo[servoBucket] = BEGINNING_POINT + 90;
	wait1Msec(200);
	servo[servoBucket] = BEGINNING_POINT;
}

#ifdef touch1
// Only include this code if the touch sensor is installed on the robot
void liftToBottom(){ //moves the lift to the bottom until the touch sensor is hit
	int goesAround = 0;
	while(SensorValue[touch1] == 0 && goesAround < 30000){
		goesAround += 1;
		motor[motorLift] = -50;
	}
}
#endif

void initializeRobot(){
//	servo[bucket] = BEGINNING_POINT;  //working point
//	liftMove(50, 1000);
//	liftToBottom(); // takes the lift to the touch sensor
}
const int ENCODER_RESOLUTION=1440;
const int WHEEL_SIZE=4; //Diameter of Wheel
const int RATIO=1/1;            //wheel/gear
int inchesToEncoder(int inches)
{
        int ticks;
        ticks = ((inches/(PI*WHEEL_SIZE))*ENCODER_RESOLUTION)/RATIO;
        return ticks;
}
