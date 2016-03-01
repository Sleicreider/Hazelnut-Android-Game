//
//  AchievementNotification.cpp
//  Hazelnut
//
//  Created by Dominik Reisner on 20.01.16.
//
//

#include "AchievementNotification.h"
#include "FSprite.h"

AchievementNotification::AchievementNotification()
{
    this->scheduleUpdate();
}

AchievementNotification::~AchievementNotification()
{
}


AchievementNotification* AchievementNotification::create(const std::string& text)
{
    AchievementNotification* ret = new (std::nothrow) AchievementNotification();
    if (ret && ret->InitWithText(text))
    {
        ret->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(ret);
    }
    
    return ret;
}
AchievementNotification* AchievementNotification::create(const std::string& text, const std::string& reward_sprite_filename)
{
    
    AchievementNotification* ret = new (std::nothrow) AchievementNotification();
    
    
    if (ret && ret->InitWithText(text))
    {
        FSprite* sprite = FSprite::create(reward_sprite_filename);
        
        if(sprite != nullptr)
        {
            
        }
        
        ret->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(ret);
    }
    
    return ret;
}

bool AchievementNotification::InitWithText(const std::string& text)
{
    if(Node::init())
    {
        label_archievment_ = Label::createWithTTF(text, DataHandler::FONT_QUARMIC_SANS, 50);
        label_archievment_->setColor(Color3B::RED);
        label_archievment_->setZOrder(1);
//        label_archievment_->setCascadeColorEnabled(true);
        addChild(label_archievment_);
        
        sprite_bg_ = FSprite::create(DataHandler::TEXTURE_ACHIEVMENTS_BG);
        sprite_bg_->setZOrder(0);
        sprite_bg_->setOpacity(255/2);
        int32_t x = sprite_bg_->getTexture()->getContentSize().width;
        int32_t y = sprite_bg_->getTexture()->getContentSize().height;
        int32_t desired_x = label_archievment_->getContentSize().width;
        int32_t desired_y = label_archievment_->getContentSize().height;
        
        sprite_bg_->setScaleX(desired_x/(float)x);
        sprite_bg_->setScaleY(desired_y/(float)y);
        setContentSize(Size(desired_x,desired_y));
//        sprite_bg_->setCascadeColorEnabled(true);
        addChild(sprite_bg_);
        
        setOpacity(0);
        
        setCascadeOpacityEnabled(true);
        FUtil::SetActiveAndVisible(this, false);
        
        FrameworkScene::GetActiveScene()->AddTickable(timer_);
        
        return true;
    }
    return false;
}



void AchievementNotification::update(float delta)
{
    if(timer_.WasRunning())
    {
        func_task();
    }
}
