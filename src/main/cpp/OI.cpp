/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "OI.h"
#include "Robot.h"
#include <WPILib.h>

#include "GamepadMap.h"
#include "Commands/CmdTrannyGearCtrl.h"
#include "Commands/CmdDriveClearAll.h"
#include "Commands/CmdTylerModeEnable.h"
#include "Commands/CmdLogEnable.h"

#include "Commands/GrpTest.h"
#include "Commands/GrpTest2.h"
#include "Commands/CmdTurnPIDTest.h"

OI::OI() {
  // Process operator interface input here.

  std::cout<<"In OI"<<std::endl;

  //Init Gamepads
  driver_gamepad   = new frc::Joystick(0);
//operator_gamepad = new frc::Joystick(1);

  //Define Driver Button Commands
  m_driver_lbump = new frc::JoystickButton( driver_gamepad, GAMEPADMAP_BUTTON_LBUMP);
  m_driver_lbump->WhenPressed( new CmdTrannyGearCtrl( Drivetrain::LO_GEAR) );

  m_driver_rbump = new frc::JoystickButton( driver_gamepad, GAMEPADMAP_BUTTON_RBUMP);
  m_driver_rbump->WhenPressed( new CmdTrannyGearCtrl( Drivetrain::HI_GEAR) );

    //A_Button = new frc::JoystickButton( gamepad, 1);
    //A_Button->WhenPressed(new CmdPrintText("A Button"));

  //Define Operator Button Commands


  //Smartdashboard Commands Buttons
  frc::SmartDashboard::PutData("CmdGearControl: LO_GEAR", new CmdTrannyGearCtrl(Drivetrain::LO_GEAR));
  frc::SmartDashboard::PutData("CmdGearControl: HI_GEAR", new CmdTrannyGearCtrl(Drivetrain::HI_GEAR));

  frc::SmartDashboard::PutData("GrpTest Command", new GrpTest() );
  frc::SmartDashboard::PutData("GrpTest2 Command", new GrpTest2() );
  
  frc::SmartDashboard::PutData("CmdTurnPIDTest Command", new CmdTurnPIDTest() );
 
  frc::SmartDashboard::PutData("Drive Clear All", new CmdDriveClearAll() );

  frc::SmartDashboard::PutData("TylerModeEnable", new CmdTylerModeEnable() );

  frc::SmartDashboard::PutData("Enable Logger", new CmdLogEnable(true) );
}


//Public Gamepad Access
frc::Joystick* OI::DriverGamepad() {
   return driver_gamepad;
}
// frc::Joystick* OI::OperatorGamepad() {
//    return operrator_gamepad;
// }
