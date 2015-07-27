 //
//  MenuScene.cpp
//  Hazelnut
//
//  Created by Dominik Reisner on 28.11.14.
//
//

#include "MenuScene.h"
#include <CCLabel.h>
#include "DataHandler.h"
#include "MenuPopup.h"
#include "FPopup.h"
#include "AdmobHelper.h"

const std::string MenuScene::BACKGROUND = "background";

MenuScene::MenuScene()
{
}

MenuScene::~MenuScene()
{
}

void MenuScene::onExit()
{
    Layer::onExit();
}

Scene* MenuScene::createMenuScene()
{
    auto scene = Scene::create();
    auto layer = MenuScene::create();
     
    scene->addChild(layer);
	
	
    
    return scene;
}

bool MenuScene::init()
{
    if(!Layer::init())
    {
        return false;
    }
    
    background_ = FSprite::create(  DataHandler::TEXTURE_GAME_MAP_1
                                    ,Vec2(DataHandler::GAME_RESOLUTION_WIDTH/2 ,DataHandler::GAME_RESOLUTION_HEIGHT/2));
    background_->setZOrder(0);
    addChild(background_);
    
    if(DataHandler::app_layout_ == EAppLayout::LAYOUT_IPAD)
    {
        
        FSprite* background_extension = FSprite::create(DataHandler::TEXTURE_GAME_MAP_1_EXTENSION
                                                    ,Vec2(DataHandler::GAME_RESOLUTION_WIDTH/2,DataHandler::GAME_RESOLUTION_HEIGHT+180));
        
        background_extension->setScale(32, 6);
        
        addChild(background_extension);
    }
    else if(DataHandler::app_layout_ == EAppLayout::LAYOUT_DEFAULT)
    {
        FSprite* background_extension = FSprite::create(
                                                        DataHandler::TEXTURE_GAME_MAP_1_EXTENSION
                                                        ,Vec2(DataHandler::GAME_RESOLUTION_WIDTH/2,DataHandler::GAME_RESOLUTION_HEIGHT+100));
        background_extension->setScale(32, 3.35);
        
        addChild(background_extension);
    }
    
    //CLOUDS
    cloud_1_ = FSprite::create(DataHandler::TEXTURE_GAME_CLOUD_1);
    cloud_1_->setPosition(Vec2(DataHandler::GAME_RESOLUTION_CENTER_WIDTH-500,DataHandler::GAME_RESOLUTION_CENTER_HEIGHT + 100));
    MoveTo* move1 = MoveTo::create(12.0, Vec2(DataHandler::GAME_RESOLUTION_CENTER_WIDTH - 1150,DataHandler::GAME_RESOLUTION_CENTER_HEIGHT + 100));
    cloud_1_->runAction(move1);
    addChild(cloud_1_);
    
    cloud_2_ = FSprite::create(DataHandler::TEXTURE_GAME_CLOUD_2);
    cloud_2_->setPosition(Vec2(DataHandler::GAME_RESOLUTION_CENTER_WIDTH,DataHandler::GAME_RESOLUTION_CENTER_HEIGHT + 500));
    MoveTo* move2 = MoveTo::create(35.0, Vec2(DataHandler::GAME_RESOLUTION_CENTER_WIDTH - 1150,DataHandler::GAME_RESOLUTION_CENTER_HEIGHT + 500));
    cloud_2_->runAction(move2);
    addChild(cloud_2_);
    
    cloud_3_ = FSprite::create(DataHandler::TEXTURE_GAME_CLOUD_3);
    cloud_3_->setPosition(Vec2(DataHandler::GAME_RESOLUTION_CENTER_WIDTH + 500,DataHandler::GAME_RESOLUTION_CENTER_HEIGHT + 200));
    MoveTo* move3 = MoveTo::create(50.0, Vec2(DataHandler::GAME_RESOLUTION_CENTER_WIDTH - 1150,DataHandler::GAME_RESOLUTION_CENTER_HEIGHT + 200));
    cloud_3_->runAction(move3);
    addChild(cloud_3_);
    
    
    
    //Particle Test
    
//    ParticleSystemQuad* ps = ParticleSystemQuad::create(DataHandler::TEXTURE_COLLECT_GAME_WASTE);
    

//
//    CCParticleSystemQuad* cp = CCParticleSystemQuad::createWithTotalParticles(900);
//    cp->setTexture(Director::getInstance()->getTextureCache()->addImage(DataHandler::TEXTURE_COLLECT_GAME_WASTE));
//    cp->setPosition(DataHandler::GAME_RESOLUTION_CENTER);
//    addChild(cp);
//    
    ParticleSystemQuad* psq = ParticleSystemQuad::createWithTotalParticles(999);
    psq->setEmitterMode(ParticleSystem::Mode::GRAVITY);
    
    psq->setTexture(Director::getInstance()->getTextureCache()->addImage(DataHandler::TEXTURE_COLLECT_GAME_HEART));
    psq->setZOrder(1);
    psq->setDuration(2.0);
    
    psq->setEmissionRate(30.0);
    
    psq->setSpeed(50.);
    psq->setSpeedVar(40.);
    psq->setRadialAccel(200.);
    psq->setRadialAccelVar(30.);
    
    
    psq->setStartColor(Color4F::WHITE);
    psq->setStartSize(50);
    psq->setEndSize(30);
    psq->setEndColor(Color4F(1.0,1.0,1.0,0.0));
    psq->setLife(1.5);
    psq->setGravity(Vec2(0,-90));
    psq->setAngle(60.);
    psq->setAngleVar(20.);
    
    psq->setAutoRemoveOnFinish(true);
    psq->setTangentialAccel(100.0);
    psq->setTangentialAccelVar(50.0);
    psq->setPositionX(50);
    
    cloud_1_->addChild(psq);
    
    
    
    
    
//    char str[100] = {0};
//    for(int i = 1; i < animFrames.size(); i++)
//    {
    
        //sprintf(str, "grossini_dance_%02d.png",i);
//        auto frame = SpriteFrame::create(str,Rect(0,0,40,40)); //we assume that the sprites' dimentions are 40*40 rectangles.
//        animFrames.pushBack(frame);
//    }
    
    sprite = FSprite::create();
    
    animFrames = Vector<SpriteFrame*>(6);
    
    animFrames.pushBack(SpriteFrame::create(DataHandler::TEXTURE_COLLECT_GAME_HEART,        Rect(0,0,100,100)));
    animFrames.pushBack(SpriteFrame::create(DataHandler::TEXTURE_COLLECT_GAME_HEART_ANIM_1, Rect(0,0,100,100)));
    animFrames.pushBack(SpriteFrame::create(DataHandler::TEXTURE_COLLECT_GAME_HEART_ANIM_2, Rect(0,0,100,100)));
    animFrames.pushBack(SpriteFrame::create(DataHandler::TEXTURE_COLLECT_GAME_HEART_ANIM_3, Rect(0,0,100,100)));
    animFrames.pushBack(SpriteFrame::create(DataHandler::TEXTURE_COLLECT_GAME_HEART_ANIM_4, Rect(0,0,100,100)));
    animFrames.pushBack(SpriteFrame::create(DataHandler::TEXTURE_COLLECT_GAME_HEART_ANIM_5, Rect(0,0,100,100)));
    

    n = Node::create();
    
    spriteL = FSprite::create("Heart_piece_left.png");
    spriteR = FSprite::create("Heart_piece_right.png");
    
    float loffsetx = -20;
    float roffsetx =  20;
    


    addChild(sprite);
    
    

    n->setPosition(700,700);


    
    spriteL->setPosition(700+loffsetx,700);
    spriteR->setPosition(700+roffsetx,700);
    
    
    addChild(spriteL);
    addChild(spriteR);
    

    AddTickable(tframe);
    AddTickable(tframe2);
    
    tframe2.Start(milliseconds(3000), this, &MenuScene::StartHeartAnimation);
    
    
    //RepeatForever* r = RepeatForever::create(animate);
    

    sprite->setZOrder(10);
    sprite->setPosition(Vec2(700,700));
    
    
    FSprite* buttonSpriteStart = FSprite::create(DataHandler::TEXTURE_MENU_BUTTON_START);
//    buttonStart = this->CreateButton(700, 120,buttonSpriteStart);
    buttonStart = FrameworkButton::create(this, 700, 120, buttonSpriteStart);
    buttonStart->SetPositionX(DataHandler::GAME_RESOLUTION_WIDTH/2);
    buttonStart->SetPositionY(DataHandler::GAME_RESOLUTION_HEIGHT/2 + 20);
    buttonStart->SetZOrder(0);
    addChild(buttonStart);
    
    FSprite* buttonSpriteHighscore = FSprite::create(DataHandler::TEXTURE_MENU_BUTTON_HIGHSCORE);
//    buttonHighscore = this->CreateButton(700, 120,buttonSpriteHighscore);
    buttonHighscore = FrameworkButton::create(this, 700, 120, buttonSpriteHighscore);
    buttonHighscore->SetPositionX(DataHandler::GAME_RESOLUTION_WIDTH/2);
    buttonHighscore->SetPositionY(DataHandler::GAME_RESOLUTION_HEIGHT/2 - 120);
    buttonHighscore->SetZOrder(0);
    addChild(buttonHighscore);
    
    FSprite* button_sprite_tutorial = FSprite::create(DataHandler::TEXTURE_MENU_BUTTON_TUTORIAL);
//    button_tutorial_ = this->CreateButton(700, 120,button_sprite_tutorial);
    button_tutorial_ = FrameworkButton::create(this, 700, 120, button_sprite_tutorial);
    button_tutorial_->SetPositionX(DataHandler::GAME_RESOLUTION_WIDTH/2);
    button_tutorial_->SetPositionY(DataHandler::GAME_RESOLUTION_HEIGHT/2 - 260);
    button_tutorial_->SetZOrder(0);
    addChild(button_tutorial_);
    
    FSprite* buttonSpriteExit = FSprite::create(DataHandler::TEXTURE_MENU_BUTTON_EXIT);
//    buttonExit = this->CreateButton(700, 120,buttonSpriteExit);
    buttonExit = FrameworkButton::create(this, 700, 120,buttonSpriteExit);
    buttonExit->SetPositionX(DataHandler::GAME_RESOLUTION_WIDTH/2);
    buttonExit->SetPositionY(DataHandler::GAME_RESOLUTION_HEIGHT/2 - 400);
    buttonExit->SetZOrder(0);
    addChild(buttonExit);
    
    FSprite* button_sprite_menu_popup = FSprite::create(DataHandler::TEXTURE_COLLECT_GAME_BUTTON_MENU
                                                        , FUtil::GenerateETC1AlphaString(DataHandler::TEXTURE_COLLECT_GAME_BUTTON_MENU));
//    button_menu_popup_ = this->CreateButton(100, 100, button_sprite_menu_popup);
    button_menu_popup_ = FrameworkButton::create(this, 100, 100, button_sprite_menu_popup);
    button_menu_popup_->SetPositionX(100);
    button_menu_popup_->SetPositionY(100);
    button_menu_popup_->SetZOrder(4);
    addChild(button_menu_popup_);
    

    popup_menu_ = MenuPopup::CreateMenuPopup(this);
    SetActiveAndVisible(popup_menu_, false);
    
    //BACKGROUND AUDIO LOOP
#pragma message WARN("NOT PRELOADED")
    if(!CocosDenshion::SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying())
    {
        CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(DataHandler::MUSIC_BIRDS_ENVIRONMENT,true);
    }
    
    AdmobHelper::hideAd();
	AdmobHelper::hideAdBottom();
	AdmobHelper::hideAdScreen();
    
    return true;
}

void MenuScene::StartHeartAnimation()
{
    
    auto animation = Animation::createWithSpriteFrames(animFrames, 0.11f);
    auto animate = Animate::create(animation);
//    animation->setLoops(10);
    
    sprite->runAction(animate);
    
    tframe.Start(milliseconds(1000), this, &MenuScene::HeartAnimation);

}

void MenuScene::HeartAnimation()
{
    sprite->setOpacity(0);
    
    MoveTo* ml = MoveTo::create(1.0, Vec2(700 - 200,700));
    MoveTo* mr = MoveTo::create(1.0, Vec2(700 + 200,700));
    spriteL->runAction(ml);
    spriteR->runAction(mr);
    
    FadeTo* fl = FadeTo::create(1.0, 0);
    FadeTo* fr = FadeTo::create(1.0, 0);
    spriteL->runAction(fl);
    spriteR->runAction(fr);
    

}

void MenuScene::Tick(float delta)
{
    if(buttonStart->WasPressed())
    {
        DataHandler::game_audio->playEffect(DataHandler::SOUND_BUTTON_1);
        
        onEnterTransitionDidFinish();
        
        loader.UnloadMenu();
        loader.LoadCollectGame();
    }
    else if(buttonExit->WasPressed())
    {
        DataHandler::game_audio->playEffect(DataHandler::SOUND_BUTTON_1);
        
        loader.UnloadGame();
        
        CCDirector::sharedDirector()->end();
    }
	else if (buttonHighscore->WasPressed())
    {
        DataHandler::game_audio->playEffect(DataHandler::SOUND_BUTTON_1);

		onEnterTransitionDidFinish();
        
        loader.UnloadMenu();
		loader.LoadHighscore("");
	}
    else if(button_tutorial_->WasPressed())
    {        
        DataHandler::game_audio->playEffect(DataHandler::SOUND_BUTTON_1);
       
        onEnterTransitionDidFinish();
        loader.UnloadMenu();
        loader.LoadTutorial();
    }
    else if(button_menu_popup_->WasPressed())
    {
        popup_menu_->Show();
    }
    
    CloudMovement();
}

void MenuScene::CloudMovement()
{
    if(cloud_1_->getPosition().x <= DataHandler::GAME_RESOLUTION_CENTER_WIDTH - 1150)
    {
        cloud_1_->setPositionX(DataHandler::GAME_RESOLUTION_CENTER_WIDTH + 1150);
        MoveTo* move = MoveTo::create(50.0,Vec2(DataHandler::GAME_RESOLUTION_CENTER_WIDTH - 1150,cloud_1_->getPosition().y));
        cloud_1_->runAction(move);
    }
    
    if(cloud_2_->getPosition().x <= DataHandler::GAME_RESOLUTION_CENTER_WIDTH - 1150)
    {
        cloud_2_->setPositionX(DataHandler::GAME_RESOLUTION_CENTER_WIDTH + 1150);
        MoveTo* move = MoveTo::create(50.0,Vec2(DataHandler::GAME_RESOLUTION_CENTER_WIDTH - 1150,cloud_2_->getPosition().y));
        cloud_2_->runAction(move);
    }
    
    if(cloud_3_->getPosition().x <= DataHandler::GAME_RESOLUTION_CENTER_WIDTH - 1150)
    {
        cloud_3_->setPositionX(DataHandler::GAME_RESOLUTION_CENTER_WIDTH + 1150);
        MoveTo* move = MoveTo::create(50.0,Vec2(DataHandler::GAME_RESOLUTION_CENTER_WIDTH - 1150,cloud_3_->getPosition().y));
        cloud_3_->runAction(move);
    }
}