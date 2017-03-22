//
//  LevelSystem.h
//  Hazelnut
//
//  Created by Dominik Reisner on 01.12.14.
//
//

//  Extremely old logic
//  Might contain inefficient code

#ifndef __Hazelnut__LevelSystem__
#define __Hazelnut__LevelSystem__

#include "FGeneral.h"

#include <stdio.h>
#include <cocos2d.h>
#include "HazelnutEnum.h"

USING_NS_CC;

class LevelSystem
{
public:
    LevelSystem();
    //void SetLevel(EInGameLevel level);
	void GetLevelSettings(int& squirrelSpeed, int& dropObjectSpeedMin, int& dropObjectSpeeMax, int& dropIntervalMin, int& dropIntervalMax, int& levelMultiplier, int& c_hazelnut, int& c_waste, int& c_apple, int& c_heart, int& c_coin, int& hazelnut_speed);
    void LevelControl(int playerScore);
    bool OnLevelUp();
    int GetLevel();
    
private:
    EInGameLevel level_;
    EInGameLevel prev_level_;
    int level_count_;
    
    bool bLevelUp_;
    
};

inline bool LevelSystem::OnLevelUp()  { return bLevelUp_; }
inline int  LevelSystem::GetLevel()   { return level_count_; }



#endif /* defined(__Hazelnut__LevelSystem__) */
