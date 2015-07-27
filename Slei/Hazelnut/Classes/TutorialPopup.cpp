//
//  TutorialPopup.cpp
//  Hazelnut
//
//  Created by Dominik Reisner on 20.05.15.
//
//

#include "TutorialPopup.h"
#include "FUtil.h"
#include "DataHandler.h"

const std::string TutorialPopup::text_hazelnut_ = "The Hazelnut!\n\nHazelnuts will bring you 1 point.\nDon't forget, to always try to catch them.\nMissing a hazelnut makes the evil squirrel angry,\nwhich causes you to loose one life!";

const std::string TutorialPopup::text_waste_ = "The Waste!\n\nWaste is evil! Catching a waste item\nwill cause loosing one live. Play safe and avoid them!";

const std::string TutorialPopup::text_apple_ = "The Apple!\n\nApples will bring you 5 points \nDon't forget, you won't loose a life missing them, \nbut you will give away valuable points.";

const std::string TutorialPopup::text_heart_ = "The Heart!\n\nHearts will bring you an additional life.\nYou will start with 3 lives and \nyou can collect a maximum of 7 lifes.";

const std::string TutorialPopup::text_coin_ = "The Coin!\n\nCoins are rare! Coins will bring you 15 points.\nDon't forget, you won't loose a life missing them, \nbut you will give away valuable points.";

TutorialPopup::TutorialPopup()
{
    
}

TutorialPopup::~TutorialPopup()
{
    
}

TutorialPopup* TutorialPopup::CreatePopup(FrameworkScene* scene)
{
    TutorialPopup* ret = new (std::nothrow) TutorialPopup();
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


void TutorialPopup::OnInit()
{
    sprite_background_ = Sprite::create(DataHandler::TEXTURE_GAME_MAP_1_POPUP);
    sprite_background_->setOpacity(80);
    sprite_background_->setZOrder(1);
    addChild(sprite_background_);
    
    //    Sprite* hazelnut = Sprite::create(DataHandler::TEXTURE_COLLECT_GAME_HAZELNUT);
    //    hazelnut->setAnchorPoint(Vec2(0.5,0.5));
    //    hazelnut->setPosition(Vec2(-100,250));
    //    hazelnut->setZOrder(2);
    //    addChild(hazelnut);
    
    sprite_hazelnut_= FSprite::create(DataHandler::TEXTURE_COLLECT_GAME_HAZELNUT,FUtil::GenerateETC1AlphaString(DataHandler::TEXTURE_COLLECT_GAME_HAZELNUT));
    SpriteTextSettings(sprite_hazelnut_);
    
    sprite_waste_ = FSprite::create(DataHandler::TEXTURE_COLLECT_GAME_WASTE,FUtil::GenerateETC1AlphaString(DataHandler::TEXTURE_COLLECT_GAME_WASTE));
    SpriteTextSettings(sprite_waste_);
    
    sprite_apple_ = FSprite::create(DataHandler::TEXTURE_COLLECT_GAME_APPLE, FUtil::GenerateETC1AlphaString(DataHandler::TEXTURE_COLLECT_GAME_APPLE));
    SpriteTextSettings(sprite_apple_);
    
    sprite_heart_ = FSprite::create(DataHandler::TEXTURE_COLLECT_GAME_HEART, FUtil::GenerateETC1AlphaString(DataHandler::TEXTURE_COLLECT_GAME_HEART));
    SpriteTextSettings(sprite_heart_);
    
    sprite_coin_ = FSprite::create(DataHandler::TEXTURE_COLLECT_GAME_COIN, FUtil::GenerateETC1AlphaString(DataHandler::TEXTURE_COLLECT_GAME_COIN));
    SpriteTextSettings(sprite_coin_);
    
    
    label_text_ = Label::createWithTTF("",DataHandler::FONT_QUARMIC_SANS, 50);
    label_text_->setAnchorPoint(Vec2(0.0,0.0));
    label_text_->setPosition(-750,0);
    label_text_->setColor(Color3B::WHITE);
    label_text_->setZOrder(2);
    addChild(label_text_);
    
    label_text_->setAlignment(TextHAlignment::LEFT);
    
    SetSize(Vec2(1600,700));
}

void TutorialPopup::Tick()
{
}

void TutorialPopup::OnShow()
{
    scene_->SetActiveAndVisible(sprite_apple_, false);
    scene_->SetActiveAndVisible(sprite_hazelnut_, false);
    scene_->SetActiveAndVisible(sprite_coin_, false);
    scene_->SetActiveAndVisible(sprite_heart_, false);
    scene_->SetActiveAndVisible(sprite_waste_, false);
    
    scene_->SetActiveAndVisible(sprite_text_description, true);
}

void TutorialPopup::OnClosed()
{
    scene_->SetActiveAndVisible(sprite_text_description, false);
}

void TutorialPopup::SetTextIndex(EItemText item_text)
{
    switch (item_text)
    {
        case HAZELNUT:  label_text_->setString(text_hazelnut_);
            label_text_->setPosition(-750, -130);
            sprite_text_description = sprite_hazelnut_;
            sprite_text_description->setPosition(-300,265);
            break;
            
        case WASTE:     label_text_->setString(text_waste_);
            label_text_->setPosition(-750, -10);
            sprite_text_description = sprite_waste_;
            sprite_text_description->setPosition(-300,240);
            
            break;
            
        case APPLE:     label_text_->setString(text_apple_);
            label_text_->setPosition(-750, -80);
            sprite_text_description = sprite_apple_;
            sprite_text_description->setPosition(-330,240);
            
            break;
            
        case HEART:     label_text_->setString(text_heart_);
            label_text_->setPosition(-750, -70);
            sprite_text_description = sprite_heart_;
            sprite_text_description->setPosition(-320,260);
            
            break;
            
        case COIN:      label_text_->setString(text_coin_);
            label_text_->setPosition(-750, -80);
            sprite_text_description = sprite_coin_;
            sprite_text_description->setPosition(-300,250);
            
            break;
    }
}

void TutorialPopup::SpriteTextSettings(FSprite *sprite)
{
    sprite->WithAnimation(true, FSprite::SCALE);
    sprite->setAnchorPoint(Vec2(0.5,0.5));
    sprite->setZOrder(2);
    scene_->SetActiveAndVisible(sprite, false);
    addChild(sprite);
}