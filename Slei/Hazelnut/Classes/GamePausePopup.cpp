//
//  GamePausePopup.cpp
//  Hazelnut
//
//  Created by Dominik Reisner on 19.06.15.
//
//

#include "GamePausePopup.h"
#include "AdmobHelper.h"

GamePausePopup::GamePausePopup()
: bExit_(false)
{
}

GamePausePopup::~GamePausePopup()
{
    
}

GamePausePopup* GamePausePopup::create(FrameworkScene* scene)
{
    GamePausePopup* ret = new (std::nothrow) GamePausePopup();
    scene_ = scene;
    if (ret && ret->init())
    {
        ret->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(ret);
    }
    
#pragma warn message("add them in scnene not HERE!")
    scene_->addChild(ret);
    
    return ret;
}

void GamePausePopup::OnInit()
{
    FSprite* sprite_exit = FSprite::create(DataHandler::TEXTURE_COLLECT_GAME_POPUP_EXIT);
    button_exit_ = FrameworkButton::create(scene_, 800, 200, sprite_exit);
    button_exit_->SetZOrder(getZOrder()+2);
    addChild(button_exit_);
    
    sprite_background_ = FSprite::create(DataHandler::TEXTURE_GAME_MAP_1_POPUP);
    sprite_background_->setOpacity(200);
    sprite_background_->setZOrder(getZOrder()+1);
    
    Vec2 size;
    
    if(DataHandler::app_layout_ != EAppLayout::LAYOUT_WIDESCREEN)
    {
        size = Vec2(1920,1536);
        sprite_background_->setPositionY(150);
    }
    else
    {
        size = Vec2(1920,1080);
    }
    
    sprite_background_->setScale(size.x/sprite_background_->getContentSize().width,size.y/sprite_background_->getContentSize().height);
    addChild(sprite_background_);
    
    scene_->AddTickable(state_machine_);
}

void GamePausePopup::Tick()
{
    if(button_exit_->WasPressed())
    {
		AdmobHelper::hideAd();
		AdmobHelper::hideAdBottom();
	
        DataHandler::game_audio->playEffect(DataHandler::SOUND_BUTTON_1);
        bExit_ = true;
    }
}

void GamePausePopup::OnShow()
{
	AdmobHelper::showAd();
	AdmobHelper::showAdBottom();
	
    bExit_ = false;
}

void GamePausePopup::OnClosed()
{  
	CCLOG("onclosed");
	AdmobHelper::hideAd();
	AdmobHelper::hideAdBottom();
}

bool GamePausePopup::GetExit() const
{
    return bExit_;
}
