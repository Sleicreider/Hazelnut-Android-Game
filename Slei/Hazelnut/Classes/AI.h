//
//  AI.h
//  Hazelnut
//
//  Created by Dominik Reisner on 13.11.14.
//
//

#ifndef __Hazelnut__AI___
#define __Hazelnut__AI___

#include "FGeneral.h"

#include "cocos2d.h"
#include "FrameworkScene.h"

#include "FrameworkTimer.h"
#include "AIDropObject.h"

#include <memory>
#include <vector>

USING_NS_CC;

class FSprite;
class InGameScene;

class AI
{
    
public:
    AI(FrameworkScene* scene);
    void Movement(int squirrelSpeed, int dropObjectSpeedMin,int dropObjectSpeedMax,int dropIntervalMin,int dropIntervalMax, int hazelnut_speed);
    void InitAI(cocos2d::Sprite* aiObject);
    std::vector<std::unique_ptr<AIDropObject>>& GetDropObjects();
    std::vector<std::unique_ptr<AIDropObject>>& GetInactiveDropObjects();
    
    /**
     * Amount of dropObjects which hit the ground in the current frame
     */
    int GetHitGroundCounter();
    
    void SpawnObject();
    
    void GenearteNewDropTimer(int dropObjectSpeedMin,int dropObjectSpeedMax, int dropIntervalMin,int dropIntervalMax);
	int32_t GetNewDropTypeValue();

	void DecreaseHeartCounter();

	void SetDropChance(int32_t c_hazelnut, int32_t c_waste, int32_t c_apple, int32_t c_heart, int32_t c_coin);

	void ActivateHeartDrop();

private:
	int32_t GetMaxDropChance();
    InGameScene* ing_scene_;
    
private:
    FrameworkScene* scene;
    
    void DropBehaviour(int dropObjectSpeedMin,int dropObjectSpeedMax, int dropIntervalMin,int dropIntervalMax, int hazelnut_speed);
	void DropObjectMovement();
    void DropObjectTypeAssignment(AIDropObject* dropObject);

    Sprite* aiObject;

    
    std::vector<std::unique_ptr<AIDropObject>> vecDropObjects;
    std::vector<std::unique_ptr<AIDropObject>> vecInactiveObjects;
    std::vector<std::unique_ptr<AIDropObject>> vecDanglingObjects; /**< Objects where animation hasn't finished yet */
    
    int hitGroundCounter;

	bool bCanDropHeart_;
    
    int32_t randMoveValue;
    int32_t randDropWaitValueMS;
    int32_t randDropWaitValue;
    int32_t randDropObjectTypeValue;
    int32_t randDropObjectSpeedValue;
	int32_t c_hazelnut_;
	int32_t c_waste_;
	int32_t c_apple_;
	int32_t c_heart_;
	int32_t c_coin_;

    
    FSprite::EAnimation sprite_animation_;

	int counter;
    
    float aiPrevPosX;
    float aiPosX;

    int32_t aiPrevTimer;
    milliseconds aiPrevTimerMS;
    
    FrameworkTimer t;

	int heart_counter_;
    
    
private:
    bool withAnimation;
};

inline std::vector<std::unique_ptr<AIDropObject>>& AI::GetDropObjects() { return vecDropObjects; }
inline std::vector<std::unique_ptr<AIDropObject>>& AI::GetInactiveDropObjects() { return vecInactiveObjects; }
inline int AI::GetHitGroundCounter() { return hitGroundCounter; }
inline int32_t AI::GetNewDropTypeValue() { return rand() % GetMaxDropChance() + 1; }
inline void AI::DecreaseHeartCounter() { heart_counter_--; }

inline int32_t AI::GetMaxDropChance()
{
	return c_hazelnut_ + c_waste_ + c_apple_ + c_heart_ + c_coin_;
}

inline void AI::ActivateHeartDrop() { bCanDropHeart_ = true;  }

#endif /* defined(__Hazelnut__AI__) */
