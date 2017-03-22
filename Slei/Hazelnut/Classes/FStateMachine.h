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

class FStateMachine : public ITickable
{
private:
    
    struct state_item
    {
        std::function<void(float)> main_funct;
        std::function<void()> on_enter_funct;
    };
    
    std::unordered_map<std::string,state_item> state_map_;

    std::string current_state_;
    std::string previous_state_;
    
    bool bStateHasChanged_;

public:
    FStateMachine()
    : current_state_("")
    , previous_state_("")
    , bStateHasChanged_(false)
    {
    }
    
    virtual ~FStateMachine();
    
    template<typename T>
    void Register(const std::string& id, T* instance, void (T::*func)(float));
    
    template<typename T>
    void Register(const std::string& id, T* instance, void (T::*func)(float), void (T::*on_enter_func)());
    
    void SetState(const std::string& id);
    
    std::string& GetCurrentState();
    std::string& GetPreviousState();
    
private:
    virtual void Tick(float delta);
};

inline FStateMachine::~FStateMachine()
{

}

inline void FStateMachine::Tick(float delta)
{
    if(state_map_.size() == 0 || current_state_ == "") { return; } //|| (state_map_.find(current_state_) == state_map_.end())

    if(bStateHasChanged_)
    {
        if(state_map_.at(current_state_).on_enter_funct != nullptr)
        {
            state_map_.at(current_state_).on_enter_funct();
        }
        
        bStateHasChanged_ = false;
    }

    state_map_.at(current_state_).main_funct(delta);
}

template<typename T>
inline
void FStateMachine::Register(const std::string& id, T* instance, void (T::*func)(float))
{
    state_map_[id] = { std::bind(func, instance, std::placeholders::_1), nullptr };
}

template<typename T>
inline
void FStateMachine::Register(const std::string& id, T* instance, void (T::*func)(float), void (T::*on_enter_func)())
{
    state_map_[id] = { std::bind(func, instance, std::placeholders::_1), std::bind(on_enter_func, instance) };
}

inline void FStateMachine::SetState(const std::string& id)
{
    std::string tmp = current_state_;
    current_state_ = id;
    previous_state_ = tmp;
    
    bStateHasChanged_ = true;
}

inline std::string& FStateMachine::GetCurrentState()
{
    return current_state_;
}


inline std::string& FStateMachine::GetPreviousState()
{
    return previous_state_;
}

#endif /* defined(__Hazelnut__FStateMachine__) */
