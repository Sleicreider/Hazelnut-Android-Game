//
//  TutorialPopup.h
//  Hazelnut
//
//  Created by Dominik Reisner on 20.05.15.
//
//

#ifndef __Hazelnut__TutorialPopup__
#define __Hazelnut__TutorialPopup__

#include "FPopup.h"
#include "FSprite.h"

class TutorialPopup : public FPopup
{
public:
    TutorialPopup();
    virtual ~TutorialPopup();
    
    enum EItemText {HAZELNUT,WASTE,APPLE,HEART,COIN};
    
    static TutorialPopup* CreatePopup(FrameworkScene* scene);

    void SetTextIndex(EItemText item_text);
    void SpriteTextSettings(FSprite* sprite);
    
    CREATE_FUNC(TutorialPopup);
    
private:
//    static FrameworkScene* scene_;
    void SetSize(Vec2 size);
    
    Sprite* sprite_background_;
    
    FSprite* sprite_hazelnut_;
    FSprite* sprite_waste_;
    FSprite* sprite_apple_;
    FSprite* sprite_heart_;
    FSprite* sprite_coin_;
    
    Sprite* sprite_text_description;
    Label* label_text_;
    
    static const std::string text_hazelnut_;
    static const std::string text_waste_;
    static const std::string text_apple_;
    static const std::string text_heart_;
    static const std::string text_coin_;
    
protected:
    virtual void Tick();
    virtual void OnInit();
    virtual void OnShow();
    virtual void OnClosed();
};

inline void TutorialPopup::SetSize(Vec2 size)
{
        sprite_background_->setScale(size.x/sprite_background_->getContentSize().width,size.y/sprite_background_->getContentSize().height);
}

#endif /* defined(__Hazelnut__TutorialPopup__) */
