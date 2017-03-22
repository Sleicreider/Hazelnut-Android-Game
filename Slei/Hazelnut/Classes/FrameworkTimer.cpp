//
//  Timer.cpp
//  Hazelnut
//
//  Created by Dominik Reisner on 13.11.14.
//
//

#include "FrameworkTimer.h"

using namespace std::chrono;

int FrameworkTimer::GetCurrentTimeInSeconds()
{
    time_t rawtime;
    time(&rawtime);
    struct tm *tm_struct = localtime(&rawtime);
    
    
    int32_t h = tm_struct->tm_hour * 60;
    h = tm_struct->tm_hour * 60 * 60;
    int32_t m = tm_struct->tm_min;
    m = tm_struct->tm_min * 60;
    int32_t s = tm_struct->tm_sec;
    
    int32_t time = m + h;
    time = m+h+s;
    
    return time;
}