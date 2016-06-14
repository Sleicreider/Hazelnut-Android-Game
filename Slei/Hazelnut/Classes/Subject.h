#ifndef SUBJECT_H
#define SUBJECT_H

#include <vector>
#include "FGeneral.h"
#include "Observer.h"

using DelegateFunc = std::function<void()>;

class Subject
{
public:
	void AddObserver(Observer* observer);
	void Notify(EEvent event);
    
    template<typename T>
	FORCEINLINE
    void RegisterDelegate(T* instance, void (T::*func)())
    {
        delegates_.push_back(std::bind(func,instance));
    }

	//void RemoveObserver(Observer* observer);

private:
	std::vector<Observer*> observer_;
    std::vector<DelegateFunc> delegates_;
};

#endif // SUBJECT_H