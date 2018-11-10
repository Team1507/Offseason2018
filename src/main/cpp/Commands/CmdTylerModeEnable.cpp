/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Commands/CmdTylerModeEnable.h"
#include "Robot.h"

CmdTylerModeEnable::CmdTylerModeEnable() {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
}

// Called just before this Command runs the first time
void CmdTylerModeEnable::Initialize() 
{
  Robot::m_drivetrain->SetTylerMode(true);
  std::cout<<"Tyler Drive Mode ENABLE"<<std::endl;
}

// Called repeatedly when this Command is scheduled to run
void CmdTylerModeEnable::Execute() {}

// Make this return true when this Command no longer needs to run execute()
bool CmdTylerModeEnable::IsFinished() 
{
  //This is a "WHILE PRESSED" command, so always return false 
  return false; 
}

// Called once after isFinished returns true
void CmdTylerModeEnable::End() 
{
  Robot::m_drivetrain->SetTylerMode(false);
  std::cout<<"Tyler Drive Mode OFF"<<std::endl;
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CmdTylerModeEnable::Interrupted() 
{
  End();
}
