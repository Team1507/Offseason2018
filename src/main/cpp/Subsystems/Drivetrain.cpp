/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Robot.h"
#include "Subsystems\Drivetrain.h"

#include "Commands\CmdDriveWithGamepad.h"

Drivetrain::Drivetrain() : Subsystem("Drivetrain") 
{
  std::cout << "In Drivetrain" << std::endl;

  leftMotor         = new frc::Spark(0);
  rightMotor        = new frc::Spark(1);
  differentialDrive = new frc::DifferentialDrive(*leftMotor, *rightMotor);

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
  double right = Robot::m_oi->DriverGamepad()->GetRawAxis(5);
  double left  = Robot::m_oi->DriverGamepad()->GetRawAxis(1);


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