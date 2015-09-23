//
//  GamePausePopup.h
//  Hazelnut
//
//  Created by Dominik Reisner on 19.06.15.
//
//

#ifndef __Hazelnut__GamePausePopup__
#define __Hazelnut__GamePausePopup__

#include "FPopup.h"
#include "FrameworkButton.h"


class GamePausePopup : public FPopup
{
public:
    GamePausePopup();
    virtual ~GamePausePopup();
    
    static GamePausePopup* create(FrameworkScene* scene);
    
    CREATE_FUNC(GamePausePopup);
    
    bool GetExit()  const;
    
private:
    FSprite* sprite_background_;
    
    FrameworkButton* button_exit_;
    
    FStateMachine state_machine_;
    
    bool bExit_;

protected:
    virtual void Tick();
    virtual void OnInit();
    virtual void OnShow();
    virtual void OnClosed();
};


#endif /* defined(__Hazelnut__GamePausePopup__) */
