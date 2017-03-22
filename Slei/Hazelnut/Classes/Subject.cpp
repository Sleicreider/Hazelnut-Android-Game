//
//  Subject.cpp
//  
//
//  Created by Dominik Reisner on 13.06.16.
//
//

#include "Subject.h"

void Subject::AddObserver(Observer* observer)
{
    observer_.push_back(observer);
}

void Subject::Notify(EEvent event)
{
    for (auto observer : observer_)
    {
        observer->OnNotify(event);
    }
    
    for(auto& delegate : delegates_)
    {
        delegate();
    }
}
