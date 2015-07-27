//
//  Loader.cpp
//  Hazelnut
//
//  Created by Dominik Reisner on 12.11.14.
//
//

#include "Loader.h"

#include "MenuScene.h"
#include "InGameScene.h"
#include "HighscoreScene.h"
#include "TutorialScene.h"

Loader::Loader()
{
    /***********************/
    /******* Texture *******/
    /***********************/
    
    //Overall Game
    AddFile(game_textures_, DataHandler::TEXTURE_GAME_MAP_1);
    
    //Menu
    AddFile(scene_menu_textures_, DataHandler::TEXTURE_MENU_BUTTON_EXIT);
    AddFile(scene_menu_textures_, DataHandler::TEXTURE_MENU_BUTTON_HIGHSCORE);
    AddFile(scene_menu_textures_, DataHandler::TEXTURE_MENU_BUTTON_START);
    AddFile(scene_menu_textures_, DataHandler::TEXTURE_MENU_BUTTON_TUTORIAL);
    AddFile(scene_menu_textures_, DataHandler::TEXTURE_MENU_POPUP_BUTTON_ABOUT);
    AddFile(scene_menu_textures_, DataHandler::TEXTURE_MENU_POPUP_BUTTON_HELP);
    AddFile(scene_menu_textures_, DataHandler::TEXTURE_MENU_POPUP_BUTTON_SOUND_OFF);
    AddFile(scene_menu_textures_, DataHandler::TEXTURE_MENU_POPUP_BUTTON_SOUND_ON);
    
    //Collect Game
    AddFile(scene_collect_game_textures_, DataHandler::TEXTURE_COLLECT_GAME_APPLE);
    AddFile(scene_collect_game_textures_, DataHandler::TEXTURE_COLLECT_GAME_HAZELNUT);
    AddFile(scene_collect_game_textures_, DataHandler::TEXTURE_COLLECT_GAME_HEART);
    AddFile(scene_collect_game_textures_, DataHandler::TEXTURE_COLLECT_GAME_COIN);
    AddFile(scene_collect_game_textures_, DataHandler::TEXTURE_COLLECT_GAME_BASKET);
    AddFile(scene_collect_game_textures_, DataHandler::TEXTURE_COLLECT_GAME_BUTTON_MENU);
    AddFile(scene_collect_game_textures_, DataHandler::TEXTURE_COLLECT_GAME_BUTTON_REGISTER);
    AddFile(scene_collect_game_textures_, DataHandler::TEXTURE_COLLECT_GAME_BUTTON_RETRY);
    AddFile(scene_collect_game_textures_, DataHandler::TEXTURE_COLLECT_GAME_EDIT_BOX);
    AddFile(scene_collect_game_textures_, DataHandler::TEXTURE_COLLECT_GAME_POPUP_EXIT);
    AddFile(scene_collect_game_textures_, DataHandler::TEXTURE_COLLECT_GAME_POPUP_RESUME);
    
    //Highscore
    AddFile(scene_menu_textures_, DataHandler::TEXTURE_HIGHSCORE_BUTTON_BACK);
    AddFile(scene_menu_textures_, DataHandler::TEXTURE_HIGHSCORE_TABLE_BG);
    
    //Tutorial
    
    AddFile(scene_tutorial_textures_, DataHandler::TEXTURE_COLLECT_GAME_APPLE);
    AddFile(scene_tutorial_textures_, DataHandler::TEXTURE_COLLECT_GAME_HAZELNUT);
    AddFile(scene_tutorial_textures_, DataHandler::TEXTURE_COLLECT_GAME_HEART);
    AddFile(scene_tutorial_textures_, DataHandler::TEXTURE_COLLECT_GAME_COIN);
    AddFile(scene_tutorial_textures_, DataHandler::TEXTURE_COLLECT_GAME_BASKET);
    
    /***********************/
    /******** Sound ********/
    /***********************/
    
    //Overall Game
    AddFile(game_sounds_, DataHandler::SOUND_BUTTON_1);
    //AddFile(game_sounds_, DataHandler::MUSIC_BIRDS_ENVIRONMENT);
    
    //Collect Game
    AddFile(scene_collect_game_sounds_, DataHandler::SOUND_APPLE_BITE);
    AddFile(scene_collect_game_sounds_, DataHandler::SOUND_OTHER_1);
    AddFile(scene_collect_game_sounds_, DataHandler::SOUND_COIN_COLLECT);
    AddFile(scene_collect_game_sounds_, DataHandler::SOUND_PAPER_WAD);
	AddFile(scene_collect_game_sounds_, DataHandler::SOUND_PAPER_WAD);
	AddFile(scene_collect_game_sounds_, DataHandler::SOUND_HEART_COLLECT);

	//LOOK INTO LOAD GAME
//    AddFile(scene_collect_game_sounds_, DataHandler::SOUND_LEVEL_UP); got to LoadGame!!!!
    
    

}

Loader::~Loader()
{
    
}

#pragma message WARN("LOADER SHOULD HAVE ONE INSTANCE, FOR ALL SCENES NEED BETTER DESIGN")
void Loader::LoadGame()
{
	DataHandler::game_audio->preloadBackgroundMusic(DataHandler::MUSIC_BIRDS_ENVIRONMENT);
    LoadTextureContainer(game_textures_);
    LoadSoundContainer(game_sounds_);
    
    CCLOG("game assets loaded");
}

void Loader::UnloadGame()
{
    for(int i = 0; i < game_textures_.size(); i++)
    {
        Director::getInstance()->getTextureCache()->removeTextureForKey(game_textures_[i]);
    }
    
    for(int i = 0; i < game_sounds_.size();i++)
    {
        DataHandler::game_audio->unloadEffect(game_sounds_[i].c_str());
    }

    CCLOG("game assets unloaded");
}

void Loader::LoadCollectGame()
{
    LoadTextureContainer(scene_collect_game_textures_);
    LoadSoundContainer(scene_collect_game_sounds_);
    
    auto scene = InGameScene::createInGameScene();
    Director::getInstance()->replaceScene(TransitionCrossFade::create(1, scene));
    
    CCLOG("scene collect game assets loaded");

    //DataHandler::game_audio->stopBackgroundMusic();
    
    //DataHandler::game_audio->preloadBackgroundMusic("sound/manga-action_music.mp3");
//    CocosDenshion::SimpleAudioEngine::getInstance()->
    
    //currentScene = scene;
}

void Loader::UnloadCollectGame()
{
    UnloadTextureContainer(scene_collect_game_textures_);
    UnloadSoundContainer(scene_collect_game_sounds_);
    
    CCLOG("scene collect game assets unloaded");
}

void Loader::LoadMenu()
{
    LoadTextureContainer(scene_menu_textures_);
    LoadSoundContainer(scene_menu_sounds_);
    
    Scene* scene = MenuScene::createMenuScene();
    Director::getInstance()->replaceScene(TransitionCrossFade::create(1, scene));

    //currentScene = scene;
    CCLOG("scene menu assets loaded");
}

void Loader::UnloadMenu()
{
    UnloadTextureContainer(scene_menu_textures_);
    UnloadSoundContainer(scene_menu_sounds_);
    
    CCLOG("scene menu assets unloaded");
}

#pragma message WARN("NO PARAMETERS HERE PLEASE, EVERY LOAD FUNCTION SHOULD HAVE THE SAME STYLE")
void Loader::LoadHighscore(const std::string& newHighscoreEntry)
{
    LoadTextureContainer(scene_highscore_textures_);
    LoadSoundContainer(scene_highscore_sounds_);
    
    auto scene = HighscoreScene::createMenuScene(newHighscoreEntry);
    Director::getInstance()->replaceScene(TransitionCrossFade::create(1, scene));

    CCLOG("scene highscore assets loaded");
}

void Loader::UnloadHighscore()
{

    UnloadTextureContainer(scene_highscore_textures_);
    UnloadSoundContainer(scene_highscore_sounds_);

    
    CCLOG("scene highscore assets unloaded");
}

void Loader::LoadTutorial()
{
    LoadTextureContainer(scene_tutorial_textures_);
    LoadSoundContainer(scene_tutorial_sounds_);
    
    Scene* scene = TutorialScene::CreateTutorialScene();
    Director::getInstance()->replaceScene(TransitionCrossFade::create(1.0, scene));
    
    CCLOG("scene tutorial assets loaded");
}

void Loader::UnloadTutorial()
{
    UnloadTextureContainer(scene_tutorial_textures_);
    UnloadSoundContainer(scene_tutorial_sounds_);
    
    CCLOG("scene tutorial assets unloaded");
}

void Loader::BackToLastScene()
{
    
}

void Loader::LoadTextureContainer(std::vector<const std::string>& container)
{
    for(int i = 0; i < container.size(); i++)
    {
        Director::getInstance()->getTextureCache()->addImage(container[i]);
    }
}

void Loader::LoadSoundContainer(std::vector<const std::string>& container)
{
    for(int i = 0; i < container.size(); i++)
    {
        DataHandler::game_audio->preloadEffect(container[i].c_str());
    }
}

void Loader::UnloadTextureContainer(std::vector<const std::string> &container)
{
    for(int i = 0; i < container.size(); i++)
    {
        Director::getInstance()->getTextureCache()->removeTextureForKey(container[i]);
    }
}

void Loader::UnloadSoundContainer(std::vector<const std::string> &container)
{
    for(int i = 0; i < container.size(); i++)
    {
        DataHandler::game_audio->unloadEffect(container[i].c_str());
    }
}