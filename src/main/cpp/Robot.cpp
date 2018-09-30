/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Robot.h"

#include <Commands/Scheduler.h>
#include <SmartDashboard/SmartDashboard.h>

//ExampleSubsystem Robot::m_subsystem;
OI *Robot::m_oi;
Drivetrain *Robot::m_drivetrain;


//local function prototypes
void Write2Dashboard(void);


void Robot::RobotInit()
{
  // m_chooser.AddDefault("Default Auto", &m_defaultAuto);
  // m_chooser.AddObject("My Auto", &m_myAuto);
  // frc::SmartDashboard::PutData("Auto Modes", &m_chooser);

  //Subsystem Inits
  m_drivetrain = new Drivetrain();

  //OI **MUST** be after all subsystem Inits
  m_oi = new OI();

	//******** INIT *************************************
  std::cout<<"RobotInit"<<std::endl;
	std::cout<<"PracticeBot2018"<<std::endl;

	//Display Version info to Log file, for posterity
	std::cout<<"Version: " << __DATE__ <<"  "<<__TIME__<<std::endl<<std::endl;


  //Init Auto 


  //Init Subsystems

}

/**
 * This function is called every robot packet, no matter the mode. Use
 * this for items like diagnostics that you want ran during disabled,
 * autonomous, teleoperated and test.
 *
 * <p> This runs after the mode specific periodic functions, but before
 * LiveWindow and SmartDashboard integrated updating.
 */
void Robot::RobotPeriodic() 
{
  Write2Dashboard();
}

/**
 * This function is called once each time the robot enters Disabled mode. You
 * can use it to reset any subsystem information you want to clear when the
 * robot is disabled.
 */
void Robot::DisabledInit() 
{
  std::cout<<"DisabledInit"<<std::endl;

  m_drivetrain->Stop();

}

void Robot::DisabledPeriodic() { frc::Scheduler::GetInstance()->Run(); }

/**
 * This autonomous (along with the chooser code above) shows how to select
 * between different autonomous modes using the dashboard. The sendable chooser
 * code works with the Java SmartDashboard. If you prefer the LabVIEW Dashboard,
 * remove all of the chooser code and uncomment the GetString code to get the
 * auto name from the text box below the Gyro.
 *
 * You can add additional auto modes by adding additional commands to the
 * chooser code above (like the commented example) or additional comparisons to
 * the if-else structure below with additional strings & commands.
 */
void Robot::AutonomousInit() {
  // std::string autoSelected = frc::SmartDashboard::GetString(
  //     "Auto Selector", "Default");
  // if (autoSelected == "My Auto") {
  //   m_autonomousCommand = &m_myAuto;
  // } else {
  //   m_autonomousCommand = &m_defaultAuto;
  // }
	std::cout<<"AutonomousInit"<<std::endl;

  m_autonomousCommand = m_chooser.GetSelected();

  if (m_autonomousCommand != nullptr) {
    m_autonomousCommand->Start();
  }
}

void Robot::AutonomousPeriodic() { frc::Scheduler::GetInstance()->Run(); }

void Robot::TeleopInit() {
  // This makes sure that the autonomous stops running when
  // teleop starts running. If you want the autonomous to
  // continue until interrupted by another command, remove
  // this line or comment it out.


  std::cout<<"TeleopInit"<<std::endl;

  if (m_autonomousCommand != nullptr) {
    m_autonomousCommand->Cancel();
    m_autonomousCommand = nullptr;
  }
}

void Robot::TeleopPeriodic() 
{ 
  frc::Scheduler::GetInstance()->Run();

  Robot::m_drivetrain->DriveWithJoystick();

}

void Robot::TestPeriodic() 
{
  
}

#ifndef RUNNING_FRC_TESTS
START_ROBOT_CLASS(Robot)
#endif


void Write2Dashboard(void)
{

  // //Either Robot::m_oi.getGamePad  *or*  Robot::oi->getGamepad()
  // SmartDashboard::PutNumber("L X",  Robot::m_oi->getGamepad()->GetRawAxis(0)   );
  // SmartDashboard::PutNumber("L Y",  Robot::m_oi->getGamepad()->GetRawAxis(1)   );
  // SmartDashboard::PutNumber("R X",  Robot::m_oi->getGamepad()->GetRawAxis(4)   );
  // SmartDashboard::PutNumber("R Y",  Robot::m_oi->getGamepad()->GetRawAxis(5)   );

  // SmartDashboard::PutBoolean("A Button",  Robot::m_oi->getGamepad()->GetRawButton(1)  );
  // SmartDashboard::PutBoolean("B Button",  Robot::m_oi->getGamepad()->GetRawButton(2)  );
  // SmartDashboard::PutBoolean("X Button",  Robot::m_oi->getGamepad()->GetRawButton(3)  );
  // SmartDashboard::PutBoolean("Y Button",  Robot::m_oi->getGamepad()->GetRawButton(4)  );

  // SmartDashboard::PutNumber("LR",  Robot::m_gimble->GetLRservo()  );
  // SmartDashboard::PutNumber("UD",  Robot::m_gimble->GetUDservo()  );

  // SmartDashboard::PutNumber("Motor",  Robot::m_motor->GetMotor()  );

  SmartDashboard::PutNumber("L_Motor",  Robot::m_drivetrain->GetLeftMotor()  );
  SmartDashboard::PutNumber("R_Motor",  Robot::m_drivetrain->GetRightMotor()  );

  SmartDashboard::PutNumber("D_L_Y_axis",  Robot::m_oi->DriverGamepad()->GetRawAxis(1)  );
  SmartDashboard::PutNumber("D_R_Y_axis",  Robot::m_oi->DriverGamepad()->GetRawAxis(5)  );
  SmartDashboard::PutNumber("D_L_X_axis",  Robot::m_oi->DriverGamepad()->GetRawAxis(0)  );
  SmartDashboard::PutNumber("D_R_X_axis",  Robot::m_oi->DriverGamepad()->GetRawAxis(4)  );

}