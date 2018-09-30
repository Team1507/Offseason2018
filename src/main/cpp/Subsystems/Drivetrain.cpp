/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Robot.h"
#include "Subsystems\Drivetrain.h"

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
}

// Put methods for controlling this subsystem
// here. Call these from Commands.



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