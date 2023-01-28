#include "lightManager.h"

LightManager::LightManager()
{
    _fastPulse.setOnDelay(50);
    _fastPulse.setOffDelay(25);

    _slowPulse.setOnDelay(300);
    _slowPulse.setOffDelay(150);

    for (int i = 0; i < NUM_LIGHTS; ++i) {
        _lightStates[i] = State::Off;
    }
}

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
}

void LightManager::setLight(uint32_t id, bool on) {
    if (id >= NUM_LIGHTS) {
        return;
    }

    _lights[id].setState(on);
}

void LightManager::onMessage(uint8_t lightId, State state) {
    _lightStates[lightId] = state;
    if (state == State::On) {
        _lights[lightId].setState(true);
    }
    if (state == State::Off) {
        _lights[lightId].setState(false);
    }
}

void LightManager::update(int millis) {
    bool fastPulseChanged = _fastPulse.update(millis);
    bool slowPulseChanged = _slowPulse.update(millis);    

    int i = 0;
    for (; i < NUM_LIGHTS; ++i)
    {
        switch (_lightStates[i]) {
            case State::FastPulse:
            {
                if (fastPulseChanged) {
                    _lights[i].setState(_fastPulse.isOn());
                }
            }
            break;

            case State::SlowPulse:
            {
                if (slowPulseChanged) {
                    _lights[i].setState(_slowPulse.isOn());
                }
            }
            break;
        }
    }
}