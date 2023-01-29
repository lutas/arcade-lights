#ifndef _ISTATECHANGE_H_
#define _ISTATECHANGE_H_

#include <stdint.h>

#include "../lights/state.h"

class IStateChange {
public:

    virtual void setLightState(uint8_t lightId, State message) = 0;
    virtual void setPulseConfig(uint8_t pulse, int onDelay, int offDelay) = 0;
};

#endif