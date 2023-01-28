#ifndef __LIGHT_H__
#define __LIGHT_H__

class Light {

public:
    Light();

    void setPin(int pin);
    void setState(bool on);

private:
    int _pin;
};

#endif