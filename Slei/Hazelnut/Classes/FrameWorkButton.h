#ifndef FRAMEWORKBUTTON_H
#define FRAMEWORKBUTTON_H

#include <cocos2d.h>
#include <CocosGUI.h>

#include "FrameworkScene.h"

USING_NS_CC;


class FrameworkButton : public Node
{
    friend void FrameworkScene::UpdateButtons(); /**< Grants private member access to the FrameworkScene function UpdateButtons2(); */
    
public:
    /**
     * The FrameworkButton constructor.
     * @param width Constant integer value for the width of the button.
     * @param height constant integer value for the height of the button.
     * @param sprite Sprite pointer which is a nullptr by default.
     */
    FrameworkButton(int const width, int const height,Sprite* sprite = nullptr)
    : width_(width)
    , height_(height)
    , x_(0)
    , y_(0)
    , left_(0)
    , right_(0)
    , top_(0)
    , bottom_(0)
    , bWasPressed_(false)
    , bIsPressed_(false)
    , bIsActive_(true)
    , bIsVisible_(true)
    , z_order_(0)
    , sprite_(sprite)
    {
        if(sprite != nullptr) { addChild(sprite); };
        setCascadeOpacityEnabled(true);
#ifdef BUTTON_RECT
        DrawNode* rectangle = DrawNode::create();
        Vec2 vertices[] =
        {
            Vec2(-(width/2),height/2),
            Vec2(width/2,height/2),
            Vec2(width/2,-(height/2)),
            Vec2(-(width/2),-(height/2))
        };
        rectangle->drawPolygon(vertices, 4, Color4F(1.0f,0.3f,0.3f,0.5f), 3, Color4F(0.2f,0.2f,0.2f,0.5f));
        this->addChild(rectangle);
        
        SetRect(rectangle);
#endif
    }
    
    static FrameworkScene* scene_;
    
    static FrameworkButton* create(FrameworkScene* scene, int const width,int const height,Sprite* sprite = nullptr)
    {
        FrameworkButton* ret = new (std::nothrow) FrameworkButton(width,height,sprite);
        scene_ = scene;
        if (ret && ret->init())
        {
            ret->autorelease();
        }
        else
        {
            CC_SAFE_DELETE(ret);
        }
        
        scene->AddButton(ret);
        return ret;
    }
    
    /**
     * Returns the height of the button.
     * @return Integer value which holds the button height.
     */
    int GetHeight();
    /**
     * Returns the x position of the button.
     * @return Integer value which holds the x position of the button.
     */
    int GetPositionX();
    /**
     * Returns the width of the button.
     * @return Integer value which holds the button width.
     */
    int GetWidth();
    /**
     * Returns the y position of the button.
     * @return Integer value which holds the y position of the button.
     */
    int GetPositionY();
    /**
     * Returns the far left x position of the button.
     * @return Integer value which holds the x position on the far left.
     */
    int	GetLeft();
    /**
     * Returns the far right x position of the button.
     * @return Integer value which holds the x position on the far right.
     */
    int GetRight();
    /**
     * Returns the far top y position of the button.
     * @return Integer value which holds the y position on the far top.
     */
    int GetTop();
    /**
     * Returns the far bottom y position of the button.
     * @return Integer value which holds the y position on the far bot.
     */
    int GetBottom();
    /**
     * Returns the z_order of the button. Buttons with an higher zOrder
     * are above other buttons on the z axis.
     * @return Integer value which holds the zOrder of the button.
     */
    int GetZOrder();
    /**
     * Returns the sprite of the button.
     * @return Sprite object of the button.
     */
    Sprite* GetSprite();
    /**
     * Returns whether the button was pressed or not.
     * After a press it will return true only for 1 tick
     * @return Boolean value which is true for 1 tick if the button was released.
     */
    bool WasPressed();
    /**
     * Returns whether the button is press in the current tick or not
     * (when the user holds the button).
     * @return Boolean value which is true while the user is pressing the button.
     */
    bool IsPressed();
    /**
     * Returns whether the button is active or not.
     * inactive buttons will not be checked for presses
     * @return Boolean value which is true if the button is active.
     */
    bool IsActive();
    /**
     * Returns whether the button is visible or not
     * invisible buttons are set to full transparency.
     * @return Boolean value which is true if the button is visible.
     */
    //    bool IsVisible();
    
    
    
    
    
public:
    virtual void pause()
    {
        Node::pause();
        bIsActive_ = false;
    }
    virtual void resume()
    {
        Node::resume();
        bIsActive_ = true;
    }
    
    /**
     * Sets the x position of the button
     * @param x Integer value for new x position
     */
    void SetPositionX(int x);
    
    /**
     * Sets the y position of the Button
     * @param y Integer value for new y position
     */
    void SetPositionY(int y);
    /**
     * Sets the z_order position of the button.
     * Buttons with a higher z Order are more forward on the z axis
     * and will be touched if Buttons are overlapping
     * @param zOrder Integer value for new z_order
     */
    void SetZOrder(int z_order);
    
    /**
     * Sets the button active or inactive.
     * Inactive buttons won't be checked for touches
     * @param active Boolean value to set the Button active(true) or inactive(false)
     */
    void SetActive(bool active);
    
    /**
     * Sets the visibility of the button. If (false) texture/sprite will not be visible to the user
     * but it can still be pressed.
     * @param visible Integer value to set the visiblity of button texture to the user;
     */
    void SetVisible(bool visible);
    
#ifdef BUTTON_RECT
    void SetRect(DrawNode* rectangle);
#endif
    
private:
    /**
     * For the FrameworkScene to set the Button state to is_pressed
     * @param is_pressed Boolean value for the bIsPressed state
     */
    void SetIsPressed(bool bIsPressed);
    /**
     * For the FrameworkScene to set the Button state of was_pressed
     * @param was_pressed Boolean value for the bWasPressed state
     */
    void SetWasPressed(bool bWasPressed);
    
private:
    int width_;
    int height_;
    
    int x_;
    int y_;
    
    int left_;
    int right_;
    int top_;
    int bottom_;
    
    bool bWasPressed_;
    bool bIsPressed_;
    
    bool bIsActive_;
    bool bIsVisible_;
    
    int z_order_;
    
#ifdef BUTTON_RECT
    DrawNode* rectangle_;
#endif
    
    Sprite* sprite_;
};

FORCEINLINE int  FrameworkButton::GetPositionX() { return getPositionX(); }
FORCEINLINE int  FrameworkButton::GetPositionY() { return getPositionY(); }

FORCEINLINE int  FrameworkButton::GetWidth()  { return width_; }
FORCEINLINE int  FrameworkButton::GetHeight() { return height_; }
FORCEINLINE int  FrameworkButton::GetZOrder() { return getZOrder(); }
FORCEINLINE int  FrameworkButton::GetLeft()   { return (getParent()->convertToWorldSpace(getPosition()).x - width_/2); }
FORCEINLINE int  FrameworkButton::GetRight()  { return (getParent()->convertToWorldSpace(getPosition()).x + width_/2); }
FORCEINLINE int  FrameworkButton::GetTop()    { return (getParent()->convertToWorldSpace(getPosition()).y + height_/2); }
FORCEINLINE int  FrameworkButton::GetBottom() { return (getParent()->convertToWorldSpace(getPosition()).y - height_/2); }

FORCEINLINE bool FrameworkButton::IsPressed()    { return bIsPressed_; }
FORCEINLINE bool FrameworkButton::WasPressed()   { return bWasPressed_; }
FORCEINLINE void FrameworkButton::SetWasPressed(bool bWasPressed)    { bWasPressed_ = bWasPressed; }
FORCEINLINE void FrameworkButton::SetIsPressed(bool bIsPressed)      { bIsPressed_ = bIsPressed; }

FORCEINLINE Sprite*  FrameworkButton::GetSprite()    { return sprite_; }

FORCEINLINE bool     FrameworkButton::IsActive()     { return bIsActive_; }


FORCEINLINE void FrameworkButton::SetPositionX(int x)
{
    setPositionX(x);
    
#ifdef BUTTON_RECT
    rectangle_->setPositionX(x);
#endif
}

FORCEINLINE void FrameworkButton::SetPositionY(int y)
{
    setPositionY(y);
    
#ifdef BUTTON_RECT
    rectangle_->setPositionY(y);
#endif
}

FORCEINLINE void FrameworkButton::SetZOrder(int z_order)
{
    setZOrder(z_order);
    if(sprite_ != nullptr)
    {
        sprite_->setZOrder(z_order);
    }
    
#ifdef BUTTON_RECT
    rectangle_->setZOrder(z_order+1);
#endif
}

FORCEINLINE void FrameworkButton::SetActive(bool active)
{
    bIsActive_ = active;

    (active) ? resume() : pause();
    
#ifdef BUTTON_RECT
    (active) ? rectangle_->pause() : rectangle_->resume();
    rectangle_->setVisible(active);
#endif
}

FORCEINLINE void FrameworkButton::SetVisible(bool visible)
{
#pragma message WARN("is this also true for the sprite? or just for the button node??? check for all other functions too")
    setVisible(visible);
    
#ifdef BUTTON_RECT
    rectangle_->setVisible(visible);
#endif
}

#ifdef BUTTON_RECT
FORCEINLINE void FrameworkButton::SetRect(DrawNode* rectangle)
{
    this->rectangle_ = rectangle;
}
#endif

#endif // FRAMEWORKBUTTON_H