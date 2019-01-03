
#include "Commands/CmdTurnPIDTest.h"
#include "Robot.h"


CmdTurnPIDTest::CmdTurnPIDTest( int turn_angle ):PIDCommand("DriveTurnPID", 0.0, 0.0, 0.0)
{
    Requires( Robot::m_drivetrain);
    
    //SetTimeout(1.0);
    
    m_angle = turn_angle;
    m_onTargetCount = 0;
    
    // //SetUp Smart Dashboard  
    // SmartDashboard::PutNumber("Turn_kP", 0.0);    
    // SmartDashboard::PutNumber("Turn_kI", 0.0);    
    // SmartDashboard::PutNumber("Turn_kD", 0.0);   
    // SmartDashboard::PutNumber("Turn_Angle", 0.0);   
    
}

void CmdTurnPIDTest::Initialize()
{
    double kP = SmartDashboard::GetNumber("Turn_kP", 0.0);
    double kI = SmartDashboard::GetNumber("Turn_kI", 0.0);
    double kD = SmartDashboard::GetNumber("Turn_kD", 0.0); 
    double kA = SmartDashboard::GetNumber("Turn_Angle", 0.0);


    std::cout << std::fixed << std::setprecision(3);
    std::cout<<"PID:  "<<kP<<" "<<kI<<" "<<kD<<std::endl; 

    //Setup PID
    std::shared_ptr<PIDController> pid = GetPIDController();
    
    pid->Reset();
    pid->Enable();
    pid->SetPID(kP,kI,kD);
    
    pid->SetAbsoluteTolerance(3);       //+/- error 
//	pid->SetInputRange(-180, 180);      //Input Range 
//  pid->SetContinuous(true);     
	pid->SetOutputRange( -0.5, 0.5);    //Max Drive output range

    pid->SetSetpoint(m_angle);    
    
    m_onTargetCount = 0;

}

void CmdTurnPIDTest::Execute() 
{
    //Check for on target
    if( GetPIDController()->OnTarget() )
        m_onTargetCount++;
    else
        m_onTargetCount = 0;

        

}

bool CmdTurnPIDTest::IsFinished() 
{

    return (m_onTargetCount > 5);// || IsTimedOut();
}

void CmdTurnPIDTest::End()
{

	GetPIDController()->Disable();
    //Turn Motors OFF Here
    Robot::m_drivetrain->Stop();
}

void CmdTurnPIDTest::Interrupted()
{
    End();
}



double CmdTurnPIDTest::ReturnPIDInput()
{
    //return Robot::m_drivetrain->GetGyroYaw();
    return Robot::m_drivetrain->GetGyroAngle();
}

void CmdTurnPIDTest::UsePIDOutput(double output)
{
    //Drive Motors here
    Robot::m_drivetrain->Drive(output, -output);
}