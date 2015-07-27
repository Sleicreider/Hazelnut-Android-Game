//
//  ITickable.h
//  Hazelnut
//
//  Created by Dominik Reisner on 04.05.15.
//
//

#ifndef Hazelnut_ITickable_h
#define Hazelnut_ITickable_h

class FrameworkScene;

class ITickable
{
    friend class FrameworkScene;
    
public:
    virtual ~ITickable() = 0;
    
private:
    virtual void Tick(float delta) = 0;
};

inline ITickable::~ITickable() {
    

}

#endif
