//
//  AIDropObject.cpp
//  Hazelnut
//
//  Created by Dominik Reisner on 13.11.14.
//
//

//DONE STYLE CHANGED!
//TODO Check for better code etc.

#include "AIDropObject.h"
#include "InGameScene.h"
#include "DataHandler.h"

#include "FUtil.h"

AIDropObject::AIDropObject(FrameworkScene* scene)
: scene_(scene)
, bIsDead_(false)
, bIsActive_(true)
{
}

AIDropObject::~AIDropObject()
{
}

void AIDropObject::CreateDropObject()
{
    std::string fileName;
    
    if(drop_object_type_ == EDropObjectType::HAZELNUT)
    {
        fileName = DataHandler::TEXTURE_COLLECT_GAME_HAZELNUT;
    }
    else if(drop_object_type_ == EDropObjectType::WASTE)
    {
        fileName = DataHandler::TEXTURE_COLLECT_GAME_WASTE;
    }
    else if(drop_object_type_ == EDropObjectType::APPLE)
    {
        fileName = DataHandler::TEXTURE_COLLECT_GAME_APPLE;
    }
    else if(drop_object_type_ == EDropObjectType::HEART)
    {
        fileName = DataHandler::TEXTURE_COLLECT_GAME_HEART;
    }
    else if(drop_object_type_ == EDropObjectType::COIN)
    {
        fileName = DataHandler::TEXTURE_COLLECT_GAME_COIN;
    }
    
    //Position at when object is created
    drop_object_ = FSprite::create(fileName, FUtil::GenerateETC1AlphaString(fileName));
    drop_object_->setAnchorPoint(Vec2(0.5,0.5));
    drop_object_->setPositionY(DataHandler::COLLECT_GAME_SQUIRREL_POSY_START);
    drop_object_->setZOrder(1);

    
    scene_->addChild(drop_object_);
}

void AIDropObject::Remove()
{
    scene_->removeChild(drop_object_);
}

void AIDropObject::DeathAnimation()
{
    bIsDead_ = true;
    scene_->AddTickable(timeframe_death_anim_);
    timeframe_death_anim_.Start(milliseconds(700));
    
    FadeTo* fade = FadeTo::create(0.7, 0);
    drop_object_->runAction(fade);
}

void AIDropObject::DeathAnimationBroken()
{
    bIsDead_ = true;
    scene_->AddTickable(timeframe_death_anim_);
    
    auto filename = std::string{""};
    auto size = 0;
    
    if(drop_object_type_ == EDropObjectType::APPLE)
    {
        filename = DataHandler::TEXTURE_COLLECT_GAME_APPLE_BROKEN;
        size = DataHandler::TEXTURE_COLLECT_GAME_APPLE_BROKEN_SIZE;
    }
    else
    {
        filename = DataHandler::TEXTURE_COLLECT_GAME_HAZELNUT_BROKEN;
        size = DataHandler::TEXTURE_COLLECT_GAME_HAZELNUT_BROKEN_SIZE;
    }
    
    drop_object_->setTexture(Director::getInstance()->getTextureCache()->addImage(filename));
    Director::getInstance()->getTextureCache()->getTextureForKey(filename);
    drop_object_->setTextureRect(Rect(0, 0, size, size));
    
    timeframe_death_anim_.Start(milliseconds(1200));
    
    auto fade = FadeTo::create(1.2, 0);
    drop_object_->runAction(fade);
}

void AIDropObject::DeathAnimationHeart()
{
    bIsDead_ = true;
    scene_->AddTickable(timeframe_death_anim_);
    
    auto animFrames = Vector<SpriteFrame*>(6);
    
    animFrames.pushBack(SpriteFrame::create(DataHandler::TEXTURE_COLLECT_GAME_HEART,        Rect(0,0,100,100)));
    animFrames.pushBack(SpriteFrame::create(DataHandler::TEXTURE_COLLECT_GAME_HEART_ANIM_1, Rect(0,0,100,100)));
    animFrames.pushBack(SpriteFrame::create(DataHandler::TEXTURE_COLLECT_GAME_HEART_ANIM_2, Rect(0,0,100,100)));
    animFrames.pushBack(SpriteFrame::create(DataHandler::TEXTURE_COLLECT_GAME_HEART_ANIM_3, Rect(0,0,100,100)));
    animFrames.pushBack(SpriteFrame::create(DataHandler::TEXTURE_COLLECT_GAME_HEART_ANIM_4, Rect(0,0,100,100)));
    animFrames.pushBack(SpriteFrame::create(DataHandler::TEXTURE_COLLECT_GAME_HEART_ANIM_5, Rect(0,0,100,100)));
    
    auto animation = Animation::createWithSpriteFrames(animFrames, 0.11f);
    auto animate = Animate::create(animation);
    
#pragma message WARN("use action->isDone() and not timeframe")
    timeframe_death_anim_.Start(milliseconds(2000));
    
    auto fade = FadeTo::create(1.0, 0);
    auto seq = Sequence::create(animate,fade,NULL);
    
    drop_object_->runAction(seq);
}

bool AIDropObject::DeathAnimationHasFinished()
{
    auto ret = bool {timeframe_death_anim_.WasRunning()};
    
    if(ret)
    {
        scene_->RemoveTickable(timeframe_death_anim_);
    }
    
    return ret;
}