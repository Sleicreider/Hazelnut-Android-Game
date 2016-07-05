//
//  AI.h
//  Hazelnut
//
//  Created by Dominik Reisner on 13.11.14.
//
//

//DONE STYLE CHANGED!
//TODO Check for better code etc.

#ifndef __Hazelnut__AI___
#define __Hazelnut__AI___

#include "cocos2d.h"

#include "FGeneral.h"
#include "FrameworkScene.h"
#include "FrameworkTimer.h"
#include "AIDropObject.h"

#include <memory>
#include <vector>

USING_NS_CC;

class FSprite;
class InGameScene;

using AIDropObjectContainer = std::vector<std::unique_ptr<AIDropObject>>;

class AI
{
    
public:
    AI(FrameworkScene* scene);
    
    void Movement(int32_t squirrelSpeed, int32_t dropObjectSpeedMin, int32_t dropObjectSpeedMax, int32_t dropIntervalMin, int32_t dropIntervalMax, int32_t hazelnut_speed);
    void InitAI(cocos2d::Sprite* aiObject);
    void GenearteNewDropTimer(int dropObjectSpeedMin,int dropObjectSpeedMax, int dropIntervalMin,int dropIntervalMax);
    void SetDropChance(int32_t c_hazelnut, int32_t c_waste, int32_t c_apple, int32_t c_heart, int32_t c_coin);
    
    AIDropObjectContainer& GetDropObjects();
    AIDropObjectContainer& GetInactiveDropObjects();
    
    /**
     * Amount of dropObjects which hit the ground in the current frame
     */
    int32_t GetHitGroundCounter() const;
    int32_t GetNewDropTypeValue() const;

    void SpawnObject();
	void DecreaseHeartCounter();
	void ActivateHeartDrop();
    
private:
    void DropBehaviour(int dropObjectSpeedMin,int dropObjectSpeedMax, int dropIntervalMin,int dropIntervalMax, int hazelnut_speed);
    void DropObjectMovement();
    void DropObjectTypeAssignment(AIDropObject* dropObject);
    
    int32_t GetMaxDropChance() const;

private:
    FrameworkScene* scene_;
    InGameScene* ing_scene_;
    Sprite* ai_object_;

    AIDropObjectContainer vec_drop_objects_;
    AIDropObjectContainer vec_inactive_objects_;
    AIDropObjectContainer vec_dangling_objects_; /**< Objects where animation hasn't finished yet */
    
    FSprite::EAnimation sprite_animation_;
    
    uint32_t bCanDropHeart_:1;

    int32_t hit_ground_counter_;
    
    int32_t rand_move_value_;
    int32_t rand_drop_wait_value_ms_;
    int32_t rand_drop_wait_value_;
    int32_t rand_drop_object_type_value_;
    int32_t rand_drop_object_speed_value_;
    
	int32_t c_hazelnut_;
	int32_t c_waste_;
	int32_t c_apple_;
	int32_t c_heart_;
	int32_t c_coin_;

	int32_t counter_;
    int32_t heart_counter_;
    
    float ai_prev_pos_x_;
    float ai_pos_x_;

    int32_t ai_prev_timer_;
    milliseconds ai_prev_timer_ms_;
    
    FrameworkTimer t_;
    
    uint32_t bWithAnimation_:1;
};

FORCEINLINE AIDropObjectContainer& AI::GetDropObjects()             { return vec_drop_objects_; }
FORCEINLINE AIDropObjectContainer& AI::GetInactiveDropObjects()     { return vec_inactive_objects_; }

FORCEINLINE int32_t AI::GetHitGroundCounter() const { return hit_ground_counter_; }
FORCEINLINE int32_t AI::GetNewDropTypeValue() const { return rand() % GetMaxDropChance() + 1; }

FORCEINLINE int32_t AI::GetMaxDropChance() const
{
	return c_hazelnut_ + c_waste_ + c_apple_ + c_heart_ + c_coin_;
}

FORCEINLINE void AI::DecreaseHeartCounter() { heart_counter_--; }

FORCEINLINE void AI::ActivateHeartDrop() { bCanDropHeart_ = true;  }

#endif /* defined(__Hazelnut__AI__) */
