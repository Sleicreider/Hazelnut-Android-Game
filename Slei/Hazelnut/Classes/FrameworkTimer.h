//
//  FrameworkTimer.h
//  Hazelnut
//
//  Created by Dominik Reisner on 13.11.14.
//
//

#ifndef __Hazelnut__FrameworkTimer__
#define __Hazelnut__FrameworkTimer__

#include <stdlib.h>
#include <stdio.h>
#include <iostream>

#include <time.h>
#include <chrono>

typedef std::chrono::milliseconds milliseconds;

class FrameworkTimer
{
    
public:
    /**
     * Get current time in seconds.
     */
    int32_t GetCurrentTimeInSeconds();
    
    /**
     * Get current time in milliseconds.
     * @return milliseconds Type std::chrono::milliseconds
     */
    milliseconds GetCurrentTimeInMilliseconds();
};

inline milliseconds FrameworkTimer::GetCurrentTimeInMilliseconds()
{
    return std::chrono::duration_cast<milliseconds>(std::chrono::high_resolution_clock::now().time_since_epoch());
}


#endif /* defined(__Hazelnut__FrameworkTimer__) */
