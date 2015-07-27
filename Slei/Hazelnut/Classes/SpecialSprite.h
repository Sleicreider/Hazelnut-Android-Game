//
//  SpecialSprite.h
//  Hazelnut
//
//  Created by Dominik Reisner on 21.01.15.
//
//

#ifndef __Hazelnut__SpecialSprite__
#define __Hazelnut__SpecialSprite__

#include <stdio.h>

#include <cocos2d.h>

USING_NS_CC;

class SpecialSprite : public Sprite
{
public:
    SpecialSprite();
    virtual ~SpecialSprite();
    
    enum EAnimation {SCALE,ROTATE};
    
    static SpecialSprite* CreateSprite(const std::string& filename);
    
    void WithAnimation(bool active, EAnimation sprite_animation);
    
    /**
     * Resets the SpecialSprite including it's animation and animation values-
     */
    void Reset();
    
    CREATE_FUNC(SpecialSprite);
    
    
private:
    static std::string filename_;
    
    float currScale;
    bool onIncrease;
    bool withAnimation;
    
    float current_rotation_value_;
    
    EAnimation sprite_animation_;
    
protected:
    virtual bool init();
    virtual void update(float delta);
    
    
    

    
};

inline void SpecialSprite::WithAnimation(bool active,EAnimation sprite_animation) { withAnimation = active; sprite_animation_ = sprite_animation;}

#endif /* defined(__Hazelnut__SpecialSprite__) */
