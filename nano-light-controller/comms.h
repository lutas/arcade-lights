#ifndef _COMMS_H_
#define _COMMS_H_

#include "IStateChange.h"
#include "IEntity.h"

class Comms : public IEntity {

public:
    Comms(IStateChange& handler);

    void init();
    void update(int millis);

private:
    IStateChange* _pHandler;
};

#endif