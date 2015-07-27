//
//  FPopup.cpp
//  Hazelnut
//
//  Created by Dominik Reisner on 19.05.15.
//
//

#include "FPopup.h"
#include "FrameworkButton.h"

FrameworkScene* FPopup::scene_ = nullptr;

#pragma warn message("provide close function, e.g. this->Close() to close popup itself without background touch")

FPopup::FPopup()
: bIsActive_(false)
, bWasClosed_(false)
, bReadyToShow_(false)
, bIsPaused_(false)
, bHasEntered_(false)
{
    this->scheduleUpdate();
}

FPopup::~FPopup()
{
}

bool FPopup::init()
{
    if(!Node::init())
    {
        return false;
    }
    scene_->SetActiveAndVisible(this, false);
    
    //Enable opacity animation for childs
    setCascadeOpacityEnabled(true);
    
    setZOrder(1000);
    
    //Default Settings
    setOpacity(0);
    setPosition(DataHandler::GAME_RESOLUTION_CENTER);
    
    //Default background button for all popups
    
    int height = 0 , posY = 0;
    
    if(DataHandler::app_layout_ != EAppLayout::LAYOUT_WIDESCREEN)
    {
        height = 1536;
        posY = 150;
    }
    else
    {
        height = 1080;
    }
    
    button_background_ = FrameworkButton::create(scene_, 1920, height);//scene_->CreateButton(1920, 1080);
    button_background_->SetPositionX(0);
    button_background_->SetPositionY(posY);
    button_background_->SetZOrder(getZOrder());
    button_background_->SetActive(false);
    
    addChild(button_background_);
    
    scene_->AddTickable(timeframe_fade_in_);
    scene_->AddTickable(timeframe_fade_out_);
    
    OnInit();
    
    
    return true;
}

FPopup* FPopup::CreatePopup(FrameworkScene* scene)
{
    FPopup* ret = new (std::nothrow) FPopup();
    scene_ = scene;
    if (ret && ret->init())
    {
        ret->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(ret);
    }
    
    scene_->addChild(ret);
    
    return ret;
}

void FPopup::update(float delta)
{
    if(bWasClosed_)
    {
        scene_->SetActiveAndVisible(this, false);
        bWasClosed_ = false;
    }
    
    if(!timeframe_fade_in_.IsOrWasrunning() && !timeframe_fade_out_.IsOrWasrunning() && bIsActive_)
    {
        Tick();
    }
    
    if(button_background_->WasPressed() && !timeframe_fade_in_.IsOrWasrunning() && !timeframe_fade_out_.IsOrWasrunning() && bIsActive_)
    {
        FadeTo* fade = FadeTo::create(0.5,0);
        runAction(fade);
     
        timeframe_fade_out_.Start(milliseconds(700));
    }
    
    if(timeframe_fade_in_.WasRunning())
    {
        bIsActive_ = true;
    }
    else if(timeframe_fade_out_.WasRunning())
    {
        OnClosed();
        button_background_->SetActive(false);
        bIsActive_ = false;
        bWasClosed_ = true;
    }
    
    if(bReadyToShow_)
    {
        scene_->SetActiveAndVisible(this, true); // here again because bWasClosed sets it to false
        
        if(!timeframe_fade_in_.IsOrWasrunning() && !timeframe_fade_out_.IsOrWasrunning())
        {
            bReadyToShow_ = false;
            
            stopAllActions();
            
            OnShow();
            button_background_->SetActive(true);
            
            FadeTo* fade = FadeTo::create(0.5, 255);
            runAction(fade);
			    
            timeframe_fade_in_.Start(milliseconds(700));
        }
        
    }
}

void FPopup::Show()
{
    scene_->SetActiveAndVisible(this, true);
    bReadyToShow_ = true;
}
