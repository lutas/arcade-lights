#include "Pulse.h"

Pulse::Pulse() :
    _onDelay(500),
    _offDelay(500),
    _timeLeft(0),
    _on(false)
{
}

void Pulse::setOnDelay(int millis) {
    _onDelay = millis;
}

void Pulse::setOffDelay(int millis) {
    _offDelay = millis;
}

bool Pulse::update(int elapsedMillis) {
    _timeLeft -= elapsedMillis;

    if (_timeLeft < 0) {
        _on = !_on;

        // supports two delay timers if on/off time is different
        int delayTime = _on ? _onDelay : _offDelay;

        // account for any time beyond the time causing the state change
        _timeLeft += delayTime;
        return true;
    }

    return false;
}