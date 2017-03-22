//
//  AchievementManager.h
//  Hazelnut
//
//  Created by Dominik Reisner on 09.02.16.
//
//

#ifndef __Hazelnut__AchievementManager__
#define __Hazelnut__AchievementManager__

#include "FGeneral.h"

#include <map>
#include <memory>
#include <vector>

class AchievementNotification;

enum class EAchievements
{
    NO_HAZ_MISSED_L1,
    NO_HAZ_MISSED_L3,
    NO_HAZ_MISSED_L5,
    NO_WASTE_CATCHED_L2,
    NO_WASTE_CATCHED_L4,
    NO_WASTE_CATCHED_L6,
    NO_WASTE_CATCHED_L8,
    NO_WASTE_CATCHED_L10,
    NO_APPLE_MISSED_L4,
    NO_APPLE_MISSED_L6,
    NO_APPLE_MISSED_L10,
    HEART_BAR_FILLED,
    NO_HEART_MISSED_L3,
    NO_HEART_MISSED_L6,
    NO_HEART_MISSED_L9,
    COINS_COLLECTED_5,
    COINS_COLLECTED_10,
    OVERALL_GAMES_STARTED_100,
    OVERALL_COINS_COLLECTED_STAGE_1,
    OVERALL_COINS_COLLECTED_STAGE_2,
    OVERALL_COINS_COLLECTED_STAGE_3,
    OVERALL_COINS_COLLECTED_STAGE_4,
    ALL_ACHIEVEMENTS_UNLOCKED
};


struct SAchievment
{
    SAchievment():str_curr(""){}
    
    std::string str_curr;
    std::string str;
    
    int32_t     current_points;
    int32_t     target_points;
    
    bool        unlocked;
};

using AchievementCointainer = std::map<EAchievements, SAchievment>;

class AchievementManager
{
    friend class Achievements;
    
public:
    AchievementManager();
    
    static AchievementManager* GetInstance()
    {
        if(instance_ == nullptr)
        {
            instance_ = std14::make_unique<AchievementManager>();
        }
        
        return instance_.get();
    }
    
public:
    void SaveAchievmentsToFile();
	void InitAchievementsFile();
    void LoadAchievmentsFromFile();
    
    void UpdateAchievmentCurrentPoints(EAchievements type, int32_t points);
    void UnlockAchievement(EAchievements type);
    bool IsAchievementUnlocked(EAchievements type);
    
    const AchievementCointainer& GetAchievementContainer();
    const SAchievment& GetAchievmentStruct(EAchievements type);
    

protected:
    
    AchievementManager(const AchievementManager&) = delete;
    const AchievementManager& operator=(const AchievementManager&) = delete;
    

private:
    void NotificationEnd();

    
private:
    static std::unique_ptr<AchievementManager> instance_;
    
private:
    AchievementCointainer achievment_container_;
    AchievementNotification* ui_notification_;
    std::vector<EAchievements> ui_queue_;
    
};

FORCEINLINE const AchievementCointainer& AchievementManager::GetAchievementContainer()                  { return achievment_container_; }
FORCEINLINE const SAchievment&           AchievementManager::GetAchievmentStruct(EAchievements type)    { return achievment_container_[type]; }

#endif /* defined(__Hazelnut__AchievementManager__) */

