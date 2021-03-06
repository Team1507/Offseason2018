/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include "Robot.h"
#include "Commands/InstantCommand.h"

class CmdTrannyGearCtrl : public frc::InstantCommand {
public:
  CmdTrannyGearCtrl(int selectedGear);
  void Initialize() override;
private:
  int m_selectedGear;
};
