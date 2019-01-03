

#ifndef CMDTURNPIDTEST_H
#define CMDTURNPIDTEST_H


//#include "Commands/Subsystem.h"
#include "Commands/Command.h"
#include "Robot.h"

class CmdTurnPIDTest: public PIDCommand 
{

    public:
        CmdTurnPIDTest(  int turn_angle );

        virtual void Initialize();
        virtual void Execute();
        virtual bool IsFinished();
        virtual void End();
        virtual void Interrupted();

        virtual double ReturnPIDInput();
        virtual void   UsePIDOutput(double output);        
        
    private:

        double m_angle;             //angle to turn to
        int    m_onTargetCount;     //Number of consecutive hits "OnTarget"
    
    
};

#endif
