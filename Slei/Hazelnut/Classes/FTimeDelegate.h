//
//  FTimeDelegate.h
//  Hazelnut
//
//  Created by Dominik Reisner on 21.01.16.
//
//

#ifndef Hazelnut_FTimeDelegate_h
#define Hazelnut_FTimeDelegate_h

#include "FTimeframe.h"
#include "ITickable.h"
#include "FGeneral.h"
#include <functional>

class FTimeDelegate : public ITickable
{
    std::func<void()> func_task;
    
public:
    FTimeDelegate();
    
    template<class T>
    void Start(float time, T* instance, void (T::*func)());
    
    
private:
    
};

template<class T>
FORCEINLINE
void Start(float time, T* instance, void (T::*func)())
{
    func_task = std::bind(func, instance);
}
