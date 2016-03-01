//
//  MenuPopup.cpp
//  Hazelnut
//
//  Created by Dominik Reisner on 26.05.15.
//
//

#include "MenuPopup.h"
#include "DataHandler.h"

const std::string MenuPopup::STATE_MAIN = "state_main";
const std::string MenuPopup::STATE_ABOUT = "state_about";
const std::string MenuPopup::STATE_HELP = "state_help";

MenuPopup::MenuPopup()
{  
}

MenuPopup::~MenuPopup()
{ 
}

MenuPopup* MenuPopup::CreateMenuPopup(FrameworkScene *scene)
{
    MenuPopup* ret = new (std::nothrow) MenuPopup();
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

void MenuPopup::OnInit()
{
    node_menu_main_ = Node::create();
    node_menu_main_->setZOrder(getZOrder()+10);
    node_menu_main_->setCascadeOpacityEnabled(true);
    addChild(node_menu_main_);
    
    node_menu_about_ = Node::create();
    node_menu_about_->setZOrder(getZOrder()+10);
    node_menu_about_->setCascadeOpacityEnabled(true);
    addChild(node_menu_about_);
    
    node_menu_help_ = Node::create();
    node_menu_help_->setZOrder(getZOrder()+10);
    node_menu_help_->setCascadeOpacityEnabled(true);
    addChild(node_menu_help_);
    
    node_menu_frame_ = Node::create();
    node_menu_frame_->setZOrder(getZOrder()+5);
    node_menu_frame_->setCascadeOpacityEnabled(true);
    addChild(node_menu_frame_);
    
    
    CreateMainContent();
    CreateAboutContent();
    CreateHelpContent();
        
    sprite_background_ = FSprite::create(DataHandler::TEXTURE_GAME_MAP_1_POPUP);
    sprite_background_->setOpacity(200);
    sprite_background_->setZOrder(getZOrder()+1);
    
#pragma warn message("smaller devices with != WIDESCREEN wil also have 1920x1536 find correct resolution for each device")
    //BACKGROUND
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
    
    scene_->AddTickable(timeframe_active_visible_);
    scene_->AddTickable(state_machine_);
    
    state_machine_.Register(STATE_MAIN, this, &MenuPopup::OnStateMain);
    state_machine_.Register(STATE_ABOUT, this, &MenuPopup::OnStateAbout);
    state_machine_.Register(STATE_HELP, this, &MenuPopup::OnStateHelp);
}

void MenuPopup::Tick()
{
}

void MenuPopup::OnShow()
{
    scene_->SetActiveAndVisible(node_menu_main_, true);

    scene_->SetActiveAndVisible(node_menu_about_,false);
    scene_->SetActiveAndVisible(node_menu_help_, false);
    
    scene_->SetActiveAndVisible(sprite_sound_off_, !DataHandler::bIsGameSoundActive_);
    scene_->SetActiveAndVisible(sprite_sound_on_, DataHandler::bIsGameSoundActive_);
    
    
    node_menu_main_->setOpacity(255);
    node_menu_about_->setOpacity(0);
    node_menu_help_->setOpacity(0);
    
    state_machine_.SetState(STATE_MAIN);
}

void MenuPopup::OnClosed()
{
    node_menu_main_->stopAllActions();
    node_menu_about_->stopAllActions();
    node_menu_help_->stopAllActions();
    
    state_machine_.SetState("");
#pragma warn message("state machine still runs")
    //    state_machine_.SetState(STATE_MAIN);
}

void MenuPopup::OnStateMain(float delta)
{
    if(button_sound_->WasPressed())
    {
        if(DataHandler::bIsGameSoundActive_)
        {
            DataHandler::bIsGameSoundActive_ = false;
            
            DataHandler::game_audio->setBackgroundMusicVolume(0.0);
            DataHandler::game_audio->setEffectsVolume(0.0);
            DataHandler::game_audio->pauseBackgroundMusic();
            DataHandler::game_audio->pauseAllEffects();
        }
        else
        {
            DataHandler::bIsGameSoundActive_ = true;
            
            DataHandler::game_audio->setBackgroundMusicVolume(10.0);
            DataHandler::game_audio->setEffectsVolume(10.0);
            DataHandler::game_audio->resumeAllEffects();
            DataHandler::game_audio->resumeBackgroundMusic();
        }
        
        scene_->SetActiveAndVisible(sprite_sound_off_, !DataHandler::bIsGameSoundActive_);
        scene_->SetActiveAndVisible(sprite_sound_on_, DataHandler::bIsGameSoundActive_);
    }
    else if(button_about_->WasPressed())
    {
        FadeOut* fade = FadeOut::create(1.0f);
        node_menu_main_->runAction(fade);
        timeframe_active_visible_.Start(milliseconds(1000));
        
        FadeIn* fade_in = FadeIn::create(2.0f);
        node_menu_about_->runAction(fade_in);
        
        scene_->SetActiveAndVisible(node_menu_about_, true);
        
        state_machine_.SetState(STATE_ABOUT);
    }
    else if(button_help_->WasPressed())
    {
        FadeOut* fade = FadeOut::create(1.0f);
        node_menu_main_->runAction(fade);
        timeframe_active_visible_.Start(milliseconds(1000));
        
        FadeIn* fade_in = FadeIn::create(2.0f);
        node_menu_help_->runAction(fade_in);
        
        scene_->SetActiveAndVisible(node_menu_help_, true);
        
        
        state_machine_.SetState(STATE_HELP);
    }
}

void MenuPopup::OnStateAbout(float delta)
{
    if(timeframe_active_visible_.WasRunning())
    {
        scene_->SetActiveAndVisible(node_menu_main_, false);
    }
}

void MenuPopup::OnStateHelp(float delta)
{
    if(timeframe_active_visible_.WasRunning())
    {
        scene_->SetActiveAndVisible(node_menu_main_, false);
    }
}


void MenuPopup::CreateMainContent()
{
    button_sound_ = FrameworkButton::create(scene_, 700, 100);
    button_sound_->SetPositionY(200);
    button_sound_->SetZOrder(node_menu_main_->getZOrder()+2);
    
    sprite_sound_on_ = FSprite::create(DataHandler::TEXTURE_MENU_POPUP_BUTTON_SOUND_ON);
    sprite_sound_off_ = FSprite::create(DataHandler::TEXTURE_MENU_POPUP_BUTTON_SOUND_OFF);
    
    button_sound_->addChild(sprite_sound_on_);
    button_sound_->addChild(sprite_sound_off_);
    
    node_menu_main_->addChild(button_sound_);
    
    button_about_ = FrameworkButton::create(scene_, 700, 100,Sprite::create(DataHandler::TEXTURE_MENU_POPUP_BUTTON_ABOUT));
    button_about_->SetZOrder(node_menu_main_->getZOrder()+2);
    button_about_->SetPositionY(50);
    node_menu_main_->addChild(button_about_);
    
    button_help_ = FrameworkButton::create(scene_, 700, 100,Sprite::create(DataHandler::TEXTURE_MENU_POPUP_BUTTON_HELP));
    button_help_->SetZOrder(node_menu_main_->getZOrder()+2);
    button_help_->SetPositionY(-100);
    node_menu_main_->addChild(button_help_);
}

void MenuPopup::CreateAboutContent()
{
    static const std::string text_about = "Hazelnut Developers:\n\nDominik Reisner\nMatthias Reisner";
    Label* label_about = Label::create(text_about, DataHandler::FONT_QUARMIC_SANS, 80);
    label_about->setAnchorPoint(Vec2(0,0.5f));
    label_about->setPositionX(-500);
    node_menu_about_->addChild(label_about);
}

void MenuPopup::CreateHelpContent()
{
    static const std::string text_help = "Contact us!\n\nPlease tell us\nif you find a bug,\nor want to give feedback!\nEmail: hazelnutgame@gmail.com";
    Label* label_help = Label::create(text_help, DataHandler::FONT_QUARMIC_SANS, 70);
    label_help->setAnchorPoint(Vec2(0,0.5f));
    label_help->setPositionX(-500);
    node_menu_help_->addChild(label_help);
}
