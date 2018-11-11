/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Commands/CmdLogEnable.h"
#include "Robot.h"

CmdLogEnable::CmdLogEnable(bool enable) {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
  m_enable = enable;
}

// Called just before this Command runs the first time
void CmdLogEnable::Initialize() 
{
  Robot::log_enable = m_enable;
}

// Called repeatedly when this Command is scheduled to run
void CmdLogEnable::Execute() {}

// Make this return true when this Command no longer needs to run execute()
bool CmdLogEnable::IsFinished() { return true; }

// Called once after isFinished returns true
void CmdLogEnable::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CmdLogEnable::Interrupted() {}
