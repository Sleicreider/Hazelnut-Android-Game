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
    ~MenuScene();
    
    static Scene* createMenuScene();
    
    virtual bool init();
    virtual void Tick(float delta);
    virtual void onExit();
    
    CREATE_FUNC(MenuScene);

	ui::UICCTextField * textField;

private:
    void CloudMovement();
    
    void StartHeartAnimation();
    void HeartAnimation();
    
private:
    //Just for tests, should be later created once in app delegate
    Loader loader;
	        
    FrameworkButton* buttonStart;
    FrameworkButton* buttonHighscore;
    FrameworkButton* buttonExit;
    FrameworkButton* button_tutorial_;
    FrameworkButton* button_menu_popup_;
    
    FSprite* spriteL;
    FSprite* spriteR;
    FSprite* sprite;
    Node* n;
    
    Vector<SpriteFrame*> animFrames;
    
    MenuPopup* popup_menu_;
    
    FTimeframe tframe;
    FTimeframe tframe2;
    
    static const std::string BACKGROUND;
    
    FSprite* background_;
    FSprite* cloud_1_;
    FSprite* cloud_2_;
    FSprite* cloud_3_;
};

#endif /* defined(__Hazelnut__MenuScene__) */