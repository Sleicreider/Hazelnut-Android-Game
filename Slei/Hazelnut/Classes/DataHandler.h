//
//  DataHandler.h
//  Hazelnut
//
//  Created by Dominik Reisner on 20.11.14.
//
//

#ifndef __Hazelnut__DataHandler__
#define __Hazelnut__DataHandler__

#include "SimpleAudioEngine.h"
#include "AppEnum.h"

//#define PERFORMANCETEST
#pragma warn message("TODO: BUTTON RECTS DO NOT WORK IN POPUPS CHECK")
//#define BUTTON_RECT
//#define DEBUG

//Go to FSprite.cpp and remove also comment/remove comment for ETC1 definition
//#define ETC1

//#define COCOS2D_DEBUG 1

// compiler_warning.h
#define STRINGISE_IMPL(x) #x
#define STRINGISE(x) STRINGISE_IMPL(x)

//#define FORCEINLINE __attribute__((always_inline))


#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#    define FORCEINLINE __forceinline
#else
#    define FORCEINLINE __attribute__((always_inline)) inline
#endif


// Use: #pragma message WARN("My message")
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
#   define FILE_LINE_LINK __FILE__ "(" STRINGISE(__LINE__) ") : "
#   define WARN(exp) (FILE_LINE_LINK "WARNING: " exp)
#else//__GNUC__ - may need other defines for different compilers
#   define WARN(exp) ("WARNING: " exp)
#endif

namespace DataHandler
{
    static CocosDenshion::SimpleAudioEngine* game_audio = CocosDenshion::SimpleAudioEngine::getInstance();
    
    static bool bIsGameSoundActive_ = true;
    
    extern cocos2d::Size            app_screen_size_;
    extern EAppLayout               app_layout_;
    
    /****** Resolution Options *******/
    static const int32_t GAME_RESOLUTION_WIDTH = 1920;
    static const int32_t GAME_RESOLUTION_HEIGHT = 1080;
    static const int32_t GAME_RESOLUTION_CENTER_WIDTH = GAME_RESOLUTION_WIDTH/2;
    static const int32_t GAME_RESOLUTION_CENTER_HEIGHT = GAME_RESOLUTION_HEIGHT/2;
    
    static const cocos2d::Vec2 GAME_RESOLUTION_CENTER(GAME_RESOLUTION_WIDTH/2,GAME_RESOLUTION_HEIGHT/2);
    
    static const int32_t COLLECT_GAME_SQUIRREL_POSY_START = ((GAME_RESOLUTION_HEIGHT/2) + 425);
    static const float_t COLLECT_GAME_BASKET_POSY_START = ((GAME_RESOLUTION_HEIGHT/2) - 505);
    static const float_t COLLECT_GAME_BASKET_SPEED = 10;
    static const float_t COLLECT_GAME_GROUND_COLLISION_Y = 25;
    
 //   static const int32_t COLLECT_GAME_LEVEL_1_HAZELNUT_DROP_CHANCE = 36;
	//static const int32_t COLLECT_GAME_LEVEL_1_WASTE_DROP_CHANCE = 36;
	//static const int32_t COLLECT_GAME_LEVEL_1_APPLE_DROP_CHANCE = 15;
	//static const int32_t COLLECT_GAME_LEVEL_1_HEART_DROP_CHANCE = 10;
	//static const int32_t COLLECT_GAME_LEVEL_1_COIN_DROP_CHANCE = 3;
    /*static const int32_t COLLECT_GAME_LEVEL_1_MAX_DROP_CHANCE =  COLLECT_GAME_HAZELNUT_DROP_CHANCE
    + COLLECT_GAME_WASTE_DROP_CHANCE
    + COLLECT_GAME_APPLE_DROP_CHANCE
    + COLLECT_GAME_HEART_DROP_CHANCE
    + COLLECT_GAME_COIN_DROP_CHANCE;*/
    
    static const int32_t COLLECT_GAME_PLAYER_LIVES_START = 3;
    static const int32_t COLLECT_GAME_PLAYER_LIVES_MAX = 7;
    
    static const int32_t COLLECT_GAME_HAZELNUT_POINTS = 1;
    static const int32_t COLLECT_GAME_APPLE_POINTS  = 5;
    static const int32_t COLLECT_GAME_COIN_POINTS = 15;
    
    
    
    /** LEVEL SETTINGS **/
#ifndef PERFORMANCETEST
    //LEVEL 1
	static const int32_t COLLECT_GAME_LEVEL_1_SCORE_MAX = 10;
	static const float_t COLLECT_GAME_LEVEL_1_AI_SPEED = 3;
	static const float_t COLLECT_GAME_LEVEL_1_HAZELNUT_SPEED = 3;
	static const int32_t COLLECT_GAME_LEVEL_1_DROP_INTERVAL_MIN = 900;
	static const int32_t COLLECT_GAME_LEVEL_1_DROP_INTERVAL_MAX = 1400;
	static const int32_t COLLECT_GAME_LEVEL_1_DROP_SPEED_MIN = 2;
	static const int32_t COLLECT_GAME_LEVEL_1_DROP_SPEED_MAX = 3;
	static const int32_t COLLECT_GAME_LEVEL_1_SCORE_MULTIPLIER = 1;
	static const int32_t COLLECT_GAME_LEVEL_1_HAZELNUT_DROP_CHANCE = 55;
	static const int32_t COLLECT_GAME_LEVEL_1_WASTE_DROP_CHANCE = 45;
	static const int32_t COLLECT_GAME_LEVEL_1_APPLE_DROP_CHANCE = 0;
	static const int32_t COLLECT_GAME_LEVEL_1_HEART_DROP_CHANCE = 0;
	static const int32_t COLLECT_GAME_LEVEL_1_COIN_DROP_CHANCE = 0;
    
    //LEVEL 2
	static const int32_t COLLECT_GAME_LEVEL_2_SCORE_MAX = 20;
	static const float_t COLLECT_GAME_LEVEL_2_AI_SPEED = 4;
	static const float_t COLLECT_GAME_LEVEL_2_HAZELNUT_SPEED = 3;
	static const int32_t COLLECT_GAME_LEVEL_2_DROP_INTERVAL_MIN = 800;
	static const int32_t COLLECT_GAME_LEVEL_2_DROP_INTERVAL_MAX = 1300;
	static const int32_t COLLECT_GAME_LEVEL_2_DROP_SPEED_MIN = 2;
	static const int32_t COLLECT_GAME_LEVEL_2_DROP_SPEED_MAX = 4;
	static const int32_t COLLECT_GAME_LEVEL_2_SCORE_MULTIPLIER = 1;
	static const int32_t COLLECT_GAME_LEVEL_2_HAZELNUT_DROP_CHANCE = 45;
	static const int32_t COLLECT_GAME_LEVEL_2_WASTE_DROP_CHANCE = 40;
	static const int32_t COLLECT_GAME_LEVEL_2_APPLE_DROP_CHANCE = 0;
	static const int32_t COLLECT_GAME_LEVEL_2_HEART_DROP_CHANCE = 20;
	static const int32_t COLLECT_GAME_LEVEL_2_COIN_DROP_CHANCE = 0;
    
    //LEVEL 3
	static const int32_t COLLECT_GAME_LEVEL_3_SCORE_MAX = 32;
	static const float_t COLLECT_GAME_LEVEL_3_AI_SPEED = 5;
	static const float_t COLLECT_GAME_LEVEL_3_HAZELNUT_SPEED = 3;
	static const int32_t COLLECT_GAME_LEVEL_3_DROP_INTERVAL_MIN = 700;
	static const int32_t COLLECT_GAME_LEVEL_3_DROP_INTERVAL_MAX = 1200;
	static const int32_t COLLECT_GAME_LEVEL_3_DROP_SPEED_MIN = 2;
	static const int32_t COLLECT_GAME_LEVEL_3_DROP_SPEED_MAX = 4;
	static const int32_t COLLECT_GAME_LEVEL_3_SCORE_MULTIPLIER = 1;
	static const int32_t COLLECT_GAME_LEVEL_3_HAZELNUT_DROP_CHANCE = 45;
	static const int32_t COLLECT_GAME_LEVEL_3_WASTE_DROP_CHANCE = 40;
	static const int32_t COLLECT_GAME_LEVEL_3_APPLE_DROP_CHANCE = 0;
	static const int32_t COLLECT_GAME_LEVEL_3_HEART_DROP_CHANCE = 20;
	static const int32_t COLLECT_GAME_LEVEL_3_COIN_DROP_CHANCE = 0;
    
    //LEVEL 4
	static const int32_t COLLECT_GAME_LEVEL_4_SCORE_MAX = 46;
	static const float_t COLLECT_GAME_LEVEL_4_AI_SPEED = 6;
	static const float_t COLLECT_GAME_LEVEL_4_HAZELNUT_SPEED = 3;
	static const int32_t COLLECT_GAME_LEVEL_4_DROP_INTERVAL_MIN = 600;
	static const int32_t COLLECT_GAME_LEVEL_4_DROP_INTERVAL_MAX = 1100;
	static const int32_t COLLECT_GAME_LEVEL_4_DROP_SPEED_MIN = 2;
	static const int32_t COLLECT_GAME_LEVEL_4_DROP_SPEED_MAX = 4;
	static const int32_t COLLECT_GAME_LEVEL_4_SCORE_MULTIPLIER = 1;
	static const int32_t COLLECT_GAME_LEVEL_4_HAZELNUT_DROP_CHANCE = 40;
	static const int32_t COLLECT_GAME_LEVEL_4_WASTE_DROP_CHANCE = 30;
	static const int32_t COLLECT_GAME_LEVEL_4_APPLE_DROP_CHANCE = 15;
	static const int32_t COLLECT_GAME_LEVEL_4_HEART_DROP_CHANCE = 20;
	static const int32_t COLLECT_GAME_LEVEL_4_COIN_DROP_CHANCE = 0;
    
    //LEVEL 5
	static const int32_t COLLECT_GAME_LEVEL_5_SCORE_MAX = 64;
	static const float_t COLLECT_GAME_LEVEL_5_AI_SPEED = 7;
	static const float_t COLLECT_GAME_LEVEL_5_HAZELNUT_SPEED = 3;
	static const int32_t COLLECT_GAME_LEVEL_5_DROP_INTERVAL_MIN = 500;
	static const int32_t COLLECT_GAME_LEVEL_5_DROP_INTERVAL_MAX = 1000;
	static const int32_t COLLECT_GAME_LEVEL_5_DROP_SPEED_MIN = 2;
	static const int32_t COLLECT_GAME_LEVEL_5_DROP_SPEED_MAX = 4;
	static const int32_t COLLECT_GAME_LEVEL_5_SCORE_MULTIPLIER = 1;
	static const int32_t COLLECT_GAME_LEVEL_5_HAZELNUT_DROP_CHANCE = 40;
	static const int32_t COLLECT_GAME_LEVEL_5_WASTE_DROP_CHANCE = 30;
	static const int32_t COLLECT_GAME_LEVEL_5_APPLE_DROP_CHANCE = 15;
	static const int32_t COLLECT_GAME_LEVEL_5_HEART_DROP_CHANCE = 20;
	static const int32_t COLLECT_GAME_LEVEL_5_COIN_DROP_CHANCE = 0;
    
    
    //LEVEL 6
	static const int32_t COLLECT_GAME_LEVEL_6_SCORE_MAX = 86;
	static const float_t COLLECT_GAME_LEVEL_6_AI_SPEED = 8;
	static const float_t COLLECT_GAME_LEVEL_6_HAZELNUT_SPEED = 4;
	static const int32_t COLLECT_GAME_LEVEL_6_DROP_INTERVAL_MIN = 500;
	static const int32_t COLLECT_GAME_LEVEL_6_DROP_INTERVAL_MAX = 900;
	static const int32_t COLLECT_GAME_LEVEL_6_DROP_SPEED_MIN = 2;
	static const int32_t COLLECT_GAME_LEVEL_6_DROP_SPEED_MAX = 4;
	static const int32_t COLLECT_GAME_LEVEL_6_SCORE_MULTIPLIER = 1;
	static const int32_t COLLECT_GAME_LEVEL_6_HAZELNUT_DROP_CHANCE = 40;
	static const int32_t COLLECT_GAME_LEVEL_6_WASTE_DROP_CHANCE = 30;
	static const int32_t COLLECT_GAME_LEVEL_6_APPLE_DROP_CHANCE = 15;
	static const int32_t COLLECT_GAME_LEVEL_6_HEART_DROP_CHANCE = 20;
	static const int32_t COLLECT_GAME_LEVEL_6_COIN_DROP_CHANCE = 0;
    
    //LEVEL 7
	static const int32_t COLLECT_GAME_LEVEL_7_SCORE_MAX = 124;
	static const float_t COLLECT_GAME_LEVEL_7_AI_SPEED = 9;
	static const float_t COLLECT_GAME_LEVEL_7_HAZELNUT_SPEED = 4;
	static const int32_t COLLECT_GAME_LEVEL_7_DROP_INTERVAL_MIN = 400;
	static const int32_t COLLECT_GAME_LEVEL_7_DROP_INTERVAL_MAX = 800;
	static const int32_t COLLECT_GAME_LEVEL_7_DROP_SPEED_MIN = 2;
	static const int32_t COLLECT_GAME_LEVEL_7_DROP_SPEED_MAX = 4;
	static const int32_t COLLECT_GAME_LEVEL_7_SCORE_MULTIPLIER = 1;
	static const int32_t COLLECT_GAME_LEVEL_7_HAZELNUT_DROP_CHANCE = 40;
	static const int32_t COLLECT_GAME_LEVEL_7_WASTE_DROP_CHANCE = 30;
	static const int32_t COLLECT_GAME_LEVEL_7_APPLE_DROP_CHANCE = 15;
	static const int32_t COLLECT_GAME_LEVEL_7_HEART_DROP_CHANCE = 20;
	static const int32_t COLLECT_GAME_LEVEL_7_COIN_DROP_CHANCE = 0;
   
    //LEVEL 8
	static const int32_t COLLECT_GAME_LEVEL_8_SCORE_MAX = 166;
	static const float_t COLLECT_GAME_LEVEL_8_AI_SPEED = 10;
	static const float_t COLLECT_GAME_LEVEL_8_HAZELNUT_SPEED = 4;
	static const int32_t COLLECT_GAME_LEVEL_8_DROP_INTERVAL_MIN = 300;
	static const int32_t COLLECT_GAME_LEVEL_8_DROP_INTERVAL_MAX = 700;
	static const int32_t COLLECT_GAME_LEVEL_8_DROP_SPEED_MIN = 2;
	static const int32_t COLLECT_GAME_LEVEL_8_DROP_SPEED_MAX = 4;
	static const int32_t COLLECT_GAME_LEVEL_8_SCORE_MULTIPLIER = 1;
	static const int32_t COLLECT_GAME_LEVEL_8_HAZELNUT_DROP_CHANCE = 40;
	static const int32_t COLLECT_GAME_LEVEL_8_WASTE_DROP_CHANCE = 30;
	static const int32_t COLLECT_GAME_LEVEL_8_APPLE_DROP_CHANCE = 12;
	static const int32_t COLLECT_GAME_LEVEL_8_HEART_DROP_CHANCE = 20;
	static const int32_t COLLECT_GAME_LEVEL_8_COIN_DROP_CHANCE = 3;
    
    //LEVEL 9
	static const int32_t COLLECT_GAME_LEVEL_9_SCORE_MAX = 214;
	static const float_t COLLECT_GAME_LEVEL_9_AI_SPEED = 11;
	static const float_t COLLECT_GAME_LEVEL_9_HAZELNUT_SPEED = 4;
	static const int32_t COLLECT_GAME_LEVEL_9_DROP_INTERVAL_MIN = 200;
	static const int32_t COLLECT_GAME_LEVEL_9_DROP_INTERVAL_MAX = 600;
	static const int32_t COLLECT_GAME_LEVEL_9_DROP_SPEED_MIN = 2;
	static const int32_t COLLECT_GAME_LEVEL_9_DROP_SPEED_MAX = 4;
	static const int32_t COLLECT_GAME_LEVEL_9_SCORE_MULTIPLIER = 1;
	static const int32_t COLLECT_GAME_LEVEL_9_HAZELNUT_DROP_CHANCE = 40;
	static const int32_t COLLECT_GAME_LEVEL_9_WASTE_DROP_CHANCE = 30;
	static const int32_t COLLECT_GAME_LEVEL_9_APPLE_DROP_CHANCE = 12;
	static const int32_t COLLECT_GAME_LEVEL_9_HEART_DROP_CHANCE = 20;
	static const int32_t COLLECT_GAME_LEVEL_9_COIN_DROP_CHANCE = 3;
    
    //LEVEL 10
    static const int32_t COLLECT_GAME_LEVEL_10_SCORE_MAX = 258;
    static const float_t COLLECT_GAME_LEVEL_10_AI_SPEED = 12;
	static const float_t COLLECT_GAME_LEVEL_10_HAZELNUT_SPEED = 4;
    static const int32_t COLLECT_GAME_LEVEL_10_DROP_INTERVAL_MIN = 200;
    static const int32_t COLLECT_GAME_LEVEL_10_DROP_INTERVAL_MAX = 500;
    static const int32_t COLLECT_GAME_LEVEL_10_DROP_SPEED_MIN = 2;
    static const int32_t COLLECT_GAME_LEVEL_10_DROP_SPEED_MAX = 4;
    static const int32_t COLLECT_GAME_LEVEL_10_SCORE_MULTIPLIER = 1;
	static const int32_t COLLECT_GAME_LEVEL_10_HAZELNUT_DROP_CHANCE = 40;
	static const int32_t COLLECT_GAME_LEVEL_10_WASTE_DROP_CHANCE = 30;
	static const int32_t COLLECT_GAME_LEVEL_10_APPLE_DROP_CHANCE = 12;
	static const int32_t COLLECT_GAME_LEVEL_10_HEART_DROP_CHANCE = 20;
	static const int32_t COLLECT_GAME_LEVEL_10_COIN_DROP_CHANCE = 3;
    
    //LEVEL 11
	static const int32_t COLLECT_GAME_LEVEL_11_SCORE_MAX = 328;
	static const float_t COLLECT_GAME_LEVEL_11_AI_SPEED = 13;
	static const float_t COLLECT_GAME_LEVEL_11_HAZELNUT_SPEED = 5;
	static const int32_t COLLECT_GAME_LEVEL_11_DROP_INTERVAL_MIN = 200;
	static const int32_t COLLECT_GAME_LEVEL_11_DROP_INTERVAL_MAX = 450;
	static const int32_t COLLECT_GAME_LEVEL_11_DROP_SPEED_MIN = 2;
	static const int32_t COLLECT_GAME_LEVEL_11_DROP_SPEED_MAX = 4;
	static const int32_t COLLECT_GAME_LEVEL_11_SCORE_MULTIPLIER = 1;
	static const int32_t COLLECT_GAME_LEVEL_11_HAZELNUT_DROP_CHANCE = 40;
	static const int32_t COLLECT_GAME_LEVEL_11_WASTE_DROP_CHANCE = 30;
	static const int32_t COLLECT_GAME_LEVEL_11_APPLE_DROP_CHANCE = 12;
	static const int32_t COLLECT_GAME_LEVEL_11_HEART_DROP_CHANCE = 20;
	static const int32_t COLLECT_GAME_LEVEL_11_COIN_DROP_CHANCE = 3;
   
    //LEVEL 12
	static const int32_t COLLECT_GAME_LEVEL_12_SCORE_MAX = 394;
	static const float_t COLLECT_GAME_LEVEL_12_AI_SPEED = 14;
	static const float_t COLLECT_GAME_LEVEL_12_HAZELNUT_SPEED = 5;
	static const int32_t COLLECT_GAME_LEVEL_12_DROP_INTERVAL_MIN = 150;
	static const int32_t COLLECT_GAME_LEVEL_12_DROP_INTERVAL_MAX = 400;
	static const int32_t COLLECT_GAME_LEVEL_12_DROP_SPEED_MIN = 2;
	static const int32_t COLLECT_GAME_LEVEL_12_DROP_SPEED_MAX = 4;
	static const int32_t COLLECT_GAME_LEVEL_12_SCORE_MULTIPLIER = 1;
	static const int32_t COLLECT_GAME_LEVEL_12_HAZELNUT_DROP_CHANCE = 40;
	static const int32_t COLLECT_GAME_LEVEL_12_WASTE_DROP_CHANCE = 30;
	static const int32_t COLLECT_GAME_LEVEL_12_APPLE_DROP_CHANCE = 12;
	static const int32_t COLLECT_GAME_LEVEL_12_HEART_DROP_CHANCE = 20;
	static const int32_t COLLECT_GAME_LEVEL_12_COIN_DROP_CHANCE = 3;
    
    //LEVEL 13
	static const int32_t COLLECT_GAME_LEVEL_13_SCORE_MAX = 466;
	static const float_t COLLECT_GAME_LEVEL_13_AI_SPEED = 15;
	static const float_t COLLECT_GAME_LEVEL_13_HAZELNUT_SPEED = 5;
	static const int32_t COLLECT_GAME_LEVEL_13_DROP_INTERVAL_MIN = 150;
	static const int32_t COLLECT_GAME_LEVEL_13_DROP_INTERVAL_MAX = 350;
	static const int32_t COLLECT_GAME_LEVEL_13_DROP_SPEED_MIN = 2;
	static const int32_t COLLECT_GAME_LEVEL_13_DROP_SPEED_MAX = 4;
	static const int32_t COLLECT_GAME_LEVEL_13_SCORE_MULTIPLIER = 1;
	static const int32_t COLLECT_GAME_LEVEL_13_HAZELNUT_DROP_CHANCE = 40;
	static const int32_t COLLECT_GAME_LEVEL_13_WASTE_DROP_CHANCE = 30;
	static const int32_t COLLECT_GAME_LEVEL_13_APPLE_DROP_CHANCE = 12;
	static const int32_t COLLECT_GAME_LEVEL_13_HEART_DROP_CHANCE = 20;
	static const int32_t COLLECT_GAME_LEVEL_13_COIN_DROP_CHANCE = 3;
    
    //LEVEL 14
	static const int32_t COLLECT_GAME_LEVEL_14_SCORE_MAX = 544;
	static const float_t COLLECT_GAME_LEVEL_14_AI_SPEED = 16;
	static const float_t COLLECT_GAME_LEVEL_14_HAZELNUT_SPEED = 5;
	static const int32_t COLLECT_GAME_LEVEL_14_DROP_INTERVAL_MIN = 100;
	static const int32_t COLLECT_GAME_LEVEL_14_DROP_INTERVAL_MAX = 300;
	static const int32_t COLLECT_GAME_LEVEL_14_DROP_SPEED_MIN = 2;
	static const int32_t COLLECT_GAME_LEVEL_14_DROP_SPEED_MAX = 4;
	static const int32_t COLLECT_GAME_LEVEL_14_SCORE_MULTIPLIER = 1;
	static const int32_t COLLECT_GAME_LEVEL_14_HAZELNUT_DROP_CHANCE = 40;
	static const int32_t COLLECT_GAME_LEVEL_14_WASTE_DROP_CHANCE = 30;
	static const int32_t COLLECT_GAME_LEVEL_14_APPLE_DROP_CHANCE = 12;
	static const int32_t COLLECT_GAME_LEVEL_14_HEART_DROP_CHANCE = 20;
	static const int32_t COLLECT_GAME_LEVEL_14_COIN_DROP_CHANCE = 3;
   
    //LEVEL 15
	static const int32_t COLLECT_GAME_LEVEL_15_SCORE_MAX = 590;
	static const float_t COLLECT_GAME_LEVEL_15_AI_SPEED = 17;
	static const float_t COLLECT_GAME_LEVEL_15_HAZELNUT_SPEED = 6;
	static const int32_t COLLECT_GAME_LEVEL_15_DROP_INTERVAL_MIN = 100;
	static const int32_t COLLECT_GAME_LEVEL_15_DROP_INTERVAL_MAX = 250;
	static const int32_t COLLECT_GAME_LEVEL_15_DROP_SPEED_MIN = 2;
	static const int32_t COLLECT_GAME_LEVEL_15_DROP_SPEED_MAX = 4;
	static const int32_t COLLECT_GAME_LEVEL_15_SCORE_MULTIPLIER = 1;
	static const int32_t COLLECT_GAME_LEVEL_15_HAZELNUT_DROP_CHANCE = 40;
	static const int32_t COLLECT_GAME_LEVEL_15_WASTE_DROP_CHANCE = 30;
	static const int32_t COLLECT_GAME_LEVEL_15_APPLE_DROP_CHANCE = 12;
	static const int32_t COLLECT_GAME_LEVEL_15_HEART_DROP_CHANCE = 20;
	static const int32_t COLLECT_GAME_LEVEL_15_COIN_DROP_CHANCE = 3;
    
#endif
    
#ifdef PERFORMANCETEST
    //LEVEL PERFORMANCE TEST
//    static const int32_t COLLECT_GAME_LEVEL_X_AI_SPEED = 1;
//    static const float_t COLLECT_GAME_LEVEL_X_DROP_INTERVAL_MIN = 1;
//    static const int32_t COLLECT_GAME_LEVEL_X_DROP_INTERVAL_MAX = 1;
//    static const int32_t COLLECT_GAME_LEVEL_X_DROP_SPEED_MIN = 1;
//    static const int32_t COLLECT_GAME_LEVEL_X_DROP_SPEED_MAX = 1;
//    static const int32_t COLLECT_GAME_LEVEL_X_SCORE_MULTIPLIER = 10000;
    
    static const int32_t COLLECT_GAME_LEVEL_X_SCORE_MAX = 1;
    static const float_t COLLECT_GAME_LEVEL_X_AI_SPEED = 1;
    static const float_t COLLECT_GAME_LEVEL_X_HAZELNUT_SPEED = 1;
    static const int32_t COLLECT_GAME_LEVEL_X_DROP_INTERVAL_MIN = 10;
    static const int32_t COLLECT_GAME_LEVEL_X_DROP_INTERVAL_MAX = 30;
    static const int32_t COLLECT_GAME_LEVEL_X_DROP_SPEED_MIN = 1;
    static const int32_t COLLECT_GAME_LEVEL_X_DROP_SPEED_MAX = 5;
    static const int32_t COLLECT_GAME_LEVEL_X_SCORE_MULTIPLIER = 10000;
    static const int32_t COLLECT_GAME_LEVEL_X_HAZELNUT_DROP_CHANCE = 20;
    static const int32_t COLLECT_GAME_LEVEL_X_WASTE_DROP_CHANCE = 20;
    static const int32_t COLLECT_GAME_LEVEL_X_APPLE_DROP_CHANCE = 20;
    static const int32_t COLLECT_GAME_LEVEL_X_HEART_DROP_CHANCE = 20;
    static const int32_t COLLECT_GAME_LEVEL_X_COIN_DROP_CHANCE = 20;
#endif
    
    //TEXTURES

#ifdef ETC1
	static const std::string extension = ".pkm";
#else
	static const std::string extension = ".png";
#endif
    
    //Overall Game
    static const std::string TEXTURE_GAME_MAP_1 = "Map1" + extension;
    static const std::string TEXTURE_GAME_MAP_1_EXTENSION = "Map1_extension" + extension;
    static const std::string TEXTURE_GAME_MAP_1_POPUP = "GamePopupBackground" + extension;
	static const std::string TEXTURE_GAME_BRANCH = "branch" + extension;
    
    static const std::string TEXTURE_GAME_POPUP_FRAME = "frame" + extension;
    
    static const std::string TEXTURE_GAME_CLOUD_1 = "cloud1" + extension;
    static const std::string TEXTURE_GAME_CLOUD_2 = "cloud2" + extension;
    static const std::string TEXTURE_GAME_CLOUD_3 = "cloud3" + extension;

	static const std::string TEXTURE_GAME_BIRD_FRAME_1 = "bird_down" + extension;
	static const std::string TEXTURE_GAME_BIRD_FRAME_2 = "bird_up" + extension;

    
    //Menu
	static const std::string TEXTURE_MENU_LABEL_HEADER		= "MenuHeader" + extension;
    static const std::string TEXTURE_MENU_BUTTON_START      = "MenuButtonStart" + extension;
    static const std::string TEXTURE_MENU_BUTTON_HIGHSCORE  = "MenuButtonHighscore" + extension;
    static const std::string TEXTURE_MENU_BUTTON_EXIT       = "MenuButtonExit" + extension;
    static const std::string TEXTURE_MENU_BUTTON_TUTORIAL   = "MenuButtonTutorial" + extension;
    
    static const std::string TEXTURE_MENU_POPUP_BUTTON_ABOUT        = "MenuButtonAbout" + extension;
    static const std::string TEXTURE_MENU_POPUP_BUTTON_HELP         = "MenuButtonHelp" + extension;
    static const std::string TEXTURE_MENU_POPUP_BUTTON_SOUND_OFF    = "MenuButtonSoundOff" + extension;
    static const std::string TEXTURE_MENU_POPUP_BUTTON_SOUND_ON     = "MenuButtonSoundOn" + extension;
    
    //Collect Game
    
    //Size needed to change texture of a sprite (DropObject object pool)
    static const std::string TEXTURE_COLLECT_GAME_HEART_ANIM_1 = "Heart_anim_1" + extension;
    static const std::string TEXTURE_COLLECT_GAME_HEART_ANIM_2 = "Heart_anim_2" + extension;
    static const std::string TEXTURE_COLLECT_GAME_HEART_ANIM_3 = "Heart_anim_3" + extension;
    static const std::string TEXTURE_COLLECT_GAME_HEART_ANIM_4 = "Heart_anim_4" + extension;
    static const std::string TEXTURE_COLLECT_GAME_HEART_ANIM_5 = "Heart_anim_5" + extension;


    
    
    static const std::string TEXTURE_COLLECT_GAME_APPLE     = "Apple2" + extension;
    static const int32_t TEXTURE_COLLECT_GAME_APPLE_SIZE    = 53;
    
    static const std::string TEXTURE_COLLECT_GAME_APPLE_BROKEN     = "Apple2_broken" + extension;
    static const int32_t TEXTURE_COLLECT_GAME_APPLE_BROKEN_SIZE    = 53;
    
    static const std::string TEXTURE_COLLECT_GAME_WASTE     = "Waste2" + extension;
    static const int32_t TEXTURE_COLLECT_GAME_WASTE_SIZE    = 50;
    
    
    static const std::string TEXTURE_COLLECT_GAME_HAZELNUT  = "Hazelnut2" + extension;
    static const int32_t TEXTURE_COLLECT_GAME_HAZELNUT_SIZE = 58;
    
    static const std::string TEXTURE_COLLECT_GAME_HAZELNUT_BROKEN = "Hazelnut2_broken" + extension;
    static const int32_t TEXTURE_COLLECT_GAME_HAZELNUT_BROKEN_SIZE = 50;
    
    static const std::string TEXTURE_COLLECT_GAME_HEART     = "Heart" + extension;
    static const int32_t TEXTURE_COLLECT_GAME_HEART_SIZE    = 100;
    
    static const std::string TEXTURE_COLLECT_GAME_COIN      = "coin" + extension;
    static const int32_t TEXTURE_COLLECT_GAME_COIN_SIZE     = 78;
    
    static const std::string TEXTURE_COLLECT_GAME_BASKET    = "Korb" + extension;
    static const int32_t TEXTURE_COLLECT_GAME_BASKET_SIZE    = 106;
     
    static const std::string TEXTURE_COLLECT_GAME_SQUIRREL  = "squirrel" + extension;

	static const std::string TEXTURE_COLLECT_GAME_SQUIRREL_ANGRY = "Squirrel_angry" + extension;

    static const std::string TEXTURE_COLLECT_GAME_BUTTON_MENU       = "MenuButton" + extension;
    
    static const std::string TEXTURE_COLLECT_GAME_BUTTON_RETRY      = "MenuButtonRetry" + extension;
    static const std::string TEXTURE_COLLECT_GAME_BUTTON_REGISTER   = "MenuButtonRegister" + extension;
    static const std::string TEXTURE_COLLECT_GAME_EDIT_BOX          = "EditBoxTemplate" + extension;

    static const std::string TEXTURE_COLLECT_GAME_POPUP_RESUME  = "PopupButtonResume" + extension;
    static const std::string TEXTURE_COLLECT_GAME_POPUP_EXIT    = "PopupButtonQuit" + extension;
    
    static const std::string TEXTURE_COLLECT_GAME_TEXT_FIELD    = "EditBoxTemplate" + extension;
    
    //Highscore
    static const std::string TEXTURE_HIGHSCORE_TABLE_BG     = "highscore" + extension;
    static const std::string TEXTURE_HIGHSCORE_BUTTON_BACK  = "MenuButtonBack" + extension;
    
    //Tutorial
    static const std::string TEXTURE_TUTORIAL_TAP_HERE_RIGHT = "tap_right" + extension;
    static const std::string TEXTURE_TUTORIAL_TAP_HERE_LEFT = "tap_left" + extension;
    
    
    //SOUNDS & MUSIC
    
    //Engine audio requires char*
    static const char* MUSIC_BIRDS_ENVIRONMENT =    "sound/music_generic.m4a";
    static const char* SOUND_APPLE_BITE =           "sound/sound_apple.m4a";
    static const char* SOUND_COIN_COLLECT =         "sound/sound_coin.m4a";
    static const char* SOUND_PAPER_WAD =            "sound/sound_waste.m4a";
    static const char* SOUND_BUTTON_1 =             "sound/sound_button.m4a";
    static const char* SOUND_OTHER_1 =              "sound/sound_hazelnut.m4a";
    static const char* SOUND_LEVEL_UP =             "sound/sound_level_up.m4a";
	static const char* SOUND_HEART_COLLECT =		"sound/sound_heart.m4a";
	
	//TEXT
	static const char* FONT_QUARMIC_SANS = 			"fonts/Qarmic sans Abridged.ttf";
}

#endif /* defined(__Hazelnut__DataHandler__) */
