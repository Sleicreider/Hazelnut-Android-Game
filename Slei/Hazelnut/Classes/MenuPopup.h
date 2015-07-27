//
//  MenuPopup.h
//  Hazelnut
//
//  Created by Dominik Reisner on 26.05.15.
//
//

#include "FPopup.h"
#include "FrameworkButton.h"

#ifndef __Hazelnut__MenuPopup__
#define __Hazelnut__MenuPopup__

class MenuPopup : public FPopup
{
public:
    MenuPopup();
    virtual ~MenuPopup();
    
    static MenuPopup* CreateMenuPopup(FrameworkScene* scene);
    
    CREATE_FUNC(MenuPopup);
    
private:
    void CreateMainContent();
    void CreateAboutContent();
    void CreateHelpContent();
    
    void CreatePopupFrame();
    
    void OnStateMain(float delta);
    void OnStateAbout(float delta);
    void OnStateHelp(float delta);
    
private:
    FSprite* sprite_background_;
    
    FSprite* sprite_sound_on_;
    FSprite* sprite_sound_off_;
    
    FrameworkButton* button_sound_;
    FrameworkButton* button_about_;
    FrameworkButton* button_help_;

    FrameworkButton* button_background_;
    
    Node* node_menu_main_;
    Node* node_menu_about_;
    Node* node_menu_help_;
    
    Node* node_menu_frame_;
    
    FTimeframe timeframe_active_visible_;
    
    FStateMachine<MenuPopup> state_machine_;
    
private:
    static const std::string STATE_MAIN;
    static const std::string STATE_ABOUT;
    static const std::string STATE_HELP;
    
protected:
    virtual void Tick();
    virtual void OnInit();
    virtual void OnShow();
    virtual void OnClosed();
};

#endif /* defined(__Hazelnut__MenuPopup__) */
