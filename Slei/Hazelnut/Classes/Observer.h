#ifndef OBSERVER_H
#define OBSERVER_H

enum class EEvent
{
    EVENT_COIN_COLLECTED,
    EVENT_APPLE_COLLECTED,
    EVENT_WASTES_COLLECTED,
    EVENT_HEART_COLLECTED,
    EVENT_COIN_MISSED,
    EVENT_APPLE_MISSED,
    EVENT_HAZELNUT_MISSED,
    EVENT_HEART_MISSED,
    EVENT_GAME_OVER,
    EVENT_LEVEL_UP,
    EVENT_GAME_STARTED
};

class Observer
{
public:
	virtual ~Observer() {}
	virtual void OnNotify(EEvent event) = 0;
};

#endif // OBSERVER_H