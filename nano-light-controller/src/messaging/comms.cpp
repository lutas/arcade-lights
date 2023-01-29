#include <Arduino.h>

#include "comms.h"

namespace {
    const int MessageLength = 2;

    const byte CommandMarker = 0xFE;

    const int PulseTimeBufferSize = 1 + 4 + 4; //buffer for the pulse data
}

Comms::Comms(IStateChange& handler) :
    _pHandler(&handler),
    _commState(Comms::Command::Off),
    _newCommandState(false),
    _buffer(PulseTimeBufferSize)
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
    _buffer.reset();

    // Serial.print("Comm state now ");
    // switch (_commState)
    // {
    // case Command::Off:
    //     Serial.println("Off"); break;
    // case Command::SetLightState:
    //     Serial.println("SetLightState"); break;
    // case Command::SetPulseTime:
    //     Serial.println("SetPulseTime"); break;
    // case Command::End:
    //     Serial.println("End"); break;
    // }
    return true;
}
    
void Comms::handleLightData(byte data) {
    // notify from the byte
    // 5MSB = lightId
    uint8_t lightId = data >> 3;
    uint8_t stateId = data & 0x07;
    State state = static_cast<State>(stateId);
    // Serial.print("v: ");
    // Serial.print(v);
    // Serial.print("Light: ");
    // Serial.print(lightId);
    // Serial.print(" State: ");
    // Serial.println(stateId);
    _pHandler->setLightState(lightId, state);
}

void Comms::handlePulseData(byte data) {

    _buffer.write(data);

    // Serial.print("Rcvd pulse data. Buffer size = ");
    // Serial.print(_buffer.availableData());
    // Serial.print(", data = ");
    // Serial.println(data);

    // if we have enough data then parse it
    if (_buffer.availableData() == PulseTimeBufferSize) {

        //Serial.println("Buffer complete");

        _buffer.seek(0);        
        byte pulseId = _buffer.readByte();
        int onDelay = _buffer.readInt();
        int offDelay = _buffer.readInt();
        

        // Serial.println("RCVD pulse command");
        // Serial.print("pulseId: ");
        // Serial.print(pulseId);
        // Serial.print(", onDelay: ");
        // Serial.print(onDelay);
        // Serial.print(", offDelay: ");
        // Serial.println(offDelay);

        _pHandler->setPulseConfig(pulseId, onDelay, offDelay);

        switchCommand(Command::Off);
    }
}

void Comms::update(int millis)
{
    while (Serial.available())
    {
        // if we're awaiting a command, then switch mode      
        byte data;
        Serial.readBytes(&data, 1);
        
        // handle command reset
        if (_newCommandState) {
            _newCommandState = false;

            if (switchCommand(data)) {
                continue;
            }
        }        
        else if (data == CommandMarker && _commState != Command::SetPulseTime) {
            Serial.println("New command marker");
            _newCommandState = true;
            continue;
        }
        
        // handle data when in command state
        switch (_commState) {
            case Command::SetLightState:
                handleLightData(data);
                break;

            case Command::SetPulseTime:
                handlePulseData(data);
                break;

            default:
                _newCommandState = false;
                break;
        }
    }
}