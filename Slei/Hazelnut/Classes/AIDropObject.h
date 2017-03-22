//
//  AIDropObject.h
//  Hazelnut
//
//  Created by Dominik Reisner on 13.11.14.
//
//

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

	bool GroundCollision();
    bool DeathAnimationHasFinished();
    
    FSprite* GetSprite();
    EDropObjectType GetType();
    
    int GetDropObjectSpeed();
    bool IsActive();
    bool IsDead();
    
    void Remove();
    
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
    
private:
    
    FTimeframe timeframe_death_anim_;
    
    FrameworkScene* scene;
    FSprite* dropObject;
    
    EDropObjectType dropObjectType;
    
    int dropObjectSpeed;
    uint32_t bIsDead_:1;
    uint32_t bIsActive_:1;
};

FORCEINLINE void AIDropObject::WithAnimation(bool active, FSprite::EAnimation sprite_animation){ dropObject->WithAnimation(active,sprite_animation); }
FORCEINLINE void AIDropObject::SetPositionX(int posX){ dropObject->setPositionX(posX); }
FORCEINLINE void AIDropObject::SetPositionY(int posY){ dropObject->setPositionY(posY); }
FORCEINLINE void AIDropObject::SetType(EDropObjectType type){ this->dropObjectType = type; }
FORCEINLINE void AIDropObject::SetDropObjectSpeed(int dropObjectSpeed){ this->dropObjectSpeed = dropObjectSpeed; }

FORCEINLINE void AIDropObject::SetActive(bool active)
{
    if(active)
    {
        dropObject->setVisible(true);
        dropObject->resume();
    }
    else
    {
        dropObject->setVisible(false);
        dropObject->pause();
    }
    
    bIsActive_ = active;
}

FORCEINLINE EDropObjectType AIDropObject::GetType() { return dropObjectType; }
FORCEINLINE FSprite* AIDropObject::GetSprite()      { return dropObject; }
FORCEINLINE int AIDropObject::GetDropObjectSpeed()  { return dropObjectSpeed; }

FORCEINLINE bool AIDropObject::GroundCollision()
{
    if(dropObject->getPositionY() <= DataHandler::COLLECT_GAME_GROUND_COLLISION_Y)
    {
        return true;
    }
    return false;
}

FORCEINLINE bool AIDropObject::IsDead()                 { return bIsDead_; }
FORCEINLINE void AIDropObject::SetDead(bool bIsDead)    { bIsDead_ = bIsDead; };
FORCEINLINE bool AIDropObject::IsActive()               { return bIsActive_; }

#endif /* defined(__Hazelnut__AIDropObject__) */
