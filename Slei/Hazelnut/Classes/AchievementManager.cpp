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
#include "FileOperation.h"

std::unique_ptr<AchievementManager> AchievementManager::instance_;

AchievementManager::AchievementManager()
{
#pragma WARN message("maybe use the static map from DataHandler")
    achievment_container_[EAchievements::NO_HAZ_MISSED_L1].str = "NO_HAZ_MISSED_L1";
    achievment_container_[EAchievements::NO_HAZ_MISSED_L3].str = "NO_HAZ_MISSED_L3";
    achievment_container_[EAchievements::NO_HAZ_MISSED_L5].str = "NO_HAZ_MISSED_L5";
    achievment_container_[EAchievements::NO_WASTE_CATCHED_L2].str = "NO_WASTE_CATCHED_L2";
    achievment_container_[EAchievements::NO_WASTE_CATCHED_L4].str = "NO_WASTE_CATCHED_L4";
    achievment_container_[EAchievements::NO_WASTE_CATCHED_L6].str = "NO_WASTE_CATCHED_L6";
    achievment_container_[EAchievements::NO_WASTE_CATCHED_L8].str = "NO_WASTE_CATCHED_L8";
    achievment_container_[EAchievements::NO_WASTE_CATCHED_L10].str = "NO_WASTE_CATCHED_L10";
    achievment_container_[EAchievements::NO_APPLE_MISSED_L4].str = "NO_APPLE_MISSED_L4";
    achievment_container_[EAchievements::NO_APPLE_MISSED_L6].str = "NO_APPLE_MISSED_L6";
    achievment_container_[EAchievements::NO_APPLE_MISSED_L10].str = "NO_APPLE_MISSED_L10";
    achievment_container_[EAchievements::HEART_BAR_FILLED].str = "HEART_BAR_FILLED";
    achievment_container_[EAchievements::NO_HEART_MISSED_L3].str = "NO_HEART_MISSED_L3";
    achievment_container_[EAchievements::NO_HEART_MISSED_L6].str = "NO_HEART_MISSED_L6";
    achievment_container_[EAchievements::NO_HEART_MISSED_L9].str = "NO_HEART_MISSED_L9";
    achievment_container_[EAchievements::COINS_COLLECTED_5].str = "COINS_COLLECTED_5";
    achievment_container_[EAchievements::COINS_COLLECTED_10].str = "COINS_COLLECTED_10";
    achievment_container_[EAchievements::OVERALL_GAMES_STARTED_100].str = "OVERALL_GAMES_STARTED_100";
    achievment_container_[EAchievements::OVERALL_COINS_COLLECTED_STAGE_1].str = "OVERALL_COINS_COLLECTED_STAGE_1";
    achievment_container_[EAchievements::OVERALL_COINS_COLLECTED_STAGE_2].str = "OVERALL_COINS_COLLECTED_STAGE_2";
    achievment_container_[EAchievements::OVERALL_COINS_COLLECTED_STAGE_3].str = "OVERALL_COINS_COLLECTED_STAGE_3";
    achievment_container_[EAchievements::OVERALL_COINS_COLLECTED_STAGE_4].str = "OVERALL_COINS_COLLECTED_STAGE_4";
    achievment_container_[EAchievements::ALL_ACHIEVEMENTS_UNLOCKED].str = "ALL_ACHIEVEMENTS_UNLOCKED";

    achievment_container_[EAchievements::OVERALL_GAMES_STARTED_100].str_curr = "OVERALL_GAMES_STARTED_100.curr";
    achievment_container_[EAchievements::OVERALL_COINS_COLLECTED_STAGE_1].str_curr = "OVERALL_COINS_COLLECTED_STAGE_1.curr";
    achievment_container_[EAchievements::OVERALL_COINS_COLLECTED_STAGE_2].str_curr = "OVERALL_COINS_COLLECTED_STAGE_2.curr";
    achievment_container_[EAchievements::OVERALL_COINS_COLLECTED_STAGE_3].str_curr = "OVERALL_COINS_COLLECTED_STAGE_3.curr";
    achievment_container_[EAchievements::OVERALL_COINS_COLLECTED_STAGE_4].str_curr = "OVERALL_COINS_COLLECTED_STAGE_4.curr";
    achievment_container_[EAchievements::ALL_ACHIEVEMENTS_UNLOCKED].str_curr = "ALL_ACHIEVEMENTS_UNLOCKED.curr";

//    ui_queue_.reserve(5);
}

void AchievementManager::LoadAchievmentsFromFile()
{
    int32_t a_counter = 0;
    
    for(auto iterator = achievment_container_.begin(); iterator != achievment_container_.end(); iterator++)
    {
        int unlocked = false;
        FileOperation::GetInt(iterator->second.str, unlocked);
        
        if(unlocked > 0)
        {
            //count all unlocked achievments
            if(iterator->first != EAchievements::ALL_ACHIEVEMENTS_UNLOCKED)
            {
                a_counter++;
            }

            iterator->second.unlocked = true;
        }
        else
        {
            iterator->second.unlocked = false;
        }
        
        
        CCLOGERROR("%s = %s", iterator->second.str.c_str(),iterator->second.unlocked ? "1" : "0");


        if(iterator->second.str_curr != "")
        {
            FileOperation::GetInt(iterator->second.str_curr, iterator->second.current_points);
            CCLOGERROR("%s = %s", iterator->second.str_curr.c_str(),std::to_string(iterator->second.current_points).c_str());
        }
    }
    
    //set the unlocked achievments, and write them to the file
    //calculated them everytime, so its safer
    achievment_container_[EAchievements::ALL_ACHIEVEMENTS_UNLOCKED].current_points = a_counter;
    FileOperation::SetInt(achievment_container_[EAchievements::ALL_ACHIEVEMENTS_UNLOCKED].str_curr, a_counter);

    int32_t cosmetic_value = 1;
    
    if(FileOperation::GetInt("COSMETIC_BASKET", cosmetic_value))
    {
        CCLOG("basekt string found");
    }
    
    switch(cosmetic_value)
    {
        case 1: DataHandler::COSMETIC_BASKET = DataHandler::COSMETIC_BASKET_LV1; break;
        case 2: DataHandler::COSMETIC_BASKET = DataHandler::COSMETIC_BASKET_LV2; break;
        case 3: DataHandler::COSMETIC_BASKET = DataHandler::COSMETIC_BASKET_LV3; break;
        case 4: DataHandler::COSMETIC_BASKET = DataHandler::COSMETIC_BASKET_LV4; break;
    }
}

void AchievementManager::InitAchievementsFile()
{
	for (auto& item : achievment_container_)
	{
		FileOperation::SetInt(item.second.str,0);
		
		if (item.second.str_curr != "")
		{
			FileOperation::SetInt(item.second.str_curr,1);
		}
	}
    
    //init basket
    FileOperation::SetInt("COSMETIC_BASKET", 1);
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
    FileOperation::SetInt(achievment_container_[type].str, true);
    
    if(type != EAchievements::ALL_ACHIEVEMENTS_UNLOCKED)
    {
        FileOperation::SetInt(achievment_container_[EAchievements::ALL_ACHIEVEMENTS_UNLOCKED].str_curr
                          ,++achievment_container_[EAchievements::ALL_ACHIEVEMENTS_UNLOCKED].current_points);
    }
    
    
//    ui_queue_.push_back(type);
    
    if(ui_notification_ != nullptr)
    {
//        FrameworkScene::GetActiveScene()->removeChild(ui_notification_);
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
//    ui_queue_.erase(ui_queue_.begin());
    
//    if(ui_queue_.size() > 0)
//    {
//        ui_notification_->SetText("next text");
//        ui_notification_->Show(this, &AchievementManager::NotificationEnd);
//    }
}

