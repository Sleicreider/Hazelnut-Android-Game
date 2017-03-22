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
        label_archievment_->setColor(Color3B::GREEN);
		label_archievment_->setAnchorPoint(Vec2(0.5, 0.5));
		label_archievment_->setHorizontalAlignment(TextHAlignment::CENTER);
		int32_t desired_x = label_archievment_->getContentSize().width;
		int32_t desired_y = label_archievment_->getContentSize().height;
		label_archievment_->setPosition(DataHandler::GAME_RESOLUTION_WIDTH - desired_x - 100, -DataHandler::GAME_RESOLUTION_HEIGHT + 100);
        label_archievment_->setZOrder(10);
        addChild(label_archievment_);

        setContentSize(Size(desired_x,desired_y));
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
