#ifndef FRAMEWORKLAYER_H
#define FRAMEWORKLAYER_H

#include <cocos2d.h>
#include <CocosGUI.h>

#include "AppEnum.h"

#include "DataHandler.h"
#include "SimpleAudioEngine.h"

#include "FTimeframe.h"
#include "FStateMachine.h"
#include "FSprite.h"
#include "FGeneral.h"

//class Gamepopup;
class FrameworkButton;






USING_NS_CC;

typedef void(*touchListenerFunction)(void);

class FrameworkScene : public Layer
{
public:
    FrameworkScene();
    virtual ~FrameworkScene();
    
    virtual bool init() override;
    
    void NodeRecursion(Node* node, bool active_and_visible)
    {
        if(!active_and_visible)
        {
            node->pause();
            node->setVisible(false);
        }
        else
        {
            node->resume();
            node->setVisible(true);
        }
        
        auto& children = node->getChildren();
        for (size_t i = 0; i < children.size(); i++)
        {
            NodeRecursion(children.at(i), active_and_visible);
        }
    }
    
    //DEPRECATED USE FUtil::SetActiveAndVisible(..)
    DEPRECATED(void SetActiveAndVisible(Node* node, bool active));
 
    /**
     * Updates all FrameworkButtons in the FrameworkScene. Checks for touches on active buttons.
     * Is used by the FrameworkScene only, it is not necessary to call this function.
     */
#pragma message WARN("TODO:MAYBE PRIVATE")
    void UpdateButtons();
    
    
    bool updateDelayControl(float delta, float checkpoint);
    
    bool isDelayControlEnabled();
    void setDelayControlEnabled(bool value);
    
    void AddTickable(ITickable& tickable);
    void RemoveTickable(ITickable& tickable);
    
    void AddButton(FrameworkButton* button)
    {
        vec_buttons_.push_back(button);
    }
    
public:
    
    static FrameworkScene* GetActiveScene()
    {
        return FrameworkScene::active_scene_;
    }
    
private:
    static FrameworkScene* active_scene_;

    
private:
    
    
    /**
     * Updates FrameworkScene and it's objects. Items are FrameworkObjects and the Tick(float) function.
     */
    virtual void update(float delta);
    
    /**
     * Triggers when a touch in the scene happened.
     */
    virtual bool onTouchBegan(Touch* touches, Event* event);
    /**
     * Triggers when touch in the scene is moving while being pressed.
     */
    virtual void onTouchMoved(Touch* touche, Event* event);
    /**
     * Triggers when touch in the is released.
     */
    virtual void onTouchEnded(Touch* touche, Event* event);
    /**
     * Triggers when the touch never will reach its release state in the scene.
     */
    virtual void onTouchCancelled(Touch* touche, Event* event);
    
private:
    std::vector<FrameworkButton*> vec_buttons_;     /**< Container which holds pointers to all buttons which are created in the scene by string id*/
    std::vector<ITickable*> vec_tickables_;
        
    bool bTouchHappened_;               /**< True when a button is touched */
    int touch_x_;                       /**< Current touch x position */
    int touch_y_;                       /**< Current touch y position */
    
    bool bReleaseHappened_;             /**< True when a button is released */
    bool bWasPressed_;                  /**< True for one tick when a button touch ended/is released*/
    
    int higher_z_order_;                /**< Helper variable for z_order comparison */
    int curr_target_z_order_;           /**< Z Order of the currently observed button */
    
#pragma message WARN("TODO: button_click_ MAYBE NOT NEEDED")
    bool bButtonClick_;                 /**< True if a touch happened */
    
    FrameworkButton* active_button_;    /**< The pressed button */
    
    
    
    // Delay Control
    float sumDelta;
    void initDelayControl();
    bool delayControlEnabled;
    
protected:
    /**
     * Updates the Scene and it's object every frame.
     */
    virtual void Tick(float delta);
};

//DEPRECATED USE FUtil::SetActiveAndVisible(..)
inline void FrameworkScene::SetActiveAndVisible(Node* node, bool active_and_visible)
{
    if(node == nullptr) { CCLOGERROR("SetActiveAndVisible didn't work, node is a nullptr"); return; }

    NodeRecursion(node, active_and_visible);
}


inline void FrameworkScene::AddTickable(ITickable &tickable)         { vec_tickables_.push_back(&tickable); }



#endif // FRAMEWORKLAYER_H