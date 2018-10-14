/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Robot.h"
#include "GamepadMap.h"
#include "Subsystems\Drivetrain.h"

#include "Commands\CmdDriveWithGamepad.h"


//Drivetrain Constants
const int Drivetrain::LO_GEAR = 0;
const int Drivetrain::HI_GEAR = 1;


Drivetrain::Drivetrain() : Subsystem("Drivetrain") 
{
  std::cout << "In Drivetrain" << std::endl;

  leftMotor         = new frc::Spark(0);
  rightMotor        = new frc::Spark(1);
  differentialDrive = new frc::DifferentialDrive(*leftMotor, *rightMotor);

  rightEncoder      = new frc::Encoder(0, 1, false, frc::Encoder::k4X);
  leftEncoder       = new frc::Encoder(2, 3, false, frc::Encoder::k4X);

//  gearShift         = new frc::DoubleSolenoid(1, 0, 1);

  ahrs                = new AHRS(SPI::Port::kMXP);

}

void Drivetrain::InitDefaultCommand() {
  // Set the default command for a subsystem here.
  // SetDefaultCommand(new MySpecialCommand());
  SetDefaultCommand(new CmdDriveWithGamepad() );
}

// Put methods for controlling this subsystem
// here. Call these from Commands.


#define GP_NULL_ZONE  	0.12

//**************************************************************
void Drivetrain::DriveWithJoystick( void )
{
  double right = Robot::m_oi->DriverGamepad()->GetRawAxis(GAMEPADMAP_AXIS_R_Y);
  double left  = Robot::m_oi->DriverGamepad()->GetRawAxis(GAMEPADMAP_AXIS_L_Y);


	//Check if readings are in null zone..
	if( fabs(right)  < GP_NULL_ZONE )	right = 0.0;
	if( fabs(left )  < GP_NULL_ZONE )	left  = 0.0;

  differentialDrive->TankDrive( left,  right,  true);

}

//**************************************************************
void Drivetrain::Drive( double left, double right )
{
	//Neg=Fwd.   Pos=Rev
	differentialDrive->TankDrive( (-1.0)*left,  (-1.0)*right,  false);

}


//**************************************************************
void Drivetrain::Stop( void )
{
	differentialDrive->TankDrive(0.0, 0.0, false);
  std::cout << "STOP!" << std::endl;
}

//**************************************************************
double Drivetrain::GetRightMotor(void)
{
	return rightMotor->Get();
}
double Drivetrain::GetLeftMotor(void)
{
	return leftMotor->Get();
}



//**************** TRANNY *********************

void Drivetrain::SetLowGear( void )
{
//	gearShift->Set(DoubleSolenoid::kForward);
}
void Drivetrain::SetHighGear( void )
{
//	gearShift->Set(DoubleSolenoid::kReverse);
}

void Drivetrain::SetGear( int gear )
{
	if( gear == LO_GEAR ) SetLowGear();
	if( gear == HI_GEAR ) SetHighGear();
}

bool Drivetrain::IsLowGear(void)
{
	// DoubleSolenoid::Value CurrGear = (gearShift->Get());

	// if( CurrGear == DoubleSolenoid::kForward)
	// 	return true;
	// else
	// 	return false;
  return false;
}


//**************** ENCODERS *********************
int Drivetrain::GetLeftEncoder(void)
{
	return leftEncoder->GetRaw();
}
int Drivetrain::GetRightEncoder(void)
{
	return rightEncoder->GetRaw();
}

void Drivetrain::ResetEncoders(void)
{
	leftEncoder->Reset();
	rightEncoder->Reset();
}



//**************** AHRS (NavX) *********************

bool Drivetrain::IsGyroConnected(void)
{
	return ahrs->IsConnected();
}
double Drivetrain::GetGyroYaw(void)
{
	return (double) ahrs->GetYaw();
}
double Drivetrain::GetGyroRate(void)
{
	return ahrs->GetRate();
}
void Drivetrain::ZeroGyro(void)
{
  std::cout<<"ZeroGyro"<<std::endl;
	ahrs->ZeroYaw();
}

