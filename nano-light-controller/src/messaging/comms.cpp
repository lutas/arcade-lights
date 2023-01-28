#include <Arduino.h>

#include "comms.h"

namespace {
    const int MessageLength = 2;
}

Comms::Comms(IStateChange& handler) :
    _pHandler(&handler)
{    
}

void Comms::init() {
    // put your setup code here, to run once:
    Serial.begin(9600);
}

void Comms::update(int millis)
{
    while (Serial.available() >= MessageLength)
    {
        byte c[MessageLength];
        int numBytes = Serial.readBytes(c, MessageLength);
        if (numBytes)
        {
            short buttonState = (c[1] << 8) | c[0];
            int pinOut = HIGH;
            if (buttonState >= 6)
            {
                buttonState %= 6;
                pinOut = LOW;
            }

            uint8_t lightId = 0;
            int state = 0;

            State mt = static_cast<State>(state);

            _pHandler->onMessage(lightId, mt);
        }
    }
}