/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Commands\CmdDriveFwdGyro.h"
#include "Robot.h"

CmdDriveFwdGyro::CmdDriveFwdGyro(double power, double heading, double distance, bool stop, double timeout)
{
  m_power    = power;
	m_heading  = heading;
  m_distance = distance;
  m_stop     = stop;
  m_timeout  = timeout;

  // Use Requires() here to declare subsystem dependencies
  Requires( Robot::m_drivetrain);
}

// Called just before this Command runs the first time
void CmdDriveFwdGyro::Initialize() 
{
  Robot::m_drivetrain->ResetEncoders();

	if( m_timeout > 0.0)
	{
		SetTimeout (m_timeout);
	}

}

// Called repeatedly when this Command is scheduled to run
void CmdDriveFwdGyro::Execute() 
{
	double errorAngle = Robot::m_drivetrain->GetGyroYaw() - m_heading;
	double kp = 0.075;


	//Robot::m_drivetrain->Drive(m_power - errorAngle*kp  ,  m_power + errorAngle*kp ); 
	Robot::m_drivetrain->DriveAcc(m_power - errorAngle*kp  ,  m_power + errorAngle*kp ); 
}

// Make this return true when this Command no longer needs to run execute()
bool CmdDriveFwdGyro::IsFinished() 
{

	double l_dir = Robot::m_drivetrain->GetLeftEncoder()/Drivetrain::ENC_TICKS_PER_INCH;
	double r_dir = Robot::m_drivetrain->GetRightEncoder()/Drivetrain::ENC_TICKS_PER_INCH;

	if(  (l_dir > m_distance) || (r_dir > m_distance)  )
	  return true;

	if ((m_timeout>0.0) && IsTimedOut())
	{
		std::cout<<"CmdDriveFwdGyro: Timeout"<<std::endl;
		return true;
	}

	return false;
}

// Called once after isFinished returns true
void CmdDriveFwdGyro::End() 
{
  if(m_stop)
	{
		Robot::m_drivetrain->Stop();
	}
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CmdDriveFwdGyro::Interrupted() 
{
  End();
}
