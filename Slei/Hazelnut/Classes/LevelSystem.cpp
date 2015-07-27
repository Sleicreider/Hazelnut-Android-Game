//
//  LevelSystem.cpp
//  Hazelnut
//
//  Created by Dominik Reisner on 01.12.14.
//
//

#include "LevelSystem.h"
#include "DataHandler.h"

LevelSystem::LevelSystem()
: level_(EInGameLevel::NONE)
, level_count_(1)
, bLevelUp_(false)
{
}

void LevelSystem::LevelControl(int playerScore)
{
#ifndef PERFORMANCETEST
    
    prev_level_ = level_;
    
    if(playerScore < DataHandler::COLLECT_GAME_LEVEL_1_SCORE_MAX)
    {
        level_ = EInGameLevel::LEVEL_1;
    }
    else if((playerScore >= DataHandler::COLLECT_GAME_LEVEL_1_SCORE_MAX) && (playerScore < DataHandler::COLLECT_GAME_LEVEL_2_SCORE_MAX))
    {
        level_ = EInGameLevel::LEVEL_2;
    }
    else if((playerScore >= DataHandler::COLLECT_GAME_LEVEL_2_SCORE_MAX) && (playerScore < DataHandler::COLLECT_GAME_LEVEL_3_SCORE_MAX))
    {
        level_ = EInGameLevel::LEVEL_3;
    }
    else if((playerScore >= DataHandler::COLLECT_GAME_LEVEL_3_SCORE_MAX) && (playerScore < DataHandler::COLLECT_GAME_LEVEL_4_SCORE_MAX))
    {
        level_ = EInGameLevel::LEVEL_4;
    }
    else if((playerScore >= DataHandler::COLLECT_GAME_LEVEL_4_SCORE_MAX) && (playerScore < DataHandler::COLLECT_GAME_LEVEL_5_SCORE_MAX))
    {
        level_ = EInGameLevel::LEVEL_5;
    }
    else if((playerScore >= DataHandler::COLLECT_GAME_LEVEL_5_SCORE_MAX) && (playerScore < DataHandler::COLLECT_GAME_LEVEL_6_SCORE_MAX))
    {
        level_ = EInGameLevel::LEVEL_6;
    }
    else if((playerScore >= DataHandler::COLLECT_GAME_LEVEL_6_SCORE_MAX) && (playerScore < DataHandler::COLLECT_GAME_LEVEL_7_SCORE_MAX))
    {
        level_ = EInGameLevel::LEVEL_7;
    }
    else if((playerScore >= DataHandler::COLLECT_GAME_LEVEL_7_SCORE_MAX) && (playerScore < DataHandler::COLLECT_GAME_LEVEL_8_SCORE_MAX))
    {
        level_ = EInGameLevel::LEVEL_8;
    }
    else if((playerScore >= DataHandler::COLLECT_GAME_LEVEL_8_SCORE_MAX) && (playerScore < DataHandler::COLLECT_GAME_LEVEL_9_SCORE_MAX))
    {
        level_ = EInGameLevel::LEVEL_9;
    }
    else if((playerScore >= DataHandler::COLLECT_GAME_LEVEL_9_SCORE_MAX) && (playerScore < DataHandler::COLLECT_GAME_LEVEL_10_SCORE_MAX))
    {
        level_ = EInGameLevel::LEVEL_10;
    }
    else if((playerScore >= DataHandler::COLLECT_GAME_LEVEL_10_SCORE_MAX) && (playerScore < DataHandler::COLLECT_GAME_LEVEL_11_SCORE_MAX))
    {
        level_ = EInGameLevel::LEVEL_11;
    }
    else if((playerScore >= DataHandler::COLLECT_GAME_LEVEL_11_SCORE_MAX) && (playerScore < DataHandler::COLLECT_GAME_LEVEL_12_SCORE_MAX))
    {
        level_ = EInGameLevel::LEVEL_12;
    }
    else if((playerScore >= DataHandler::COLLECT_GAME_LEVEL_12_SCORE_MAX) && (playerScore < DataHandler::COLLECT_GAME_LEVEL_13_SCORE_MAX))
    {
        level_ = EInGameLevel::LEVEL_13;
    }
    else if((playerScore >= DataHandler::COLLECT_GAME_LEVEL_13_SCORE_MAX) && (playerScore < DataHandler::COLLECT_GAME_LEVEL_14_SCORE_MAX))
    {
        level_ = EInGameLevel::LEVEL_14;
    }
    else if(playerScore >= DataHandler::COLLECT_GAME_LEVEL_14_SCORE_MAX)
    {
        level_ = EInGameLevel::LEVEL_15;
    }
    
#else
    level_ = EInGameLevel::LEVEL_X;
#endif
}

void LevelSystem::GetLevelSettings(int& squirrel_speed, int& drop_object_speed_min, int& drop_object_speed_max, int& drop_interval_min, int& drop_interval_max, int& level_score_multiplier, int& c_hazelnut, int& c_waste, int& c_apple, int& c_heart, int& c_coin,int& hazelnut_speed)
{
    
#ifndef PERFORMANCETEST
    
    bLevelUp_ = false;
    
    if(level_ != prev_level_)
    {
        bLevelUp_ = true;
        
        if(level_ == EInGameLevel::LEVEL_1)
        {
            drop_object_speed_min  = DataHandler::COLLECT_GAME_LEVEL_1_DROP_SPEED_MIN;
            drop_object_speed_max   = DataHandler::COLLECT_GAME_LEVEL_1_DROP_SPEED_MAX;
            drop_interval_min     = DataHandler::COLLECT_GAME_LEVEL_1_DROP_INTERVAL_MIN;
            drop_interval_max     = DataHandler::COLLECT_GAME_LEVEL_1_DROP_INTERVAL_MAX;
            squirrel_speed       = DataHandler::COLLECT_GAME_LEVEL_1_AI_SPEED;
			hazelnut_speed = DataHandler::COLLECT_GAME_LEVEL_1_HAZELNUT_SPEED;
            level_score_multiplier     = DataHandler::COLLECT_GAME_LEVEL_1_SCORE_MULTIPLIER;
			c_hazelnut = DataHandler::COLLECT_GAME_LEVEL_1_HAZELNUT_DROP_CHANCE;
			c_waste = DataHandler::COLLECT_GAME_LEVEL_1_WASTE_DROP_CHANCE;
			c_apple = DataHandler::COLLECT_GAME_LEVEL_1_APPLE_DROP_CHANCE;
			c_heart = DataHandler::COLLECT_GAME_LEVEL_1_HEART_DROP_CHANCE;
			c_coin = DataHandler::COLLECT_GAME_LEVEL_1_COIN_DROP_CHANCE;
            
            level_count_ = 1;

        }
        else if(level_ == EInGameLevel::LEVEL_2)
        {
            drop_object_speed_min  = DataHandler::COLLECT_GAME_LEVEL_2_DROP_SPEED_MIN;
            drop_object_speed_max   = DataHandler::COLLECT_GAME_LEVEL_2_DROP_SPEED_MAX;
            drop_interval_min     = DataHandler::COLLECT_GAME_LEVEL_2_DROP_INTERVAL_MIN;
            drop_interval_max     = DataHandler::COLLECT_GAME_LEVEL_2_DROP_INTERVAL_MAX;
            squirrel_speed       = DataHandler::COLLECT_GAME_LEVEL_2_AI_SPEED;
			hazelnut_speed = DataHandler::COLLECT_GAME_LEVEL_2_HAZELNUT_SPEED;
            level_score_multiplier     = DataHandler::COLLECT_GAME_LEVEL_2_SCORE_MULTIPLIER;
			c_hazelnut = DataHandler::COLLECT_GAME_LEVEL_2_HAZELNUT_DROP_CHANCE;
			c_waste = DataHandler::COLLECT_GAME_LEVEL_2_WASTE_DROP_CHANCE;
			c_apple = DataHandler::COLLECT_GAME_LEVEL_2_APPLE_DROP_CHANCE;
			c_heart = DataHandler::COLLECT_GAME_LEVEL_2_HEART_DROP_CHANCE;
			c_coin = DataHandler::COLLECT_GAME_LEVEL_2_COIN_DROP_CHANCE;
            
            level_count_ = 2;
        }
        else if(level_ == EInGameLevel::LEVEL_3)
        {
            drop_object_speed_min  = DataHandler::COLLECT_GAME_LEVEL_3_DROP_SPEED_MIN;
            drop_object_speed_max   = DataHandler::COLLECT_GAME_LEVEL_3_DROP_SPEED_MAX;
            drop_interval_min     = DataHandler::COLLECT_GAME_LEVEL_3_DROP_INTERVAL_MIN;
            drop_interval_max     = DataHandler::COLLECT_GAME_LEVEL_3_DROP_INTERVAL_MAX;
            squirrel_speed       = DataHandler::COLLECT_GAME_LEVEL_3_AI_SPEED;
			hazelnut_speed = DataHandler::COLLECT_GAME_LEVEL_3_HAZELNUT_SPEED;
            level_score_multiplier     = DataHandler::COLLECT_GAME_LEVEL_3_SCORE_MULTIPLIER;
			c_hazelnut = DataHandler::COLLECT_GAME_LEVEL_3_HAZELNUT_DROP_CHANCE;
			c_waste = DataHandler::COLLECT_GAME_LEVEL_3_WASTE_DROP_CHANCE;
			c_apple = DataHandler::COLLECT_GAME_LEVEL_3_APPLE_DROP_CHANCE;
			c_heart = DataHandler::COLLECT_GAME_LEVEL_3_HEART_DROP_CHANCE;
			c_coin = DataHandler::COLLECT_GAME_LEVEL_3_COIN_DROP_CHANCE;
            
            level_count_ = 3;
        }
        else if(level_ == EInGameLevel::LEVEL_4)
        {
            drop_object_speed_min  = DataHandler::COLLECT_GAME_LEVEL_4_DROP_SPEED_MIN;
            drop_object_speed_max   = DataHandler::COLLECT_GAME_LEVEL_4_DROP_SPEED_MAX;
            drop_interval_min     = DataHandler::COLLECT_GAME_LEVEL_4_DROP_INTERVAL_MIN;
            drop_interval_max     = DataHandler::COLLECT_GAME_LEVEL_4_DROP_INTERVAL_MAX;
            squirrel_speed       = DataHandler::COLLECT_GAME_LEVEL_4_AI_SPEED;
			hazelnut_speed = DataHandler::COLLECT_GAME_LEVEL_4_HAZELNUT_SPEED;
            level_score_multiplier     = DataHandler::COLLECT_GAME_LEVEL_4_SCORE_MULTIPLIER;
			c_hazelnut = DataHandler::COLLECT_GAME_LEVEL_4_HAZELNUT_DROP_CHANCE;
			c_waste = DataHandler::COLLECT_GAME_LEVEL_4_WASTE_DROP_CHANCE;
			c_apple = DataHandler::COLLECT_GAME_LEVEL_4_APPLE_DROP_CHANCE;
			c_heart = DataHandler::COLLECT_GAME_LEVEL_4_HEART_DROP_CHANCE;
			c_coin = DataHandler::COLLECT_GAME_LEVEL_4_COIN_DROP_CHANCE;
            
            level_count_ = 4;
        }
        else if(level_ == EInGameLevel::LEVEL_5)
        {
            drop_object_speed_min  = DataHandler::COLLECT_GAME_LEVEL_5_DROP_SPEED_MIN;
            drop_object_speed_max   = DataHandler::COLLECT_GAME_LEVEL_5_DROP_SPEED_MAX;
            drop_interval_min     = DataHandler::COLLECT_GAME_LEVEL_5_DROP_INTERVAL_MIN;
            drop_interval_max     = DataHandler::COLLECT_GAME_LEVEL_5_DROP_INTERVAL_MAX;
            squirrel_speed       = DataHandler::COLLECT_GAME_LEVEL_5_AI_SPEED;
			hazelnut_speed = DataHandler::COLLECT_GAME_LEVEL_5_HAZELNUT_SPEED;
            level_score_multiplier     = DataHandler::COLLECT_GAME_LEVEL_5_SCORE_MULTIPLIER;
			c_hazelnut = DataHandler::COLLECT_GAME_LEVEL_5_HAZELNUT_DROP_CHANCE;
			c_waste = DataHandler::COLLECT_GAME_LEVEL_5_WASTE_DROP_CHANCE;
			c_apple = DataHandler::COLLECT_GAME_LEVEL_5_APPLE_DROP_CHANCE;
			c_heart = DataHandler::COLLECT_GAME_LEVEL_5_HEART_DROP_CHANCE;
			c_coin = DataHandler::COLLECT_GAME_LEVEL_5_COIN_DROP_CHANCE;
            
            level_count_ = 5;
        }
        else if(level_ == EInGameLevel::LEVEL_6)
        {
            drop_object_speed_min  = DataHandler::COLLECT_GAME_LEVEL_6_DROP_SPEED_MIN;
            drop_object_speed_max   = DataHandler::COLLECT_GAME_LEVEL_6_DROP_SPEED_MAX;
            drop_interval_min     = DataHandler::COLLECT_GAME_LEVEL_6_DROP_INTERVAL_MIN;
            drop_interval_max     = DataHandler::COLLECT_GAME_LEVEL_6_DROP_INTERVAL_MAX;
            squirrel_speed       = DataHandler::COLLECT_GAME_LEVEL_6_AI_SPEED;
			hazelnut_speed = DataHandler::COLLECT_GAME_LEVEL_6_HAZELNUT_SPEED;
            level_score_multiplier     = DataHandler::COLLECT_GAME_LEVEL_6_SCORE_MULTIPLIER;
			c_hazelnut = DataHandler::COLLECT_GAME_LEVEL_6_HAZELNUT_DROP_CHANCE;
			c_waste = DataHandler::COLLECT_GAME_LEVEL_6_WASTE_DROP_CHANCE;
			c_apple = DataHandler::COLLECT_GAME_LEVEL_6_APPLE_DROP_CHANCE;
			c_heart = DataHandler::COLLECT_GAME_LEVEL_6_HEART_DROP_CHANCE;
			c_coin = DataHandler::COLLECT_GAME_LEVEL_6_COIN_DROP_CHANCE;
        
            level_count_ = 6;
        }
        else if(level_ == EInGameLevel::LEVEL_7)
        {
            drop_object_speed_min  = DataHandler::COLLECT_GAME_LEVEL_7_DROP_SPEED_MIN;
            drop_object_speed_max   = DataHandler::COLLECT_GAME_LEVEL_7_DROP_SPEED_MAX;
            drop_interval_min     = DataHandler::COLLECT_GAME_LEVEL_7_DROP_INTERVAL_MIN;
            drop_interval_max     = DataHandler::COLLECT_GAME_LEVEL_7_DROP_INTERVAL_MAX;
            squirrel_speed       = DataHandler::COLLECT_GAME_LEVEL_7_AI_SPEED;
			hazelnut_speed = DataHandler::COLLECT_GAME_LEVEL_7_HAZELNUT_SPEED;
            level_score_multiplier     = DataHandler::COLLECT_GAME_LEVEL_7_SCORE_MULTIPLIER;
			c_hazelnut = DataHandler::COLLECT_GAME_LEVEL_7_HAZELNUT_DROP_CHANCE;
			c_waste = DataHandler::COLLECT_GAME_LEVEL_7_WASTE_DROP_CHANCE;
			c_apple = DataHandler::COLLECT_GAME_LEVEL_7_APPLE_DROP_CHANCE;
			c_heart = DataHandler::COLLECT_GAME_LEVEL_7_HEART_DROP_CHANCE;
			c_coin = DataHandler::COLLECT_GAME_LEVEL_7_COIN_DROP_CHANCE;
        
            level_count_ = 7;
        }
        else if(level_ == EInGameLevel::LEVEL_8)
        {
            drop_object_speed_min  = DataHandler::COLLECT_GAME_LEVEL_8_DROP_SPEED_MIN;
            drop_object_speed_max   = DataHandler::COLLECT_GAME_LEVEL_8_DROP_SPEED_MAX;
            drop_interval_min     = DataHandler::COLLECT_GAME_LEVEL_8_DROP_INTERVAL_MIN;
            drop_interval_max     = DataHandler::COLLECT_GAME_LEVEL_8_DROP_INTERVAL_MAX;
            squirrel_speed       = DataHandler::COLLECT_GAME_LEVEL_8_AI_SPEED;
			hazelnut_speed = DataHandler::COLLECT_GAME_LEVEL_8_HAZELNUT_SPEED;
            level_score_multiplier     = DataHandler::COLLECT_GAME_LEVEL_8_SCORE_MULTIPLIER;
			c_hazelnut = DataHandler::COLLECT_GAME_LEVEL_8_HAZELNUT_DROP_CHANCE;
			c_waste = DataHandler::COLLECT_GAME_LEVEL_8_WASTE_DROP_CHANCE;
			c_apple = DataHandler::COLLECT_GAME_LEVEL_8_APPLE_DROP_CHANCE;
			c_heart = DataHandler::COLLECT_GAME_LEVEL_8_HEART_DROP_CHANCE;
			c_coin = DataHandler::COLLECT_GAME_LEVEL_8_COIN_DROP_CHANCE;
            
            level_count_ = 8;
        }
        else if(level_ == EInGameLevel::LEVEL_9)
        {
            drop_object_speed_min  = DataHandler::COLLECT_GAME_LEVEL_9_DROP_SPEED_MIN;
            drop_object_speed_max   = DataHandler::COLLECT_GAME_LEVEL_9_DROP_SPEED_MAX;
            drop_interval_min     = DataHandler::COLLECT_GAME_LEVEL_9_DROP_INTERVAL_MIN;
            drop_interval_max     = DataHandler::COLLECT_GAME_LEVEL_9_DROP_INTERVAL_MAX;
            squirrel_speed       = DataHandler::COLLECT_GAME_LEVEL_9_AI_SPEED;
			hazelnut_speed = DataHandler::COLLECT_GAME_LEVEL_9_HAZELNUT_SPEED;
            level_score_multiplier     = DataHandler::COLLECT_GAME_LEVEL_9_SCORE_MULTIPLIER;
			c_hazelnut = DataHandler::COLLECT_GAME_LEVEL_9_HAZELNUT_DROP_CHANCE;
			c_waste = DataHandler::COLLECT_GAME_LEVEL_9_WASTE_DROP_CHANCE;
			c_apple = DataHandler::COLLECT_GAME_LEVEL_9_APPLE_DROP_CHANCE;
			c_heart = DataHandler::COLLECT_GAME_LEVEL_9_HEART_DROP_CHANCE;
			c_coin = DataHandler::COLLECT_GAME_LEVEL_9_COIN_DROP_CHANCE;
            
            level_count_ = 9;
        }
        else if(level_ == EInGameLevel::LEVEL_10)
        {
            drop_object_speed_min  =    DataHandler::COLLECT_GAME_LEVEL_10_DROP_SPEED_MIN;
            drop_object_speed_max   =   DataHandler::COLLECT_GAME_LEVEL_10_DROP_SPEED_MAX;
            drop_interval_min     =     DataHandler::COLLECT_GAME_LEVEL_10_DROP_INTERVAL_MIN;
            drop_interval_max     =     DataHandler::COLLECT_GAME_LEVEL_10_DROP_INTERVAL_MAX;
            squirrel_speed       =      DataHandler::COLLECT_GAME_LEVEL_10_AI_SPEED;
			hazelnut_speed = DataHandler::COLLECT_GAME_LEVEL_10_HAZELNUT_SPEED;
            level_score_multiplier  =   DataHandler::COLLECT_GAME_LEVEL_10_SCORE_MULTIPLIER;
			c_hazelnut = DataHandler::COLLECT_GAME_LEVEL_10_HAZELNUT_DROP_CHANCE;
			c_waste = DataHandler::COLLECT_GAME_LEVEL_10_WASTE_DROP_CHANCE;
			c_apple = DataHandler::COLLECT_GAME_LEVEL_10_APPLE_DROP_CHANCE;
			c_heart = DataHandler::COLLECT_GAME_LEVEL_10_HEART_DROP_CHANCE;
			c_coin = DataHandler::COLLECT_GAME_LEVEL_10_COIN_DROP_CHANCE;
            
            level_count_ = 10;
        }
        else if(level_ == EInGameLevel::LEVEL_11)
        {
            drop_object_speed_min  =    DataHandler::COLLECT_GAME_LEVEL_11_DROP_SPEED_MIN;
            drop_object_speed_max   =   DataHandler::COLLECT_GAME_LEVEL_11_DROP_SPEED_MAX;
            drop_interval_min     =     DataHandler::COLLECT_GAME_LEVEL_11_DROP_INTERVAL_MIN;
            drop_interval_max     =     DataHandler::COLLECT_GAME_LEVEL_11_DROP_INTERVAL_MAX;
            squirrel_speed       =      DataHandler::COLLECT_GAME_LEVEL_11_AI_SPEED;
			hazelnut_speed = DataHandler::COLLECT_GAME_LEVEL_10_HAZELNUT_SPEED;
            level_score_multiplier =    DataHandler::COLLECT_GAME_LEVEL_11_SCORE_MULTIPLIER;
			c_hazelnut = DataHandler::COLLECT_GAME_LEVEL_11_HAZELNUT_DROP_CHANCE;
			c_waste = DataHandler::COLLECT_GAME_LEVEL_11_WASTE_DROP_CHANCE;
			c_apple = DataHandler::COLLECT_GAME_LEVEL_11_APPLE_DROP_CHANCE;
			c_heart = DataHandler::COLLECT_GAME_LEVEL_11_HEART_DROP_CHANCE;
			c_coin = DataHandler::COLLECT_GAME_LEVEL_11_COIN_DROP_CHANCE;
            
            level_count_ = 11;
        }
        else if(level_ == EInGameLevel::LEVEL_12)
        {
            drop_object_speed_min  =    DataHandler::COLLECT_GAME_LEVEL_12_DROP_SPEED_MIN;
            drop_object_speed_max   =   DataHandler::COLLECT_GAME_LEVEL_12_DROP_SPEED_MAX;
            drop_interval_min     =     DataHandler::COLLECT_GAME_LEVEL_12_DROP_INTERVAL_MIN;
            drop_interval_max     =     DataHandler::COLLECT_GAME_LEVEL_12_DROP_INTERVAL_MAX;
            squirrel_speed       =      DataHandler::COLLECT_GAME_LEVEL_12_AI_SPEED;
			hazelnut_speed = DataHandler::COLLECT_GAME_LEVEL_12_HAZELNUT_SPEED;
            level_score_multiplier =    DataHandler::COLLECT_GAME_LEVEL_12_SCORE_MULTIPLIER;
			c_hazelnut = DataHandler::COLLECT_GAME_LEVEL_12_HAZELNUT_DROP_CHANCE;
			c_waste = DataHandler::COLLECT_GAME_LEVEL_12_WASTE_DROP_CHANCE;
			c_apple = DataHandler::COLLECT_GAME_LEVEL_12_APPLE_DROP_CHANCE;
			c_heart = DataHandler::COLLECT_GAME_LEVEL_12_HEART_DROP_CHANCE;
			c_coin = DataHandler::COLLECT_GAME_LEVEL_12_COIN_DROP_CHANCE;
            
            level_count_ = 12;
        }
        else if(level_ == EInGameLevel::LEVEL_13)
        {
            drop_object_speed_min  =    DataHandler::COLLECT_GAME_LEVEL_13_DROP_SPEED_MIN;
            drop_object_speed_max   =   DataHandler::COLLECT_GAME_LEVEL_13_DROP_SPEED_MAX;
            drop_interval_min     =     DataHandler::COLLECT_GAME_LEVEL_13_DROP_INTERVAL_MIN;
            drop_interval_max     =     DataHandler::COLLECT_GAME_LEVEL_13_DROP_INTERVAL_MAX;
            squirrel_speed       =      DataHandler::COLLECT_GAME_LEVEL_13_AI_SPEED;
			hazelnut_speed = DataHandler::COLLECT_GAME_LEVEL_13_HAZELNUT_SPEED;
            level_score_multiplier =    DataHandler::COLLECT_GAME_LEVEL_13_SCORE_MULTIPLIER;
			c_hazelnut = DataHandler::COLLECT_GAME_LEVEL_13_HAZELNUT_DROP_CHANCE;
			c_waste = DataHandler::COLLECT_GAME_LEVEL_13_WASTE_DROP_CHANCE;
			c_apple = DataHandler::COLLECT_GAME_LEVEL_13_APPLE_DROP_CHANCE;
			c_heart = DataHandler::COLLECT_GAME_LEVEL_13_HEART_DROP_CHANCE;
			c_coin = DataHandler::COLLECT_GAME_LEVEL_13_COIN_DROP_CHANCE;
            
            level_count_ = 13;
        }
        else if(level_ == EInGameLevel::LEVEL_14)
        {
            drop_object_speed_min  =    DataHandler::COLLECT_GAME_LEVEL_14_DROP_SPEED_MIN;
            drop_object_speed_max   =   DataHandler::COLLECT_GAME_LEVEL_14_DROP_SPEED_MAX;
            drop_interval_min     =     DataHandler::COLLECT_GAME_LEVEL_14_DROP_INTERVAL_MIN;
            drop_interval_max     =     DataHandler::COLLECT_GAME_LEVEL_14_DROP_INTERVAL_MAX;
            squirrel_speed       =      DataHandler::COLLECT_GAME_LEVEL_14_AI_SPEED;
			hazelnut_speed = DataHandler::COLLECT_GAME_LEVEL_14_HAZELNUT_SPEED;
            level_score_multiplier =    DataHandler::COLLECT_GAME_LEVEL_14_SCORE_MULTIPLIER;
			c_hazelnut = DataHandler::COLLECT_GAME_LEVEL_14_HAZELNUT_DROP_CHANCE;
			c_waste = DataHandler::COLLECT_GAME_LEVEL_14_WASTE_DROP_CHANCE;
			c_apple = DataHandler::COLLECT_GAME_LEVEL_14_APPLE_DROP_CHANCE;
			c_heart = DataHandler::COLLECT_GAME_LEVEL_14_HEART_DROP_CHANCE;
			c_coin = DataHandler::COLLECT_GAME_LEVEL_14_COIN_DROP_CHANCE;
            
            level_count_ = 14;
        }
        else if(level_ == EInGameLevel::LEVEL_15)
        {
            drop_object_speed_min  =    DataHandler::COLLECT_GAME_LEVEL_15_DROP_SPEED_MIN;
            drop_object_speed_max   =   DataHandler::COLLECT_GAME_LEVEL_15_DROP_SPEED_MAX;
            drop_interval_min     =     DataHandler::COLLECT_GAME_LEVEL_15_DROP_INTERVAL_MIN;
            drop_interval_max     =     DataHandler::COLLECT_GAME_LEVEL_15_DROP_INTERVAL_MAX;
            squirrel_speed       =      DataHandler::COLLECT_GAME_LEVEL_15_AI_SPEED;
			hazelnut_speed = DataHandler::COLLECT_GAME_LEVEL_15_HAZELNUT_SPEED;
            level_score_multiplier =    DataHandler::COLLECT_GAME_LEVEL_15_SCORE_MULTIPLIER;
			c_hazelnut = DataHandler::COLLECT_GAME_LEVEL_15_HAZELNUT_DROP_CHANCE;
			c_waste = DataHandler::COLLECT_GAME_LEVEL_15_WASTE_DROP_CHANCE;
			c_apple = DataHandler::COLLECT_GAME_LEVEL_15_APPLE_DROP_CHANCE;
			c_heart = DataHandler::COLLECT_GAME_LEVEL_15_HEART_DROP_CHANCE;
			c_coin = DataHandler::COLLECT_GAME_LEVEL_15_COIN_DROP_CHANCE;
            
            level_count_ = 15;
        }
    }
    
#else
    
    drop_object_speed_min  =    DataHandler::COLLECT_GAME_LEVEL_X_DROP_SPEED_MIN;
    drop_object_speed_max   =   DataHandler::COLLECT_GAME_LEVEL_X_DROP_SPEED_MAX;
    drop_interval_min     =     DataHandler::COLLECT_GAME_LEVEL_X_DROP_INTERVAL_MIN;
    drop_interval_max     =     DataHandler::COLLECT_GAME_LEVEL_X_DROP_INTERVAL_MAX;
    squirrel_speed       =      DataHandler::COLLECT_GAME_LEVEL_X_AI_SPEED;
    hazelnut_speed = DataHandler::COLLECT_GAME_LEVEL_X_HAZELNUT_SPEED;
    level_score_multiplier =    DataHandler::COLLECT_GAME_LEVEL_X_SCORE_MULTIPLIER;
    c_hazelnut = DataHandler::COLLECT_GAME_LEVEL_X_HAZELNUT_DROP_CHANCE;
    c_waste = DataHandler::COLLECT_GAME_LEVEL_X_WASTE_DROP_CHANCE;
    c_apple = DataHandler::COLLECT_GAME_LEVEL_X_APPLE_DROP_CHANCE;
    c_heart = DataHandler::COLLECT_GAME_LEVEL_X_HEART_DROP_CHANCE;
    c_coin = DataHandler::COLLECT_GAME_LEVEL_X_COIN_DROP_CHANCE;
    
//    drop_object_speed_min  = DataHandler::COLLECT_GAME_LEVEL_X_DROP_SPEED_MIN;
//    drop_object_speed_max   = DataHandler::COLLECT_GAME_LEVEL_X_DROP_SPEED_MAX;
//    drop_interval_min     = DataHandler::COLLECT_GAME_LEVEL_X_DROP_INTERVAL_MIN;
//    drop_interval_max     = DataHandler::COLLECT_GAME_LEVEL_X_DROP_INTERVAL_MAX;
//    squirrel_speed       = DataHandler::COLLECT_GAME_LEVEL_X_AI_SPEED;
//    level_score_multiplier     = DataHandler::COLLECT_GAME_LEVEL_X_SCORE_MULTIPLIER;
    
    bLevelUp_ = false;
    
#endif
}