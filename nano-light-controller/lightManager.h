#ifndef __LIGHTMANAGER_H__
#define __LIGHTMANAGER_H__

#include <Arduino.h>

#include "Light.h"

#define NUM_LIGHTS 8

class LightManager {

public:
    void init();

    void setLight(uint32_t id, bool on);
    int numLights() const { return NUM_LIGHTS; };

private:
    Light _lights[NUM_LIGHTS];
};


#endif
