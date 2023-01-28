#include "lightManager.h"

namespace {
    const int FastPulseDelay = 50;
    const int SlowPulseDelay = 200;
};

void LightManager::init() {

    int light = 0;
    _lights[light++].setPin(2);
    _lights[light++].setPin(4);
    _lights[light++].setPin(6);
    _lights[light++].setPin(8);
    _lights[light++].setPin(10);
    _lights[light++].setPin(12);
    _lights[light++].setPin(14); // A0
    _lights[light++].setPin(16); // A2

    _fastPulseTime = FastPulseDelay;
    _slowPulseTime = SlowPulseDelay;
}

void LightManager::setLight(uint32_t id, bool on) {
    if (id >= NUM_LIGHTS) {
        return;
    }

    _lights[id].setState(on);
}

void LightManager::onMessage(uint8_t lightId, State state) {

}

void LightManager::update(int millis) {
    static bool on = true;

    on = !on;

    for (int i = 0; i < NUM_LIGHTS; ++i)
    {
        setLight(i, on);
    }
}