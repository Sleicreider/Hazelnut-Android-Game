//
//  AchievementNotification.h
//  Hazelnut
//
//  Created by Dominik Reisner on 20.01.16.
//
//

#ifndef Hazelnut_AchievementNotification_h
#define Hazelnut_AchievementNotification_h

#include <cocos2d.h>
#include "FrameworkScene.h"
#include "FUtil.h"
#include "FrameworkTimer.h"


class FSprite;

USING_NS_CC;

class AchievementNotification : public Node
{
    std::function<void()> func_task;
    
public:
    AchievementNotification();
    
    virtual ~AchievementNotification();

    
    static AchievementNotification* create(const std::string& text);
    static AchievementNotification* create(const std::string& text, const std::string& reward_sprite_filename);

    bool InitWithText(const std::string& text);
    
    template <typename T>
    void Show(T* instance, void (T::*func)());
    
    void SetText(const std::string& text);
    void SetSprite(const std::string& filename);
    
    
private:
    void Hide()
    {
        CCLOG("GadasafdaffdasfO");
        runAction(FadeTo::create(0.5,0));
    }
    
private:
    Label* label_archievment_;
    FSprite* sprite_reward_;
    FSprite* sprite_bg_;
    Node* node_;
    
    FTimeframe timer_;
    
    
protected:
    virtual void update(float delta) override;
};

FORCEINLINE void AchievementNotification::SetText(const std::string &text)
{
    label_archievment_->setString(text);
    
    int32_t x = sprite_bg_->getTexture()->getContentSize().width;
    int32_t y = sprite_bg_->getTexture()->getContentSize().height;
    int32_t desired_x = label_archievment_->getContentSize().width;
    int32_t desired_y = label_archievment_->getContentSize().height;
    
    sprite_bg_->setScaleX(desired_x/(float)x);
    sprite_bg_->setScaleY(desired_y/(float)y);
    setContentSize(Size(desired_x,desired_y));
}

FORCEINLINE void AchievementNotification::SetSprite(const std::string &filename)
{
    //reuse sprite
}

template <typename T>
FORCEINLINE
void AchievementNotification::Show(T* instance, void (T::*func)())
{
    FUtil::SetActiveAndVisible(this, true);
    
    runAction(FadeTo::create(0.5f, 255));
    timer_.Start(milliseconds(2000), this, &AchievementNotification::Hide);
    
    func_task = std::bind(func, instance);
    
    CCLOG("startttt");
    
//    timer_.Start(milliseconds(2000));
}

#endif
