//
//  FSprite.cpp
//  Hazelnut
//
//  Created by Dominik Reisner on 14.07.15.
//
//

//#define ETC1

#include "FSprite.h"

FSprite::FSprite()
:previous_opacity_(getOpacity())
,current_alpha_file_("")
, withAnimation(false)
, onIncrease(true)
, currScale(0.6)
, current_rotation_value_(0.0)
{
    this->scheduleUpdate();
}

FSprite::~FSprite()
{
    
}

FSprite* FSprite::create(const std::string &filename, const Vec2& position)
{
    FSprite* sprite = new (std::nothrow) FSprite();
    if (sprite && sprite->initWithFile(filename))
    {
        sprite->autorelease();
        
        sprite->setAnchorPoint(Vec2(0.5,0.5));
        sprite->setPosition(position);
        
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    
    return nullptr;
}

FSprite* FSprite::create(const std::string &filename, const std::string &alpha_file, const Vec2& position)
{
#ifdef ETC1
    FSprite* sprite = new (std::nothrow) FSprite();
    if (sprite && sprite->initWithFile(filename))
    {
        sprite->autorelease();
        
        sprite->InitShader(alpha_file);
        
        sprite->setAnchorPoint(Vec2(0.5,0.5));
        sprite->setPosition(position);
                
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
#else
    return create(filename,position); //use default create(..) w/o etc1 support if etc1 not defined
#endif
    
    return nullptr;
}

void FSprite::InitShader(const std::string& alpha_file)
{
#ifdef ETC1
    //Shader
    GLProgram* glp = new GLProgram();
    glp->autorelease();
    
    glp->initWithFilenames("testv.vsh", "test.fsh");
    glp->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_POSITION, GLProgram::VERTEX_ATTRIB_POSITION);
    glp->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_COLOR, GLProgram::VERTEX_ATTRIB_COLOR);
    glp->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_TEX_COORD, GLProgram::VERTEX_ATTRIB_TEX_COORD);
    glp->link();
    glp->updateUniforms();
    
    opacity_location_ = glGetUniformLocation(glp->getProgram(), "u_opacity");
    
    current_alpha_file_ = alpha_file;
    
//  #pragma message WARN("getTextureForKey or someth else, texture should be added on loading scene, do not add (cocos should check that anyway but still dont do it)  all the time!!")
    Texture2D* tex = Director::getInstance()->getTextureCache()->addImage(alpha_file);
	setBlendFunc(BlendFunc({ GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA }));
    //setBlendFunc((BlendFunc) { GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA });
    
    GLProgramState* glprogramstate = GLProgramState::getOrCreateWithGLProgram(glp);
    
    setGLProgramState(glprogramstate);
    
    glprogramstate->setUniformFloat(opacity_location_, (float)getOpacity()/255.0);
    
    glprogramstate->setUniformTexture("u_texture1", tex);
    

    
    setGLProgram(glp);
#endif
}

void FSprite::UpdateAlphaTexture(const std::string& alpha_file)
{
#ifdef ETC1
    #pragma message("getTextureForKey or someth else, texture should be added (cocos should check that anyway but still dont do it) on loading scene, do not add all the time!!")
    Texture2D* tex = Director::getInstance()->getTextureCache()->addImage(alpha_file);
    current_alpha_file_ = alpha_file;
    getGLProgramState()->setUniformTexture("u_texture1", tex);
#endif
}

void FSprite::update(float delta)
{
#ifdef ETC1
    if(previous_opacity_ != (float)getOpacity())
    {
        //Update opacity in shader
        getGLProgramState()->setUniformFloat(opacity_location_, (float)getOpacity()/255.0);
        
        previous_opacity_ = (float) getOpacity();
    }
#endif
    
    AnimationUpdate();
}

void FSprite::AnimationUpdate()
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


void FSprite::Reset()
{
    current_rotation_value_ = 0.0;
    currScale = 1.0;
    
    setScale(currScale);
    setRotation(current_rotation_value_);
}
