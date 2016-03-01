#ifndef SUBJECT_H
#define SUBJECT_H

#include <vector>
#include "Observer.h"

using DelegateFunc = std::function<void()>;

class Subject
{
public:
	void AddObserver(Observer* observer)
	{
		observer_.push_back(observer);
	}
    
    template<typename T>
    void RegisterDelegate(T* instance, void (T::*func)())
    {
        delegates_.push_back(std::bind(func,instance));
    }

	void RemoveObserver(Observer* observer)
	{
		for (int i = 0; i < observer_.size(); i++)
		{
			if (observer_[i] == observer)
			{
				//observer_.erase(observer_.begin + i);
			}
		}
	}

private:
	std::vector<Observer*> observer_;
    std::vector<DelegateFunc> delegates_;

public:
	void Notify(EEvent event)
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
};

#endif // SUBJECT_H
