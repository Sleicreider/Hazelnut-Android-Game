//
//  MenuScene.h
//  Hazelnut
//
//  Created by Dominik Reisner on 28.11.14.
//
//

#ifndef __Hazelnut__MenuScene__
#define __Hazelnut__MenuScene__

#include <stdio.h>
#include <cocos2d.h>
#include "CocosGUI.h"

#include "FrameworkScene.h"
#include "FrameWorkButton.h"

#include "FUtil.h"

#include "Loader.h"

class MenuPopup;

USING_NS_CC;

class MenuScene : public FrameworkScene
{
public:
    MenuScene();
    virtual ~MenuScene();
    
	MenuScene(MenuScene&&);
	MenuScene& operator=(MenuScene&&);
    
    static Scene* createMenuScene();
    
    virtual bool init();
    virtual void Tick(float delta);
    virtual void onExit();
    
    CREATE_FUNC(MenuScene);

private:
	void CloudMovement();
	void BirdMovement();

    
    void StartHeartAnimation();
    void HeartAnimation();
    
private:
    //Just for tests, should be later created once in app delegate
    Loader loader;
	        
    FrameworkButton* buttonStart;
    FrameworkButton* buttonHighscore;
	FrameworkButton* buttonAchievement;
    FrameworkButton* buttonExit;
    FrameworkButton* button_tutorial_;
    FrameworkButton* button_menu_popup_;
        
    MenuPopup* popup_menu_;

    FSprite* background_;
    FSprite* cloud_1_;
    FSprite* cloud_2_;
    FSprite* cloud_3_;
	FSprite* sprite_anim_bird;
	FSprite* sprite_anim_bird1;

	static const std::string BACKGROUND;
};

#endif /* defined(__Hazelnut__MenuScene__) */