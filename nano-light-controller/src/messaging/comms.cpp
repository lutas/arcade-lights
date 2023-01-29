#include <Arduino.h>

#include "comms.h"

namespace {
    const int MessageLength = 2;

    const byte CommandMarker = 0xFF;
}

Comms::Comms(IStateChange& handler) :
    _pHandler(&handler),
    _commState(Comms::Command::Off),
    _newCommandState(false)
{    
}

void Comms::init() {
    Serial.begin(9600);
}

bool Comms::switchCommand(byte command) {
    if (command >= static_cast<byte>(Comms::End)) {
        // invalid command specified
        return false;
    }

    _commState = static_cast<Command>(command);
}

void Comms::update(int millis)
{
    while (Serial.available())
    {
        // if we're awaiting a command, then switch mode      
        byte v;
        Serial.readBytes(&v, 1);

        if (_newCommandState) {
            switchCommand(v);
            _newCommandState = false;
            continue;
        }        
        else if (v == CommandMarker) {
            _newCommandState = true;
            continue;
        }
        
        if (_commState == Command::SetLightState) {
            // notify from the byte
            // 5MSB = lightId
            uint8_t lightId = v >> 3;
            uint8_t stateId = v & 0x07;
            State state = static_cast<State>(stateId);
            // Serial.print("v: ");
            // Serial.print(v);
            // Serial.print("Light: ");
            // Serial.print(lightId);
            // Serial.print(" State: ");
            // Serial.println(stateId);
            _pHandler->setLightState(lightId, state);
        }
    }
}