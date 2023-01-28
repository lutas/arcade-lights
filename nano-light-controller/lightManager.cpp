#include "lightManager.h"

void LightManager::init() {

    int light = 0;
    _lights[light++].setPin(2);
    _lights[light++].setPin(4);
    _lights[light++].setPin(6);
    _lights[light++].setPin(8);
    _lights[light++].setPin(10);
    _lights[light++].setPin(12);
    _lights[light++].setPin(A0);
    _lights[light++].setPin(A2);

}

void LightManager::setLight(uint32_t id, bool on) {
    if (id >= NUM_LIGHTS) {
        Serial.println("Invalid light Id");
        return;
    }

    Serial.print("Setting light ");
    Serial.print(id);
    Serial.print(" to ");
    Serial.println(on ? "on" : "off");

    _lights[id].setState(on);
}
