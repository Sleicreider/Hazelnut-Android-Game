//
//  AchievementManager.cpp
//  Hazelnut
//
//  Created by Dominik Reisner on 09.02.16.
//
//

#include "AchievementManager.h"
#include "FrameworkScene.h"
#include "AchievementNotification.h"

std::unique_ptr<AchievementManager> AchievementManager::instance_;

AchievementManager::AchievementManager(const tmp&)
{

    
    ui_queue_.reserve(5);
}

void AchievementManager::LoadAchievmentsFromFile()
{
    
}

void AchievementManager::SaveAchievmentsToFile()
{
    
}

void AchievementManager::UpdateAchievmentCurrentPoints(EAchievements type, int32_t points)
{
    achievment_container_[type].current_points = points;
}

void AchievementManager::UnlockAchievement(EAchievements type)
{
    achievment_container_[type].unlocked = true;
    
    ui_queue_.push_back(type);
    
    if(ui_notification_ != nullptr)
    {
        FrameworkScene::GetActiveScene()->removeChild(ui_notification_);
    }
    
    //just create it every time we need to display, not sure if cocos alwys garbage collect the ptr when the scene changes
    auto data = &DataHandler::ACHIEVEMENT_STATIC_MAP.at(type);
    ui_notification_ = AchievementNotification::create(data->text, data->sprite_file_name);
    ui_notification_->setPosition(0 + ui_notification_->getContentSize().width/2.f,DataHandler::GAME_RESOLUTION_HEIGHT - ui_notification_->getContentSize().height/2.f);
    
    FrameworkScene::GetActiveScene()->addChild(ui_notification_);
//    ui_notification_->SetText("next text");
    ui_notification_->Show(this, &AchievementManager::NotificationEnd);
}

bool AchievementManager::IsAchievementUnlocked(EAchievements type)
{
    return achievment_container_[type].unlocked;
}

void AchievementManager::NotificationEnd()
{
    ui_queue_.erase(ui_queue_.begin());
    
    if(ui_queue_.size() > 0)
    {
        ui_notification_->SetText("next text");
        ui_notification_->Show(this, &AchievementManager::NotificationEnd);
    }
}
