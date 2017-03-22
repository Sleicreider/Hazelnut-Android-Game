//
//  TutorialScene.h
//  Hazelnut
//
//  Created by Dominik Reisner on 04.05.15.
//
//

#ifndef __Hazelnut__TutorialScene__
#define __Hazelnut__TutorialScene__



#include "FrameworkScene.h"
#include "Loader.h"
#include "FrameworkButton.h"
#include "TutorialPopup.h"

class GamePopup;

USING_NS_CC;

class TutorialScene : public FrameworkScene
{
    typedef void (TutorialScene::*state_func_ptr)(float delta);
    
public:
    TutorialScene();
    virtual ~TutorialScene();
    
    static Scene* CreateTutorialScene();
    
    virtual bool init();
    virtual void Tick(float delta);
    virtual void onExit();
    virtual void onEnter();
    
    CREATE_FUNC(TutorialScene);
    
private:
    
    void OnStateMoveTutorial(float delta);
    void OnStateCollectTutorial(float delta);
    void OnStateEnter(float delta);

    
    
    void FadeInBackground();

private:
    static const std::string STATE_MOVE_TUTORIAL;
    static const std::string STATE_COLLECT_TUTORIAL;
    static const std::string STATE_ENTER;
    static const std::string STATE_PAUSED;
    static const std::string STATE_GAME_OVER;
    static const std::string STATE_LEVEL_UP;
    static const std::string STATE_EXIT;
    static const std::string STATE_IDLE;

private:
    FStateMachine state_machine_;
    FrameworkTimer timer_;
    
    FTimeframe timeframe_;
    FTimeframe timeframe_animation_;
    FTimeframe timeframe_animation_2_;
    FTimeframe timeframe_animation_3_;
    
    Loader loader_;
    
    FSprite* background_;
    FSprite* scene_object_;
    FSprite* basket_;
    
    FSprite* tap_right_;
    FSprite* tap_left_;
    
    FSprite* tap_area_;
    
    
    TutorialPopup* tutorial_popup_;
    
    FrameworkButton* button_left_;
    FrameworkButton* button_right_;
    FrameworkButton* button_menu_;
    
    float fade_in_start_alpha_;
    float fade_in_end_alpha_;
    milliseconds fade_in_time_;
    bool bReadyToStart_;
    
    milliseconds fade_in_current_time_;
    milliseconds fade_in_end_time_;
    
    
    Sprite* sprite_;
    
    static const int MAX_STEPS = 10;
    bool steps_[MAX_STEPS];
};

#endif /* defined(__Hazelnut__TutorialScene__) */
