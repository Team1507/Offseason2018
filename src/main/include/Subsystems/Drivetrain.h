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

  frc::DoubleSolenoid     *gearShift;

	AHRS *ahrs;	    //NavX

  double acc_curr_l;
  double acc_curr_r;
  bool   tyler_mode_enable;

  //Encoder Velocity
  int    prev_l_enc;
  int    prev_r_enc;
  int    delta_l_enc;
  int    delta_r_enc;


 public:
  Drivetrain();
  void InitDefaultCommand() override;


  //Constants
  const static int LO_GEAR;
  const static int HI_GEAR;  
  const static int ENC_TICKS_PER_INCH;

  //*****Our Functions******

  //Periodic
  void   DrivePeriodic(void);

  //Drive
  void   DriveWithJoystick( void );
  void   Drive( double left, double right );
  void   DriveAcc( double left, double right );
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
    int  GetLeftEncVel(void);
    int  GetRightEncVel(void);
    


  //NavX
	bool   IsGyroConnected(void);
	double GetGyroYaw(void);            //yaw: Relative -180 to +180
	double GetGyroAngle(void);          //angle: absolute -inf to +inf
	double GetGyroRate(void);
	void   ZeroGyro(void);

  //Tyler Drive Mode
  void SetTylerMode(bool);
  bool GetTylerMode(void);


};
