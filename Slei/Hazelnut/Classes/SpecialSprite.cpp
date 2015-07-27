//
//  SpecialSprite.cpp
//  Hazelnut
//
//  Created by Dominik Reisner on 21.01.15.
//
//

#include "SpecialSprite.h"

std::string SpecialSprite::filename_ = "";

SpecialSprite::SpecialSprite()
: currScale(0.6)
, onIncrease(true)
, withAnimation(false)
{
    this->scheduleUpdate();
}

SpecialSprite::~SpecialSprite()
{
    
}

bool SpecialSprite::init()
{
    if(!Node::init())
    {
        return false;
    }
    return true;
    
//    //Shader
//    GLProgram* glp = new GLProgram();
//    
//    glp->initWithVertexShaderFilename("testv.vsh", "test.fsh");
//    glp->addAttribute(GLProgram::ATTRIBUTE_NAME_POSITION, GLProgram::VERTEX_ATTRIB_POSITION);
//    glp->addAttribute(GLProgram::ATTRIBUTE_NAME_COLOR, GLProgram::VERTEX_ATTRIB_COLOR);
//    glp->addAttribute(GLProgram::ATTRIBUTE_NAME_TEX_COORD, GLProgram::VERTEX_ATTRIB_TEX_COORD);
//    glp->link();
//    glp->updateUniforms();
//    
//    
//    Texture2D* tex = Director::getInstance()->getTextureCache()->addImage(filename_.insert(filename_.size()-4,"_alpha"));
//
//    
//    GL::bindTexture2DN(1, tex->getName());
//    
//    //button_sprite_menu_popup->setBlendFunc(BlendFunc::DISABLE);
//    
//    
//    setBlendFunc((ccBlendFunc) { GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA });
//    
//    GLuint t1Location = glGetUniformLocation(glp->getProgram(), "tex1");
//    //    GLuint t2Location = glGetUniformLocation(glp->getProgram(), "tex2");
//    
//    
//    
//    glp->setUniformLocationWith1i(t1Location, 1);
//    //    glp->setUniformLocationWith1i(t2Location, 0);
//    
//    
//    setShaderProgram(glp);
}

SpecialSprite* SpecialSprite::CreateSprite(const std::string& filename)
{
    SpecialSprite* sprite = new (std::nothrow) SpecialSprite();
    if (sprite && sprite->initWithFile(filename))
    {
        sprite->autorelease();
        filename_ = filename;
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    
    return nullptr;
}

void SpecialSprite::update(float delta)
{
    if(withAnimation)
    {
        if(sprite_animation_ == SCALE)
        {
            if(onIncrease)
            {
                currScale += 0.02;
                
            }
            else
            {
                currScale -= 0.02;
            }
            
            if(onIncrease && currScale >= 1.0)
            {
                onIncrease = false;
            }
            else if(!onIncrease && currScale <= 0.6)
            {
                onIncrease = true;
            }
            
            this->cocos2d::Node::setScale(currScale);
        }
        else if(sprite_animation_ == ROTATE)
        {
            current_rotation_value_ += 2.0;
            
            if(current_rotation_value_ >= 360)
            {
                current_rotation_value_ = 0;
            }
            
            this->setRotation(current_rotation_value_);
        }
    }
}

void SpecialSprite::Reset()
{
    current_rotation_value_ = 0.0;
    currScale = 1.0;
    
    setScale(currScale);
    setRotation(current_rotation_value_);
}
