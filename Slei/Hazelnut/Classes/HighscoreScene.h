//
// HighscoreScene.h
// Hazelnut
//
// Created by Matthias Reisner on 16.01.2015
//
//

#ifndef __Hazelnut__HighscoreScene__
#define __Hazelnut__HighscoreScene__

#include <stdio.h>
#include <cocos2d.h>
#include "CocosGUI.h"

#include "FrameworkScene.h"
#include "FrameWorkButton.h"

#include "Loader.h"

USING_NS_CC;

class HighscoreScene : public FrameworkScene
{
public:
	static Scene* createMenuScene(std::string user);
	
	virtual bool init();
	virtual void Tick(float delta);
	virtual void onExit();

	CREATE_FUNC(HighscoreScene);

	struct GameUser {
		std::string username;
		int points;
	};

	void registerHighscoreEntry(std::string entry);

private:
	//Just for tests, should be later created once in app delegate
	Loader loader;

	FrameworkButton* buttonExit;
	FSprite* highscore_;
    FSprite* background_;

	void calculateEntryPositions();
	void loadHighscoreEntries();
	void createEntryList();

	std::vector<HighscoreScene::GameUser> userData;
	std::vector<Label*> highscoreLabels;
	std::vector<Vec2> entryPositionListName;
	std::vector<Vec2> entryPositionListPoint;
    
private:
    static const std::string BACKGROUND;
    static const std::string TABLE_BACKGROUND;
};

#endif /* defined(__Hazelnut__HighscoreScene__) */

