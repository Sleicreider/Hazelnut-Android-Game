//
//  AI.cpp
//  Hazelnut
//
//  Created by Dominik Reisner on 13.11.14.
//
//

//DONE STYLE CHANGED!
//TODO Check for better code etc.

#include "AI.h"
#include "DataHandler.h"
#include "FSprite.h"
#include "FUtil.h"
#include "InGameScene.h"

AI::AI(FrameworkScene* scene)
: scene_(scene)
, heart_counter_(0)
, c_hazelnut_(0)
, c_waste_(0)
, c_apple_(0)
, c_heart_(0)
, c_coin_(0)
, bCanDropHeart_(true)
{
}

void AI::InitAI(cocos2d::Sprite* ai_object)
{
    ai_object_ = ai_object;
    ai_pos_x_ = ai_object_->getPositionX();
    
    //CHECK IF MOVEMENT AND DROP ARE ALWAYS THE SAME
    srand ( time(NULL) );
    rand_move_value_ = rand() % (DataHandler::GAME_RESOLUTION_WIDTH-100) + 100;
    rand_drop_wait_value_ms_ =  rand() % 3000 + 500;
    
    ai_prev_timer_ = t_.GetCurrentTimeInSeconds();
    ai_prev_timer_ms_ = t_.GetCurrentTimeInMilliseconds();
    
    counter_ = 0;
}

void AI::Movement(int32_t squirrelSpeed, int32_t dropObjectSpeedMin,int32_t dropObjectSpeedMax,int32_t dropIntervalMin,int32_t dropIntervalMax, int32_t hazelnut_speed)
{
    if((ai_object_->getPositionX() >= rand_move_value_ && ai_prev_pos_x_ <= rand_move_value_) ||
       (ai_object_->getPositionX() <= rand_move_value_ && ai_prev_pos_x_ >= rand_move_value_))
    {
        rand_move_value_ = rand() % DataHandler::GAME_RESOLUTION_WIDTH + 1;
    }
    
    ai_prev_pos_x_ = ai_pos_x_;
    
    if(rand_move_value_ > ai_object_->getPositionX())
    {
        ai_pos_x_ += squirrelSpeed;
    }
    else
    {
        ai_pos_x_ -= squirrelSpeed;
    }
    
    ai_object_->setPositionX(ai_pos_x_);
    
    DropBehaviour(dropObjectSpeedMin,dropObjectSpeedMax,dropIntervalMin,dropIntervalMax,hazelnut_speed);
    DropObjectMovement();
}

void AI::DropBehaviour(int32_t dropObjectSpeedMin,int32_t dropObjectSpeedMax, int32_t dropIntervalMin,int32_t dropIntervalMax, int32_t hazelnut_speed)
{
    if((ai_prev_timer_ms_.count() + rand_drop_wait_value_ms_) <= t_.GetCurrentTimeInMilliseconds().count())
    {
        rand_drop_wait_value_ms_ = rand() % dropIntervalMax + dropIntervalMin;
        ai_prev_timer_ms_ = t_.GetCurrentTimeInMilliseconds();
        
        //RAND DROP TYPE
        rand_drop_object_type_value_ = rand() % GetMaxDropChance() + 1;
        //RAND DROP SPEED FOR EACH DROP OBJECT
        rand_drop_object_speed_value_ = rand() % dropObjectSpeedMax + dropObjectSpeedMin;
        
        //Assign Type befor creating a DropObject
        SpawnObject();
        
        if (vec_drop_objects_[vec_drop_objects_.size()-1]->GetType() == EDropObjectType::HAZELNUT)
        {
            vec_drop_objects_[vec_drop_objects_.size() - 1]->SetDropObjectSpeed(hazelnut_speed);
        }
    }
}

void AI::DropObjectMovement()
{
    hit_ground_counter_ = 0;
    
    for(auto i = 0lu; i < vec_drop_objects_.size(); i++)
    {
        if(!vec_drop_objects_.at(i)->GroundCollision())
        {
            vec_drop_objects_.at(i)->SetPositionY(vec_drop_objects_.at(i)->GetSprite()->getPositionY() - vec_drop_objects_.at(i)->GetDropObjectSpeed());
        }
        else
        {
            if(!vec_drop_objects_[i]->IsDead())
            {
                if(vec_drop_objects_[i]->GetType() == EDropObjectType::HAZELNUT)
                {
                    vec_drop_objects_[i]->DeathAnimationBroken();
                    
                    ((InGameScene*)scene_)->subject_.Notify(EEvent::EVENT_HAZELNUT_MISSED);
                }
                else if(vec_drop_objects_[i]->GetType() == EDropObjectType::APPLE)
                {
                    vec_drop_objects_[i]->DeathAnimationBroken();
                    ((InGameScene*)scene_)->subject_.Notify(EEvent::EVENT_APPLE_MISSED);
                }
                else if(vec_drop_objects_[i]->GetType() == EDropObjectType::HEART)
                {
                    vec_drop_objects_[i]->DeathAnimationHeart();
                    ((InGameScene*)scene_)->subject_.Notify(EEvent::EVENT_HEART_MISSED);
                }
                else if(vec_drop_objects_[i]->GetType() == EDropObjectType::WASTE)
                {
                    vec_drop_objects_[i]->DeathAnimation();
                }
                
                //If a APPLE or HAZELNUT dropped on the ground increase the hit_ground_counter_
                if(vec_drop_objects_.at(i)->GetType() == EDropObjectType::HAZELNUT)
                {
                    hit_ground_counter_++;
                }
            }
            
            //move to inactive object to avoid collision detection, but item remains active
            vec_dangling_objects_.push_back(std::move(vec_drop_objects_.at(i)));
            vec_drop_objects_.erase(vec_drop_objects_.begin() + i);
            i--;
        }
        
        
    }
    
    //animation objects
    for(auto k = 0lu; k < vec_dangling_objects_.size(); k++)
    {
        if(vec_dangling_objects_[k]->DeathAnimationHasFinished())
        {
            //DropObject HIT GROUND
            vec_dangling_objects_.at(k)->SetActive(false);
            vec_dangling_objects_.at(k)->SetPositionX(DataHandler::COLLECT_GAME_SQUIRREL_POSY_START);
            vec_dangling_objects_.at(k)->SetPositionY(ai_pos_x_);
            
            vec_inactive_objects_.push_back(std::move(vec_dangling_objects_.at(k)));
            vec_dangling_objects_.erase(vec_dangling_objects_.begin() + k);
            k--;
        }
    }
}

void AI::DropObjectTypeAssignment(AIDropObject* dropObject)
{
    bWithAnimation_ = false;
    //Hazelnut
    if(rand_drop_object_type_value_ <= c_hazelnut_)
    {
        dropObject->SetType(EDropObjectType::HAZELNUT);
    }
    //Waste
    else if(rand_drop_object_type_value_ <= (c_waste_ + c_hazelnut_) && rand_drop_object_type_value_ > c_hazelnut_)
    {
        dropObject->SetType(EDropObjectType::WASTE);
    }
    //Apple
    else if (rand_drop_object_type_value_ <= (c_hazelnut_ + c_waste_ + c_apple_) && rand_drop_object_type_value_ > (c_hazelnut_ + c_waste_))
    {
        dropObject->SetType(EDropObjectType::APPLE);
    }
    else if (rand_drop_object_type_value_ <= (c_hazelnut_ + c_waste_ + c_apple_ + c_heart_) && rand_drop_object_type_value_ > (c_hazelnut_ + c_waste_ + c_apple_))
    {
        dropObject->SetType(EDropObjectType::HEART);
        bWithAnimation_ = true;
        sprite_animation_ = FSprite::EAnimation::SCALE;
    }
    else if (rand_drop_object_type_value_ > (c_hazelnut_ + c_waste_ + c_apple_ + c_heart_))
    {
        dropObject->SetType(EDropObjectType::COIN);
        bWithAnimation_ = true;
        sprite_animation_ = FSprite::EAnimation::ROTATE;
    }
}

void AI::SpawnObject()
{
    if(vec_inactive_objects_.size() > 0)
    {
        auto fileName = std::string{""};
        auto size = 0;
        
        DropObjectTypeAssignment(vec_inactive_objects_[0].get());
        
        if (heart_counter_ > 0 || !bCanDropHeart_)
        {
            while (vec_inactive_objects_[0]->GetType() == EDropObjectType::HEART)
            {
                rand_drop_object_type_value_ = GetNewDropTypeValue();
                DropObjectTypeAssignment(vec_inactive_objects_[0].get());
            }
        }
        else if (vec_inactive_objects_[0]->GetType() == EDropObjectType::HEART)
        {
            bCanDropHeart_ = false;
            heart_counter_++;
        }
        
        if(vec_inactive_objects_[0]->GetType() == EDropObjectType::HAZELNUT)
        {
            fileName = DataHandler::TEXTURE_COLLECT_GAME_HAZELNUT;
            size = DataHandler::TEXTURE_COLLECT_GAME_HAZELNUT_SIZE;
        }
        else if(vec_inactive_objects_[0]->GetType() == EDropObjectType::WASTE)
        {
            fileName = DataHandler::TEXTURE_COLLECT_GAME_WASTE;
            size = DataHandler::TEXTURE_COLLECT_GAME_WASTE_SIZE;
        }
        else if(vec_inactive_objects_[0]->GetType() == EDropObjectType::APPLE)
        {
            fileName = DataHandler::TEXTURE_COLLECT_GAME_APPLE;
            size = DataHandler::TEXTURE_COLLECT_GAME_APPLE_SIZE;
        }
        else if(vec_inactive_objects_[0]->GetType() == EDropObjectType::HEART)
        {
            fileName = DataHandler::TEXTURE_COLLECT_GAME_HEART;
            size = DataHandler::TEXTURE_COLLECT_GAME_HEART_SIZE;
        }
        else if(vec_inactive_objects_[0]->GetType() == EDropObjectType::COIN)
        {
            fileName = DataHandler::TEXTURE_COLLECT_GAME_COIN;
            size = DataHandler::TEXTURE_COLLECT_GAME_COIN_SIZE;
        }
        
        // GET TEXTURE BY NAME!!!! DONT ADD IT AGAIN (COCOS CHECKS IT BUT STILL DONT DO IT)
        vec_inactive_objects_[0]->GetSprite()->setTexture(Director::getInstance()->getTextureCache()->addImage(fileName));
        Director::getInstance()->getTextureCache()->getTextureForKey(fileName);
        vec_inactive_objects_[0]->GetSprite()->setTextureRect(Rect(0, 0, size, size));
        
        vec_inactive_objects_[0]->GetSprite()->UpdateAlphaTexture(FUtil::GenerateETC1AlphaString(fileName));
        
        vec_inactive_objects_[0]->SetActive(true);
        
        vec_inactive_objects_[0]->SetDropObjectSpeed(rand_drop_object_speed_value_);
        vec_inactive_objects_[0]->GetSprite()->setPositionX(ai_pos_x_-30);
        vec_inactive_objects_[0]->GetSprite()->setPositionY(DataHandler::COLLECT_GAME_SQUIRREL_POSY_START);
        
        vec_inactive_objects_[0]->GetSprite()->Reset();
        vec_inactive_objects_[0]->WithAnimation(bWithAnimation_,sprite_animation_);
        
        vec_inactive_objects_[0]->GetSprite()->setOpacity(255);
        vec_inactive_objects_[0]->GetSprite()->stopAllActions();
        vec_inactive_objects_[0]->SetDead(false);
        
        vec_drop_objects_.push_back(std::move(vec_inactive_objects_[0]));
        vec_inactive_objects_.erase(vec_inactive_objects_.begin() + 0);
    }
    else
    {
        auto dropObject = std14::make_unique<AIDropObject>(scene_);//std::unique_ptr<AIDropObject>(new AIDropObject(scene_));
        
        DropObjectTypeAssignment(dropObject.get());
        
        if (heart_counter_ > 0 || !bCanDropHeart_)
        {
            while (dropObject->GetType() == EDropObjectType::HEART)
            {
                rand_drop_object_type_value_ = GetNewDropTypeValue();
                DropObjectTypeAssignment(dropObject.get());
            }
        }
        else if (dropObject->GetType() == EDropObjectType::HEART)
        {
            bCanDropHeart_ = false;
            heart_counter_++;
        }
        
        
        dropObject->SetDropObjectSpeed(rand_drop_object_speed_value_);
        dropObject->CreateDropObject();
        
        dropObject->WithAnimation(bWithAnimation_,sprite_animation_);
        
        dropObject->GetSprite()->setPositionX(ai_pos_x_-30);
        
        vec_drop_objects_.push_back(std::move(dropObject));
    }
}

void AI::GenearteNewDropTimer(int32_t dropObjectSpeedMin, int32_t dropObjectSpeedMax, int32_t dropIntervalMin, int32_t dropIntervalMax)
{
    rand_drop_wait_value_ms_ = rand() % dropIntervalMax + dropIntervalMin;
    ai_prev_timer_ms_ = t_.GetCurrentTimeInMilliseconds();
    
    //RAND DROP TYPE
    rand_drop_object_type_value_ = rand() % GetMaxDropChance() + 1;
    //RAND DROP SPEED FOR EACH DROP OBJECT
    rand_drop_object_speed_value_ = rand() % dropObjectSpeedMax + dropObjectSpeedMin;
}

void AI::SetDropChance(int32_t c_hazelnut, int32_t c_waste, int32_t c_apple, int32_t c_heart, int32_t c_coin)
{
    c_hazelnut_ = c_hazelnut;
    c_waste_ = c_waste;
    c_apple_ = c_apple;
    c_heart_ = c_heart;
    c_coin_ = c_coin;
}