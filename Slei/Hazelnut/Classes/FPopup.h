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
#include "FGeneral.h"

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
    

#pragma WARN message("NEED COMMENT")
    /**
     * 
     */
    bool WasClosed() const;
    
    CREATE_FUNC(FPopup);
    
private:
    FrameworkButton* button_background_;
    
    FTimeframe timeframe_fade_in_;
    FTimeframe timeframe_fade_out_;
    
	unsigned int bIsActive_:1;
    unsigned int bWasClosed_:1;
    unsigned int bReadyToShow_:1;
    
#pragma warn message("JUST USE IT UNTIL FRAMEWORKBUTTON IS A NODE")
    float button_opacity_;
    
protected:
    unsigned int bIsPaused_:1;
    unsigned int bHasEntered_:1;

    virtual bool init() override;
    virtual void update(float delta) override;

	virtual void onEnter();
	virtual void onExit();
	virtual void pause();
	virtual void resume();
    
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

FORCEINLINE bool FPopup::WasClosed() const { return bWasClosed_; }

FORCEINLINE void FPopup::onEnter()
{
	if (!bIsPaused_) Node::onEnter();
}

FORCEINLINE void FPopup::onExit()
{
	Node::onExit();
	bHasEntered_ = false;
}

FORCEINLINE void FPopup::pause()
{
	Node::pause();
	bIsPaused_ = true;
}

FORCEINLINE void FPopup::resume()
{
	Node::resume();
	bIsPaused_ = false;

	if (!bHasEntered_)
	{
		bHasEntered_ = true;
		Node::onEnter();
	}
}

#endif /* defined(__Hazelnut__FPopup__) */
