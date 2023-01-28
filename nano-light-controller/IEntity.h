#ifndef _IENTITY_H_
#define _IENTITY_H_

class IEntity {

public:
    virtual void init() = 0;
    virtual void update(int millis) = 0;
};

#endif