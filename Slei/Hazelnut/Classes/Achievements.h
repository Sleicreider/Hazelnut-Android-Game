#ifndef ACHIEVEMENTS_H
#define ACHIEVEMENTS_H

#include "FGeneral.h"
#include "Observer.h"
#include <vector>
#include "AchievementManager.h"

class Achievements : public Observer
{
public:
    Achievements()
    : bNoHazMissed_(true)
    , bNoWasteCollected_(true)
    , bNoAppleMissed_(true)
    , bNoHeartMissed_(true)
    , level_(1)
    {
    }
    
    virtual ~Achievements() {}
    
    virtual void OnNotify(EEvent event) override
    {
        switch (event)
        {
            case EEvent::EVENT_WASTES_COLLECTED:
                
                AchievementManager::GetInstance()->UnlockAchievement(EAchievements::COINS_COLLECTED_5);
                
                bNoWasteCollected_ = false;
                
                break; //write to file
                
            case EEvent::EVENT_APPLE_COLLECTED:
                break;
                
            case EEvent::EVENT_HEART_COLLECTED:
                hearts_++;
                
                if(hearts_ == DataHandler::COLLECT_GAME_PLAYER_LIVES_MAX)
                {
                    //unlock heart bar filled
                }
                
                break;
                
            case EEvent::EVENT_COIN_COLLECTED:
                coins_++;
                
                if(coins_ == 5){}
                if(coins_ == 10){}
                
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
                
            case EEvent::EVENT_LEVEL_UP: level_++;
                if(bNoHazMissed_ && level_ == 1){/*unlock no value item missed*/}
                if(bNoHazMissed_ && level_ == 3){}
                if(bNoHazMissed_ && level_ == 5){}
                if(bNoWasteCollected_ && level_ == 2){}
                if(bNoWasteCollected_ && level_ == 4){}
                if(bNoWasteCollected_ && level_ == 6){}
                if(bNoWasteCollected_ && level_ == 8){}
                if(bNoWasteCollected_ && level_ == 10){}
                if(bNoAppleMissed_ && level_ == 2){}
                if(bNoAppleMissed_ && level_ == 4){}
                if(bNoAppleMissed_ && level_ == 6){}
                if(bNoHeartMissed_ && level_ == 3){}
                if(bNoHeartMissed_ && level_ == 6){}
                if(bNoHeartMissed_ && level_ == 9){}
                
                break;
                
        }
    }
    
    bool NewAchievement()                              { return achievement_list_.size() > 0; }
    std::vector<EAchievements> GetAchievementList()    { return achievement_list_; }
    
private:
    void Unlock(); //unlock achievment

    
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
