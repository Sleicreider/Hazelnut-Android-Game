//
//  AIDropObject.h
//  Hazelnut
//
//  Created by Dominik Reisner on 13.11.14.
//
//

//DONE STYLE CHANGED!
//TODO Check for better code etc.

#ifndef __Hazelnut__AIDropObject__
#define __Hazelnut__AIDropObject__

#include "FGeneral.h"
#include "cocos2d.h"
#include "FrameworkScene.h"
#include "FSprite.h"

#include "HazelnutEnum.h"

USING_NS_CC;

class AIDropObject
{

public:
	AIDropObject(FrameworkScene* scene);
    ~AIDropObject();
    
    void DeathAnimation();
    void DeathAnimationHeart();
    void DeathAnimationBroken();
    
    void CreateDropObject();

	void SetPositionX(int posX);
	void SetPositionY(int posY);
    void SetType(EDropObjectType type);
    void SetDropObjectSpeed(int dropObjectSpeed);
    void SetActive(bool active);
    void WithAnimation(bool active, FSprite::EAnimation sprite_animation);
    void SetDead(bool bIsDead);
    
    void Remove();

    
    FSprite* GetSprite();
    bool DeathAnimationHasFinished();
    
    EDropObjectType GetType() const;

    bool IsActive() const;
    bool IsDead() const;
    bool GroundCollision() const;
    
    int32_t GetDropObjectSpeed() const;
    
private:
    FrameworkScene* scene_;
    FSprite* drop_object_;
    
    EDropObjectType drop_object_type_;
    FTimeframe timeframe_death_anim_;
    
    int32_t drop_object_speed_;

    uint32_t bIsDead_:1;
    uint32_t bIsActive_:1;
};

FORCEINLINE void AIDropObject::SetPositionX(int posX){ drop_object_->setPositionX(posX); }
FORCEINLINE void AIDropObject::SetPositionY(int posY){ drop_object_->setPositionY(posY); }
FORCEINLINE void AIDropObject::SetType(EDropObjectType type){ drop_object_type_ = type; }
FORCEINLINE void AIDropObject::SetDropObjectSpeed(int dropObjectSpeed){ drop_object_speed_ = dropObjectSpeed; }

FORCEINLINE void AIDropObject::SetActive(bool active)
{
    if(active)
    {
        drop_object_->setVisible(true);
        drop_object_->resume();
    }
    else
    {
        drop_object_->setVisible(false);
        drop_object_->pause();
    }
    
    bIsActive_ = active;
}

FORCEINLINE void AIDropObject::WithAnimation(bool active, FSprite::EAnimation sprite_animation)     { drop_object_->WithAnimation(active,sprite_animation); }
FORCEINLINE void AIDropObject::SetDead(bool bIsDead)                                                { bIsDead_ = bIsDead; };

FORCEINLINE FSprite* AIDropObject::GetSprite() { return drop_object_; }

FORCEINLINE EDropObjectType AIDropObject::GetType() const       { return drop_object_type_; }
FORCEINLINE int32_t AIDropObject::GetDropObjectSpeed() const    { return drop_object_speed_; }

FORCEINLINE bool AIDropObject::GroundCollision() const
{
    return drop_object_->getPositionY() <= DataHandler::COLLECT_GAME_GROUND_COLLISION_Y;
}

FORCEINLINE bool AIDropObject::IsDead() const   { return bIsDead_; }
FORCEINLINE bool AIDropObject::IsActive() const { return bIsActive_; }

#endif /* defined(__Hazelnut__AIDropObject__) */
