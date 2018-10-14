/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Commands\CmdTrannyGearCtrl.h"

CmdTrannyGearCtrl::CmdTrannyGearCtrl(int selectedGear) {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());

  m_selectedGear = selectedGear;
}

// Called once when the command executes
void CmdTrannyGearCtrl::Initialize() 
{
  Robot::m_drivetrain->SetGear(m_selectedGear);
}
