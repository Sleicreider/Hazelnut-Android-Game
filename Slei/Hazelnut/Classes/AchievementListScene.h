//
// AchievementListScene.h
// Hazelnut
//
// Created by Matthias Reisner on 16.01.2015
//
//

#ifndef __Hazelnut__AchievementListScene__
#define __Hazelnut__AchievementListScene__

#include <stdio.h>
#include <cocos2d.h>
#include "CocosGUI.h"

#include "FrameworkScene.h"
#include "FrameWorkButton.h"

#include "Loader.h"

USING_NS_CC;

class AchievementListScene : public FrameworkScene
{
public:
	static Scene* createMenuScene(std::string user);
	
	virtual bool init() override;
	virtual void Tick(float delta) override ;
	virtual void onExit() override;

	CREATE_FUNC(AchievementListScene);

	struct GameUser {
		std::string username;
		int points;
	};

private:
	//Just for tests, should be later created once in app delegate
	Loader loader;

	FrameworkButton* buttonExit;
	FSprite* scrollerbackground_;
    FSprite* background_;

	std::vector<GameUser> userData;
	std::vector<Label*> highscoreLabels;
	std::vector<Vec2> entryPositionListName;
	std::vector<Vec2> entryPositionListPoint;
    
private:
	static const int SCROLLVIEW_HEIGHT;
	static const int SCROLLVIEW_WIDTH;
	static const int SCROLLVIEW_INNER_HEIGHT;
	static const int SCROLLVIEW_INNER_WIDTH;
};

#endif /* defined(__Hazelnut__AchievementListScene__) */

