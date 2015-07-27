//
//  FPopup.h
//  Hazelnut
//
//  Created by Dominik Reisner on 19.05.15.
//
//

#ifndef __Hazelnut__FPopup__
#define __Hazelnut__FPopup__

#include <cocos2d.h>
#include "FrameworkScene.h"

USING_NS_CC;

#pragma warn message("CREATE METHOD CLOSEPOPUP() which closes the popup beside clicking on background")

class FPopup : public Node
{
public:
    FPopup();
    virtual ~FPopup();
    
    /**
     * Automatically adds itself to the scene with addChild(..)
     */
    static FPopup* CreatePopup(FrameworkScene* scene);
    /**
     * Fades in the popup.
     */
    void Show();
    
    /**
     *
     */
    bool WasClosed() const;
    
    CREATE_FUNC(FPopup);
    
private:
    FrameworkButton* button_background_;
    
    FTimeframe timeframe_fade_in_;
    FTimeframe timeframe_fade_out_;
    
    bool bIsActive_;
    bool bWasClosed_;
    bool bReadyToShow_;
    
#pragma warn message("JUST USE IT UNTIL FRAMEWORKBUTTON IS A NODE")
    float button_opacity_;
    
protected:
    bool bIsPaused_;
    bool bHasEntered_;
    virtual bool init();
    virtual void update(float delta);
    virtual void onEnter()
    {
        if(!bIsPaused_)
        {
            Node::onEnter();
        }
    }
    virtual void onExit()
    {
        Node::onExit();
        bHasEntered_ = false;
    }
    virtual void pause()
    {
        Node::pause();
        bIsPaused_ = true;
    }
    virtual void resume()
    {
        Node::resume();
        bIsPaused_ = false;
        
        if(!bHasEntered_)
        {
            bHasEntered_ = true;
            Node::onEnter();
        }
    }
    
    /**
     * Ticks each frame when fade in animation has started
     * until the fade out animation starts.
     */
    virtual void Tick() {};
    /**
     * Gets called when the popup is initialized.
     * Create Nodes,Buttons etc. here.
     */
    virtual void OnInit() {};
    /**
     * Called once before the fade in animation starts.
     */
    virtual void OnShow() {};
    /**
     * Called once after the popup faded out completely.
     */
    virtual void OnClosed() {};
    
protected:
    /**
     * The Popup needs the current scene.
     */
    static FrameworkScene* scene_;

};

inline bool FPopup::WasClosed() const
{
    return bWasClosed_;
}

#endif /* defined(__Hazelnut__FPopup__) */
