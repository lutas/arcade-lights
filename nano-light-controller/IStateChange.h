#ifndef _ISTATECHANGE_H_
#define _ISTATECHANGE_H_

#include <stdint.h>

#include "state.h"

class IStateChange {
public:

    virtual void onMessage(uint8_t lightId, State message) = 0;
};

#endif