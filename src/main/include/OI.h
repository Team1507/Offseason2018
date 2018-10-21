/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once
#include "WPILib.h"

class OI {


private:
  frc::Joystick *driver_gamepad;
//frc::Joystick *operator_gamepad;

  frc::JoystickButton *m_driver_lbump;
  frc::JoystickButton *m_driver_rbump;

public:
  OI();


  frc::Joystick *DriverGamepad();
//frc::Joystick *OperatorGamepad();
};
