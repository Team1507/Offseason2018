/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <Commands/Subsystem.h>
#include "WPILib.h"
#include "AHRS.h"

class Drivetrain : public frc::Subsystem {
 private:
  // It's desirable that everything possible under private except
  // for methods that implement subsystem capabilities

  frc::SpeedController    *leftMotor;
  frc::SpeedController    *rightMotor;
  frc::DifferentialDrive  *differentialDrive;

  frc::Encoder            *rightEncoder;
  frc::Encoder            *leftEncoder;

  //frc::DoubleSolenoid     *gearShift;

	AHRS *ahrs;	    //NavX

 public:
  Drivetrain();
  void InitDefaultCommand() override;


  //Constants
  const static int LO_GEAR;
  const static int HI_GEAR;  

  //*****Our Functions******

  //Drive
  void   DriveWithJoystick( void );
  void   Drive( double left, double right );
  void   Stop( void );
  double GetRightMotor(void);
  double GetLeftMotor(void);

  //Tranny
  void SetLowGear( void );
  void SetHighGear( void );
  void SetGear( int gear );
  bool IsLowGear(void);

  //Encoders
	int  GetLeftEncoder(void);
	int  GetRightEncoder(void);
	void ResetEncoders(void);

  //NavX
	bool   IsGyroConnected(void);
	double GetGyroYaw(void);
	double GetGyroRate(void);
	void   ZeroGyro(void);



};
