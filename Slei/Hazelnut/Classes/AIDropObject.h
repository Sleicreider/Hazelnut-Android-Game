//
//  AIDropObject.h
//  Hazelnut
//
//  Created by Dominik Reisner on 13.11.14.
//
//

#ifndef __Hazelnut__AIDropObject__
#define __Hazelnut__AIDropObject__

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
    
    void DeathAnimation();
    void DeathAnimationHeart();
    void DeathAnimationBroken();
    
    bool DeathAnimationHasFinished();
    
    bool isrun() { return timeframe_death_anim_.IsRunning(); }


	FSprite* GetSprite();
    
    void CreateDropObject();

	void SetPositionX(int posX);
	void SetPositionY(int posY);
    void SetType(EDropObjectType type);
    void SetDropObjectSpeed(int dropObjectSpeed);
    void SetActive(bool active);
    void WithAnimation(bool active, FSprite::EAnimation sprite_animation);
    void SetDead(bool bIsDead);
    
    EDropObjectType GetType();
    int GetDropObjectSpeed();
    bool IsActive();
    
    bool IsDead();

	void Remove();
    

    
private:
    FrameworkScene* scene;
    
    FSprite* dropObject;
    EDropObjectType dropObjectType;
    int dropObjectSpeed;
    
    FTimeframe timeframe_death_anim_;
    
    bool bIsDead_;
    bool bIsActive_;
};

inline void AIDropObject::WithAnimation(bool active, FSprite::EAnimation sprite_animation){ dropObject->WithAnimation(active,sprite_animation); }
inline void AIDropObject::SetPositionX(int posX){ dropObject->setPositionX(posX); }
inline void AIDropObject::SetPositionY(int posY){ dropObject->setPositionY(posY); }
inline void AIDropObject::SetType(EDropObjectType type){ this->dropObjectType = type; }
inline void AIDropObject::SetDropObjectSpeed(int dropObjectSpeed){ this->dropObjectSpeed = dropObjectSpeed; }

inline void AIDropObject::SetActive(bool active)
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

inline EDropObjectType AIDropObject::GetType(){ return dropObjectType; }
inline FSprite* AIDropObject::GetSprite(){ return dropObject; }
inline int AIDropObject::GetDropObjectSpeed(){ return dropObjectSpeed; }

inline bool AIDropObject::GroundCollision()
{
    if(dropObject->getPositionY() <= DataHandler::COLLECT_GAME_GROUND_COLLISION_Y)
    {
        return true;
    }
    return false;
}

FORCEINLINE bool AIDropObject::IsDead() { return bIsDead_; }
FORCEINLINE void AIDropObject::SetDead(bool bIsDead) { bIsDead_ = bIsDead; };

FORCEINLINE bool AIDropObject::IsActive() { return bIsActive_; }

#endif /* defined(__Hazelnut__AIDropObject__) */
