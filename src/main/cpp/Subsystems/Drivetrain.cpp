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
const int Drivetrain::ENC_TICKS_PER_INCH = 42;


Drivetrain::Drivetrain() : Subsystem("Drivetrain") 
{
	std::cout << "In Drivetrain" << std::endl;

	leftMotor         = new frc::Spark(0);
	rightMotor        = new frc::Spark(1);
	differentialDrive = new frc::DifferentialDrive(*leftMotor, *rightMotor);

	rightEncoder      = new frc::Encoder(0, 1, false, frc::Encoder::k4X);
	leftEncoder       = new frc::Encoder(2, 3, false, frc::Encoder::k4X);

	gearShift         = new frc::DoubleSolenoid(1, 0, 1);

	ahrs            	= new AHRS(SPI::Port::kMXP);

	//acceleration test
	acc_curr_l = 0;
	acc_curr_r = 0;

	//Tyler Mode
	tyler_mode_enable = false;


	//Disable Motor Saftey
	//Not a good idea, but required for GrpTest -> WaitCommand() 
	differentialDrive->SetSafetyEnabled(false);

}

void Drivetrain::InitDefaultCommand() {
  // Set the default command for a subsystem here.
  // SetDefaultCommand(new MySpecialCommand());
  SetDefaultCommand(new CmdDriveWithGamepad() );
}

// Put methods for controlling this subsystem
// here. Call these from Commands.


#define GP_NULL_ZONE  	0.08
//#define DRIVE_MULT			0.5		//Half power for concrete
#define DRIVE_MULT				0.75	//Max Adult Allowed Drive power on Carpet

//**************************************************************
void Drivetrain::DriveWithJoystick( void )
{
    double r_y = Robot::m_oi->DriverGamepad()->GetRawAxis(GAMEPADMAP_AXIS_R_Y);
    double r_x = Robot::m_oi->DriverGamepad()->GetRawAxis(GAMEPADMAP_AXIS_R_X); 
	double l_y = Robot::m_oi->DriverGamepad()->GetRawAxis(GAMEPADMAP_AXIS_L_Y);
    double l_x = Robot::m_oi->DriverGamepad()->GetRawAxis(GAMEPADMAP_AXIS_L_X);

	double rTrig = Robot::m_oi->DriverGamepad()->GetRawAxis(GAMEPADMAP_AXIS_R_TRIG);
	double lTrig = Robot::m_oi->DriverGamepad()->GetRawAxis(GAMEPADMAP_AXIS_L_TRIG);

	//Check if readings are in null zone..
	if( fabs(r_y)  < GP_NULL_ZONE )	r_y = 0.0;
	if( fabs(r_x)  < GP_NULL_ZONE )	r_x = 0.0;
	if( fabs(l_y)  < GP_NULL_ZONE )	l_y = 0.0;
	if( fabs(l_x)  < GP_NULL_ZONE )	l_x = 0.0;


	if( tyler_mode_enable )
	{
		//Arcade Drive
		l_y *= DRIVE_MULT;	//Reduce drive power
		r_x *= DRIVE_MULT;
		//ly=fwd/rev   rx=(inverted)Rotate
		differentialDrive->ArcadeDrive(l_y,(-1.0)*r_x,true);
	}
	else
	{
		//DEFAULT TANK DRIVE
	
		//Check for Drive Straight
		if( lTrig > 0.5)
		{
			//Drive Straight
			//differentialDrive->TankDrive( l_y ,  r_y ,  true);													//True for sraight power
			differentialDrive->TankDrive( r_y * DRIVE_MULT,  r_y * DRIVE_MULT,  false);	//False for reduced power
		}
		else
		{
			//Normal Driving
			//differentialDrive->TankDrive( l_y ,  r_y ,  true);													//True for sraight power
			differentialDrive->TankDrive( l_y * DRIVE_MULT,  r_y * DRIVE_MULT,  false);	//False for reduced power
		}
	}


}

//**************************************************************
void Drivetrain::Drive( double left, double right )
{
	//Neg=Fwd.   Pos=Rev
	differentialDrive->TankDrive( (-1.0)*DRIVE_MULT*left,  (-1.0)*DRIVE_MULT*right,  false);

}

//**************************************************************
void Drivetrain::DriveAcc( double left, double right )
{
	const double ACC_ADDER = 0.05;			//roughly 1/25  ~~ about half second acc
	//const double ACC_ADDER = 0.01;		//roughly 1/100  ~~ about 2 second acc

	bool l_neg = (left < 0);
	bool r_neg = (right < 0);

	double abs_l = fabs(left);
	double abs_r = fabs(right);

	double f_l = 0;
	double f_r = 0;


	//*** LEFT ***
	if( abs_l < acc_curr_l )	
	{
		//Power Decreased - immediate match lower power
		f_l = abs_l;
		acc_curr_l = abs_l;
	}
	else if( abs_l > acc_curr_l )
	{
		//current is less than requested.  Add power
		acc_curr_l += ACC_ADDER;
		f_l = acc_curr_l;
	}
	else
	{
		//power is equal to current
		f_l = abs_l;
	}

	//*** RIGHT ***
	if( abs_r < acc_curr_r )	
	{
		//Power Decreased - immediate match lower power
		f_r = abs_r;
		acc_curr_r = abs_r;
	}
	else if( abs_r > acc_curr_r )
	{
		//current is less than requested.  Add power
		acc_curr_r += ACC_ADDER;
		f_r = acc_curr_r;
	}
	else
	{
		//power is equal to current
		f_r = abs_r;
	}


	//Adjust for direction
	if(  l_neg ) f_l *= (-1.0);
	if(  r_neg ) f_r *= (-1.0);


	//Neg=Fwd.   Pos=Rev
	differentialDrive->TankDrive( (-1.0)*DRIVE_MULT*f_l,  (-1.0)*DRIVE_MULT*f_r,  false);

}

//**************************************************************
void Drivetrain::Stop( void )
{
	differentialDrive->TankDrive(0.0, 0.0, false);
  	std::cout << "STOP!" << std::endl;

	acc_curr_l = 0;
  	acc_curr_r = 0;
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
	gearShift->Set(DoubleSolenoid::kForward);
	std::cout << "LowGear" << std::endl;
}
void Drivetrain::SetHighGear( void )
{
	gearShift->Set(DoubleSolenoid::kReverse);
	std::cout << "HighGear" << std::endl;
}

void Drivetrain::SetGear( int gear )
{
	if( gear == LO_GEAR ) SetLowGear();
	if( gear == HI_GEAR ) SetHighGear();
}

bool Drivetrain::IsLowGear(void)
{
	DoubleSolenoid::Value CurrGear = (gearShift->Get());

	if( CurrGear == DoubleSolenoid::kForward)
		return true;
	else
		return false;
  return false;
}


//**************** ENCODERS *********************
int Drivetrain::GetLeftEncoder(void)
{
	//return leftEncoder->GetRaw();
	//We only have 1 encoder and it's mounted on the right.  Use the right encoder
	return rightEncoder->GetRaw();
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
	//**OR
	//ahrs->Reset();//????
}

//**************** Tyler Drive Mode *********************
void Drivetrain::SetTylerMode(bool enable)
{
	tyler_mode_enable = enable;
}
bool Drivetrain::GetTylerMode(void)
{
	return tyler_mode_enable;
}