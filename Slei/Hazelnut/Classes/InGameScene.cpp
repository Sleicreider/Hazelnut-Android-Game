//
//  InGameScene.cpp
//  Hazelnut
//
//  Created by Dominik Reisner on 12.11.14.
//
//

#include "InGameScene.h"
#include "MenuScene.h"
#include "DataHandler.h"

InGameScene::InGameScene()
:ingController(this)
{
}

InGameScene::~InGameScene()
{
}

void InGameScene::onExit()
{
    Layer::onExit();
}

void InGameScene::onEnter()
{
    Layer::onEnter();

    ingController.OnEnter();
}

Scene* InGameScene::createInGameScene()
{
    auto scene = Scene::create();
    auto layer = InGameScene::create();
    
    scene->addChild(layer);
    return scene;
}

bool InGameScene::init()
{
    if(!FrameworkScene::init())
    {
        return false;
    }
    
	subject_.AddObserver(&achievments_);
    
	DataHandler::game_audio->playBackgroundMusic(DataHandler::MUSIC_BIRDS_ENVIRONMENT,true);
    
    an_ = AchievementNotification::create("Test");
    addChild(an_);
    
    achievments_.OnNotify(EEvent::EVENT_GAME_STARTED);

    //AddTickable(timeframe_);
    //timeframe_.Start(milliseconds(3000));
    
    return true;
}

void InGameScene::Tick(float delta)
{
    //Delay ingcontroller because of scene transition
    //if(timeframe_.IsOrWasrunning())
    //{
    //    return;
    //}

    ingController.Tick(delta);
    
    if(achievments_.NewAchievement())
    {
//        if(achievments_.GetAchievementList()[0] == EAchievements::ARCHIEVEMENT_NO_WASTE_COLLECTED)
//        {
//            an_->SetText("NEW ACHIEVEMENT - NO WASTE COLLECTED");
//            an_->Show();
//        }
//        else if(achievments_.GetAchievementList()[0] == EAchievements::ARCHIEVEMENT_NO_VALUE_ITEM_MISSED)
//        {
//            an_->SetText("NEW ACHIEVEMENT - NO VAL MISSED");
//            an_->Show();
//        }
    }
}

void InGameScene::LoadMenu()
{
    this->onEnterTransitionDidFinish();
    
    loader.UnloadCollectGame();
    loader.LoadMenu();
}

void InGameScene::ReloadGame(){
    this->onEnterTransitionDidFinish();
    
    loader.LoadCollectGame();
}

void InGameScene::LoadHighscoreMenu(std::string newHighscoreEntry)
{
    this->onEnterTransitionDidFinish();
    
    loader.UnloadCollectGame();
    loader.LoadHighscore(newHighscoreEntry);
}