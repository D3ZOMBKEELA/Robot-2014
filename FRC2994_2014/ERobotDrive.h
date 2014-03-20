/*----------------------------------------------------------------------------*/
/* Copyright (c) FIRST 2008. All Rights Reserved.							  */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in $(WIND_BASE)/WPILib.  */
/*----------------------------------------------------------------------------*/

#ifndef EROBOTDRIVE_H_
#define EROBOTDRIVE_H_

#include "ErrorBase.h"
#include <stdlib.h>
#include <vxWorks.h>
#include "MotorSafety.h"
#include "MotorSafetyHelper.h"

class SpeedController;
class GenericHID;

/**
 * Utility class for handling Robot drive based on a definition of the motor configuration.
 * The robot drive class handles basic driving for a robot. Currently, 2 and 4 motor standard
 * drive trains are supported. In the future other drive types like swerve and meccanum might
 * be implemented. Motor channel numbers are passed supplied on creation of the class. Those are
 * used for either the Drive function (intended for hand created drive code, such as autonomous)
 * or with the Tank/Arcade functions intended to be used for Operator Control driving.
 */
class ERobotDrive: public MotorSafety, public ErrorBase
{
public:
	typedef enum
	{
		kFrontLeftMotor,
		kFrontRightMotor,
		kRearLeftMotor,
		kRearRightMotor,
		kCenterLeftMotor,
		kCenterRightMotor
	} MotorType;

	ERobotDrive(SpeedController &frontLeftMotor, SpeedController &rearLeftMotor, SpeedController &centerLeftMotor, SpeedController &centerRightMotor,
				SpeedController &frontRightMotor, SpeedController &rearRightMotor);

	virtual ~ERobotDrive();

	void Drive(float outputMagnitude, float curve);
	void ArcadeDrive(GenericHID *stick, bool squaredInputs = true);
	void ArcadeDrive(GenericHID &stick, bool squaredInputs = true);
	void ArcadeDrive(GenericHID *moveStick, uint32_t moveChannel, GenericHID *rotateStick, uint32_t rotateChannel, bool squaredInputs = true);
	void ArcadeDrive(GenericHID &moveStick, uint32_t moveChannel, GenericHID &rotateStick, uint32_t rotateChannel, bool squaredInputs = true);
	void ArcadeDrive(float moveValue, float rotateValue, bool squaredInputs = true);
	virtual void SetLeftRightMotorOutputs(float leftOutput, float rightOutput);
	void SetInvertedMotor(MotorType motor, bool isInverted);
	void SetSensitivity(float sensitivity);
	void SetMaxOutput(double maxOutput);

	void SetExpiration(float timeout);
	float GetExpiration();
	bool IsAlive();
	void StopMotor();
	bool IsSafetyEnabled();
	void SetSafetyEnabled(bool enabled);
	void GetDescription(char *desc);

protected:
	void InitRobotDrive();
	float Limit(float num);
	void Normalize(double *wheelSpeeds);
	void RotateVector(double &x, double &y, double angle);

	static const int32_t kMaxNumberOfMotors = 6;

	int32_t m_invertedMotors[kMaxNumberOfMotors];
	float m_sensitivity;
	double m_maxOutput;
	bool m_deleteSpeedControllers;
	SpeedController *m_frontLeftMotor;
	SpeedController *m_centerLeftMotor;
	SpeedController *m_frontRightMotor;
	SpeedController *m_rearLeftMotor;
	SpeedController *m_centerRightMotor;
	SpeedController *m_rearRightMotor;
	MotorSafetyHelper *m_safetyHelper;
	
private:
	int32_t GetNumMotors()
	{
		int motors = 0;
		if (m_frontLeftMotor) motors++;
		if (m_frontRightMotor) motors++;
		if (m_rearLeftMotor) motors++;
		if (m_rearRightMotor) motors++;
		if (m_centerRightMotor) motors++;
		if (m_centerLeftMotor) motors++;
		return motors;
	}
	DISALLOW_COPY_AND_ASSIGN(ERobotDrive);
};

#endif

