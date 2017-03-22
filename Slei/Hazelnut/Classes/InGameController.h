//
//  InGameController.h
//  Hazelnut
//
//  Created by Dominik Reisner on 12.11.14.
//
//

#ifndef __Hazelnut__InGameController__
#define __Hazelnut__InGameController__

#include "FGeneral.h"

#include <stdlib.h>
#include <CocosGUI.h>

#include "FSprite.h"

#include "FrameworkScene.h"

#include "AI.h"
#include "CollisionBox.h"
#include "LevelSystem.h"
#include "TextFieldExtended.h"
#include "FrameworkButton.h"

#include "FStateMachine.h"
#include "GamePausePopup.h"
#include "Subject.h"

USING_NS_CC;


class InGameScene;

class InGameController
{
    typedef void (InGameController::*state_func_ptr)(float delta);
    
public:
    InGameController(InGameScene* scene);
    ~InGameController();
    
    
    //============================================================================================================
    // General
    void OnInit();
    void OnEnter();
    
    void Tick(float delta);
    
    bool GetNewObjectFound();
    void SetNewObjectFound(bool new_object_found);
    
    Vector<Sprite*>& GetSceneObjects();
    Sprite* GetNewObject();
    
private:
    void NotifyHappen();
    void UpdateTextAndLives();
    void UpdateLiveBar();
    void GenerateLiveBar();
    
    //============================================================================================================
    //Timeframe functionptr
    void MoveOutLevelUp();
    void LevelUpEnd();
    
    //======================================================
    // Clouds
    void CloudMovement();
    
    //======================================================
    // Birds
    void BirdMovement();
    
    
    //============================================================================================================
    // States
private:
    void OnStateRunning(float delta);
    void OnStateEnter(float delta);
    void OnStatePaused(float delta);
    void OnStateGameOver(float delta);
    void OnStateLevelUp(float delta);
    void OnStatePopupMenu(float delta);
    void OnStateExit(float delta);
    void OnStateIdle(float delta); //intentionally left empty to do nothing
    
    //============================================================================================================
    // General variables
private:
    Vector<Sprite*> scene_objects_;
    std::vector<Sprite*> live_bar_player_lives_;

    LevelSystem lvl_system_;
    
    CollisionBox basket_collision_box_;
    
    FStateMachine f;
    FStateMachine state_machine_;
    
    FTimeframe timeframe_;
    FTimeframe timeframe_animation_;
    FTimeframe timeframe_animation_2_;
    FTimeframe timeframe_state_;
    
    
    AI ai_;

    
    FSprite* squirrel_;
	FSprite* background_;
	FSprite* branch_;
    FSprite* cloud_1_;
    FSprite* cloud_2_;
    FSprite* cloud_3_;
	FSprite* bird_;
	FSprite* sprite_anim_bird;
	FSprite* sprite_anim_bird1;
    FSprite* scene_object_;
    FSprite* basket_;
    
    
    GamePausePopup* popup_pause_;
    
    FrameworkButton* button_menu_;
    FrameworkButton* button_left_;
    FrameworkButton* button_right_;
    FrameworkButton* button_start_game_;
	FrameworkButton* buttonRetry;
	FrameworkButton* buttonRegister;
	FrameworkButton* buttonShareScore;
	TextFieldExtended* tfeUsername;
    
    Label* label_level_up_;
    Label* label_player_score_;

    
    InGameScene* scene_;
    
    
    int squirrel_speed_;
	int hazelnut_speed_;
    int drop_object_speed_min_;
    int drop_object_speed_max_;
    int drop_interval_min_;
    int drop_interval_max_;
	int drop_c_hazelnut_;
	int drop_c_waste_;
	int drop_c_apple_;
	int drop_c_heart_;
	int drop_c_coin_;
    int level_score_multiplier_;
    
    bool    button_pressed_;
    long    player_score_;
    long    prev_player_score_;
    int     player_lives_;
    int     prev_player_lives_;
    
    EInGameState in_game_state_;
    
    int squirrel_pos_x_;
    
    //============================================================================================================
    // States
private:
    const std::string SQUIRREL;
    const std::string BASKET;
    const std::string BACKGROUND;
    
    const std::string STATE_RUNNING;
    const std::string STATE_ENTER;
    const std::string STATE_PAUSED;
    const std::string STATE_GAME_OVER;
    const std::string STATE_LEVEL_UP;
    const std::string STATE_POPUP_MENU;
    const std::string STATE_EXIT;
    const std::string STATE_IDLE;

};

FORCEINLINE Vector<Sprite*>& InGameController::GetSceneObjects()
{
    return scene_objects_;
}

#endif /* defined(__Hazelnut__InGameController__) */
