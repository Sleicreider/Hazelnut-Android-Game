//
//  AI.h
//  Hazelnut
//
//  Created by Dominik Reisner on 13.11.14.
//
//

//  Extremely old logic
//  Might contain inefficient code

#ifndef __Hazelnut__AI___
#define __Hazelnut__AI___

#include "FGeneral.h"

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
    
    
    std::vector<std::unique_ptr<AIDropObject>>& GetDropObjects();
    std::vector<std::unique_ptr<AIDropObject>>& GetInactiveDropObjects();
    
    /**
     * Amount of dropObjects which hit the ground in the current frame
     */
    int GetHitGroundCounter();
    int GetNewDropTypeValue();
    
    void SpawnObject();
    
    void DecreaseHeartCounter();
    void ActivateHeartDrop();
    
    void Movement(int squirrelSpeed, int dropObjectSpeedMin,int dropObjectSpeedMax,int dropIntervalMin,int dropIntervalMax, int hazelnut_speed);
    void InitAI(cocos2d::Sprite* aiObject);
    void GenearteNewDropTimer(int dropObjectSpeedMin,int dropObjectSpeedMax, int dropIntervalMin,int dropIntervalMax);
    void SetDropChance(int c_hazelnut, int c_waste, int c_apple, int c_heart, int c_coin);
    
    
private:
    int GetMaxDropChance();
    
    void DropBehaviour(int dropObjectSpeedMin,int dropObjectSpeedMax, int dropIntervalMin,int dropIntervalMax, int hazelnut_speed);
    void DropObjectMovement();
    void DropObjectTypeAssignment(AIDropObject* dropObject);
    
private:
    std::vector<std::unique_ptr<AIDropObject>> vecDropObjects;
    std::vector<std::unique_ptr<AIDropObject>> vecInactiveObjects;
    std::vector<std::unique_ptr<AIDropObject>> vecDanglingObjects; /**< Objects where animation hasn't finished yet */
    
    FrameworkTimer timer_;
    
    milliseconds aiPrevTimerMS;
    
    FSprite::EAnimation sprite_animation_;
    
    FrameworkScene* scene;
    InGameScene*    ing_scene_;
    
    Sprite* aiObject;
    
    bool bCanDropHeart_;
    
    int hitGroundCounter;
    int randMoveValue;
    int randDropWaitValueMS;
    int randDropWaitValue;
    int randDropObjectTypeValue;
    int randDropObjectSpeedValue;
    int c_hazelnut_;
    int c_waste_;
    int c_apple_;
    int c_heart_;
    int c_coin_;
    
    int counter;
    
    float aiPrevPosX;
    float aiPosX;
    
    int aiPrevTimer;
    int heart_counter_;
    
    bool withAnimation;
};

FORCEINLINE std::vector<std::unique_ptr<AIDropObject>>& AI::GetDropObjects() { return vecDropObjects; }
FORCEINLINE std::vector<std::unique_ptr<AIDropObject>>& AI::GetInactiveDropObjects() { return vecInactiveObjects; }
FORCEINLINE int AI::GetHitGroundCounter() { return hitGroundCounter; }
FORCEINLINE int AI::GetNewDropTypeValue() { return rand() % GetMaxDropChance() + 1; }
FORCEINLINE void AI::DecreaseHeartCounter() { heart_counter_--; }

FORCEINLINE int AI::GetMaxDropChance()
{
    return c_hazelnut_ + c_waste_ + c_apple_ + c_heart_ + c_coin_;
}

FORCEINLINE void AI::ActivateHeartDrop() { bCanDropHeart_ = true;  }

#endif /* defined(__Hazelnut__AI__) */
