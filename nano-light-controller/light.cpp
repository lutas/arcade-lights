#include <Arduino.h>
#include "light.h"

Light::Light() : 
    _pin(0) 
{
}

void Light::setPin(int pin) {

    _pin = pin;
    pinMode(_pin, OUTPUT);
}

void Light::setState(bool on) {
    digitalWrite(_pin, on ? HIGH : LOW);
}
