/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Commands/GrpTest.h"
#include "Commands/CmdPrintAutoText.h"
#include "Commands/CmdDriveFwdEncoder.h"
#include "Commands/CmdDriveRevEncoder.h"
#include "Commands/CmdDriveFwdGyro.h"
#include "Commands/CmdDriveRevGyro.h"

#include "Commands/CmdDriveClearAll.h"

GrpTest::GrpTest() 
{
    AddSequential(new CmdPrintAutoText("GrpTest Begin"));
    AddSequential(new CmdDriveClearAll());
    AddSequential(new WaitCommand(0.25));
    //***************************************************

    AddSequential(new CmdDriveFwdGyro(1.0, 0.0,  40, true, 0) );
    AddSequential(new WaitCommand(2.0));

    AddSequential(new CmdDriveRevGyro(1.0, 0.0,  40, true, 0) );  
    AddSequential(new WaitCommand(2.0));  

    
    AddSequential(new CmdDriveFwdGyro(1.0, 0.0,  40, true, 0) );
    AddSequential(new WaitCommand(2.0));

    AddSequential(new CmdDriveRevGyro(1.0, 0.0,  40, true, 0) );  
    AddSequential(new WaitCommand(2.0));  

    // AddSequential(new CmdDriveFwdEncoder(1.0, 40, true, 0) );
    // AddSequential(new WaitCommand(2.0));
    // AddSequential(new CmdDriveRevEncoder(1.0, 40, true, 0) );
    // AddSequential(new WaitCommand(2.0));
    // //*********
    // AddSequential(new CmdDriveFwdEncoder(1.0, 40, true, 0) );
    // AddSequential(new WaitCommand(2.0));
    // AddSequential(new CmdDriveRevEncoder(1.0, 40, true, 0) );
    // AddSequential(new WaitCommand(2.0));



    //***************************************************
    AddSequential(new CmdPrintAutoText("GrpTest Done!"));
}
