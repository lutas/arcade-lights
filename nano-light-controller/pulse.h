#ifndef _PULSE_H_
#define _PULSE_H_

class Pulse {
public:
    // onDelay = time left in on state
    // offDelay = independent time for left in off state
    Pulse();

    void setOnDelay(int millis);
    void setOffDelay(int millis);

    bool isOn() const { return _on; };

    // returns whether a state change has been triggered
    bool update(int elapsedMillis);

private:
    bool _on;
    int _timeLeft;

    int _onDelay;
    int _offDelay;
};

#endif