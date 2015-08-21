//
//  AI.cpp
//  Hazelnut
//
//  Created by Dominik Reisner on 13.11.14.
//
//

#include "AI.h"
#include "DataHandler.h"
#include "FSprite.h"
#include "FUtil.h"

AI::AI(FrameworkScene* scene)
: scene(scene)
, vecInactiveObjects()
, heart_counter_(0)

, c_hazelnut_(0)
, c_waste_(0)
, c_apple_(0)
, c_heart_(0)
, c_coin_(0)

, bCanDropHeart_(true)
{
}

void AI::InitAI(cocos2d::Sprite *aiObject)
{
    this->aiObject = aiObject;
    aiPosX = aiObject->getPositionX();
    
    //CHECK IF MOVEMENT AND DROP ARE ALWAYS THE SAME
    srand ( time(NULL) );
    randMoveValue = rand() % (DataHandler::GAME_RESOLUTION_WIDTH-100) + 100;
    //    randDropWaitValue = rand() % 5 + 1;
    randDropWaitValueMS =  rand() % 3000 + 500;
    
    aiPrevTimer = t.GetCurrentTimeInSeconds();
    aiPrevTimerMS = t.GetCurrentTimeInMilliseconds();
    
    counter = 0;
    
}

void AI::Movement(int squirrelSpeed, int dropObjectSpeedMin,int dropObjectSpeedMax,int dropIntervalMin,int dropIntervalMax, int hazelnut_speed)
{
    if((aiObject->getPositionX() >= randMoveValue && aiPrevPosX <= randMoveValue) ||
       (aiObject->getPositionX() <= randMoveValue && aiPrevPosX >= randMoveValue))
    {
        randMoveValue = rand() % DataHandler::GAME_RESOLUTION_WIDTH + 1;
    }
    
    aiPrevPosX = aiPosX;
    
    if(randMoveValue > aiObject->getPositionX())
    {
        aiPosX += squirrelSpeed;
    }
    else
    {
        aiPosX -= squirrelSpeed;
    }
    
    aiObject->setPositionX(aiPosX);
    
    DropBehaviour(dropObjectSpeedMin,dropObjectSpeedMax,dropIntervalMin,dropIntervalMax,hazelnut_speed);
    DropObjectMovement();
    
}

void AI::DropBehaviour(int dropObjectSpeedMin,int dropObjectSpeedMax, int dropIntervalMin,int dropIntervalMax, int hazelnut_speed)
{
    if((aiPrevTimerMS.count() + randDropWaitValueMS) <= t.GetCurrentTimeInMilliseconds().count())
    {
        //randDropWaitValue = (std::chrono::milliseconds) (rand() % 5000 + 1000);
        randDropWaitValueMS = rand() % dropIntervalMax + dropIntervalMin;
        aiPrevTimerMS = t.GetCurrentTimeInMilliseconds();
        
        //RAND DROP TYPE
        randDropObjectTypeValue = rand() % GetMaxDropChance() + 1;
        //RAND DROP SPEED FOR EACH DROP OBJECT
        randDropObjectSpeedValue = rand() % dropObjectSpeedMax + dropObjectSpeedMin;
        
        //Assign Type befor creating a DropObject
        SpawnObject();
        
        //        for(int i = 0; i < 4; i++)
        //        {
        //            SpawnObject();
        //        }
        
        
        if (vecDropObjects[vecDropObjects.size()-1]->GetType() == EDropObjectType::HAZELNUT)
        {
            vecDropObjects[vecDropObjects.size() - 1]->SetDropObjectSpeed(hazelnut_speed);
        }
        
        
        //        AIDropObject dropObject(scene);
        //        DropObjectTypeAssignment(dropObject);
        //        dropObject.SetDropObjectSpeed(randDropObjectSpeedValue);
        //        dropObject.CreateDropObject();
        //        dropObject.GetSprite()->setPositionX(aiPosX-30);
        //
        //        vecDropObjects.push_back(dropObject);
    }
}

void AI::DropObjectMovement()
{
    hitGroundCounter = 0;
    
    for(int i = 0; i < vecDropObjects.size(); i++)
    {
        if(!vecDropObjects.at(i)->GroundCollision())
        {
            vecDropObjects.at(i)->SetPositionY(vecDropObjects.at(i)->GetSprite()->getPositionY() - vecDropObjects.at(i)->GetDropObjectSpeed());
        }
        else
        {
            if(!vecDropObjects[i]->IsDead())
            {
                if(vecDropObjects[i]->GetType() == EDropObjectType::APPLE || vecDropObjects[i]->GetType() == EDropObjectType::HAZELNUT)
                {
                    vecDropObjects[i]->DeathAnimationBroken();
                }
                else if(vecDropObjects[i]->GetType() == EDropObjectType::HEART)
                {
                    vecDropObjects[i]->DeathAnimationHeart();
                }
                else
                {
                    vecDropObjects[i]->DeathAnimation();
                }
                
                //If a APPLE or HAZELNUT dropped on the ground increase the hitGroundCounter
                if(vecDropObjects.at(i)->GetType() == EDropObjectType::HAZELNUT)
                {
                    hitGroundCounter++;
                }
            }
            
            //move to inactive object to avoid collision detection, but item remains active
            vecDanglingObjects.push_back(std::move(vecDropObjects.at(i)));
            vecDropObjects.erase(vecDropObjects.begin() + i);
            i--;
        }
        
        
    }
    
    //animation objects
    for(int k = 0; k < vecDanglingObjects.size(); k++)
    {
        if(vecDanglingObjects[k]->DeathAnimationHasFinished())
        {
            //DropObject HIT GROUND
            
            CCLOG("animation of %d has finished inactive object now", k);
            
            vecDanglingObjects.at(k)->SetActive(false);
            vecDanglingObjects.at(k)->SetPositionX(DataHandler::COLLECT_GAME_SQUIRREL_POSY_START);
            vecDanglingObjects.at(k)->SetPositionY(aiPosX);
            
            vecInactiveObjects.push_back(std::move(vecDanglingObjects.at(k)));
            vecDanglingObjects.erase(vecDanglingObjects.begin() + k);
            k--;
        }
    }
}

void AI::DropObjectTypeAssignment(AIDropObject* dropObject)
{
    withAnimation = false;
    //Hazelnut
    if(randDropObjectTypeValue <= c_hazelnut_)
    {
        dropObject->SetType(EDropObjectType::HAZELNUT);
    }
    //Waste
    else if(randDropObjectTypeValue <= (c_waste_ + c_hazelnut_) && randDropObjectTypeValue > c_hazelnut_)
    {
        dropObject->SetType(EDropObjectType::WASTE);
    }
    //Apple
    else if (randDropObjectTypeValue <= (c_hazelnut_ + c_waste_ + c_apple_) && randDropObjectTypeValue > (c_hazelnut_ + c_waste_))
    {
        dropObject->SetType(EDropObjectType::APPLE);
    }
    else if (randDropObjectTypeValue <= (c_hazelnut_ + c_waste_ + c_apple_ + c_heart_) && randDropObjectTypeValue > (c_hazelnut_ + c_waste_ + c_apple_))
    {
        dropObject->SetType(EDropObjectType::HEART);
        withAnimation = true;
        sprite_animation_ = FSprite::EAnimation::SCALE;
    }
    else if (randDropObjectTypeValue > (c_hazelnut_ + c_waste_ + c_apple_ + c_heart_))
    {
        dropObject->SetType(EDropObjectType::COIN);
        withAnimation = true;
        sprite_animation_ = FSprite::EAnimation::ROTATE;
    }
}

void AI::SpawnObject()
{
    if(vecInactiveObjects.size() > 0)
    {
        std::string fileName = "";
        int size = 0;
        
        DropObjectTypeAssignment(vecInactiveObjects[0].get());
        
        if (heart_counter_ > 0 || !bCanDropHeart_)
        {
            while (vecInactiveObjects[0]->GetType() == EDropObjectType::HEART)
            {
                randDropObjectTypeValue = GetNewDropTypeValue();
                DropObjectTypeAssignment(vecInactiveObjects[0].get());
            }
        }
        else if (vecInactiveObjects[0]->GetType() == EDropObjectType::HEART)
        {
            bCanDropHeart_ = false;
            heart_counter_++;
        }
        
        if(vecInactiveObjects[0]->GetType() == EDropObjectType::HAZELNUT)
        {
            fileName = DataHandler::TEXTURE_COLLECT_GAME_HAZELNUT;
            size = DataHandler::TEXTURE_COLLECT_GAME_HAZELNUT_SIZE;
        }
        else if(vecInactiveObjects[0]->GetType() == EDropObjectType::WASTE)
        {
            fileName = DataHandler::TEXTURE_COLLECT_GAME_WASTE;
            size = DataHandler::TEXTURE_COLLECT_GAME_WASTE_SIZE;
        }
        else if(vecInactiveObjects[0]->GetType() == EDropObjectType::APPLE)
        {
            fileName = DataHandler::TEXTURE_COLLECT_GAME_APPLE;
            size = DataHandler::TEXTURE_COLLECT_GAME_APPLE_SIZE;
        }
        else if(vecInactiveObjects[0]->GetType() == EDropObjectType::HEART)
        {
            fileName = DataHandler::TEXTURE_COLLECT_GAME_HEART;
            size = DataHandler::TEXTURE_COLLECT_GAME_HEART_SIZE;
        }
        else if(vecInactiveObjects[0]->GetType() == EDropObjectType::COIN)
        {
            fileName = DataHandler::TEXTURE_COLLECT_GAME_COIN;
            size = DataHandler::TEXTURE_COLLECT_GAME_COIN_SIZE;
        }
        
        // GET TEXTURE BY NAME!!!! DONT ADD IT AGAIN (COCOS CHECKS IT BUT STILL DONT DO IT)
        vecInactiveObjects[0]->GetSprite()->setTexture(CCTextureCache::sharedTextureCache()->addImage(fileName));
        CCTextureCache::getInstance()->getTextureForKey(fileName);
        vecInactiveObjects[0]->GetSprite()->setTextureRect(Rect(0, 0, size, size));
        
        vecInactiveObjects[0]->GetSprite()->UpdateAlphaTexture(FUtil::GenerateETC1AlphaString(fileName));
        
        vecInactiveObjects[0]->SetActive(true);
        
        vecInactiveObjects[0]->SetDropObjectSpeed(randDropObjectSpeedValue);
        vecInactiveObjects[0]->GetSprite()->setPositionX(aiPosX-30);
        vecInactiveObjects[0]->GetSprite()->setPositionY(DataHandler::COLLECT_GAME_SQUIRREL_POSY_START);
        
        vecInactiveObjects[0]->GetSprite()->Reset();
        vecInactiveObjects[0]->WithAnimation(withAnimation,sprite_animation_);
        
        vecInactiveObjects[0]->GetSprite()->setOpacity(255);
        vecInactiveObjects[0]->GetSprite()->stopAllActions();
        vecInactiveObjects[0]->SetDead(false);
        
        vecDropObjects.push_back(std::move(vecInactiveObjects[0]));
        vecInactiveObjects.erase(vecInactiveObjects.begin() + 0);
        
        CCLOG("FROM OBJECT POOL activeSize=%lu inactivSize=%lu",vecDropObjects.size(),vecInactiveObjects.size());
        
    }
    else
    {
        std::shared_ptr<AIDropObject> dropObject = std::make_shared<AIDropObject>(scene);
        
        
        DropObjectTypeAssignment(dropObject.get());
        
        if (heart_counter_ > 0 || !bCanDropHeart_)
        {
            while (dropObject->GetType() == EDropObjectType::HEART)
            {
                randDropObjectTypeValue = GetNewDropTypeValue();
                DropObjectTypeAssignment(dropObject.get());
            }
        }
        else if (dropObject->GetType() == EDropObjectType::HEART)
        {
            bCanDropHeart_ = false;
            heart_counter_++;
        }
        
        
        
        dropObject->SetDropObjectSpeed(randDropObjectSpeedValue);
        dropObject->CreateDropObject();
        
        dropObject->WithAnimation(withAnimation,sprite_animation_);
        
        dropObject->GetSprite()->setPositionX(aiPosX-30);
        
        vecDropObjects.push_back(std::move(dropObject));
    }
}

void AI::GenearteNewDropTimer(int dropObjectSpeedMin,int dropObjectSpeedMax, int dropIntervalMin,int dropIntervalMax)
{
    randDropWaitValueMS = rand() % dropIntervalMax + dropIntervalMin;
    aiPrevTimerMS = t.GetCurrentTimeInMilliseconds();
    
    //RAND DROP TYPE
    randDropObjectTypeValue = rand() % GetMaxDropChance() + 1;
    //RAND DROP SPEED FOR EACH DROP OBJECT
    randDropObjectSpeedValue = rand() % dropObjectSpeedMax + dropObjectSpeedMin;
}


void AI::SetDropChance(int32_t c_hazelnut, int32_t c_waste, int32_t c_apple, int32_t c_heart, int32_t c_coin)
{
    c_hazelnut_ = c_hazelnut;
    c_waste_ = c_waste;
    c_apple_ = c_apple;
    c_heart_ = c_heart;
    c_coin_ = c_coin;
}