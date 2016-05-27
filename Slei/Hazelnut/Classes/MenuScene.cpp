//
//  MenuScene.cpp
//  Hazelnut
//
//  Created by Dominik Reisner on 28.11.14.
//
//

#include "MenuScene.h"
#include <CCLabel.h>
#include "DataHandler.h"
#include "MenuPopup.h"
#include "FPopup.h"
#include "AdmobHelper.h"
#include "AchievementNotification.h"
#include "AchievementManager.h"

const std::string MenuScene::BACKGROUND = "background";

MenuScene::MenuScene()
{
}

MenuScene::~MenuScene()
{
}

MenuScene::MenuScene(MenuScene&& ms)
	: loader(std::move(ms.loader))
	, buttonStart(std::move(buttonStart))
	, buttonHighscore(std::move(ms.buttonHighscore))
	, buttonExit(std::move(ms.buttonExit))
	, button_tutorial_(std::move(ms.button_tutorial_))
	, button_menu_popup_(std::move(ms.button_menu_popup_))
	, popup_menu_(std::move(ms.popup_menu_))
	, background_(std::move(ms.background_))
	, cloud_1_(std::move(ms.cloud_1_))
	, cloud_2_(std::move(ms.cloud_2_))
	, cloud_3_(std::move(ms.cloud_3_))
	, sprite_anim_bird(std::move(ms.sprite_anim_bird))
	, sprite_anim_bird1(std::move(ms.sprite_anim_bird1))
{
	CCLOG("MOVE CONSTR");
}

MenuScene& MenuScene::operator=(MenuScene&& ms)
{
	loader = std::move(ms.loader);
	buttonStart = (std::move(buttonStart));
	buttonHighscore = (std::move(ms.buttonHighscore));
	buttonExit = (std::move(ms.buttonExit));
	button_tutorial_ = (std::move(ms.button_tutorial_));
	button_menu_popup_ = (std::move(ms.button_menu_popup_));
	popup_menu_ = (std::move(ms.popup_menu_));
	background_ = (std::move(ms.background_));
	cloud_1_ = (std::move(ms.cloud_1_));
	cloud_2_ = (std::move(ms.cloud_2_));
	cloud_3_ = (std::move(ms.cloud_3_));
	sprite_anim_bird = (std::move(ms.sprite_anim_bird));
	sprite_anim_bird1 = (std::move(ms.sprite_anim_bird1));
	CCLOG("MOVE ASSIGN");

	return *this;
}

void MenuScene::onExit()
{
    Layer::onExit();
}

Scene* MenuScene::createMenuScene()
{
    auto scene = Scene::create();
    auto layer = MenuScene::create();

    scene->addChild(layer);

    return scene;
}

bool MenuScene::init()
{
    if(!FrameworkScene::init())
    {
        return false;
    }
    
    background_ = FSprite::create(  DataHandler::TEXTURE_GAME_MAP_1
                                  ,Vec2(DataHandler::GAME_RESOLUTION_WIDTH/2 ,DataHandler::GAME_RESOLUTION_HEIGHT/2));
    background_->setZOrder(0);
    addChild(background_);
    
    if(DataHandler::app_layout_ == EAppLayout::LAYOUT_IPAD)
    {
        
        FSprite* background_extension = FSprite::create(DataHandler::TEXTURE_GAME_MAP_1_EXTENSION
                                                        ,Vec2(DataHandler::GAME_RESOLUTION_WIDTH/2,DataHandler::GAME_RESOLUTION_HEIGHT+180));
        
        background_extension->setScale(32, 6);
        
        addChild(background_extension);
    }
    else if(DataHandler::app_layout_ == EAppLayout::LAYOUT_DEFAULT)
    {
        FSprite* background_extension = FSprite::create(
                                                        DataHandler::TEXTURE_GAME_MAP_1_EXTENSION
                                                        ,Vec2(DataHandler::GAME_RESOLUTION_WIDTH/2,DataHandler::GAME_RESOLUTION_HEIGHT+100));
        background_extension->setScale(32, 3.35);
        
        addChild(background_extension);
    }
    
    //CLOUDS
    cloud_1_ = FSprite::create(DataHandler::TEXTURE_GAME_CLOUD_1);
    cloud_1_->setPosition(Vec2(DataHandler::GAME_RESOLUTION_CENTER_WIDTH-500,DataHandler::GAME_RESOLUTION_CENTER_HEIGHT + 100));
    MoveTo* move1 = MoveTo::create(12.0, Vec2(DataHandler::GAME_RESOLUTION_CENTER_WIDTH - 1150,DataHandler::GAME_RESOLUTION_CENTER_HEIGHT + 100));
    cloud_1_->runAction(move1);
    addChild(cloud_1_);
    
    cloud_2_ = FSprite::create(DataHandler::TEXTURE_GAME_CLOUD_2);
    cloud_2_->setPosition(Vec2(DataHandler::GAME_RESOLUTION_CENTER_WIDTH,DataHandler::GAME_RESOLUTION_CENTER_HEIGHT + 500));
    MoveTo* move2 = MoveTo::create(35.0, Vec2(DataHandler::GAME_RESOLUTION_CENTER_WIDTH - 1150,DataHandler::GAME_RESOLUTION_CENTER_HEIGHT + 500));
    cloud_2_->runAction(move2);
    addChild(cloud_2_);
    
    cloud_3_ = FSprite::create(DataHandler::TEXTURE_GAME_CLOUD_3);
    cloud_3_->setPosition(Vec2(DataHandler::GAME_RESOLUTION_CENTER_WIDTH + 500,DataHandler::GAME_RESOLUTION_CENTER_HEIGHT + 200));
    MoveTo* move3 = MoveTo::create(50.0, Vec2(DataHandler::GAME_RESOLUTION_CENTER_WIDTH - 1150,DataHandler::GAME_RESOLUTION_CENTER_HEIGHT + 200));
    cloud_3_->runAction(move3);
    addChild(cloud_3_);

	//BIRDS
	Vector<SpriteFrame*> anim_bird_frames = Vector<SpriteFrame*>(2);
	anim_bird_frames.pushBack(SpriteFrame::create(DataHandler::TEXTURE_GAME_BIRD_FRAME_1, Rect(0, 0, 106, 120)));
	anim_bird_frames.pushBack(SpriteFrame::create(DataHandler::TEXTURE_GAME_BIRD_FRAME_2, Rect(0, 0, 106, 120)));

	auto animation = Animation::createWithSpriteFrames(anim_bird_frames, 0.2f);
	auto animate = Animate::create(animation);

	sprite_anim_bird = FSprite::create();
	sprite_anim_bird->setTextureRect(Rect(0, 0, 106, 120));
	sprite_anim_bird->setScale(0.6);
	sprite_anim_bird->setRotation(15);
	sprite_anim_bird->setPosition(Vec2(DataHandler::GAME_RESOLUTION_CENTER_WIDTH - 500, DataHandler::GAME_RESOLUTION_CENTER_HEIGHT + 100));
	sprite_anim_bird->runAction(RepeatForever::create(animate));
	MoveTo* bMove1 = MoveTo::create(12.0, Vec2(DataHandler::GAME_RESOLUTION_CENTER_WIDTH + 1150, DataHandler::GAME_RESOLUTION_CENTER_HEIGHT + 100));
	sprite_anim_bird->runAction(bMove1);
	addChild(sprite_anim_bird);

	auto animation1 = Animation::createWithSpriteFrames(anim_bird_frames, 0.2f);
	auto animate1 = Animate::create(animation1);
	sprite_anim_bird1 = FSprite::create();
	sprite_anim_bird1->setTextureRect(Rect(0, 0, 106, 120));
	sprite_anim_bird1->setScale(0.6);
	sprite_anim_bird1->setRotation(-15);
	sprite_anim_bird1->setFlippedX(true);
	sprite_anim_bird1->setPosition(Vec2(DataHandler::GAME_RESOLUTION_CENTER_WIDTH - 500, DataHandler::GAME_RESOLUTION_CENTER_HEIGHT + 200));
	sprite_anim_bird1->runAction(RepeatForever::create(animate1));
	MoveTo* bMove2 = MoveTo::create(12.0, Vec2(DataHandler::GAME_RESOLUTION_CENTER_WIDTH - 1150, DataHandler::GAME_RESOLUTION_CENTER_HEIGHT + 200));
	sprite_anim_bird1->runAction(bMove2);
	addChild(sprite_anim_bird1);
 
    
    FSprite* labelHeader = FSprite::create(DataHandler::TEXTURE_MENU_LABEL_HEADER);
    labelHeader->setPositionX(DataHandler::GAME_RESOLUTION_WIDTH / 2);
    labelHeader->setPositionY(DataHandler::GAME_RESOLUTION_HEIGHT / 2 + 320);
    labelHeader->setZOrder(0);
    addChild(labelHeader);
    
    FSprite* buttonSpriteStart = FSprite::create(DataHandler::TEXTURE_MENU_BUTTON_START);
    buttonStart = FrameworkButton::create(this, 700, 120, buttonSpriteStart);
    buttonStart->SetPositionX(DataHandler::GAME_RESOLUTION_WIDTH/2);
    buttonStart->SetPositionY(DataHandler::GAME_RESOLUTION_HEIGHT/2 + 20);
    buttonStart->SetZOrder(0);
    addChild(buttonStart);
    
    FSprite* buttonSpriteHighscore = FSprite::create(DataHandler::TEXTURE_MENU_BUTTON_HIGHSCORE);
    buttonHighscore = FrameworkButton::create(this, 700, 120, buttonSpriteHighscore);
    buttonHighscore->SetPositionX(DataHandler::GAME_RESOLUTION_WIDTH/2);
    buttonHighscore->SetPositionY(DataHandler::GAME_RESOLUTION_HEIGHT/2 - 120);
    buttonHighscore->SetZOrder(0);
    addChild(buttonHighscore);

	FSprite* buttonSpriteAchievement = FSprite::create(DataHandler::TEXTURE_MENU_BUTTON_ACHIEVEMENT);
	buttonAchievement = FrameworkButton::create(this, 700, 120, buttonSpriteAchievement);
	buttonAchievement->SetPositionX(DataHandler::GAME_RESOLUTION_WIDTH / 2);
	buttonAchievement->SetPositionY(DataHandler::GAME_RESOLUTION_HEIGHT / 2 - 260);
	buttonAchievement->SetZOrder(0);
	addChild(buttonAchievement);
    
    FSprite* button_sprite_tutorial = FSprite::create(DataHandler::TEXTURE_MENU_BUTTON_TUTORIAL);
    button_tutorial_ = FrameworkButton::create(this, 700, 120, button_sprite_tutorial);
    button_tutorial_->SetPositionX(DataHandler::GAME_RESOLUTION_WIDTH/2);
    button_tutorial_->SetPositionY(DataHandler::GAME_RESOLUTION_HEIGHT/2 - 400);
    button_tutorial_->SetZOrder(0);
    addChild(button_tutorial_);
    
    FSprite* buttonSpriteExit = FSprite::create(DataHandler::TEXTURE_MENU_BUTTON_EXIT);
    buttonExit = FrameworkButton::create(this, 700, 120,buttonSpriteExit);
    buttonExit->SetPositionX(DataHandler::GAME_RESOLUTION_WIDTH/2);
    buttonExit->SetPositionY(DataHandler::GAME_RESOLUTION_HEIGHT/2 - 540);
    buttonExit->SetZOrder(0);
    addChild(buttonExit);
    
    FSprite* button_sprite_menu_popup = FSprite::create(DataHandler::TEXTURE_COLLECT_GAME_BUTTON_MENU
                                                        , FUtil::GenerateETC1AlphaString(DataHandler::TEXTURE_COLLECT_GAME_BUTTON_MENU));
    button_menu_popup_ = FrameworkButton::create(this, 100, 100, button_sprite_menu_popup);
    button_menu_popup_->SetPositionX(100);
    button_menu_popup_->SetPositionY(100);
    button_menu_popup_->SetZOrder(4);
    addChild(button_menu_popup_);
    
    
//    auto ach = AchievementNotification::create("Unlocked 199 MUTNATE");
//    addChild(ach);
////    starting left bottom
//    ach->setAnchorPoint(Vec2(0.5,0.5));
//    ach->setPosition(0 + ach->getContentSize().width/2.f,DataHandler::GAME_RESOLUTION_HEIGHT - ach->getContentSize().height/2.f);
//    ach->Show(this , &MenuScene::CloudMovement);
    
    popup_menu_ = MenuPopup::CreateMenuPopup(this);
    SetActiveAndVisible(popup_menu_, false);
    
    //BACKGROUND AUDIO LOOP
#pragma message WARN("NOT PRELOADED")
    if(!CocosDenshion::SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying())
    {
        CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(DataHandler::MUSIC_BIRDS_ENVIRONMENT,true);
    }
    
    AdmobHelper::hideAd();
    AdmobHelper::hideAdBottom();
    AdmobHelper::hideAdScreen();
    
    return true;
}

void MenuScene::Tick(float delta)
{
    if(buttonStart->WasPressed())
    {
        DataHandler::game_audio->playEffect(DataHandler::SOUND_BUTTON_1);
        
        onEnterTransitionDidFinish();
        
        loader.UnloadMenu();
        loader.LoadCollectGame();
    }
    else if(buttonExit->WasPressed())
    {
        DataHandler::game_audio->playEffect(DataHandler::SOUND_BUTTON_1);
        
        loader.UnloadGame();
        
        Director::getInstance()->end();
    }
    else if (buttonHighscore->WasPressed())
    {
        DataHandler::game_audio->playEffect(DataHandler::SOUND_BUTTON_1);
        
        onEnterTransitionDidFinish();
        
        loader.UnloadMenu();
        loader.LoadHighscore("");
    }
	else if (buttonAchievement->WasPressed())
	{
		DataHandler::game_audio->playEffect(DataHandler::SOUND_BUTTON_1);

		onEnterTransitionDidFinish();

		loader.UnloadMenu();
		loader.LoadAchievement("");
	}
    else if(button_tutorial_->WasPressed())
    {
        DataHandler::game_audio->playEffect(DataHandler::SOUND_BUTTON_1);
        
        onEnterTransitionDidFinish();
        loader.UnloadMenu();
        loader.LoadTutorial();
    }
    else if(button_menu_popup_->WasPressed())
    {
        popup_menu_->Show();
    }
    
    CloudMovement();
	BirdMovement();
}

void MenuScene::CloudMovement()
{
    if(cloud_1_->getPosition().x <= DataHandler::GAME_RESOLUTION_CENTER_WIDTH - 1150)
    {
        cloud_1_->setPositionX(DataHandler::GAME_RESOLUTION_CENTER_WIDTH + 1150);
        MoveTo* move = MoveTo::create(50.0,Vec2(DataHandler::GAME_RESOLUTION_CENTER_WIDTH - 1150,cloud_1_->getPosition().y));
        cloud_1_->runAction(move);
    }
    
    if(cloud_2_->getPosition().x <= DataHandler::GAME_RESOLUTION_CENTER_WIDTH - 1150)
    {
        cloud_2_->setPositionX(DataHandler::GAME_RESOLUTION_CENTER_WIDTH + 1150);
        MoveTo* move = MoveTo::create(50.0,Vec2(DataHandler::GAME_RESOLUTION_CENTER_WIDTH - 1150,cloud_2_->getPosition().y));
        cloud_2_->runAction(move);
    }
    
    if(cloud_3_->getPosition().x <= DataHandler::GAME_RESOLUTION_CENTER_WIDTH - 1150)
    {
        cloud_3_->setPositionX(DataHandler::GAME_RESOLUTION_CENTER_WIDTH + 1150);
        MoveTo* move = MoveTo::create(50.0,Vec2(DataHandler::GAME_RESOLUTION_CENTER_WIDTH - 1150,cloud_3_->getPosition().y));
        cloud_3_->runAction(move);
    }
}

void MenuScene::BirdMovement()
{
	if (sprite_anim_bird->getPosition().x >= DataHandler::GAME_RESOLUTION_CENTER_WIDTH + 1150)
	{
		sprite_anim_bird->setPositionX(DataHandler::GAME_RESOLUTION_CENTER_WIDTH - 1150);
		sprite_anim_bird->setPositionY(DataHandler::GAME_RESOLUTION_CENTER_HEIGHT - 300 + RandomHelper::random_int(0, 600));
		MoveTo* move = MoveTo::create(RandomHelper::random_int(15, 30), Vec2(DataHandler::GAME_RESOLUTION_CENTER_WIDTH + 1150, sprite_anim_bird->getPosition().y));
		sprite_anim_bird->runAction(move);
	}
	if (sprite_anim_bird1->getPosition().x <= DataHandler::GAME_RESOLUTION_CENTER_WIDTH - 1150)
	{
		sprite_anim_bird1->setPositionX(DataHandler::GAME_RESOLUTION_CENTER_WIDTH + 1150);
		sprite_anim_bird1->setPositionY(DataHandler::GAME_RESOLUTION_CENTER_HEIGHT - 300 + RandomHelper::random_int(0, 600));
		MoveTo* move = MoveTo::create(RandomHelper::random_int(15, 30), Vec2(DataHandler::GAME_RESOLUTION_CENTER_WIDTH - 1150, sprite_anim_bird1->getPosition().y));
		sprite_anim_bird1->runAction(move);
	}
}