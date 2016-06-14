//
// AchievementListScene.cpp
// Hazelnut
//
// Created by Matthias Reisner on 16.01.2015
//
//

#include "AchievementListScene.h"
#include <CCLabel.h>
#include "DataHandler.h"
#include "FileOperation.h"
#include "GameUtil.h"
#include "AdmobHelper.h"
//include "cocos-ext.h"
#include "CocosGUI.h"

#include "AchievementManager.h"

USING_NS_CC;

//USING_NS_CC_EXT;
using namespace ui;

const int AchievementListScene::SCROLLVIEW_HEIGHT = 584;
const int AchievementListScene::SCROLLVIEW_WIDTH = 700;
const int AchievementListScene::SCROLLVIEW_INNER_HEIGHT = 2860;
const int AchievementListScene::SCROLLVIEW_INNER_WIDTH = 700;

void AchievementListScene::onExit()
{
	AdmobHelper::hideAd();
	
    Layer::onExit();
}

Scene* AchievementListScene::createMenuScene(std::string newHighscoreEntry)
{
    auto scene = Scene::create();
    auto layer = AchievementListScene::create();
    
    scene->addChild(layer);
    
    return scene;
}

bool AchievementListScene::init()
{
    if (!FrameworkScene::init())
    {
        return false;
    }
    
    //Background
    background_ = FSprite::create(DataHandler::TEXTURE_GAME_MAP_1
                                ,Vec2(DataHandler::GAME_RESOLUTION_WIDTH / 2,
                                 DataHandler::GAME_RESOLUTION_HEIGHT / 2));
    
    addChild(background_);
    
    background_->setZOrder(0);
    
    if(DataHandler::app_layout_ == EAppLayout::LAYOUT_IPAD)
    {
        Sprite* background_extension = FSprite::create(   DataHandler::TEXTURE_GAME_MAP_1_EXTENSION
                                                         ,Vec2(DataHandler::GAME_RESOLUTION_WIDTH/2,DataHandler::GAME_RESOLUTION_HEIGHT+180));
        background_extension->setScale(32, 6);
        
        addChild(background_extension);
    }
    else if(DataHandler::app_layout_ == EAppLayout::LAYOUT_DEFAULT)
    {
        FSprite* background_extension = FSprite::create( DataHandler::TEXTURE_GAME_MAP_1_EXTENSION
                                                         ,Vec2(DataHandler::GAME_RESOLUTION_WIDTH/2,DataHandler::GAME_RESOLUTION_HEIGHT+100));
        background_extension->setScale(32, 3.35);
        
        addChild(background_extension);
    }

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//Achievment head
	auto achievment_head = FSprite::create(DataHandler::TEXTURE_ACHIEVEMENT_TABLE_BG, Vec2(Vec2(DataHandler::GAME_RESOLUTION_WIDTH / 2 + origin.x, DataHandler::GAME_RESOLUTION_HEIGHT / 2 + origin.y + 380)));
	
	addChild(achievment_head);

    // Create the menu buttons
	ui::ScrollView* scrollView = ui::ScrollView::create();
	scrollView->setDirection(ui::ScrollView::Direction::VERTICAL);
	scrollView->setContentSize(Size(AchievementListScene::SCROLLVIEW_WIDTH, AchievementListScene::SCROLLVIEW_HEIGHT));
	scrollView->setInnerContainerSize(Size(0, 500));
	scrollView->setInnerContainerSize(Size(AchievementListScene::SCROLLVIEW_INNER_WIDTH, AchievementListScene::SCROLLVIEW_INNER_HEIGHT));
	scrollView->setBounceEnabled(true);
	scrollView->setBackGroundImage(DataHandler::TEXTURE_ACHIEVEMENT_TABLE_BG_SCROLLER);
	scrollView->setAnchorPoint(Vec2(0.5, 0.5));
	scrollView->setPosition(Vec2(DataHandler::GAME_RESOLUTION_WIDTH / 2 + origin.x, DataHandler::GAME_RESOLUTION_HEIGHT / 2 + origin.y));

	int32_t counter = 0;
    
//    for(auto i = 0lu; i < DataHandler::ACHIEVEMENT_STATIC_MAP.size(); i++)
//    {
//        auto& item = AchievementManager::GetInstance()->GetAchievementContainer();
//    
//        FSprite* achievementButton = FSprite::create(DataHandler::TEXTURE_ACHIEVEMENT_EMPTY);
//        achievementButton->setAnchorPoint(Vec2(0, 0));
//        achievementButton->setPosition(Vec2(0, (i * 120) + 30));
//        scrollView->addChild(achievementButton);
//        
//        item
//        auto ach_name = Label::createWithTTF(item.second.str, DataHandler::FONT_QUARMIC_SANS, 20);
//        ach_name->setPosition(Vec2(250.f,50.f));
//        ach_name->setAlignment(TextHAlignment::LEFT);
//        achievementButton->addChild(ach_name);
//        
//        auto ach_status = Label::createWithTTF(item.second.unlocked ? "Unlocked" : "Locked", DataHandler::FONT_QUARMIC_SANS, 30);
//        ach_status->setPosition(Vec2(620.f,50.f));
//        achievementButton->addChild(ach_status);
//    }
    
    /* do stuff */
    
//    for (auto item = AchievementManager::GetInstance()->GetAchievementContainer().rbegin(); item != AchievementManager::GetInstance()->GetAchievementContainer().rend(); ++item)
    
    counter = AchievementManager::GetInstance()->GetAchievementContainer().size()-1;


	for (auto& item : AchievementManager::GetInstance()->GetAchievementContainer())
	{
		FSprite* achievementButton = FSprite::create(DataHandler::TEXTURE_ACHIEVEMENT_EMPTY);
		achievementButton->setAnchorPoint(Vec2(0, 0));
		achievementButton->setPosition(Vec2(0, (counter * 120) + 30));
		scrollView->addChild(achievementButton);

		auto ach_name = Label::createWithTTF(DataHandler::ACHIEVEMENT_STATIC_MAP.at(item.first).text, DataHandler::FONT_QUARMIC_SANS, 26);
		ach_name->setPosition(Vec2(320.f,50.f));
        
        ach_name->setWidth(420.f);
		ach_name->setAlignment(TextHAlignment::LEFT);
		achievementButton->addChild(ach_name);

		auto ach_status = Label::createWithTTF(item.second.unlocked ? "Unlocked" : "Locked", DataHandler::FONT_QUARMIC_SANS, 30);
		ach_status->setPosition(Vec2(620.f,50.f));
		achievementButton->addChild(ach_status);
        
        if(item.second.str_curr != "")
        {
            auto ach_progress = Label::createWithTTF(std::to_string(item.second.current_points) + " of " + std::to_string(DataHandler::ACHIEVEMENT_STATIC_MAP.at(item.first).target_points), DataHandler::FONT_QUARMIC_SANS, 30);
            ach_progress->setPosition(Vec2(320.f,0.f));
            achievementButton->addChild(ach_progress);
        }


		counter--;
	}

	//for (int i = 0; i < AchievementManager::GetInstance()->GetAchievementContainer().size(); i++)
	//{
	//	//ui::Button* btn = ui::Button::create(DataHandler::TEXTURE_MENU_POPUP_BUTTON_SOUND_OFF, DataHandler::TEXTURE_MENU_POPUP_BUTTON_SOUND_ON);
	//	


	//		label_archievment_ = Label::createWithTTF(text, DataHandler::FONT_QUARMIC_SANS, 50);
	//	label_archievment_->setColor(Color3B::RED);
	//	label_archievment_->setZOrder(1);
	//	//        label_archievment_->setCascadeColorEnabled(true);
	//	addChild(label_archievment_);

	//	
	//}

	addChild(scrollView);
    
    FSprite* buttonSpriteBack = FSprite::create(DataHandler::TEXTURE_HIGHSCORE_BUTTON_BACK);
//    buttonExit = CreateButton(700, 120, buttonSpriteBack);
    buttonExit = FrameworkButton::create(this, 700, 100, buttonSpriteBack),
    buttonExit->SetPositionX(DataHandler::GAME_RESOLUTION_WIDTH / 2);
    buttonExit->SetPositionY(DataHandler::GAME_RESOLUTION_HEIGHT / 2 - 425);
    buttonExit->SetZOrder(2);
    addChild(buttonExit);
	
	AdmobHelper::showAd();
    
    return true;
}

void AchievementListScene::Tick(float delta)
{
    if (buttonExit->WasPressed())
    {
        DataHandler::game_audio->playEffect(DataHandler::SOUND_BUTTON_1);
        
        onEnterTransitionDidFinish();
        
        loader.UnloadAchievement();
        loader.LoadMenu();
    }
}
