/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Robot.h"
#include "GamepadMap.h"

#include <Commands/Scheduler.h>
#include <SmartDashboard/SmartDashboard.h>

#include <fstream>
#include <string>
#include <ctime>
#include <iomanip>      // std::setprecision

//ExampleSubsystem Robot::m_subsystem;
OI *Robot::m_oi;
Drivetrain *Robot::m_drivetrain;
frc::Timer *Robot::m_timer;



//local function prototypes
void Write2Dashboard(void);
void LogFileOpen(void);
void LogFileClose(void);
void LogFileWrite(void);

//LogFiles
static std::ofstream logfile;		//Defined here - not a member of Robot::

bool Robot::log_enable;
int  Robot::log_marker;

void Robot::RobotInit()
{
  // m_chooser.AddDefault("Default Auto", &m_defaultAuto);
  // m_chooser.AddObject("My Auto", &m_myAuto);
  // frc::SmartDashboard::PutData("Auto Modes", &m_chooser);

  //Subsystem Inits
  m_drivetrain = new Drivetrain();

  //OI **MUST** be after all subsystem Inits
  m_oi = new OI();

  m_timer = new frc::Timer();

	//******** INIT *************************************
    std::cout<<"RobotInit"<<std::endl;
	std::cout<<"PracticeBot2018"<<std::endl;

	//Display Version info to Log file, for posterity
	std::cout<<"Version: " << __DATE__ <<"  "<<__TIME__<<std::endl<<std::endl;


  //Init Auto 


  //Init Subsystems
  m_drivetrain->ResetEncoders();
  m_drivetrain->SetGear( Drivetrain::HI_GEAR );

  log_enable = false;
  log_marker = 0;

  //I don't think this works.  It may be too early and not talking to NavX yet
  //m_drivetrain->ZeroGyro();   

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
  LogFileWrite();

  m_drivetrain->DrivePeriodic();
}

/**
 * This function is called once each time the robot enters Disabled mode. You
 * can use it to reset any subsystem information you want to clear when the
 * robot is disabled.
 */
void Robot::DisabledInit() 
{
	std::cout<<"DisabledInit"<<std::endl;

  	LogFileClose();
    log_enable = false;

  	m_drivetrain->Stop();
  	m_timer->Stop();

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

    m_timer->Reset();
    m_timer->Start();

    if (m_autonomousCommand != nullptr) {
        m_autonomousCommand->Cancel();
        m_autonomousCommand = nullptr;
    }
}

void Robot::TeleopPeriodic() 
{ 

    //I don't like this here.  There has to be a better way!
    if( log_enable && !logfile.is_open() )
        LogFileOpen();
    if( !log_enable && logfile.is_open() )
        LogFileClose();        


    frc::Scheduler::GetInstance()->Run();
}

void Robot::TestPeriodic() 
{
  
}

#ifndef RUNNING_FRC_TESTS
START_ROBOT_CLASS(Robot)
#endif


void Write2Dashboard(void)
{

  SmartDashboard::PutNumber("L_Motor",  Robot::m_drivetrain->GetLeftMotor()  );
  SmartDashboard::PutNumber("R_Motor",  Robot::m_drivetrain->GetRightMotor()  );

  SmartDashboard::PutNumber("D_L_Y_axis",  Robot::m_oi->DriverGamepad()->GetRawAxis(GAMEPADMAP_AXIS_L_Y)  );
  SmartDashboard::PutNumber("D_R_Y_axis",  Robot::m_oi->DriverGamepad()->GetRawAxis(GAMEPADMAP_AXIS_R_Y)  );
  SmartDashboard::PutNumber("D_L_X_axis",  Robot::m_oi->DriverGamepad()->GetRawAxis(GAMEPADMAP_AXIS_L_X)  );
  SmartDashboard::PutNumber("D_R_X_axis",  Robot::m_oi->DriverGamepad()->GetRawAxis(GAMEPADMAP_AXIS_R_X)  );

  SmartDashboard::PutNumber("D_L_Trig",    Robot::m_oi->DriverGamepad()->GetRawAxis(GAMEPADMAP_AXIS_L_TRIG)  );
  SmartDashboard::PutNumber("D_R_Trig",    Robot::m_oi->DriverGamepad()->GetRawAxis(GAMEPADMAP_AXIS_R_TRIG)  );


	SmartDashboard::PutNumber("LeftEnc",    Robot::m_drivetrain->GetLeftEncoder());
	SmartDashboard::PutNumber("RightEnc",   Robot::m_drivetrain->GetRightEncoder());  
	SmartDashboard::PutNumber("LeftEncVel", Robot::m_drivetrain->GetLeftEncVel());
	SmartDashboard::PutNumber("RightEncVel",Robot::m_drivetrain->GetRightEncVel());  

	SmartDashboard::PutBoolean("navx_IsConn", Robot::m_drivetrain->IsGyroConnected() );
	SmartDashboard::PutNumber("navx_Yaw",     Robot::m_drivetrain->GetGyroYaw() );
   	SmartDashboard::PutNumber("navx_Angle",   Robot::m_drivetrain->GetGyroAngle() );
 
  SmartDashboard::PutNumber("navx_Rate",    Robot::m_drivetrain->GetGyroRate() );

	SmartDashboard::PutBoolean("TylerModeFlag", Robot::m_drivetrain->GetTylerMode() );
    SmartDashboard::PutBoolean("Log Enabled", Robot::log_enable );

  //Time
  //SmartDashboard::PutNumber("FPGATime1",  GetFPGATime() );                      //us
  SmartDashboard::PutNumber("FPGATime2",  Robot::m_timer->GetFPGATimestamp() );   //sec
  SmartDashboard::PutNumber("Timer",      Robot::m_timer->Get() );                //sec

}

//*********** LOG File Handlers **************************
#define LOGFILEDIRNAME "/media/sda1/"
void LogFileOpen(void)
{
    std::string filename;
    char tbuf[100];

    //Get current time and format into a filename -> mmdd_HHMMSS
    std::time_t time = std::time(0); 
    std::tm*    ts   = std::localtime(&time);
    strftime(tbuf, sizeof(tbuf), "%m%d_%H%M%S", ts);

    //Generate path and filename into a string
    filename  = LOGFILEDIRNAME;     //Start with directory
    filename += tbuf;               //Add time file name
    filename += ".csv";             //Add CSV as the extention

    //Finally, open the file
	logfile.open(filename, std::ios::out | std::ios::trunc );

	if( logfile.is_open() )
    {
        std::cout<<"LogFile Opened: " << tbuf <<std::endl;
        //Write header
        logfile << "Time "      << ","; // 1:  ms since start
        logfile << "Mode"       << ","; // 2:  mode
        logfile << "Marker"     << ","; // 3:  log marker
        logfile << "Yaw"        << ","; // 4:  Yaw
        logfile << "LMotor"     << ","; // 5:  LeftMotor
        logfile << "RMotor"     << ","; // 6:  RightMotor
        logfile << "LEnc"       << ","; // 7:  Left Encoder
        logfile << "REnc"       << ","; // 8:  Right Encoder
        logfile << "LEncV"      << ","; // 9:  Left Encoder Velocity
        logfile << "REncV"      << ","; // 10: Right Encoder Velocity


        //Must be last
        logfile << "\n";
    }     
	else
        std::cout<<"*** Could NOT Open Logfile!!!!"<<std::endl;
		
}
void LogFileClose(void)
{
    if( logfile.is_open() )
    {
		logfile.close();
        std::cout<<"LogFile Closed"<<std::endl;
    }
}
void LogFileWrite(void)
{
    if( !logfile.is_open() ) return;


    logfile << std::fixed << std::setprecision(3);

    logfile << Robot::m_timer->Get()                    << ","; // 1:  ms since start
    logfile << 0                                        << ","; // 2:  mode
    if(Robot::log_marker>0)logfile << Robot::log_marker << ","; // 3:  With debug marker
    else                   logfile                      << ","; // 3:  No debug marker (blank)
    logfile << Robot::m_drivetrain->GetGyroAngle()      << ","; // 4:  Yaw
    logfile << Robot::m_drivetrain->GetLeftMotor()      << ","; // 5:  LeftMotor
    logfile << Robot::m_drivetrain->GetRightMotor()     << ","; // 6:  RightMotor
    logfile << Robot::m_drivetrain->GetLeftEncoder()    << ","; // 7:  Left Encoder
    logfile << Robot::m_drivetrain->GetRightEncoder()   << ","; // 8:  Right Encoder
    logfile << Robot::m_drivetrain->GetLeftEncVel()     << ","; // 9:  Left Encoder Velocity
    logfile << Robot::m_drivetrain->GetRightEncVel()    << ","; // 10: Right Encoder Velocity

    //Write Debug Log Markers to screen
    if( Robot::log_marker>0 )
        std::cout<<"LogMarker: "<< Robot::log_marker <<std::endl;

    //Must be last
    Robot::log_marker = 0;
    logfile << "\n";
}
