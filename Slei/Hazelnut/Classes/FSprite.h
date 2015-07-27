//
//  FSprite.h
//  Hazelnut
//
//  Created by Dominik Reisner on 14.07.15.
//
//

#ifndef __Hazelnut__FSprite__
#define __Hazelnut__FSprite__

#include <cocos2d.h>

USING_NS_CC;

class FSprite : public Sprite
{
public:
    FSprite();
    virtual ~FSprite();
    
    enum EAnimation {SCALE,ROTATE};

    
    static FSprite* create(const std::string& filename, const Vec2& position = Vec2(0,0));
    
    /**
     * For ETC1 Only
     */
    static FSprite* create(const std::string& filename, const std::string& alpha_file, const Vec2& position = Vec2(0,0));
    
    void InitShader(const std::string& alpha_file);
    void UpdateAlphaTexture(const std::string& alpha_file);
    
    void AnimationUpdate();
    void Reset();
    
    void WithAnimation(bool active, EAnimation sprite_animation);

    
    CREATE_FUNC(FSprite);
    
private:
    float previous_opacity_;
    GLint opacity_location_;
    
    std::string current_alpha_file_;
    
private:    
    float currScale;
    bool onIncrease;
    bool withAnimation;
    
    float current_rotation_value_;
    
    EAnimation sprite_animation_;

    
protected:
    virtual void update(float delta);
};

inline void FSprite::WithAnimation(bool active,EAnimation sprite_animation) { withAnimation = active; sprite_animation_ = sprite_animation;}

#endif /* defined(__Hazelnut__FSprite__) */
