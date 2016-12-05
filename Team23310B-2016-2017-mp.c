#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, in1,    LIFTARM_POT,    sensorNone)
#pragma config(Sensor, in2,    CLAW_POT,       sensorPotentiometer)
#pragma config(Sensor, in3,    GYRO,           sensorGyro)
#pragma config(Sensor, in4,    BATTERY_2,      sensorAnalog)
#pragma config(Sensor, dgtl1,  LED_AUTO, sensorLEDtoVCC)
#pragma config(Sensor, dgtl2,  LED_INITIALIZED, sensorLEDtoVCC)
#pragma config(Sensor, dgtl10, AUTON_CONFIG_SWITCH_2, sensorTouch)
#pragma config(Sensor, dgtl11, AUTON_CONFIG_SWITCH_1, sensorTouch)
#pragma config(Sensor, dgtl12, IS_RED_TEAM_SWITCH, sensorTouch)
#pragma config(Sensor, I2C_1,  DRIVE_LEFT_ENCODER, sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Sensor, I2C_2,  DRIVE_RIGHT_ENCODER, sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Motor,  port1,           ARM_RIGHT_BOTTOM, tmotorVex393HighSpeed_HBridge, openLoop, reversed)
#pragma config(Motor,  port3,           DRIVE_RIGHT,   tmotorVex393HighSpeed_MC29, openLoop, reversed, encoderPort, I2C_2)
#pragma config(Motor,  port4,           ARM_RIGHT_TOP, tmotorVex393HighSpeed_MC29, openLoop, reversed)
#pragma config(Motor,  port5,           CLAW_RIGHT,    tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port6,           CLAW_LEFT,     tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port7,           ARM_LEFT_TOP,  tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port8,           DRIVE_LEFT,    tmotorVex393HighSpeed_MC29, openLoop, encoderPort, I2C_1)
#pragma config(Motor,  port10,          ARM_LEFT_BOTTOM, tmotorVex393HighSpeed_HBridge, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#pragma platform(VEX)

//Competition Control and Duration Settings
#pragma competitionControl(Competition)
#pragma autonomousDuration(15)
#pragma userControlDuration(105)

#include "Vex_Competition_Includes.c"   //Main competition background code...do not modify!

// We have 8 possible places to store data, we call each one a datalog series
// This example uses the first four to store values.
#define   DATALOG_SERIES_0    0
#define   DATALOG_SERIES_1    1
#define   DATALOG_SERIES_2    2
#define   DATALOG_SERIES_3    3
#define   DATALOG_SERIES_4    4
#define   DATALOG_SERIES_5    5
#define   DATALOG_SERIES_6    6
#define   DATALOG_SERIES_7    7

// Red/blue team
bool isRedTeam = false;
int autonConfigId1 = 0;
int autonConfigId2 = 0;

// Claw
bool clawPIDActive = false;

float CLAW_KP = 0.3;
float CLAW_KD = 0.0;
float CLAW_FF = 0.0;

int CLAW_CLOSE = 360.0;
int CLAW_MID = 1000.0;
int CLAW_OPEN = 1450.0;
int CLAW_STRAIGHT = 1760;
int CLAW_AUTON = 2800.0;
int CLAW_ERROR_TOLERANCE = 50;

int targetClawValue = CLAW_MID;
int targetClawDelayValue = -1;
int targetLiftArmClawDelayValue = -1;
int currentClawEncoderValue = 0;
int previousClawError = 0;
bool isClawAtTarget = false;

// Liftarm
bool liftArmPIDActive = false;

float LIFTARM_KP = 0.4;
float LIFTARM_KD = 0.0;
float LIFTARM_FF = -0.1;

int LIFTARM_PICKUP = 350.0;
int LIFTARM_CLIMB_LOAD = 925.0;
int LIFTARM_HOLD = 1600.0; // 1800;
int LIFTARM_DUMP = 2800.0;
int LIFTARM_STAR_LIFT_LOW = 1000.0;
int LIFTARM_STAR_LIFT_HIGH = 1915.0;
int LIFTARM_CLIMB_LIFT = 3400.0;
int LIFTARM_DUMP_CLAW_OPEN = 1750; // 2000;

int LIFTARM_ERROR_TOLERANCE = 30;

int targetLiftArmValue = LIFTARM_PICKUP;
int targetLiftArmDelayValue = -1;
int targetLiftArmDelayTime = 0;
int currentLiftArmEncoderValue = 0;
int previousLiftArmError = 0;
bool isLiftArmAtTarget = false;

// VEX 4" Omni Direction Wheel to determine distance - diameter = 4" --- 4" * Pi = 12.566" per revolution
// Encoders are 360 count per revolution so 392/12.566" = 31.2 counts/inch
float ENCODER_COUNTS_PER_INCH = 28.0;   // Fudged
float ENCODER_DISTANCE_KP = 0.6;  //0.15
float ENCODER_DISTANCE_KI = 0.0; //0.00015
float ENCODER_DISTANCE_KD = 50.0;
float ENCODER_TURN_CORRECTION_KP = 0.0;
int ENCODER_OFFSET_KP = 0;
int WHEEL_INTEGRAL_BAND = 200;
int ENCODER_COUNT_TOLERANCE = 10;
int ERROR_PASS_COUNT = 400;
int previousDistanceCountError = 0;

// Motion profile gains
float MP_STRAIGHT_KP = 0.7;		// Position P gain
float MP_STRAIGHT_KV = 1.7;		// Velocity gain
float MP_STRAIGHT_KA = 0.09;	// Acceleration gain
float MP_STRAIGHT_KG = 10.0;	// Gyro turn gain  20.0
float MP_STRAIGHT_KT = 0.0;   // Encoder turn gain
float MP_AUTON_STRAIGHT_SPEED = 30;

float MP_TURN_KP = 1.4;		// Position P gain
float MP_TURN_KV = 0.4;		// Velocity gain
float MP_TURN_KA = 0.06;	// Acceleration gain
float MP_AUTON_TURN_RATE = 130;

int NUM_MP_POST_FRAMES = 10;  // # of frames (10ms each) after MP is finished

// Gyro
int GYRO_COUNT_TOLERANCE = 10;
int GYRO_INTEGRAL_BAND = 200;
float GYRO_TURN_KP = 0.5;  //.08
float GYRO_TURN_KD = 0.1;  //.08
float GYRO_TURN_KI = 0.0; //0.00016
float GYRO_FUDGE_FACTOR = 0.946;   // 0.946
float PIVOT_TURN_RADIUS_INCHES = 19.0;
int previousTurnCountError = 0;
float absoluteGyroAngle = 0;

//++++++++++++++++++++++++++++++++++++++++++++| UTILITY |++++++++++++++++++++++++++++++++++++++++++++++

int limitMotorPower(int desiredPowerValue, int maxAbsPowerValue) {
	if (desiredPowerValue > maxAbsPowerValue) {
		return maxAbsPowerValue;
	}
	else if (desiredPowerValue < -maxAbsPowerValue) {
		return -maxAbsPowerValue;
	}
	return desiredPowerValue;
}

void setDriveMotorPower(float leftMotorPower, float rightMotorPower)
{
		// Check for proper turn delta power
		if (leftMotorPower > 127) {
			rightMotorPower -= (leftMotorPower - 127);
			leftMotorPower = 127;
		}
		else if (leftMotorPower < -127) {
			rightMotorPower -= (leftMotorPower + 127);
			leftMotorPower = -127;
		}
		else if (rightMotorPower > 127) {
			leftMotorPower -= (rightMotorPower - 127);
			rightMotorPower = 127;
		}
		else if (rightMotorPower < -127) {
			leftMotorPower -= (rightMotorPower + 127);
			rightMotorPower = -127;
		}

		// Update motor power
	  motor[DRIVE_LEFT] = leftMotorPower;
		motor[DRIVE_RIGHT]  = rightMotorPower;
}

float max(float var1, float var2) {
	if (var1 > var2) {
		return var1;
	}
	return var2;
}

float min(float var1, float var2) {
	if (var1 < var2) {
		return var1;
	}
	return var2;
}

//+++++++++++++++++++++++++++++++++++++++++| CLAW |+++++++++++++++++++++++++++++++++++++++++
void setClawPower(int clawPower) {

	int limitedClawPower = limitMotorPower(clawPower, 127);

  motor[CLAW_RIGHT] = limitedClawPower;
  motor[CLAW_LEFT] = limitedClawPower;
}

void checkClawTargetDelayed()
{
	if (targetClawDelayValue > 0 &&  currentLiftArmEncoderValue > targetLiftArmClawDelayValue) {
		targetClawValue = targetClawDelayValue;
		targetClawDelayValue = -1;
		targetLiftArmClawDelayValue = 0;
	}
}

void updateClawPosition()
{
	checkClawTargetDelayed();
	currentClawEncoderValue = SensorValue[CLAW_POT];
	int clawError = targetClawValue - currentClawEncoderValue;
	int diffClawError = clawError - previousClawError;

	float clawPower = (float)clawError * CLAW_KP + (float)diffClawError * CLAW_KD + CLAW_FF;
	setClawPower((int)clawPower);

  // datalogAddValue when surrounded by datalogDataGroupStart and datalogDataGroupEnd
  // adds several values to one row of the datalog with a common time stamp
  //datalogDataGroupStart();
  //datalogAddValue( DATALOG_SERIES_0, targetClawValue );
  //datalogAddValue( DATALOG_SERIES_1, currentClawEncoderValue );
  //datalogAddValue( DATALOG_SERIES_2, clawError );
  //datalogAddValue( DATALOG_SERIES_3, clawPower );
  //datalogAddValue( DATALOG_SERIES_4, limitedClawPower );
  //datalogDataGroupEnd();

	if (abs(clawError) < CLAW_ERROR_TOLERANCE) {
		isClawAtTarget = true;
	}
	else {
		isClawAtTarget = false;
	}

	previousClawError = clawError;
	wait1Msec(1);
}

void waitForClawToComplete()
{
	wait1Msec(30);
	while(!isClawAtTarget) {
		wait1Msec(10);
	}
}

task clawPositionTask()
{
	while(true)
	{
		if (clawPIDActive) {
			updateClawPosition();
		}
		wait1Msec(10);
	}
}

void setClawTargetDelayed(int position, int liftArmPosition)
{
	targetClawDelayValue = position;
	targetLiftArmClawDelayValue = liftArmPosition;
}

void setClawTarget(int position, bool waitToComplete)
{
	targetClawValue = position;

	if (waitToComplete) {
		waitForClawToComplete();
	}
}

//+++++++++++++++++++++++++++++++++++++++++| LIFTARM |+++++++++++++++++++++++++++++++++++++++++
void setLiftArmPower(int liftArmPower) {

	int limitedLiftArmPower = limitMotorPower(liftArmPower, 127);

  motor[ARM_RIGHT_BOTTOM] = limitedLiftArmPower;
  motor[ARM_RIGHT_TOP] = limitedLiftArmPower;
  motor[ARM_LEFT_BOTTOM] = limitedLiftArmPower;
  motor[ARM_LEFT_TOP] = limitedLiftArmPower;
}

void checkLiftArmTargetDelayed()
{
	if (targetLiftArmDelayValue > 0 && time1(T1) > targetLiftArmDelayTime) {
		targetLiftArmValue = targetLiftArmDelayValue;
		targetLiftArmDelayValue = -1;
		targetLiftArmDelayTime = 0;
	}
}

void updateLiftArmPosition()
{
	checkLiftArmTargetDelayed();
	currentLiftArmEncoderValue = SensorValue[LIFTARM_POT];
	int liftArmError = targetLiftArmValue - currentLiftArmEncoderValue;
	int diffLiftArmError = liftArmError - previousLiftArmError;

	float liftArmPower = (float)liftArmError * LIFTARM_KP + (float)diffLiftArmError * LIFTARM_KD + LIFTARM_FF;
	setLiftArmPower((int)liftArmPower);

  // datalogAddValue when surrounded by datalogDataGroupStart and datalogDataGroupEnd
  // adds several values to one row of the datalog with a common time stamp
  //datalogDataGroupStart();
  //datalogAddValue( DATALOG_SERIES_0, targetLiftArmValue );
  //datalogAddValue( DATALOG_SERIES_1, currentLiftArmEncoderValue );
  //datalogAddValue( DATALOG_SERIES_2, liftArmError );
  //datalogAddValue( DATALOG_SERIES_3, liftArmPower );
  //datalogAddValue( DATALOG_SERIES_4, limitedLiftArmPower );
  //datalogDataGroupEnd();

	if (abs(liftArmError) < LIFTARM_ERROR_TOLERANCE) {
		isLiftArmAtTarget = true;
	}
	else {
		isLiftArmAtTarget = false;
	}

	previousLiftArmError = liftArmError;
	wait1Msec(1);
}

void waitForLiftArmToComplete()
{
	wait1Msec(30);
	while(!isLiftArmAtTarget) {
		wait1Msec(10);
	}
}

task liftArmPositionTask()
{
	while(true)
	{
		if (liftArmPIDActive) {
			SensorValue[LED_AUTO] = 1;
			updateLiftArmPosition();
		}
		else {
			SensorValue[LED_AUTO] = 0;
		}
		wait1Msec(10);
	}
}

void setLiftArmTargetDelayed(int position, int waitTime)
{
	targetLiftArmDelayValue = position;
	targetLiftArmDelayTime = waitTime;
	clearTimer(T1);
}

void setLiftArmTarget(int position, bool waitToComplete)
{
	targetLiftArmValue = position;

	if (waitToComplete) {
		waitForLiftArmToComplete();
	}
}

void armPickupPositionOpenClaw() {
	setLiftArmTarget(LIFTARM_PICKUP, false);
	setClawTarget(CLAW_MID, false);
}

void closeClawArmHoldPosition() {
	setClawTarget(CLAW_CLOSE, false);
  setLiftArmTargetDelayed(LIFTARM_HOLD, 300);
}

void armDumpPositionOpenClaw() {
	setLiftArmTarget(LIFTARM_DUMP, false);
	setClawTargetDelayed(CLAW_OPEN, LIFTARM_DUMP_CLAW_OPEN);
}

//++++++++++++++++++++++++++++++++++++++++| DRIVE WITH ENCODERS |++++++++++++++++++++++++++++++++++++++++++++

void moveStraight(float distanceInches, int maxPower)
{
	// Reset encoders
	SensorValue[DRIVE_RIGHT_ENCODER] = 0;
	SensorValue[DRIVE_LEFT_ENCODER] = 0;

	// Calculate the number of encoder counts required to go the distance
	int targetCount = round(ENCODER_COUNTS_PER_INCH * distanceInches);
	int distanceCountError = targetCount;
	float integralCountError = 0;
	int numberPassesAfterTolerance = 0;

	// Loop until the desired distance is achieved
	while(numberPassesAfterTolerance < ERROR_PASS_COUNT)
	{
		if (numberPassesAfterTolerance == 0) {
			if (abs(distanceCountError) < ENCODER_COUNT_TOLERANCE) {
				numberPassesAfterTolerance = 1;
			}
		}
		else {
			numberPassesAfterTolerance++;
		}

		// Update count error
		int rightWheelCount = -SensorValue[DRIVE_RIGHT_ENCODER];
		int leftWheelCount = SensorValue[DRIVE_LEFT_ENCODER];
		int turnCountError = leftWheelCount - rightWheelCount;
  	distanceCountError =  targetCount - (rightWheelCount + leftWheelCount) / 2;
		int diffDistanceCountError = distanceCountError - previousDistanceCountError;
		if (abs(distanceCountError) < WHEEL_INTEGRAL_BAND) {
			integralCountError += distanceCountError;
			maxPower = 127;
		}

		// Calculate the motor power using Kp and Ki terms
		int distanceMotorPower = limitMotorPower((distanceCountError - ENCODER_OFFSET_KP) * ENCODER_DISTANCE_KP + integralCountError * ENCODER_DISTANCE_KI + diffDistanceCountError * ENCODER_DISTANCE_KD, maxPower);
		int turnMotorPower = turnCountError * ENCODER_TURN_CORRECTION_KP;
		int leftMotorPower = distanceMotorPower - turnMotorPower;
		int rightMotorPower = distanceMotorPower + turnMotorPower;

		setDriveMotorPower(leftMotorPower, rightMotorPower);

		previousDistanceCountError = distanceCountError;
		wait1Msec(1);
	}

	// All done time to exit
	setDriveMotorPower(0, 0);
}

void tankTurnGyro(float turnAngleDegrees, int maxPower)
{
	if (isRedTeam) {
		turnAngleDegrees = -turnAngleDegrees;
	}

	// Reset gyro
	SensorValue[GYRO] = 0;

	// Initialize errors
	int targetCount = turnAngleDegrees * 10;
	int turnCountError = targetCount;
	float integralTurnCountError = 0;

	// Loop until the desired turn angle is achieved
	int numberPassesAfterTolerance = 0;

	// Loop until the desired distance is achieved
	while(numberPassesAfterTolerance < ERROR_PASS_COUNT)
	{
		if (numberPassesAfterTolerance == 0) {
			if (abs(turnCountError) < GYRO_COUNT_TOLERANCE) {
				numberPassesAfterTolerance = 1;
			}
		}
		else {
			numberPassesAfterTolerance++;
		}

		// Update count error
		float gyroCount = (float)SensorValue[GYRO] * GYRO_FUDGE_FACTOR;
		turnCountError =  targetCount - gyroCount;
		int diffTurnCountError = turnCountError - previousTurnCountError;
		if (abs(turnCountError) < GYRO_INTEGRAL_BAND) {
			integralTurnCountError += turnCountError;
			maxPower = 80;
		}

		// Calculate the motor power using Kp and Ki terms
		int turnMotorPower = limitMotorPower(turnCountError * GYRO_TURN_KP + integralTurnCountError * GYRO_TURN_KI + diffTurnCountError * GYRO_TURN_KD, maxPower);
		int leftMotorPower = turnMotorPower;
		int rightMotorPower = -turnMotorPower;

		setDriveMotorPower(leftMotorPower, rightMotorPower);
		wait1Msec(1);
	}

	// All done time to exit
	setDriveMotorPower(0, 0);
	previousTurnCountError = turnCountError;
}

void tankTurnEncoder(float turnAngleDegrees, int maxPower)
{
	if (isRedTeam) {
		turnAngleDegrees = -turnAngleDegrees;
	}

	// Reset encoders
	SensorValue[DRIVE_RIGHT_ENCODER] = 0;
	SensorValue[DRIVE_LEFT_ENCODER] = 0;

	// Calculate the number of encoder counts required to go the distance
	float outerTrackDistance = PIVOT_TURN_RADIUS_INCHES / 2.0 * turnAngleDegrees * PI / 180.0;
	int targetCount = round(ENCODER_COUNTS_PER_INCH * outerTrackDistance);
	int distanceCountError = targetCount;
	float integralCountError = 0;

	// Loop until the desired distance is achieved
	while(abs(distanceCountError) > ENCODER_COUNT_TOLERANCE)
	{
		// Update count error
		int rightWheelCount = -SensorValue[DRIVE_RIGHT_ENCODER];
		int leftWheelCount = SensorValue[DRIVE_LEFT_ENCODER];
		int turnCountError = leftWheelCount + rightWheelCount;
		distanceCountError =  targetCount - (leftWheelCount - rightWheelCount) / 2;
		if (abs(distanceCountError) < WHEEL_INTEGRAL_BAND) {
			integralCountError += distanceCountError;
		}

		// Calculate the motor power using Kp and Ki terms
		int distanceMotorPower = limitMotorPower(distanceCountError * ENCODER_DISTANCE_KP + integralCountError * ENCODER_DISTANCE_KI, maxPower);
		int turnMotorPower = turnCountError * ENCODER_TURN_CORRECTION_KP;
		int leftMotorPower = distanceMotorPower - turnMotorPower;
		int rightMotorPower = -distanceMotorPower - turnMotorPower;

		setDriveMotorPower(leftMotorPower, rightMotorPower);
		wait1Msec(1);
	}

	// All done time to exit
	setDriveMotorPower(0, 0);
}

void pivotTurnGyro(int turnDirection, float turnAngleDegrees, int maxPower)
{
	if (isRedTeam) {
		turnAngleDegrees = -turnAngleDegrees;
	}

	// Reset gyro
	SensorValue[GYRO] = 0;

	// Initialize errors
	int targetCount = turnAngleDegrees * 10;
	int turnCountError = targetCount;
	float integralTurnCountError = 0;

	// Loop until the desired turn angle is achieved
	while(abs(turnCountError) > GYRO_COUNT_TOLERANCE)
	{
		// Update count error
		float gyroCount = (float)SensorValue[GYRO] * GYRO_FUDGE_FACTOR;
		turnCountError =  targetCount - gyroCount;
		if (abs(turnCountError) < GYRO_INTEGRAL_BAND) {
			integralTurnCountError += turnCountError;
		}

		// Calculate the motor power using Kp and Ki terms
		int turnMotorPower = limitMotorPower(turnCountError * GYRO_TURN_KP * 1.5 + integralTurnCountError * GYRO_TURN_KI, maxPower);
		int leftMotorPower = turnDirection > 0 ? turnMotorPower : 0;
		int rightMotorPower = turnDirection > 0 ? 0: turnMotorPower;

		setDriveMotorPower(leftMotorPower, rightMotorPower);
	}

	// All done time to exit
	setDriveMotorPower(0, 0);
}

void pivotTurnEncoder(int turnDirection, float turnAngleDegrees, int maxPower)
{
	if (isRedTeam) {
		turnAngleDegrees = -turnAngleDegrees;
	}

	// Reset encoders
	SensorValue[DRIVE_RIGHT_ENCODER] = 0;
	SensorValue[DRIVE_LEFT_ENCODER] = 0;

	// Calculate the number of encoder counts required to go the distance
	float outerTrackDistance = PIVOT_TURN_RADIUS_INCHES * turnAngleDegrees * PI / 180.0;
	int targetCount = round(ENCODER_COUNTS_PER_INCH * outerTrackDistance);
	int distanceCountError = targetCount;
	float integralCountError = 0;

	// Loop until the desired distance is achieved
	while(abs(distanceCountError) > ENCODER_COUNT_TOLERANCE)
	{
		// Update count error
		int outerWheelCount = turnDirection > 0 ? SensorValue[DRIVE_LEFT_ENCODER] : -SensorValue[DRIVE_RIGHT_ENCODER];
		distanceCountError =  targetCount - outerWheelCount;
		if (abs(distanceCountError) < WHEEL_INTEGRAL_BAND) {
			integralCountError += distanceCountError;
		}

		// Calculate the motor power using Kp and Ki terms
		int distanceMotorPower = limitMotorPower(distanceCountError * ENCODER_DISTANCE_KP + integralCountError * ENCODER_DISTANCE_KI, maxPower);
		int leftMotorPower = turnDirection > 0 ? distanceMotorPower : 0;
		int rightMotorPower = turnDirection > 0 ? 0: distanceMotorPower;

		setDriveMotorPower(leftMotorPower, rightMotorPower);
	}

	// All done time to exit
	setDriveMotorPower(0, 0);
}

void pivotTurnRightGyro(float turnAngleDegrees, int maxPower)
{
	if (isRedTeam) {
		pivotTurnGyro(-1, turnAngleDegrees, maxPower);
	}
	else {
		pivotTurnGyro(1, turnAngleDegrees, maxPower);
	}
}

void pivotTurnLeftGyro(float turnAngleDegrees, int maxPower)
{
	if (isRedTeam) {
		pivotTurnGyro(1, turnAngleDegrees, maxPower);
	}
	else {
		pivotTurnGyro(-1, turnAngleDegrees, maxPower);
	}
}

void pivotTurnRightEncoder(float turnAngleDegrees, int maxPower)
{
	if (isRedTeam) {
		pivotTurnEncoder(-1, turnAngleDegrees, maxPower);
	}
	else {
		pivotTurnEncoder(1, turnAngleDegrees, maxPower);
	}
}

void pivotTurnLeftEncoder(float turnAngleDegrees, int maxPower)
{
	if (isRedTeam) {
		pivotTurnEncoder(1, turnAngleDegrees, maxPower);
	}
	else {
		pivotTurnEncoder(-1, turnAngleDegrees, maxPower);
	}
}

void updateStraightController(float time, float position, float velocity, float acceleration, int itp) {
	// Loop for itp times at 1ms then go get next point
	for (int j = 0; j < (int)itp; j++)
	{
		// Update count error
		int rightWheelCount = -SensorValue[DRIVE_RIGHT_ENCODER];
		int leftWheelCount = SensorValue[DRIVE_LEFT_ENCODER];
		int positionCount = round(ENCODER_COUNTS_PER_INCH * position);
  	int distanceCountError =  positionCount - (rightWheelCount + leftWheelCount) / 2;
		int turnCountError = leftWheelCount - rightWheelCount;
		float turnAngleError = (float)SensorValue[GYRO] * GYRO_FUDGE_FACTOR / 10.0 - absoluteGyroAngle;

		// Calculate the motor power using K terms
		int distanceMotorPower = limitMotorPower(distanceCountError * MP_STRAIGHT_KP + velocity * MP_STRAIGHT_KV + acceleration * MP_STRAIGHT_KA, 127);
		int turnMotorPower = turnCountError * MP_STRAIGHT_KT + turnAngleError * MP_STRAIGHT_KG;
		int leftMotorPower = distanceMotorPower - turnMotorPower;
		int rightMotorPower = distanceMotorPower + turnMotorPower;

		setDriveMotorPower(leftMotorPower, rightMotorPower);
/*
		datalogDataGroupStart();
		datalogAddValue( DATALOG_SERIES_0, mpDist );
		datalogAddValue( DATALOG_SERIES_1, mpVel );
		datalogAddValue( DATALOG_SERIES_2, mpAccel );
		datalogAddValue( DATALOG_SERIES_3, distanceCountError );
		datalogAddValue( DATALOG_SERIES_4, distanceMotorPower );
		datalogDataGroupEnd();
*/
		wait1Msec(1);
	}
}

void updateTurnController(float time, float position, float velocity, float acceleration, int itp) {
	// Loop for itp times at 1ms then go get next point
	for (int j = 0; j < (int)itp; j++)
	{
		// Update count error
		float turnGyroError = position - (float)SensorValue[GYRO] * GYRO_FUDGE_FACTOR / 10.0;

		// Calculate the motor power using K terms
		int turnMotorPower = limitMotorPower(turnGyroError * MP_TURN_KP + velocity * MP_TURN_KV + acceleration * MP_TURN_KA, 127);
		int leftMotorPower = turnMotorPower;
		int rightMotorPower = -turnMotorPower;

		setDriveMotorPower(leftMotorPower, rightMotorPower);
/*
		datalogDataGroupStart();
		datalogAddValue( DATALOG_SERIES_0, mpDist );
		datalogAddValue( DATALOG_SERIES_1, mpVel );
		datalogAddValue( DATALOG_SERIES_2, mpAccel );
		datalogAddValue( DATALOG_SERIES_3, distanceCountError );
		datalogAddValue( DATALOG_SERIES_4, distanceMotorPower );
		datalogDataGroupEnd();
*/
		wait1Msec(1);
	}
}

void calculateMP(float startPositionInput, float targetPositionInput, float maxVelocityInput, bool isStraight) {
	float startPosition = startPositionInput;  		// any position unit
	float targetPosition = targetPositionInput;  	// any position unit
	float maxVelocity = maxVelocityInput;					// velocity unit consistent with targetPosition

	float t1 = 200;	// millisecond
	float t2 = 100; // millisecond
	float itp = 10;	// millisecond

	// t4 is the time in ms it takes to get to the end point when at max velocity
	float t4 = abs((targetPosition - startPosition)/maxVelocity) * 1000;

	// We need to make t4 an even multiple of itp
	t4 = (int)(itp * ceil(t4/itp));

	// In the case where t4 is less than the accel times, we need to adjust the
	// accel times down so the filters works out.  Lots of ways to do this but
	// to keep things simple we will make t4 slightly larger than the sum of
	// the accel times.
	if (t4 < t1 + t2) {
		float total = t1 + t2 + t4;
		float t1t2Ratio = t1/t2;
		float t2Adjusted = floor(total / 2 / (1 + t1t2Ratio) / itp);
		if (t2Adjusted % 2 != 0) {
			t2Adjusted -= 1;
		}
		t2 = t2Adjusted * itp;
		t1 = t2 * t1t2Ratio;
		t4 = total - t1 - t2;
	}

	// Adjust max velocity so that the end point works out to the correct position.
	maxVelocity = abs((targetPosition - startPosition) / t4) * 1000;

	int numFilter1Boxes = (int)ceil(t1/itp);
	int numFilter2Boxes = (int)ceil(t2/itp);
	int numPoints = (int)ceil(t4/itp);

	int numITP = numPoints + numFilter1Boxes + numFilter2Boxes;
	float filter1 = 0;
	float filter2 = 0;
	float previousVelocity = 0;
	float previousPosition = startPosition;
	float deltaFilter1 = 1.0/numFilter1Boxes;

	// Don't see a way o dynamically set array size, just oversize based on nominal t2 and itp values
	float filter2Window[20];
	int windowIndex = 0;
	int pointIndex = 0;
	if (startPosition > targetPosition && maxVelocity > 0) {
		maxVelocity = -maxVelocity;
	}

	float time = 0;
	float position = 0;
	float velocity = 0;
	float acceleration = 0;

	// First point
	if (isStraight) {
		updateStraightController(time, position, velocity, acceleration, itp);
	}
	else {
		updateTurnController(time, position, velocity, acceleration, itp);
	}
	pointIndex++;

	// Start looping through the points
	while (pointIndex <= numITP) {
		int input = (pointIndex - 1) < numPoints ? 1 : 0;
		if (input > 0) {
			filter1 = min(1, filter1 + deltaFilter1);
		}
		else {
			filter1 = max(0, filter1 - deltaFilter1);
		}

		float firstFilter1InWindow = filter2Window[windowIndex];
		if (pointIndex <= numFilter2Boxes) {
			firstFilter1InWindow = 0;
		}
		filter2Window[windowIndex] = filter1;

		filter2 += (filter1 - firstFilter1InWindow) / numFilter2Boxes;

		time = pointIndex * itp / 1000.0;
		velocity = filter2 * maxVelocity;
		position = previousPosition + (velocity + previousVelocity) /  2 * itp / 1000;
		acceleration = (velocity - previousVelocity) / itp * 1000;

		previousVelocity = velocity;
		previousPosition = position;
		windowIndex++;
		if (windowIndex == numFilter2Boxes) {
			windowIndex = 0;
		}

		if (isStraight) {
			updateStraightController(time, position, velocity, acceleration, itp);
		}
		else {
			updateTurnController(time, position, velocity, acceleration, itp);
		}

		pointIndex++;
	}

	for (int i = 0; i < NUM_MP_POST_FRAMES; i++) {
		if (isStraight) {
			updateStraightController(time, targetPosition, 0, 0, itp);
		}
		else {
			updateTurnController(time, targetPosition, 0, 0, itp);
		}
	}

	// When finished stop the motors as there still might some small motor power from last iteration
	setDriveMotorPower(0, 0);
}

void moveStraightMP(float targetDistanceInches, float maxVelocityInchesPerSecond) {
	// Reset encoders/gyro
	SensorValue[DRIVE_RIGHT_ENCODER] = 0;
	SensorValue[DRIVE_LEFT_ENCODER] = 0;
	SensorValue[GYRO] = 0;
	absoluteGyroAngle = 0;
	calculateMP(0, targetDistanceInches, maxVelocityInchesPerSecond, true);
}

void moveStraightMPAbsolute(float targetDistanceInches, float maxVelocityInchesPerSecond, float gyroAngle) {
	// Reset encoders/gyro
	SensorValue[DRIVE_RIGHT_ENCODER] = 0;
	SensorValue[DRIVE_LEFT_ENCODER] = 0;
	absoluteGyroAngle = gyroAngle;
	if (isRedTeam) {
		absoluteGyroAngle = -absoluteGyroAngle;
	}
	calculateMP(0, targetDistanceInches, maxVelocityInchesPerSecond, true);
}

void tankTurnGyroMP(float targetAngleDegrees, float maxTurnRateDegPerSecond) {
	if (isRedTeam) {
		targetAngleDegrees = -targetAngleDegrees;
	}

	// Reset gyro
	SensorValue[GYRO] = 0;
	calculateMP(0, targetAngleDegrees, maxTurnRateDegPerSecond, false);
}

void tankTurnGyroMPAbsolute(float targetAngleDegrees, float maxTurnRateDegPerSecond) {
	if (isRedTeam) {
		targetAngleDegrees = -targetAngleDegrees;
	}

	calculateMP(SensorValue[GYRO], targetAngleDegrees, maxTurnRateDegPerSecond, false);
}

//++++++++++++++++++++++++++++++++++++++++++| LCD DISPLAY |+++++++++++++++++++++++++++++++++++++++++++++

string lcdInfo;

void updateDisplay()
{
	clearLCDLine(0);
	clearLCDLine(1);

	int leftWheelCount = SensorValue[DRIVE_LEFT_ENCODER];
	int rightWheelCount = -SensorValue[DRIVE_RIGHT_ENCODER];
	float secondBatteryVoltageRaw = (float)SensorValue[BATTERY_2];
	float gyroRaw = (float)SensorValue[GYRO] * GYRO_FUDGE_FACTOR / 10.0;
	int armPotValue = SensorValue[LIFTARM_POT];
 	int clawPotValue = SensorValue[CLAW_POT];

	sprintf(lcdInfo, "L%i", leftWheelCount);
	displayLCDString(0, 0, lcdInfo);

	sprintf(lcdInfo, "R%i", rightWheelCount);
	displayLCDString(0, 4, lcdInfo);

	sprintf(lcdInfo, "G%i", (int)gyroRaw);
	displayLCDString(0, 8, lcdInfo);

	sprintf(lcdInfo, "M%1.1f", nImmediateBatteryLevel/1000.0);
	displayLCDString(0, 12, lcdInfo);

	sprintf(lcdInfo, "A%i", armPotValue);
	displayLCDString(1, 0, lcdInfo);

	sprintf(lcdInfo, "C%i", clawPotValue);
	displayLCDString(1, 6, lcdInfo);

	sprintf(lcdInfo, "S%1.1f", secondBatteryVoltageRaw/182.0);
	displayLCDString(1, 12, lcdInfo);
}

/////////////////////////////////////////////////////////////////////////////////////////
//
//                          Pre-Autonomous Functions
//
// You may want to perform some actions before the competition starts. Do them in the
// following function.
//
/////////////////////////////////////////////////////////////////////////////////////////

void pre_auton()
{
  // Set bStopTasksBetweenModes to false if you want to keep user created tasks running between
  // Autonomous and Tele-Op modes. You will need to manage all user created tasks if set to false.
  bStopTasksBetweenModes = false;

	// All activities that occur before the competition starts
	isRedTeam = (SensorValue(IS_RED_TEAM_SWITCH) == 1);    // red = 1 (jumper in place)
	autonConfigId1 = SensorValue(AUTON_CONFIG_SWITCH_1);   // auton switch 1
	autonConfigId2 = SensorValue(AUTON_CONFIG_SWITCH_2);   // auton switch 2

	// Start tasks to keep the pivot arm and elevator in the proper position
  setLiftArmTarget(LIFTARM_PICKUP, false);
  setClawTarget(CLAW_MID, false);

	startTask(liftArmPositionTask);
	startTask(clawPositionTask);

	SensorValue[GYRO] = 0;
	SensorValue[LED_INITIALIZED] = 0;
}

/////////////////////////////////////////////////////////////////////////////////////////
//
//                                 Autonomous Task
//
// This task is used to control your robot during the autonomous phase of a VEX Competition.
//
/////////////////////////////////////////////////////////////////////////////////////////

task autonomous()
{
	// Pre-load star match play auton
	if (autonConfigId1 == 0 && autonConfigId2 == 0) {
		clawPIDActive = true;
    setClawTarget(CLAW_AUTON, false);
    moveStraightMP(-14, MP_AUTON_STRAIGHT_SPEED);
    wait1Msec(500);

    // Turn on the active software control
		liftArmPIDActive = true;

		// First cube
    setClawTarget(CLAW_CLOSE, false);
    wait1Msec(1000);
		moveStraightMP(-22, MP_AUTON_STRAIGHT_SPEED);
		armDumpPositionOpenClaw();
		wait1Msec(200);
		moveStraightMP(-30, MP_AUTON_STRAIGHT_SPEED);
		wait1Msec(500);
		armPickupPositionOpenClaw();
		moveStraightMP(32, MP_AUTON_STRAIGHT_SPEED);
	}

	// Programming skills auton
	else if (autonConfigId1 == 1 && autonConfigId2 == 0) {
		clawPIDActive = true;
    setClawTarget(CLAW_AUTON, false);
    moveStraightMP(-20, MP_AUTON_STRAIGHT_SPEED);
    wait1Msec(500);

    // Turn on the active software control
		liftArmPIDActive = true;

		// First cube
    setClawTarget(CLAW_CLOSE, false);
    wait1Msec(1000);
		moveStraightMP(-10, MP_AUTON_STRAIGHT_SPEED);
		armDumpPositionOpenClaw();
		wait1Msec(200);
		moveStraightMP(-30, MP_AUTON_STRAIGHT_SPEED);
		wait1Msec(500);
		armPickupPositionOpenClaw();
		moveStraightMP(32, MP_AUTON_STRAIGHT_SPEED);

		// Second cube
		setClawTarget(CLAW_CLOSE, false);
    wait1Msec(1000);
		moveStraightMP(-10, MP_AUTON_STRAIGHT_SPEED);
		armDumpPositionOpenClaw();
		wait1Msec(200);
		moveStraightMP(-30, MP_AUTON_STRAIGHT_SPEED);
		wait1Msec(500);
		armPickupPositionOpenClaw();
		moveStraightMP(32, MP_AUTON_STRAIGHT_SPEED);

		// 3 stars
		setClawTarget(CLAW_CLOSE, false);
    wait1Msec(1000);
		moveStraightMP(-10, MP_AUTON_STRAIGHT_SPEED);
		armDumpPositionOpenClaw();
		wait1Msec(200);
		moveStraightMP(-30, MP_AUTON_STRAIGHT_SPEED);
		wait1Msec(500);
		armPickupPositionOpenClaw();
		moveStraightMP(32, MP_AUTON_STRAIGHT_SPEED);

		// center cube
		tankTurnGyroMP(90, MP_AUTON_TURN_RATE);
		moveStraightMP(20, MP_AUTON_STRAIGHT_SPEED);
		setClawTarget(CLAW_CLOSE, false);
	  setLiftArmTargetDelayed(LIFTARM_HOLD, 700);
		wait1Msec(900);
		moveStraightMP(8, MP_AUTON_STRAIGHT_SPEED);
		tankTurnGyroMP(-90, MP_AUTON_TURN_RATE);
		moveStraightMP(-31, MP_AUTON_STRAIGHT_SPEED);
		armDumpPositionOpenClaw();
		wait1Msec(1500);

		// 3 stars on the floor
		armPickupPositionOpenClaw();
		moveStraightMP(32, MP_AUTON_STRAIGHT_SPEED);
		setClawTarget(CLAW_CLOSE, false);
	  setLiftArmTargetDelayed(LIFTARM_HOLD, 700);
		wait1Msec(900);
		moveStraightMP(-32, MP_AUTON_STRAIGHT_SPEED);
		armDumpPositionOpenClaw();
	}

	// Three center stars match play auton
	else if (autonConfigId1 == 0 && autonConfigId2 == 1) {
    wait1Msec(3000);
		clawPIDActive = true;
    setClawTarget(CLAW_AUTON, false);
    wait1Msec(500);

    // Turn on the active software control
	  setLiftArmTargetDelayed(LIFTARM_HOLD, 700);
		liftArmPIDActive = true;
    wait1Msec(700);

    armPickupPositionOpenClaw();
    wait1Msec(700);

    moveStraightMP(48, MP_AUTON_STRAIGHT_SPEED);
	  setLiftArmTargetDelayed(LIFTARM_HOLD, 700);
    wait1Msec(500);

    tankTurnGyroMP(-90, MP_AUTON_TURN_RATE);

		moveStraightMP(-24, MP_AUTON_STRAIGHT_SPEED);
		armDumpPositionOpenClaw();
		wait1Msec(200);
		moveStraightMP(-30, MP_AUTON_STRAIGHT_SPEED);
		wait1Msec(500);
	}

	/*

	// Match play auton center cube to wall
	else if (autonConfigId1 == 1 && autonConfigId2 == 1) {
		// Set arm to the pickup position and then open the claw
	  setLiftArmTarget(LIFTARM_PICKUP, false);
		setClawTarget(CLAW_OPEN, false);

		// Turn on the active software control
		liftArmPIDActive = true;
		clawPIDActive = true;

		// Start auton routine
		moveStraightMP(24, MP_AUTON_STRAIGHT_SPEED);
		tankTurnGyroMP(-90, MP_AUTON_TURN_RATE);
		moveStraightMP(20, MP_AUTON_STRAIGHT_SPEED);

		setClawTarget(CLAW_CLOSE, false);
	  setLiftArmTargetDelayed(LIFTARM_HOLD, 700);
		wait1Msec(900);

		moveStraightMP(8, MP_AUTON_STRAIGHT_SPEED);
		tankTurnGyroMP(-90, MP_AUTON_TURN_RATE);
		moveStraightMP(-31, MP_AUTON_STRAIGHT_SPEED);

		armDumpPositionOpenClaw();
		wait1Msec(500);
		setClawTarget(CLAW_STRAIGHT, false);
	  moveStraightMP(24, MP_AUTON_STRAIGHT_SPEED);
		tankTurnGyroMP(-180, MP_AUTON_TURN_RATE);
	  setLiftArmTarget(LIFTARM_STAR_LIFT_LOW, true);
//	  moveStraightMP(2, MP_AUTON_STRAIGHT_SPEED);
//	  setLiftArmTarget(LIFTARM_STAR_LIFT_HIGH, true);
	}
*/

	// Match play auton center cube to wall
	else if (autonConfigId1 == 1 && autonConfigId2 == 1) {
		SensorValue[GYRO] = 0;

		// Set arm to the pickup position and then open the claw
	  setLiftArmTarget(LIFTARM_PICKUP, false);
		setClawTarget(CLAW_OPEN, false);

		// Turn on the active software control
		liftArmPIDActive = true;
		clawPIDActive = true;

		// Start auton routine
		moveStraightMPAbsolute(24, MP_AUTON_STRAIGHT_SPEED, 0);
		tankTurnGyroMPAbsolute(-90, MP_AUTON_TURN_RATE);
		moveStraightMPAbsolute(20, MP_AUTON_STRAIGHT_SPEED, -90);

		setClawTarget(CLAW_CLOSE, false);
	  setLiftArmTargetDelayed(LIFTARM_HOLD, 700);
		wait1Msec(900);

		moveStraightMPAbsolute(8, MP_AUTON_STRAIGHT_SPEED, -90);
		tankTurnGyroMPAbsolute(-180, MP_AUTON_TURN_RATE);
		moveStraightMPAbsolute(-31, MP_AUTON_STRAIGHT_SPEED, -180);

		armDumpPositionOpenClaw();
		wait1Msec(500);
		setClawTarget(CLAW_STRAIGHT, false);
	  moveStraightMPAbsolute(24, MP_AUTON_STRAIGHT_SPEED, -180);
		tankTurnGyroMPAbsolute(-1, MP_AUTON_TURN_RATE);
	  setLiftArmTarget(LIFTARM_STAR_LIFT_LOW, true);
//	  moveStraightMP(2, MP_AUTON_STRAIGHT_SPEED);
//	  setLiftArmTarget(LIFTARM_STAR_LIFT_HIGH, true);
	}

}

/////////////////////////////////////////////////////////////////////////////////////////
//
//                                 User Control Task
//
// This task is used to control your robot during the user control phase of a VEX Competition.
//
/////////////////////////////////////////////////////////////////////////////////////////

task usercontrol()
{
	while(true)
  {
		// Drivetrain control inputs
		int driveForwardReverseJoystick = vexRT[Ch3] * 1.0;

		float turnFactor = 0.6;
		if(abs(driveForwardReverseJoystick) < 0.1) {
			turnFactor = 0.4;
		}

		int driveTurnJoystick = (float)vexRT[Ch1] * turnFactor;
		int leftMotorPower = 0;
		int rightMotorPower = 0;

		if (driveForwardReverseJoystick > 0.0) {
			if (driveTurnJoystick > 0.0) {
				rightMotorPower = driveForwardReverseJoystick - driveTurnJoystick;
				leftMotorPower = driveForwardReverseJoystick + driveTurnJoystick;
			}
			else {
				rightMotorPower = driveForwardReverseJoystick - driveTurnJoystick;
				leftMotorPower = driveForwardReverseJoystick + driveTurnJoystick;
			}
		}
		else {
			if (driveTurnJoystick > 0.0) {
				rightMotorPower = driveForwardReverseJoystick - driveTurnJoystick;
				leftMotorPower = driveForwardReverseJoystick + driveTurnJoystick;
			}
			else {
				rightMotorPower = driveForwardReverseJoystick - driveTurnJoystick;
				leftMotorPower = driveForwardReverseJoystick + driveTurnJoystick;
			}
		}

		// Set the drive motor values
		setDriveMotorPower(leftMotorPower, rightMotorPower);

    // Turn on/off PID control of arm
    if(vexRT[Btn8U] == 1)
    {
    	liftArmPIDActive = true;
    	clawPIDActive = true;
    }
    else if(vexRT[Btn8D] == 1)
    {
    	liftArmPIDActive = false;
    	clawPIDActive = false;
    }

    // Set arm position/power
    if(vexRT[Btn6D] == 1)
    {
    	// Pickup position
    	if (liftArmPIDActive) {
    		armPickupPositionOpenClaw();
   		}
    	else {
    		setLiftArmPower(-127);
    	}
		}
    else if(vexRT[Btn6U] == 1)
    {
    	// Dump position
    	if (liftArmPIDActive) {
    		armDumpPositionOpenClaw();
			}
    	else {
    		setLiftArmPower(127);
    	}
		}
    else if(vexRT[Btn5U] == 1)
    {
    	// Hold position
    	if (liftArmPIDActive) {
     		closeClawArmHoldPosition();
    	}
		}
    else if(vexRT[Btn5D] == 1)
    {
    	// Hold position
    	if (liftArmPIDActive) {
     		setClawTarget(CLAW_CLOSE, false);
    	}
		}
    else if(vexRT[Btn7U] == 1)
    {
    	// Climb load position
    	if (liftArmPIDActive) {
    		setLiftArmTarget(LIFTARM_CLIMB_LOAD, false);
			}
    	else {
    		setLiftArmPower(-127);
    	}
		}
    else if(vexRT[Btn7D] == 1)
    {
    	// Climb lift position
    	if (liftArmPIDActive) {
    		setLiftArmTarget(LIFTARM_CLIMB_LIFT, false);
			}
    	else {
    		setLiftArmPower(127);
    	}
		}
		else {
			// No power
    	if (!liftArmPIDActive) {
    		setLiftArmPower(0);
    	}
		}

    // Set claw position/power
    if(vexRT[Btn7L] == 1)
    {
    	if (clawPIDActive) {
    		setClawTarget(CLAW_CLOSE, false);
    	}
    	else {
    		setClawPower(-127);
    	}
		}
    else if(vexRT[Btn7R] == 1)
    {
    	if (clawPIDActive) {
    		setClawTarget(CLAW_OPEN, false);
    	}
    	else {
    		setClawPower(127);
    	}
		}
		else {
    	if (!clawPIDActive) {
    		setClawPower(0);
    	}
		}

		if(vexRT[Btn8L] == 1)
    {
    	moveStraightMP(72, MP_AUTON_STRAIGHT_SPEED);
   		tankTurnGyroMP(180, 150);
    	moveStraightMP(24, MP_AUTON_STRAIGHT_SPEED);
		}
    else if(vexRT[Btn8R] == 1)
    {
    	tankTurnGyroMP(90, MP_AUTON_TURN_RATE);
		}

		if(vexRT[Btn5DXmtr2] == 1)
    {
    	// Hold position
    	if (liftArmPIDActive) {
     		setClawTarget(CLAW_CLOSE, false);
    	}
		}
		else if(vexRT[Btn5UXmtr2] == 1)
    {
    	// Hold position
    	if (liftArmPIDActive) {
     		setClawTarget(CLAW_STRAIGHT, false);
   		}
		}
		else if(vexRT[Btn6DXmtr2] == 1)
    {
    	// Hold position
    	if (liftArmPIDActive) {
		  	setLiftArmTarget(LIFTARM_STAR_LIFT_LOW, true);
   		}
		}
		else if(vexRT[Btn6UXmtr2] == 1)
    {
    	// Hold position
    	if (liftArmPIDActive) {
		  	setLiftArmTarget(LIFTARM_STAR_LIFT_HIGH, true);
   		}
		}
    else if(vexRT[Btn7UXmtr2] == 1)
    {
    	// Climb load position
    	if (liftArmPIDActive) {
    		setLiftArmTarget(LIFTARM_CLIMB_LOAD, false);
			}
		}
    else if(vexRT[Btn7DXmtr2] == 1)
    {
    	// Climb lift position
    	if (liftArmPIDActive) {
    		setLiftArmTarget(LIFTARM_CLIMB_LIFT, false);
			}
		}

		updateDisplay();
		wait1Msec(10);
  }
}
