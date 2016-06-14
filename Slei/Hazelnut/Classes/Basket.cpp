//
//  Basket.cpp
//  Hazelnut
//
//  Created by Dominik Reisner on 14.06.16.
//
//

#include "Basket.h"

Basket::Basket()
{
}

Basket::~Basket()
{
}

Basket* Basket::create(const std::string& filename, const std::string& fragment_shader)
{
    auto sprite = new (std::nothrow) Basket();
    
    if(sprite != nullptr && sprite->initWithFile(filename))
    {
        sprite->autorelease();
        sprite->InitShader(fragment_shader);
        sprite->setAnchorPoint(Vec2(.5f,.5f));
        
        return sprite;
    }
    
    CC_SAFE_DELETE(sprite);
    
    return nullptr;
}

void Basket::InitShader(const std::string& fragment_shader)
{
    if(fragment_shader == "") return;
    
    auto gl_programm = new GLProgram();
    
    gl_programm->autorelease();
    
    gl_programm->initWithFilenames("basket.vsh", fragment_shader);
    
    gl_programm->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_POSITION, GLProgram::VERTEX_ATTRIB_POSITION);
    gl_programm->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_COLOR, GLProgram::VERTEX_ATTRIB_COLOR);
    gl_programm->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_TEX_COORD, GLProgram::VERTEX_ATTRIB_TEX_COORD);
    
    gl_programm->link();
    gl_programm->updateUniforms();
    
//    auto gl_program_state = GLProgramState::getOrCreateWithGLProgram(gl_programm);
//    setGLProgramState(gl_program_state);

    setGLProgram(gl_programm);
}