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
#include "Commands/CmdDriveTurn2Heading.h"
#include "Commands/CmdDriveTurn2Angle.h"

#include "Commands/CmdLogEnable.h"
#include "Commands/CmdLogMark.h"

#include "Commands/CmdDriveClearAll.h"

#define FWD_PWR 0.6
#define TRN_PWR 0.5

GrpTest::GrpTest() 
{
    AddSequential(new CmdPrintAutoText("GrpTest Begin"));
    AddSequential(new CmdDriveClearAll());
    AddSequential(new WaitCommand(0.25));
    //***************************************************
     AddSequential(new CmdLogEnable(true));
    //***************************************************

    AddSequential(new CmdDriveFwdGyro(FWD_PWR, 0.0,  40, true, 0) );
        AddSequential(new CmdLogMark(1));

    AddSequential(new CmdDriveTurn2Angle(TRN_PWR, -90.0 ) );
        AddSequential(new CmdLogMark(2));

    AddSequential(new CmdDriveFwdGyro(FWD_PWR, -90,  40, true, 0) );
        AddSequential(new CmdLogMark(3));

    AddSequential(new CmdDriveTurn2Angle(TRN_PWR, -90.0 ) );
        AddSequential(new CmdLogMark(4));

    AddSequential(new CmdDriveFwdGyro(FWD_PWR, -180,  40, true, 0) );
        AddSequential(new CmdLogMark(5));

    AddSequential(new CmdDriveTurn2Angle(TRN_PWR, -90.0 ) );
        AddSequential(new CmdLogMark(6));

    AddSequential(new CmdDriveFwdGyro(FWD_PWR, -270,  40, true, 0) );
        AddSequential(new CmdLogMark(7));

    AddSequential(new CmdDriveTurn2Angle(TRN_PWR, -90.0 ) ); 
 
    // //FWD/BKWD Test ***********************************************
    // AddSequential(new CmdDriveFwdGyro(FWD_PWR, 0.0,  40, true, 0) );
    // AddSequential(new WaitCommand(2.0));
    // AddSequential(new CmdDriveRevGyro(FWD_PWR, 0.0,  40, true, 0) );  
    // AddSequential(new WaitCommand(2.0));  
    // AddSequential(new CmdDriveFwdGyro(FWD_PWR, 0.0,  40, true, 0) );
    // AddSequential(new WaitCommand(2.0));
    // AddSequential(new CmdDriveRevGyro(FWD_PWR, 0.0,  40, true, 0) );  
    // AddSequential(new WaitCommand(2.0)); 
    // //**************************************************************


    //***************************************************
    AddSequential(new WaitCommand(2.0));        //Let it finish whatever it's doing
    AddSequential(new CmdLogEnable(false));
    AddSequential(new CmdPrintAutoText("GrpTest Done!"));
}
