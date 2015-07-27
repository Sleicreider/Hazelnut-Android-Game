//
//  FTimeframe.h
//  Hazelnut
//
//  Created by Dominik Reisner on 22.04.15.
//
//

#ifndef Hazelnut_FTimeframe_h
#define Hazelnut_FTimeframe_h

#include "FrameworkTimer.h"
#include "ITickable.h"
#include <functional>

/**
 * The FTimeframe is a timer which runs in the background
 * for a given amount of time. It can be perfectly used 
 * to execute something after a particular amount of time 
 * (sound,animations, other..). The FTimeframe must be 
 * ticked/update somewhere, every scene(FrameworkScene)
 * will provide a AddTickable(..) function for this.
 * Adding a FTimeframe with this function will automatically
 * update the timeframe in every tick.
 */
class FTimeframe : public ITickable
{
    friend class FrameworkScene;
    
    std::function<void()> func_task;

public:
    /**
     * The FTimeframe constructor.
     */
    FTimeframe()
    : end_time_(0)
    , current_time_(0)
    , bIsRunning_(false)
    , bWasRunning_(false)
    {
    }
    
    virtual ~FTimeframe() {}
    
    /**
     * Returns whether the FTimeframe is currently running or not.
     * @return Boolean value which is true if the FTimeframe is running.
     */
    bool IsRunning();
    /**
     * Returns whether the FTimeframe is currently running or was running (1 Tick - look for WasRunning()) true/false.
     * @return Boolean value which is true if the FTimeframe is running or was running.
     */
    bool IsOrWasrunning();
    /**
     * Returns whether the FTimeframe was running or not. Is true for 1 Tick after it finished.
     * @return Boolean value which is true for 1 Tick when the FTimeframe finished running.
     */
    bool WasRunning();
    /**
     * Starts the FTimeframe for the given amount of time.
     * @param end_time How long the timeframe should run in milliseconds. (1000 = 1 sec)
     */
    void Start(milliseconds end_time);
    
    template <typename T>
    void Start(milliseconds end_time,T* instance,void (T::*func)());
    
private:
    /**
     * This function should only be called in the FrameworkScene to update the FTimeframe every tick
     * if it was added with a AddTickable(..) function.
     */
    virtual void Tick(float delta);
    
private:
    FrameworkTimer time_;
    
    milliseconds end_time_;
    milliseconds current_time_;
    
    bool bIsRunning_;
    bool bWasRunning_;
    
    
};

inline void FTimeframe::Start(milliseconds end_time)
{
    end_time_ = time_.GetCurrentTimeInMilliseconds() + end_time; // * 1000 ms to seconds
    bIsRunning_ = true;
}

template<class T>
inline void FTimeframe::Start(milliseconds end_time, T* instance, void (T::*func)())
{
    Start(end_time);
    
	func_task = std::bind(func, instance);
}


inline void FTimeframe::Tick(float delta)
{
    //set to false after being true for one tick
    if(bWasRunning_)
    {
        bWasRunning_ = false;
    }
    
    
    if(bIsRunning_)
    {
        
        if(end_time_<= time_.GetCurrentTimeInMilliseconds())
        {
            bWasRunning_ = true;
            bIsRunning_ = false;
            
            
			if (func_task)
            {
				func_task();
            }
        }
    }
}

inline bool FTimeframe::IsRunning()
{
    return bIsRunning_;
}

inline bool FTimeframe::WasRunning()
{
    return bWasRunning_;
}

inline bool FTimeframe::IsOrWasrunning()
{
    if(bIsRunning_ || bWasRunning_)
    {
        return true;
    }
    
    return false;
}

#endif
