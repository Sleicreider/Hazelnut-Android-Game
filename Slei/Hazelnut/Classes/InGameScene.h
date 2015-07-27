//
//  InGameScene.h
//  Hazelnut
//
//  Created by Dominik Reisner on 12.11.14.
//
//

#ifndef __Hazelnut__InGameScene__
#define __Hazelnut__InGameScene__

#include <cocos2d.h>
#include <CocosGUI.h>

#include "FrameworkScene.h"
#include "InGameController.h"
#include "Loader.h"


USING_NS_CC;

class InGameScene : public FrameworkScene
{
    
public:
    InGameScene();
    virtual ~InGameScene();

    static Scene* createInGameScene();
    
    virtual bool init();
    virtual void Tick(float delta);
    virtual void onExit();
    
    virtual void onEnter();
    
    void LoadMenu();
	void ReloadGame();
	void LoadHighscoreMenu(std::string user);
    
    CREATE_FUNC(InGameScene);
    
private:
    void AddAllGeneralSceneObjects();
    
private:
    InGameController ingController;
    
    FTimeframe timeframe_;
    
    Loader loader;
};



#endif /* defined(__Hazelnut__InGameScene__) */
