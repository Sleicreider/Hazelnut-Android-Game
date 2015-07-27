//
//  TutorialScene.cpp
//  Hazelnut
//
//  Created by Dominik Reisner on 04.05.15.
//
//

#include "TutorialScene.h"
#include "FUtil.h"


const std::string TutorialScene::STATE_MOVE_TUTORIAL = "state_move_tutorial";
const std::string TutorialScene::STATE_COLLECT_TUTORIAL = "state_collect_tutorial";

const std::string TutorialScene::STATE_ENTER = "state_enter";
const std::string TutorialScene::STATE_PAUSED = "state_paused";
const std::string TutorialScene::STATE_LEVEL_UP = "state_level_up";
const std::string TutorialScene::STATE_EXIT = "state_exit";
const std::string TutorialScene::STATE_GAME_OVER= "state_game_over";
const std::string TutorialScene::STATE_IDLE = "state_idle";


TutorialScene::TutorialScene()
: bReadyToStart_(false)
, fade_in_start_alpha_(0)
, fade_in_end_alpha_(0)
{
    for(int i = 0; i < MAX_STEPS; i++)
    {
        steps_[i] = 0;
    }
}

TutorialScene::~TutorialScene()
{
}

Scene* TutorialScene::CreateTutorialScene()
{
    Scene* scene = Scene::create();
    Layer* layer = TutorialScene::create();
    
    scene->addChild(layer);
    return scene;
}

bool TutorialScene::init()
{
    if(!Layer::init())
    {
        return false;
    }
    
    //Background
    background_ = FSprite::create(DataHandler::TEXTURE_GAME_MAP_1, Vec2(DataHandler::GAME_RESOLUTION_WIDTH/2,
                                                                                      DataHandler::GAME_RESOLUTION_HEIGHT/2));
    addChild(background_);
    
    //Background extension
    if(DataHandler::app_layout_ == EAppLayout::LAYOUT_IPAD)
    {
        FSprite* background_extension = FSprite::create( DataHandler::TEXTURE_GAME_MAP_1_EXTENSION
                                                         ,Vec2(DataHandler::GAME_RESOLUTION_WIDTH/2,DataHandler::GAME_RESOLUTION_HEIGHT+180));
        background_extension->setScale(32, 6);
        
        addChild(background_extension);
    }
    else if(DataHandler::app_layout_ == EAppLayout::LAYOUT_DEFAULT)
    {
        FSprite* background_extension = FSprite::create(  DataHandler::TEXTURE_GAME_MAP_1_EXTENSION
                                                         ,Vec2(DataHandler::GAME_RESOLUTION_WIDTH/2,DataHandler::GAME_RESOLUTION_HEIGHT+100));
        background_extension->setScale(32, 3.35);
        
        addChild(background_extension);
    }
    
    //Basket
    basket_ = FSprite::create(DataHandler::TEXTURE_COLLECT_GAME_BASKET
        , FUtil::GenerateETC1AlphaString(DataHandler::TEXTURE_COLLECT_GAME_BASKET)
        , Vec2(DataHandler::GAME_RESOLUTION_WIDTH/2
        , DataHandler::COLLECT_GAME_BASKET_POSY_START));
    addChild(basket_);
    
    //Squirrel
    squirrel_ = FSprite::create(DataHandler::TEXTURE_COLLECT_GAME_SQUIRREL
                                ,FUtil::GenerateETC1AlphaString(DataHandler::TEXTURE_COLLECT_GAME_SQUIRREL)
                                ,Vec2(DataHandler::GAME_RESOLUTION_WIDTH/2
                                ,DataHandler::COLLECT_GAME_SQUIRREL_POSY_START));
    addChild(squirrel_);
    
    background_->setZOrder(0);
    squirrel_->setZOrder(2);
    basket_->setZOrder(2);
    
    int32_t height = 1080;
    int32_t tap_area_pos_y = 0;
    if(DataHandler::app_layout_ != EAppLayout::LAYOUT_WIDESCREEN)
    {
        height = 1536;
        tap_area_pos_y = 150;
    }
    
    button_right_ = FrameworkButton::create(this, DataHandler::GAME_RESOLUTION_WIDTH/2, height);
    button_right_->SetPositionX(DataHandler::GAME_RESOLUTION_WIDTH-button_right_->GetWidth()/2);
    button_right_->SetPositionY(DataHandler::GAME_RESOLUTION_HEIGHT/2 + tap_area_pos_y);
    button_right_->SetZOrder(0);
    addChild(button_right_);
    
    button_left_ = FrameworkButton::create(this, DataHandler::GAME_RESOLUTION_WIDTH/2, height);
    button_left_->SetPositionX(button_left_->GetWidth()/2);
    button_left_->SetPositionY(DataHandler::GAME_RESOLUTION_HEIGHT/2 + tap_area_pos_y);
    button_left_->SetZOrder(0);
    addChild(button_left_);
    
    tap_right_ = FSprite::create(DataHandler::TEXTURE_TUTORIAL_TAP_HERE_RIGHT
                                 ,FUtil::GenerateETC1AlphaString(DataHandler::TEXTURE_TUTORIAL_TAP_HERE_RIGHT)
                                 ,Vec2(DataHandler::GAME_RESOLUTION_WIDTH/2 - 450,DataHandler::GAME_RESOLUTION_HEIGHT/2));
    addChild(tap_right_);
    
    tap_left_ = FSprite::create(DataHandler::TEXTURE_TUTORIAL_TAP_HERE_LEFT
                                ,FUtil::GenerateETC1AlphaString(DataHandler::TEXTURE_TUTORIAL_TAP_HERE_LEFT)
                                ,Vec2(DataHandler::GAME_RESOLUTION_WIDTH/2 + 450 ,DataHandler::GAME_RESOLUTION_HEIGHT/2));
    addChild(tap_left_);
    
    
    tap_area_ = FSprite::create(DataHandler::TEXTURE_GAME_MAP_1_POPUP, Vec2(button_right_->GetPositionX(),button_right_->GetPositionY()));
    tap_area_->setScale(button_right_->GetWidth()/tap_area_->getContentSize().width,height/tap_area_->getContentSize().height);
    addChild(tap_area_);
    
    
    SetActiveAndVisible(tap_left_, false);
    SetActiveAndVisible(tap_right_, false);
    SetActiveAndVisible(tap_area_, false);
    
    
    //TUTORIAL POPUP
    tutorial_popup_ = TutorialPopup::CreatePopup(this);
    
    
    AddTickable(state_machine_);
    AddTickable(timeframe_);
    AddTickable(timeframe_animation_);
    AddTickable(timeframe_animation_2_);
    AddTickable(timeframe_animation_3_);
    
    state_machine_.Register(STATE_MOVE_TUTORIAL, this, &TutorialScene::OnStateMoveTutorial);
    state_machine_.Register(STATE_COLLECT_TUTORIAL, this, &TutorialScene::OnStateCollectTutorial);
    state_machine_.Register(STATE_ENTER, this, &TutorialScene::OnStateEnter);
    state_machine_.Register(STATE_GAME_OVER, this, &TutorialScene::OnStateGameOver);
    state_machine_.Register(STATE_LEVEL_UP, this, &TutorialScene::OnStateLevelUp);
    state_machine_.Register(STATE_PAUSED, this, &TutorialScene::OnStatePaused);
    state_machine_.Register(STATE_EXIT, this, &TutorialScene::OnStateExit);
    state_machine_.Register(STATE_IDLE, this, &TutorialScene::OnStateIdle);
    
    state_machine_.SetState(STATE_ENTER);
    
    timeframe_.Start(milliseconds(2000));
    
    
    return true;
}

void TutorialScene::onExit()
{
    Layer::onExit();
}

void TutorialScene::onEnter()
{
    Layer::onEnter();
}

void TutorialScene::Tick(float delta)
{
    if(bReadyToStart_)
    {
        if(timer_.GetCurrentTimeInMilliseconds() <= fade_in_end_time_)
        {
            float percent = ((float)timer_.GetCurrentTimeInMilliseconds().count() - (float)fade_in_current_time_.count())/((float)fade_in_end_time_.count() - (float) fade_in_current_time_.count());
            
            float i = (1-percent)*fade_in_start_alpha_ + percent*fade_in_end_alpha_;
            
            sprite_->setOpacity(i);
        }
        else if(timer_.GetCurrentTimeInMilliseconds() > fade_in_end_time_)
        {
            sprite_->setOpacity(fade_in_end_alpha_);
            bReadyToStart_ = false;
        }
        
    }
}

void TutorialScene::OnStateEnter(float delta)
{
    if(timeframe_.WasRunning())
    {
        FadeInBackground();
        state_machine_.SetState(STATE_MOVE_TUTORIAL);
    }
}

void TutorialScene::OnStateMoveTutorial(float delta)
{
    if(button_right_->WasPressed() && !steps_[0] && !timeframe_animation_3_.IsRunning())
    {
        FadeTo* fade = FadeTo::create(1.0,0);
        tap_right_->runAction(fade);
        
        FadeTo* fade_2 = FadeTo::create(1.0, 0);
        tap_area_->runAction(fade_2);
        
        timeframe_animation_.Start(milliseconds(1000));
        
        steps_[0] = 1;
    }
    
    if(timeframe_animation_.WasRunning())
    {
        SetActiveAndVisible(tap_right_, false);
        SetActiveAndVisible(tap_left_, true);
        tap_left_->setOpacity(0);
        
        FadeTo* fade = FadeTo::create(1.0, 255);
        tap_left_->runAction(fade);
        
        tap_area_->setPosition(button_left_->GetPositionX(),button_left_->GetPositionY());
        FadeTo* fade_2 = FadeTo::create(1.0,100);
        tap_area_->runAction(fade_2);
        
        timeframe_animation_2_.Start(milliseconds(1000));
    }
    
    if(button_left_->WasPressed() && steps_[0] && !timeframe_animation_2_.IsRunning() && !timeframe_animation_.IsRunning())
    {
        FadeTo* fade = FadeTo::create(1.0,0);
        tap_left_->runAction(fade);
        
        FadeTo* fade_2 = FadeTo::create(1.0,0);
        tap_area_->runAction(fade_2);
        
        timeframe_.Start(milliseconds(1000));
        
        steps_[1] = 1;
        
        state_machine_.SetState(STATE_COLLECT_TUTORIAL);
    }
    
    
    if(button_right_->IsPressed())
    {
        if(basket_->getPositionX() < (DataHandler::GAME_RESOLUTION_WIDTH-25)) //25 hardcodet half of basket size
        {
            basket_->setPositionX(basket_->getPositionX() + DataHandler::COLLECT_GAME_BASKET_SPEED);
        }
        
    }
    else if (button_left_->IsPressed())
    {
        if(basket_->getPositionX() > (0+25)) //25 hardcodet half of basket size
        {
            basket_->setPositionX(basket_->getPositionX() - DataHandler::COLLECT_GAME_BASKET_SPEED);
        }
    }
}

void TutorialScene::OnStateCollectTutorial(float delta)
{
    if(timeframe_.WasRunning())
    {
        tutorial_popup_->SetTextIndex(TutorialPopup::HAZELNUT);
        tutorial_popup_->Show();
        
        SetActiveAndVisible(tap_left_, false);
        SetActiveAndVisible(tap_area_, false);
        
        //        timeframe_animation_2_.Start(milliseconds(5200));
    }
    
    if(tutorial_popup_->WasClosed() && steps_[1] == 1 && steps_[2] == 0)
    {
        steps_[2] = 1;
        
        tutorial_popup_->SetTextIndex(TutorialPopup::WASTE);
        tutorial_popup_->Show();
    }
    else if(tutorial_popup_->WasClosed() && steps_[2] == 1 && steps_[3] == 0)
    {
        steps_[3] = 1;
        
        tutorial_popup_->SetTextIndex(TutorialPopup::APPLE);
        tutorial_popup_->Show();
    }
    else if(tutorial_popup_->WasClosed() && steps_[3] == 1 && steps_[4] == 0)
    {
        steps_[4] = 1;
        
        tutorial_popup_->SetTextIndex(TutorialPopup::HEART);
        tutorial_popup_->Show();
    }
    else if(tutorial_popup_->WasClosed() && steps_[4] == 1 && steps_[5] == 0)
    {
        steps_[5] = 1;
        
        tutorial_popup_->SetTextIndex(TutorialPopup::COIN);
        tutorial_popup_->Show();
    }
    else if(tutorial_popup_->WasClosed() && steps_[5] == 1)
    {
        Loader loader;
        
        loader.UnloadTutorial();
        loader.LoadMenu();
    }
}

void TutorialScene::OnStateLevelUp(float delta)
{
    
}

void TutorialScene::OnStatePaused(float delta)
{
    
}

void TutorialScene::OnStateIdle(float delta)
{
    //DO NOTHING!
}

void TutorialScene::OnStateGameOver(float delta)
{
}

void TutorialScene::OnStateExit(float delta)
{
}

void TutorialScene::FadeInBackground()
{
    fade_in_start_alpha_ = 0;
    fade_in_end_alpha_ = 150;
    fade_in_time_ = milliseconds(1000);
    bReadyToStart_ = false;
    
    fade_in_current_time_ = timer_.GetCurrentTimeInMilliseconds();
    fade_in_end_time_ = fade_in_current_time_ + fade_in_time_;
   
    SetActiveAndVisible(tap_area_, true);
    SetActiveAndVisible(tap_right_, true);
    tap_right_->setOpacity(0);
    tap_area_->setOpacity(0);
    
    
    FadeTo* fade_to2 = FadeTo::create(1.0, 255);
    tap_right_->runAction(fade_to2);
    
    tap_area_->setPosition(button_right_->GetPositionX(),button_right_->GetPositionY());
    FadeTo* fade_to3 = FadeTo::create(1.0,100);
    tap_area_->runAction(fade_to3);
    
    timeframe_animation_3_.Start(milliseconds(1000));
}

