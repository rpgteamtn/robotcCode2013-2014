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

#include "JoystickDriver.c" //brings in controller functions
#include "function_library.c"
bool timeOver = false;
//there was a declaration of speed as 1200 if that's important.

task waiting()
{
	wait1Msec(9000);
	timeOver = true;
}

void findIR (tSensors ir_seeker)
{
	int ir_value;
	nMotorEncoder[motor_right] = 0;
	nMotorEncoder[motor_left] = 0;

	do {
		StartTask(waiting);
		ir_value = getIRReading(ir_seeker);
		if(ir_value < 6)
			forward(70);
		else
			forward(40);
	} while( getIRReading(ir_seeker) != 8 && nMotorEncoder[motor_left] < 6800 && timeOver == false);
	stops();

	tossBlock();
}

task main()
{
	// Initialize the robot
	nMotorEncoder[motor_right] = 0;
	nMotorEncoder[motor_left] = 0;
	servo[servoBlock] = BLOCK_INIT;

	waitForStart(); // Wait for the beginning of autonomous phase.

	liftMove(50, 600);// move lift to a  safe location
	findIR(IRSEEKER);
	drive2Encoder(80, 30, BACK);
	turnDeg(90, TURN_RIGHT, 100, 50);
	moveDist(120, 100, 30);
	turnDeg(105, TURN_RIGHT, 100, 60);
	move(-50, 2000); // go forwards to IR the comes back to go the the ramp
}
