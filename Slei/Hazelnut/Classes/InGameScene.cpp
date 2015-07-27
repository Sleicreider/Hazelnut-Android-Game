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
    if(!Layer::init())
    {
        return false;
    }
    
	DataHandler::game_audio->playBackgroundMusic(DataHandler::MUSIC_BIRDS_ENVIRONMENT,true);
    
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