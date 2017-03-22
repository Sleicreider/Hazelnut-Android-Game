#ifndef ACHIEVEMENTS_H
#define ACHIEVEMENTS_H

#include "FGeneral.h"
#include "Observer.h"
#include <vector>
#include "AchievementManager.h"
#include "FileOperation.h"

class Achievements : public Observer
{
public:
    Achievements()
    : bNoHazMissed_(true)
    , bNoWasteCollected_(true)
    , bNoAppleMissed_(true)
    , bNoHeartMissed_(true)
    , level_(1)
    , coins_(0)
    {
    }
    
    virtual ~Achievements() {}
    
    virtual void OnNotify(EEvent event) override
    {
        switch (event)
        {
            case EEvent::EVENT_WASTES_COLLECTED:
                bNoWasteCollected_ = false;
                
                break; //write to file
                
            case EEvent::EVENT_APPLE_COLLECTED:
                break;
                
            case EEvent::EVENT_HEART_COLLECTED:
                hearts_++;
                
                if(hearts_ == DataHandler::COLLECT_GAME_PLAYER_LIVES_MAX)
                {
                    Unlock(EAchievements::HEART_BAR_FILLED);
                    //unlock heart bar filled
                }
                
                break;
                
            case EEvent::EVENT_COIN_COLLECTED:
                coins_++;
                
                UpdateCurrPoints(EAchievements::OVERALL_COINS_COLLECTED_STAGE_1, 1);
                UpdateCurrPoints(EAchievements::OVERALL_COINS_COLLECTED_STAGE_2, 1);
                UpdateCurrPoints(EAchievements::OVERALL_COINS_COLLECTED_STAGE_3, 1);
                UpdateCurrPoints(EAchievements::OVERALL_COINS_COLLECTED_STAGE_4, 1);

				if (AchievementManager::GetInstance()->achievment_container_[EAchievements::OVERALL_GAMES_STARTED_100].current_points >= 100)
					Unlock(EAchievements::OVERALL_GAMES_STARTED_100);

				if (AchievementManager::GetInstance()->achievment_container_[EAchievements::OVERALL_COINS_COLLECTED_STAGE_1].current_points >= DataHandler::ACHIEVMENT_COIN_COLLECTED_STAGE_1)
				{
					Unlock(EAchievements::OVERALL_COINS_COLLECTED_STAGE_1);
				}

				if (AchievementManager::GetInstance()->achievment_container_[EAchievements::OVERALL_COINS_COLLECTED_STAGE_2].current_points >= DataHandler::ACHIEVMENT_COIN_COLLECTED_STAGE_2)
				{
					Unlock(EAchievements::OVERALL_COINS_COLLECTED_STAGE_2);
				}

				if (AchievementManager::GetInstance()->achievment_container_[EAchievements::OVERALL_COINS_COLLECTED_STAGE_3].current_points >= DataHandler::ACHIEVMENT_COIN_COLLECTED_STAGE_3)
				{
					Unlock(EAchievements::OVERALL_COINS_COLLECTED_STAGE_3);
				}

				if (AchievementManager::GetInstance()->achievment_container_[EAchievements::OVERALL_COINS_COLLECTED_STAGE_4].current_points >= DataHandler::ACHIEVMENT_COIN_COLLECTED_STAGE_4)
				{
					Unlock(EAchievements::OVERALL_COINS_COLLECTED_STAGE_4);
				}

                
                if(coins_ == 5){ Unlock(EAchievements::COINS_COLLECTED_5); }
                if(coins_ == 10){ Unlock(EAchievements::COINS_COLLECTED_10); }
                
                break; //write to file
                
            case EEvent::EVENT_HAZELNUT_MISSED:
                bNoHazMissed_ = false;
                break; //write to file
                
            case EEvent::EVENT_APPLE_MISSED:
                bNoAppleMissed_ = false;
                break; //write to file
                
            case EEvent::EVENT_COIN_MISSED:
                break; //write to file
                
            case EEvent::EVENT_HEART_MISSED:
                hearts_--;
                bNoHeartMissed_ = false;
                break; //write to file
                
            case EEvent::EVENT_GAME_OVER:
                break; //write file
                
            case EEvent::EVENT_LEVEL_UP:
                if(bNoHazMissed_ && level_ == 1){ Unlock(EAchievements::NO_HAZ_MISSED_L1); }
                if(bNoHazMissed_ && level_ == 3){ Unlock(EAchievements::NO_HAZ_MISSED_L3); }
                if(bNoHazMissed_ && level_ == 5){ Unlock(EAchievements::NO_HAZ_MISSED_L5); }
                if(bNoWasteCollected_ && level_ == 2){ Unlock(EAchievements::NO_WASTE_CATCHED_L2); }
                if(bNoWasteCollected_ && level_ == 4){ Unlock(EAchievements::NO_WASTE_CATCHED_L4); }
                if(bNoWasteCollected_ && level_ == 6){ Unlock(EAchievements::NO_WASTE_CATCHED_L6); }
                if(bNoWasteCollected_ && level_ == 8){ Unlock(EAchievements::NO_WASTE_CATCHED_L8); }
                if(bNoWasteCollected_ && level_ == 10){ Unlock(EAchievements::NO_WASTE_CATCHED_L10); }
                if(bNoAppleMissed_ && level_ == 4){ Unlock(EAchievements::NO_APPLE_MISSED_L4); }
                if(bNoAppleMissed_ && level_ == 6){ Unlock(EAchievements::NO_APPLE_MISSED_L6);}
                if(bNoAppleMissed_ && level_ == 10){ Unlock(EAchievements::NO_APPLE_MISSED_L10); }
                if(bNoHeartMissed_ && level_ == 3){ Unlock(EAchievements::NO_HEART_MISSED_L3); }
                if(bNoHeartMissed_ && level_ == 6){ Unlock(EAchievements::NO_HEART_MISSED_L6); }
                if(bNoHeartMissed_ && level_ == 9){ Unlock(EAchievements::NO_HEART_MISSED_L9); }
                
                level_++;
                
                break;
                
            case EEvent::EVENT_GAME_STARTED:
                UpdateCurrPoints(EAchievements::OVERALL_GAMES_STARTED_100, 1);
                
                if(AchievementManager::GetInstance()->achievment_container_[EAchievements::OVERALL_GAMES_STARTED_100].current_points >= 100)
                    Unlock(EAchievements::OVERALL_GAMES_STARTED_100);
                
                break;
                
        }
    }
    
    bool NewAchievement()                              { return achievement_list_.size() > 0; }
    std::vector<EAchievements> GetAchievementList()    { return achievement_list_; }
    
private:
    void Unlock(EAchievements type) //unlock achievment
    {
        auto manager = AchievementManager::GetInstance();
        auto& obj = manager->achievment_container_[type];
        
        
        if(manager->IsAchievementUnlocked(type)) return;
        

//        obj.unlocked = true;
//        FileOperation::SetInt(obj.str, true);
        
#pragma message WARN("maybe directly use UnlockAchievment? or remove it and only unlock in achievments.h, it should not be possible for other classes to be called and modify achievment unlocks etc")
        AchievementManager::GetInstance()->UnlockAchievement(type);
        
        
        switch(manager->achievment_container_[EAchievements::ALL_ACHIEVEMENTS_UNLOCKED].current_points)
        {
            case DataHandler::ACHIEVMENT_COSMETIC_BASKET_LV2:
                FileOperation::SetInt("COSMETIC_BASKET", 2);
                DataHandler::COSMETIC_BASKET = DataHandler::COSMETIC_BASKET_LV2;
                break;
                
            case DataHandler::ACHIEVMENT_COSMETIC_BASKET_LV3:
                FileOperation::SetInt("COSMETIC_BASKET", 3);
                DataHandler::COSMETIC_BASKET = DataHandler::COSMETIC_BASKET_LV3;
                break;
                
            case DataHandler::ACHIEVEMENT_AMOUNT: Unlock(EAchievements::ALL_ACHIEVEMENTS_UNLOCKED); break;
                
            default: CCLOG("nothing to do");
        }
        
        if(AchievementManager::GetInstance()->IsAchievementUnlocked(EAchievements::ALL_ACHIEVEMENTS_UNLOCKED))
        {
            FileOperation::SetInt("COSMETIC_BASKET", 4);
            DataHandler::COSMETIC_BASKET = DataHandler::COSMETIC_BASKET_LV4;
        }
    }
    
    void UpdateCurrPoints(EAchievements type, int points)
    {
        if(static_cast<int>(type) >= static_cast<int>(EAchievements::OVERALL_GAMES_STARTED_100))
        {
            AchievementManager::GetInstance()->achievment_container_[type].current_points += points;
            FileOperation::SetInt(AchievementManager::GetInstance()->achievment_container_[type].str_curr
                                  , AchievementManager::GetInstance()->achievment_container_[type].current_points);
        }
        else
        {
            CCLOGERROR("THIS TYPE HAS NO CURRENT VALUE LINE=%d", __LINE__);
//            assert(false);
        }
    }
    
private:
    bool bNoWasteCollected_;
    bool bNoHazMissed_;   /**< Hazelnut, Apple, Coin */
    bool bNoAppleMissed_;
    bool bNoHeartMissed_;
    
    
    int32_t hearts_;
    int32_t coins_;
    int32_t overall_coins_;
    int32_t overall_games_started_;
    int32_t level_;
    
    std::vector<EAchievements> achievement_list_;
};


#endif // ACHIEVEMENTS_H
