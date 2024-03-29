#pragma config(Hubs,  S1, HTMotor,  HTMotor,  none,     none)
#pragma config(Hubs,  S4, HTServo,  HTMotor,  none,     none)
#pragma config(Sensor, S2,     touch,          sensorTouch)
#pragma config(Sensor, S3,     IRSEEKER,       sensorI2CCustom)
#pragma config(Motor,  motorA,           ,             tmotorNXT, openLoop, encoder)
#pragma config(Motor,  motorB,           ,             tmotorNXT, openLoop, encoder)
#pragma config(Motor,  motorC,           ,             tmotorNXT, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C1_1,     motor_left,    tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     motor_right,   tmotorTetrix, openLoop, reversed)
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
//there was a declaration of speed as 1200 if that's important.

void findIR (tSensors ir_seeker)
{
	int ir_value;
	nMotorEncoder[motor_right] = 0;
	nMotorEncoder[motor_left] = 0;

	do {
		ir_value = getIRReading(ir_seeker);
		if(ir_value > 8)
			forward(70);
		else
			forward(40);
	} while( getIRReading(ir_seeker) != 7 && nMotorEncoder[motor_left] < 6800 );
	stops();
//	if(nMotorEncoder[motor_left] >= 900){
//	moveDist(20, 100, 50);
//	}
	if(nMotorEncoder[motor_left] <= 2500){ //Jeff wanted to be in a comment, so here he is. Also, this stops the robot from going back once it is a t the halfway point.
		drive2Encoder(nMotorEncoder[motor_left] - 200, 50, BACK, motor[motor_left]);
	}
	else{
		moveDist(35, 100, 50);
	}
	tossBlock();
}

task setLift()
{
	liftMove(50, 1000);
}
task endLift()
{
	liftMove(-50, 600);
}


task main()
{
	// Initialize the robot
	nMotorEncoder[motor_right] = 0;
	nMotorEncoder[motor_left] = 0;
	servo[servoBlock] = BLOCK_INIT;

	waitForStart(); // Wait for the beginning of autonomous phase.

	StartTask(setLift);
	findIR(IRSEEKER);
	drive2Encoder(200, 50, BACK, motor[motor_left]);
	turnDeg(120, TURN_RIGHT, 100, 50);
	moveDist(120, 100, 30);
	turnDeg(105, TURN_LEFT, 100, 60);
	StartTask(endLift);
	moveDist(130, 100, 30); // go forwards to IR then comes back to go the the ramp
}
