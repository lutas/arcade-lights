#ifndef __LIGHTMANAGER_H__
#define __LIGHTMANAGER_H__

#include <stdint.h>

#include "state.h"
#include "../framework/IEntity.h"
#include "../messaging/IStateChange.h"

#include "light.h"
#include "../framework/pulse.h"

#define NUM_LIGHTS 8

class LightManager : public IStateChange, public IEntity {

public:
    LightManager();

    int numLights() const { return NUM_LIGHTS; };
    
    // IEntity
    void init();
    void update(int elapsedMillis);
    
    // IStateChange
    void onMessage(uint8_t lightId, State state);
private:
    Light _lights[NUM_LIGHTS];
    State _lightStates[NUM_LIGHTS];
    void setLight(uint32_t id, bool on);

    // keep single vars for pulse delay 
    // so all lights are matched to the same pulse
    Pulse _fastPulse;
    Pulse _slowPulse;
};


#endif
