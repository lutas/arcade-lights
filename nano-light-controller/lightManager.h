#ifndef __LIGHTMANAGER_H__
#define __LIGHTMANAGER_H__

#include "state.h"
#include "IEntity.h"
#include "IStateChange.h"

#include "Light.h"

#include <stdint.h>

#define NUM_LIGHTS 8

class LightManager : public IStateChange, public IEntity {

public:
    int numLights() const { return NUM_LIGHTS; };
    
    // IEntity
    void init();
    void update(int elapsedMillis);
    
    // IStateChange
    void onMessage(uint8_t lightId, State state);
private:
    Light _lights[NUM_LIGHTS];
    void setLight(uint32_t id, bool on);

    // keep single vars for pulse delay 
    // so all lights are matched to the same pulse
    int _fastPulseTime;
    int _slowPulseTime;
};


#endif
