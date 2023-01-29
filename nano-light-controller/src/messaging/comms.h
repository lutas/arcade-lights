#ifndef _COMMS_H_
#define _COMMS_H_

#include "IStateChange.h"
#include "../framework/IEntity.h"
#include "data-buffer.h"

class Comms : public IEntity {

public:
    Comms(IStateChange& handler);

    void init();
    void update(int millis);

private:

    bool switchCommand(byte command);
    void handleLightData(byte data);
    void handlePulseData(byte data);

    enum Command {
        Off,
        SetLightState,
        SetPulseTime,
        End
    } _commState;

    IStateChange* _pHandler;
    DataBuffer _buffer;

    // if a command marker is sent, then await our new command
    bool _newCommandState;
};

#endif