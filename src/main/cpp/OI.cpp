/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "OI.h"
#include "Robot.h"
#include <WPILib.h>

#include "Commands\CmdTrannyGearCtrl.h"

OI::OI() {
  // Process operator interface input here.

  std::cout<<"In OI"<<std::endl;

  //Init Gamepads
  driver_gamepad   = new frc::Joystick(0);
//operator_gamepad = new frc::Joystick(1);

  //Define Driver Button Commands
    //A_Button = new frc::JoystickButton( gamepad, 1);
    //A_Button->WhenPressed(new CmdPrintText("A Button"));

  //Define Operator Button Commands


  //Smartdashboard Commands Buttons
  frc::SmartDashboard::PutData("CmdGearControl: LO_GEAR", new CmdTrannyGearCtrl(Drivetrain::LO_GEAR));
  frc::SmartDashboard::PutData("CmdGearControl: HI_GEAR", new CmdTrannyGearCtrl(Drivetrain::HI_GEAR));


}


//Public Gamepad Access
frc::Joystick* OI::DriverGamepad() {
   return driver_gamepad;
}
// frc::Joystick* OI::OperatorGamepad() {
//    return operrator_gamepad;
// }
