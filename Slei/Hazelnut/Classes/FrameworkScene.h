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

//class Gamepopup;
class FrameworkButton;


USING_NS_CC;

typedef void(*touchListenerFunction)(void);

class FrameworkScene : public Layer
{
public:
    FrameworkScene();
    virtual ~FrameworkScene();
    
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
    
//    /**
//     * Creates Button in the FrameworkScene at given width and height. Button might hold a sprite,
//     * but can also be used without a texture/sprite for touch areas.
//     *
//     * @param width Width of the button.
//     * @param height Height of the button.
//     * @param spirite Sprite to give the button a texture, not necessarily needed.
//     * @return FrameworkButton* Returns a FrameworkButton*.
//     */
//    FrameworkButton* CreateButton(int width, int height, Sprite* sprite = nullptr);
    /**
     * Creates A Object/Sprite for the Scene/World. The Object will be stored in a World Container and can be
     * Retrieved anywhere inside the scene by id.
     * Should be used for persistend/long living objects.
     *
     * @param id Is the id inside the scene/world.
     * @param file_name Is the file name of the Sprite in the Resource folder
     * @param object_position Vec2 value which sets the x,y position of the object
     * @return Sprite* Returns a pointer of the created object/sprite.
     */
//#pragma message WARN("TODO: USE FRAMEWORKSPRITE, MAP NOT NEEDED JUST RETURN POINTER, AND CREATE NODE* AND NOT SPRITE*")
//#pragma message WARN("TODO: CREATE WORLD OBJECT NOT NEEDED! redesign this usage, just use Sprite* sprite, we do not need to keep track of sprite in scene, they are destroyed anyway. SAME FOR TEXT ETC., just provide different ::create(parameter1,parameter2) versions")
//    Sprite* CreateWorldObject(const std::string& id,const std::string& file_name, const Vec2& object_position);
    
//    /**
//     * Creates a Object/Sprite which will not be stored in a scene/world container, must be manually removed from the scene.
//     * Should be used for short living objects.
//     * @param Sprite* Sprite which should be added to the scene.
//     */
//    void CreateObject(Node* Node);
    
//    /**
//     * Creates a text in the scene, which will be stored in a container by id.
//     * The Text can be retrieved through container by id with GetTextObject(const std::string& id);
//     *
//     * @param id String value which sets the id of the text object in the text container.
//     * @param pos_x X position of the text.
//     * @param pos_y Y position of the text.
//     * @param font_size Font size of the text.
//     * @param ttf_file TrueTypeFont(TTF) file name in the resource folder.
//     * @param color Color3B type which sets the color of the text in RGB.
//     */
//#pragma message WARN("TODO: CREATED TEXT SHOULD BE A ONNE TIME FUNCTION FOR EACH TEXT, PROVIDE A SETTEXT FOR EACH TEXT OBJECT")
//#pragma message WARN("TODO: PROVIDE TEXT SHOULD NOT BE PROCESSED ALL THE TIME / EACH FRAME")
//#pragma message WARN("TODO: MAYBE PROVIDE OBJECT FOR THE TEXT AND RETURN IT HERE -----  NEW COCOS NODE TEXT OBJECT OR LABEL? Label* CreateText(..)")
//#pragma message WARN("TODO: MAP MAYBE NOT NEEDED!")
//    Label* CreateText(const std::string& id, const std::string& text, const float pos_x, const float pos_y, const int fontSize,const std::string& ttfFile,const Color3B& color);
    
//    /**
//     * Removes the text from the scene/world by id.
//     * @param id Text id inside the container.
//     */
//#pragma message WARN("TODO: CHECK FOR NULL")
//    void RemoveText(const std::string& id);
    
    void SetActiveAndVisible(Node* node, bool active);
    //    Bool IsActiveAndVisible(Node* node);
    
//    /**
//     * Returns the text from the text container by the given id
//     * @return Label* Text from the text container in the scene.
//     */
//    Label* GetTextObject(const std::string& id);
//    /**
//     * Returns the object which was created with CreateWorldObject by the given id.
//     * @return Sprite* Sprite which was added to the scene as world object.
//     */
//    Sprite* GetWorldObject(const std::string& id);
    
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
    
    void AddButton(FrameworkButton* button)
    {
        vec_buttons_.push_back(button);
    }
    
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
//    Map<std::string, Sprite*> map_world_objects_;   /**< Container which holds pointers to all objects which are created as world object in the scene by string id */
//    Map<std::string, Label*> map_texts_;            /**< Container which holds pointers to all texts which are created in the scene by string id */
    std::vector<FrameworkButton*> vec_buttons_;     /**< Container which holds pointers to all buttons which are created in the scene by string id*/
    std::vector<ITickable*> vec_tickables_;
    
#pragma message WARN("TODO: MAP_INACTIVE_BUTTONS NOT USED RIGHT NOW")
    //	std::vector<FrameworkButton*> map_inactive_buttons;
    
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

//inline void     FrameworkScene::CreateObject(Node* node)            { this->addChild(node); }
//inline Sprite*  FrameworkScene::GetWorldObject(const std::string& id)   { return map_world_objects_.at(id); }
//inline Label*   FrameworkScene::GetTextObject(const std::string& id)    { return map_texts_.at(id); }

inline void     FrameworkScene::SetActiveAndVisible(Node* node, bool active_and_visible)
{
    if(node == nullptr) { CCLOGERROR("SetActiveAndVisible didn't work, node is a nullptr"); return; }
//    if(active_and_visible)
//    {
//        //        Node* extra;
//        //        while(extra->getChildren().size() > 0)
//        //        {
//        //
//        //        }
//        for(int i = 0; i < node->getChildren().size(); i++)
//        {
//            node->getChildren().at(i)->resume();
//        }
//        node->resume();
//        node->setVisible(true);
//        
//    }
//    else
//    {
//        for(int i = 0; i < node->getChildren().size(); i++)
//        {
//            node->getChildren().at(i)->pause();
//        }
//        node->pause();
//        node->setVisible(false);
//    }
    NodeRecursion(node, active_and_visible);
}

//inline Bool     FrameworkScene::IsActiveAndVisible(Node* node)
//{
//    if(node->isVisible())
//    {
//
//    }
//
//}

inline void FrameworkScene::AddTickable(ITickable &tickable)         { vec_tickables_.push_back(&tickable); }

//inline void FrameworkScene::RemoveText(const std::string &id)
//{
//    this->removeChild(map_texts_.at(id));
//    map_texts_.erase(id);
//}

#endif // FRAMEWORKLAYER_H