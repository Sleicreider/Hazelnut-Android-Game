//
//  AIDropObject.cpp
//  Hazelnut
//
//  Created by Dominik Reisner on 13.11.14.
//
//

#include "AIDropObject.h"
#include "InGameScene.h"
#include "DataHandler.h"

#include "FUtil.h"

AIDropObject::AIDropObject(FrameworkScene* scene)
: scene(scene)
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
    
    if(dropObjectType == EDropObjectType::HAZELNUT)
    {
        fileName = DataHandler::TEXTURE_COLLECT_GAME_HAZELNUT;
    }
    else if(dropObjectType == EDropObjectType::WASTE)
    {
        fileName = DataHandler::TEXTURE_COLLECT_GAME_WASTE;
    }
    else if(dropObjectType == EDropObjectType::APPLE)
    {
        fileName = DataHandler::TEXTURE_COLLECT_GAME_APPLE;
    }
    else if(dropObjectType == EDropObjectType::HEART)
    {
        fileName = DataHandler::TEXTURE_COLLECT_GAME_HEART;
    }
    else if(dropObjectType == EDropObjectType::COIN)
    {
        fileName = DataHandler::TEXTURE_COLLECT_GAME_COIN;
    }
    
    //Position at when object is created
    dropObject = FSprite::create(fileName, FUtil::GenerateETC1AlphaString(fileName));
    dropObject->setAnchorPoint(Vec2(0.5,0.5));
    dropObject->setPositionY(DataHandler::COLLECT_GAME_SQUIRREL_POSY_START);
    dropObject->setZOrder(1);

    
    scene->addChild(dropObject);
}



void AIDropObject::Remove()
{
    scene->removeChild(dropObject);
}

void AIDropObject::DeathAnimation()
{
    bIsDead_ = true;
    scene->AddTickable(timeframe_death_anim_);
    timeframe_death_anim_.Start(milliseconds(700));
    
    FadeTo* fade = FadeTo::create(0.7, 0);
    dropObject->runAction(fade);
}

void AIDropObject::DeathAnimationBroken()
{
    bIsDead_ = true;
    scene->AddTickable(timeframe_death_anim_);
    
    std::string filename = "";
    int32_t size = 0;
    
    if(dropObjectType == EDropObjectType::APPLE)
    {
        filename = DataHandler::TEXTURE_COLLECT_GAME_APPLE_BROKEN;
        size = DataHandler::TEXTURE_COLLECT_GAME_APPLE_BROKEN_SIZE;
    }
    else
    {
        filename = DataHandler::TEXTURE_COLLECT_GAME_HAZELNUT_BROKEN;
        size = DataHandler::TEXTURE_COLLECT_GAME_HAZELNUT_BROKEN_SIZE;
    }
    
    dropObject->setTexture(Director::getInstance()->getTextureCache()->addImage(filename));
    Director::getInstance()->getTextureCache()->getTextureForKey(filename);
    dropObject->setTextureRect(Rect(0, 0, size, size));
    
    timeframe_death_anim_.Start(milliseconds(1200));
    
    FadeTo* fade = FadeTo::create(1.2, 0);
    dropObject->runAction(fade);
}

void AIDropObject::DeathAnimationHeart()
{
    bIsDead_ = true;
    scene->AddTickable(timeframe_death_anim_);
    
    Vector<SpriteFrame*> animFrames = Vector<SpriteFrame*>(6);
    
    animFrames.pushBack(SpriteFrame::create(DataHandler::TEXTURE_COLLECT_GAME_HEART,        Rect(0,0,100,100)));
    animFrames.pushBack(SpriteFrame::create(DataHandler::TEXTURE_COLLECT_GAME_HEART_ANIM_1, Rect(0,0,100,100)));
    animFrames.pushBack(SpriteFrame::create(DataHandler::TEXTURE_COLLECT_GAME_HEART_ANIM_2, Rect(0,0,100,100)));
    animFrames.pushBack(SpriteFrame::create(DataHandler::TEXTURE_COLLECT_GAME_HEART_ANIM_3, Rect(0,0,100,100)));
    animFrames.pushBack(SpriteFrame::create(DataHandler::TEXTURE_COLLECT_GAME_HEART_ANIM_4, Rect(0,0,100,100)));
    animFrames.pushBack(SpriteFrame::create(DataHandler::TEXTURE_COLLECT_GAME_HEART_ANIM_5, Rect(0,0,100,100)));
    
    auto animation = Animation::createWithSpriteFrames(animFrames, 0.11f);
    auto animate = Animate::create(animation);
    //    animation->setLoops(10);
    
    
//    dropObject->runAction(animate);
    
#pragma message WARN("use action->isDone() and not timeframe")
    timeframe_death_anim_.Start(milliseconds(2000));
    
    FadeTo* fade = FadeTo::create(1.0, 0);
    
    Sequence* seq = Sequence::create(animate,fade,NULL);
    
    dropObject->runAction(seq);
}

bool AIDropObject::DeathAnimationHasFinished()
{
    bool ret = timeframe_death_anim_.WasRunning();
    
    if(ret)
    {
        scene->RemoveTickable(timeframe_death_anim_);
    }
    
    return ret;
}