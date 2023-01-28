#ifndef _COMMS_H_
#define _COMMS_H_

#include "IStateChange.h"
#include "../framework/IEntity.h"

class Comms : public IEntity {

public:
    Comms(IStateChange& handler);

    void init();
    void update(int millis);

private:

    bool switchCommand(byte command);

    enum Command {
        Off,
        SetLightState,
        SetPulseTime,
        End
    } _commState;

    IStateChange* _pHandler;

    // if a command marker is sent, then await our new command
    bool _newCommandState;
};

#endif