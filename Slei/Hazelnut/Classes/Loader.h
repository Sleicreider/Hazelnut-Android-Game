//
//  Loader.h
//  Hazelnut
//
//  Created by Dominik Reisner on 12.11.14.
//
//

#ifndef __Hazelnut__Loader__
#define __Hazelnut__Loader__

#include <cocos2d.h>
#include <vector>
#include "DataHandler.h"

USING_NS_CC;

class MenuScene;
class InGameScene;
class HighscoreScene;
class TutorialScene;

class Loader
{
public:
    Loader();
    ~Loader();
    
    void LoadGame();
    void UnloadGame();
    
    void LoadCollectGame();
    void UnloadCollectGame();
    
    void LoadMenu();
    void UnloadMenu();
    
#pragma message WARN("loader don't take arguments, every loading function should be the same, find other way for parameter!")
    
	void LoadHighscore(const std::string& user);
    void UnloadHighscore();

	void LoadAchievement(const std::string& user);
	void UnloadAchievement();
    
    void LoadTutorial();
    void UnloadTutorial();
    
    void BackToLastScene();
    
    void AddFile(std::vector<std::string>& container,const std::string& file_name);
    
    void LoadTextureContainer(std::vector<std::string>& container);
    void LoadSoundContainer(std::vector<std::string>& container);
    void UnloadTextureContainer(std::vector<std::string>& container);
    void UnloadSoundContainer(std::vector<std::string>& container);
    
private:
    std::vector<std::string> game_sounds_;
    std::vector<std::string> game_textures_;
    
    std::vector<std::string> scene_menu_sounds_;
    std::vector<std::string> scene_menu_textures_;
    
    std::vector<std::string> scene_collect_game_sounds_;
    std::vector<std::string> scene_collect_game_textures_;
    
    std::vector<std::string> scene_highscore_sounds_;
    std::vector<std::string> scene_highscore_textures_;

	std::vector<std::string> scene_achievement_sounds_;
	std::vector<std::string> scene_achievement_textures_;
    
    std::vector<std::string> scene_tutorial_sounds_;
    std::vector<std::string> scene_tutorial_textures_;
    
    //Scene* prevScene;
    //Scene* currentScene;
};

inline void Loader::AddFile(std::vector<std::string>& container, const std::string& file_name)
{
    container.push_back(file_name);
}



#endif /* defined(__Hazelnut__Loader__) */
