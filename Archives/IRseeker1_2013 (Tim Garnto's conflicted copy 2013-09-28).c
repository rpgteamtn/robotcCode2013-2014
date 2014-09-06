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
#include "function_library.c"

task main()
{

	locateIR();

	if(SensorValue(IRSEEKER) > 5){
		turn(50, 100, TURN_RIGHT);
		move(50, 100);
		turn(50, 100, TURN_LEFT);
		move(50, 100);
		move(-50, 100);
		turn(50, 100, TURN_LEFT);
		move(50, 100);
		move(-50, 100);
		turn(50, 100, TURN_LEFT);
		move(50, 100);
		move(-50, 100);
		turn(50, 100, TURN_RIGHT);
	}

	else{
		turn(50, 100, TURN_LEFT);
		move(50, 100);
		turn(50, 100, TURN_RIGHT);
		move(50, 100);
		move(-50, 100);
		turn(50, 100, TURN_RIGHT);
		move(50, 100);
		move(-50, 100);
		turn(50, 100, TURN_RIGHT);
		move(50, 100);
		move(-50, 100);
		turn(50, 100, TURN_LEFT);
	}

}
