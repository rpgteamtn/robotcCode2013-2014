#pragma config(Hubs,  S1, HTMotor,  HTMotor,  none,     none)
#pragma config(Hubs,  S4, HTServo,  HTMotor,  none,     none)
#pragma config(Sensor, S2,     touch,          sensorTouch)
#pragma config(Sensor, S3,     IRSEEKER,       sensorI2CCustom)
#pragma config(Motor,  motorA,           ,             tmotorNXT, openLoop, encoder)
#pragma config(Motor,  motorB,           ,             tmotorNXT, openLoop, encoder)
#pragma config(Motor,  motorC,           ,             tmotorNXT, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C1_1,     motor_left,    tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C1_2,     motor_right,   tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_1,     motorLift,     tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     motorFlag,     tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S4_C2_1,     motorFly,      tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S4_C2_2,     motorI,        tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S4_C1_1,    servoBucket,          tServoStandard)
#pragma config(Servo,  srvo_S4_C1_2,    servoBlock,           tServoStandard)
#pragma config(Servo,  srvo_S4_C1_3,    servoFlagAdjust,      tServoStandard)
#pragma config(Servo,  srvo_S4_C1_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S4_C1_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S4_C1_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

// Robotics and Programming Guild Code

#include "function_library.c"

task main()
{

	initializeRobot(); //sets all motors, extensions, and appliances to initial set.
	moveDist(24.13, 100, 60); //moves forward 24.13 cm (9.5 inches)
	shincapit(500, 50, 210, FORWARD);//spins shincapper for specified amount of time at specified angle (FORWARD is a test)
	turnDeg(90, TURN_LEFT, 100, 80);//turns left
	moveDist(30.48, 100, 60); //moves forward 30.48 cm (1 ft or 12 inches)
	tossBlock(); //flipper
	turnDeg(90, TURN_RIGHT, 100, 80);//turns right
	moveDist(24.13, 100, 60); //moves forward 24.13 cm (9.5 inches)
	liftMove(55, 2000); //lifts scoop for specified amount of time
	turnDeg(90, TURN_RIGHT, 100, 80);//turns right
	moveDist(60.96, 100, 60); //moves forward 60.96 cm (2 ft or 24 inches)
	liftMove(-55, 2000); //lifts scoop for specified amount of time (same as above)
	turnDeg(90, TURN_RIGHT, 100, 80);//turns right
	moveDist(24.13, 100, 60); //moves forward 24.13 cm (9.5 inches)
	shincapit(500, 50, 210, BACK); //spins shincapper for specified amount of time at specified angle (BACK is a test)
	moveDist(24.13, 100, 60); //moves forward 24.13 cm (9.5 inches)
	turnDeg(90, TURN_RIGHT, 100, 80); //turns right
	moveDist(30.48, 100, 60); //moves forward 30.48 cm (1 ft or 12 inches)

}