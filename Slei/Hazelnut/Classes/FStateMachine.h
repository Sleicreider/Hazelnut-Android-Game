//
//  FStateMachine.h
//  Hazelnut
//
//  Created by Dominik Reisner on 25.03.15.
//
//

#ifndef __Hazelnut__FStateMachine__
#define __Hazelnut__FStateMachine__

#include <cocos2d.h>
#include <unordered_map>
#include "ITickable.h"

#include <vector>

USING_NS_CC;

#pragma warn message("STATE MACHINE RUNS EVEN IF THE CLASS WHO CALLS IT DOESNT EXIST? OR ISN'T RUNNING TEST PLS!")

template <typename T> class FStateMachine : public ITickable
{
private:
    std::unordered_map<std::string,void (T::*)(float)> state_map_;
    T* instance_;
    std::string current_state_;
    std::string previous_state_;

public:
    FStateMachine()
    : current_state_("")
    , previous_state_("")
    {
    }
    
    virtual ~FStateMachine();
    
    void Register(const std::string& id,T* instance,void(T::*func)(float));
    void SetState(const std::string& id);
    std::string& GetCurrentState();
    std::string& GetPreviousState();
    
private:
    virtual void Tick(float delta);
};

template<class T>
inline
FStateMachine<T>::~FStateMachine()
{

}

template<typename T>
inline
void FStateMachine<T>::Tick(float delta)
{
    if(state_map_.size() == 0 || current_state_ == "") { return; } //|| (state_map_.find(current_state_) == state_map_.end())

    (instance_->*state_map_.at(current_state_))(delta);
}

template<typename T>
inline
void FStateMachine<T>::Register(const std::string& id,T* instance,void(T::*func)(float))
{
    instance_ = instance;
    state_map_[id] = func;
}

template<typename T>
inline
void FStateMachine<T>::SetState(const std::string& id)
{
    std::string tmp = current_state_;
    current_state_ = id;
    previous_state_ = tmp;
}

template<typename T>
inline
std::string& FStateMachine<T>::GetCurrentState()
{
    return current_state_;
}


template<typename T>
inline
std::string& FStateMachine<T>::GetPreviousState()
{
    return previous_state_;
}

#endif /* defined(__Hazelnut__FStateMachine__) */
