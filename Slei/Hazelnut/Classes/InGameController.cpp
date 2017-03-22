//
//  InGameController.cpp
//  Hazelnut
//
//  Created by Dominik Reisner on 12.11.14.
//
//

#include "InGameController.h"
#include "DataHandler.h"
#include "InGameScene.h"
#include "MenuScene.h"
#include "TextFieldExtended.h"
#include "FUtil.h"
#include "AdmobHelper.h"
#include "Basket.h"

InGameController::InGameController(InGameScene* scene)
: scene_(scene)

, ai_(scene)

, SQUIRREL("squirrel")
, BASKET("basket")
, BACKGROUND("background")

, STATE_RUNNING("state_running")
, STATE_GAME_OVER("state_game_over")
, STATE_PAUSED("state_paused")
, STATE_LEVEL_UP("state_level_up")
, STATE_POPUP_MENU("state_popup_menu")
, STATE_EXIT("state_exit")

, squirrel_pos_x_((DataHandler::GAME_RESOLUTION_WIDTH/2))
, player_score_(0)
, prev_player_score_(-1)
, player_lives_(DataHandler::COLLECT_GAME_PLAYER_LIVES_START)
, prev_player_lives_(-1)

, hazelnut_speed_(0)
{
    //Squirrel
    
    squirrel_ = FSprite::create(DataHandler::TEXTURE_COLLECT_GAME_SQUIRREL
                                , FUtil::GenerateETC1AlphaString(DataHandler::TEXTURE_COLLECT_GAME_SQUIRREL)
                                , Vec2(DataHandler::GAME_RESOLUTION_WIDTH/2, DataHandler::COLLECT_GAME_SQUIRREL_POSY_START));
    
    scene_->addChild(squirrel_);
    
    //Background
    
    background_ = FSprite::create(DataHandler::TEXTURE_GAME_MAP_1, Vec2(DataHandler::GAME_RESOLUTION_WIDTH/2,
                                                                        DataHandler::GAME_RESOLUTION_HEIGHT/2));
    
    scene_->addChild(background_);
    
    //Branch
    
    branch_ = FSprite::create(DataHandler::TEXTURE_GAME_BRANCH, Vec2(DataHandler::GAME_RESOLUTION_WIDTH / 2, DataHandler::COLLECT_GAME_SQUIRREL_POSY_START-94));
    
    scene_->addChild(branch_);
    
    if(DataHandler::app_layout_ == EAppLayout::LAYOUT_IPAD)
    {
        FSprite* background_extension = FSprite::create(DataHandler::TEXTURE_GAME_MAP_1_EXTENSION,
                                                        Vec2(DataHandler::GAME_RESOLUTION_WIDTH/2,DataHandler::GAME_RESOLUTION_HEIGHT+180));
        
        background_extension->setScale(32, 6);
        
        scene_->addChild(background_extension);
    }
    else if(DataHandler::app_layout_ == EAppLayout::LAYOUT_DEFAULT)
    {
        FSprite* background_extension = FSprite::create(DataHandler::TEXTURE_GAME_MAP_1_EXTENSION
                                                        ,Vec2(DataHandler::GAME_RESOLUTION_WIDTH/2,DataHandler::GAME_RESOLUTION_HEIGHT+100));
        
        background_extension->setScale(32, 3.35);
        
        scene_->addChild(background_extension);
    }
    
    //CLOUDS
    cloud_1_ = FSprite::create(DataHandler::TEXTURE_GAME_CLOUD_1);
    cloud_1_->setPosition(Vec2(DataHandler::GAME_RESOLUTION_CENTER_WIDTH-500,DataHandler::GAME_RESOLUTION_CENTER_HEIGHT + 100));
    MoveTo* move1 = MoveTo::create(12.0, Vec2(DataHandler::GAME_RESOLUTION_CENTER_WIDTH - 1150,DataHandler::GAME_RESOLUTION_CENTER_HEIGHT + 100));
    cloud_1_->runAction(move1);
    scene_->addChild(cloud_1_);
    
    cloud_2_ = FSprite::create(DataHandler::TEXTURE_GAME_CLOUD_2);
    cloud_2_->setPosition(Vec2(DataHandler::GAME_RESOLUTION_CENTER_WIDTH,DataHandler::GAME_RESOLUTION_CENTER_HEIGHT + 500));
    MoveTo* move2 = MoveTo::create(35.0, Vec2(DataHandler::GAME_RESOLUTION_CENTER_WIDTH - 1150,DataHandler::GAME_RESOLUTION_CENTER_HEIGHT + 500));
    cloud_2_->runAction(move2);
    scene_->addChild(cloud_2_);
    
    cloud_3_ = FSprite::create(DataHandler::TEXTURE_GAME_CLOUD_3);
    cloud_3_->setPosition(Vec2(DataHandler::GAME_RESOLUTION_CENTER_WIDTH + 500,DataHandler::GAME_RESOLUTION_CENTER_HEIGHT + 200));
    MoveTo* move3 = MoveTo::create(50.0, Vec2(DataHandler::GAME_RESOLUTION_CENTER_WIDTH - 1150,DataHandler::GAME_RESOLUTION_CENTER_HEIGHT + 200));
    cloud_3_->runAction(move3);
    scene_->addChild(cloud_3_);
    
    //BIRDS
    Vector<SpriteFrame*> anim_bird_frames = Vector<SpriteFrame*>(2);
    anim_bird_frames.pushBack(SpriteFrame::create(DataHandler::TEXTURE_GAME_BIRD_FRAME_1, Rect(0, 0, 106, 120)));
    anim_bird_frames.pushBack(SpriteFrame::create(DataHandler::TEXTURE_GAME_BIRD_FRAME_2, Rect(0, 0, 106, 120)));
    
    auto animation = Animation::createWithSpriteFrames(anim_bird_frames, 0.2f);
    auto animate = Animate::create(animation);
    
    sprite_anim_bird = FSprite::create();
    sprite_anim_bird->setTextureRect(Rect(0, 0, 106, 120));
    sprite_anim_bird->setScale(0.6);
    sprite_anim_bird->setRotation(15);
    sprite_anim_bird->setPosition(Vec2(DataHandler::GAME_RESOLUTION_CENTER_WIDTH - 500, DataHandler::GAME_RESOLUTION_CENTER_HEIGHT + 100));
    sprite_anim_bird->runAction(RepeatForever::create(animate));
    MoveTo* bMove1 = MoveTo::create(12.0, Vec2(DataHandler::GAME_RESOLUTION_CENTER_WIDTH + 1150, DataHandler::GAME_RESOLUTION_CENTER_HEIGHT + 100));
    sprite_anim_bird->runAction(bMove1);
    scene_->addChild(sprite_anim_bird);
    
    auto animation1 = Animation::createWithSpriteFrames(anim_bird_frames, 0.2f);
    auto animate1 = Animate::create(animation1);
    sprite_anim_bird1 = FSprite::create();
    sprite_anim_bird1->setTextureRect(Rect(0, 0, 106, 120));
    sprite_anim_bird1->setScale(0.6);
    sprite_anim_bird1->setRotation(-15);
    sprite_anim_bird1->setFlipX(true);
    sprite_anim_bird1->setPosition(Vec2(DataHandler::GAME_RESOLUTION_CENTER_WIDTH - 500, DataHandler::GAME_RESOLUTION_CENTER_HEIGHT + 200));
    sprite_anim_bird1->runAction(RepeatForever::create(animate1));
    MoveTo* bMove2 = MoveTo::create(12.0, Vec2(DataHandler::GAME_RESOLUTION_CENTER_WIDTH - 1150, DataHandler::GAME_RESOLUTION_CENTER_HEIGHT + 200));
    sprite_anim_bird1->runAction(bMove2);
    scene_->addChild(sprite_anim_bird1);
    
    //Basket
    basket_ = Basket::create(DataHandler::COSMETIC_BASKET.texture, DataHandler::COSMETIC_BASKET.fragment_shader);
    basket_->setAnchorPoint(Vec2(0.5,0.5));
    basket_->setPosition(Vec2(DataHandler::GAME_RESOLUTION_WIDTH/2, DataHandler::COLLECT_GAME_BASKET_POSY_START));

    scene_->addChild(basket_);
    
    background_->setZOrder(0);
    squirrel_->setZOrder(2);
    basket_->setZOrder(2);
    
    
    
    //Default set state RUNNING
    state_machine_.SetState(STATE_RUNNING);
    
    
    lvl_system_.LevelControl(player_score_);
    lvl_system_.GetLevelSettings(squirrel_speed_, drop_object_speed_min_, drop_object_speed_max_,
                                 drop_interval_min_, drop_interval_max_,level_score_multiplier_,
                                 drop_c_hazelnut_, drop_c_waste_, drop_c_apple_, drop_c_heart_, drop_c_coin_, hazelnut_speed_);
    ai_.SetDropChance(drop_c_hazelnut_, drop_c_waste_, drop_c_apple_, drop_c_heart_, drop_c_coin_);
    
    ai_.InitAI(squirrel_);
    
    basket_collision_box_.AttatchTo(basket_, ai_.GetDropObjects(),ai_.GetInactiveDropObjects());
    
    buttonRetry = NULL;
    buttonRegister = NULL;
	buttonShareScore = NULL;
    tfeUsername = NULL;

    
    GenerateLiveBar();
    UpdateLiveBar();
    
    FSprite* menuPopupSprite = FSprite::create(DataHandler::TEXTURE_COLLECT_GAME_BUTTON_MENU, FUtil::GenerateETC1AlphaString(DataHandler::TEXTURE_COLLECT_GAME_BUTTON_MENU));
    
    //    button_menu_ = scene->CreateButton(110, 100,menuPopupSprite);
    button_menu_ = FrameworkButton::create(scene, 110, 100, menuPopupSprite);
    button_menu_->SetPositionX(50);
    button_menu_->SetPositionY(50);
    button_menu_->SetZOrder(1);
    scene->addChild(button_menu_);
    
    
    int32_t height = 1080;
    if(DataHandler::app_layout_ != EAppLayout::LAYOUT_WIDESCREEN)
    {
        height = 1536;
    }
    
    //    button_right_ = scene->CreateButton(DataHandler::GAME_RESOLUTION_WIDTH/2, height);
    button_right_ = FrameworkButton::create(scene, DataHandler::GAME_RESOLUTION_WIDTH/2, height);
    button_right_->SetPositionX(DataHandler::GAME_RESOLUTION_WIDTH-button_right_->GetWidth()/2);
    button_right_->SetPositionY(DataHandler::GAME_RESOLUTION_HEIGHT/2);
    button_right_->SetZOrder(0);
    scene->addChild(button_right_);
    
    
    //    button_left_ = scene->CreateButton(DataHandler::GAME_RESOLUTION_WIDTH/2, height);
    button_left_ = FrameworkButton::create(scene, DataHandler::GAME_RESOLUTION_WIDTH/2, height);
    button_left_->SetPositionX(button_left_->GetWidth()/2);
    button_left_->SetPositionY(DataHandler::GAME_RESOLUTION_HEIGHT/2);
    button_left_->SetZOrder(0);
    scene->addChild(button_left_);
    
    popup_pause_ = GamePausePopup::create(scene_);
    FUtil::SetActiveAndVisible(popup_pause_, false);
    
    //    label_level_up_ = scene_->CreateText("levelup", "-1337", DataHandler::GAME_RESOLUTION_WIDTH/2, DataHandler::GAME_RESOLUTION_HEIGHT/2,140,"Qarmic sans Abridged.ttf", Color3B(0,0,0));
    
    label_level_up_ = Label::createWithTTF("", DataHandler::FONT_QUARMIC_SANS, 140);
    label_level_up_->setPosition(Vec2(DataHandler::GAME_RESOLUTION_WIDTH/2, DataHandler::GAME_RESOLUTION_HEIGHT/2));
    label_level_up_->setColor(Color3B(0,0,0));
    scene_->addChild(label_level_up_);
    FUtil::SetActiveAndVisible(label_level_up_, false);
    
    //    label_player_score_ = scene_->CreateText("playerscore", std::to_string(player_score_), 1550, 1000, 140, "Qarmic sans Abridged.ttf", Color3B(100, 100, 100));
    label_player_score_ = Label::createWithTTF(std::to_string(player_score_), DataHandler::FONT_QUARMIC_SANS, 140);
    label_player_score_->setColor(Color3B(100, 100, 100));
    label_player_score_->setPosition(Vec2( 1550, 1000));
    scene_->addChild(label_player_score_);
    
    scene->AddTickable(timeframe_);
    scene->AddTickable(timeframe_animation_);
    scene->AddTickable(timeframe_animation_2_);
    scene->AddTickable(timeframe_state_);
    scene->AddTickable(state_machine_);
    
    state_machine_.Register(STATE_RUNNING, this, &InGameController::OnStateRunning);
    state_machine_.Register(STATE_GAME_OVER, this, &InGameController::OnStateGameOver);
    state_machine_.Register(STATE_LEVEL_UP, this, &InGameController::OnStateLevelUp);
    state_machine_.Register(STATE_PAUSED, this, &InGameController::OnStatePaused);
    state_machine_.Register(STATE_POPUP_MENU, this, &InGameController::OnStatePopupMenu);
    state_machine_.Register(STATE_EXIT, this, &InGameController::OnStateExit);
    state_machine_.Register(STATE_IDLE, this, &InGameController::OnStateIdle);
    
    //BACKGROUND AUDIO LOOP
    DataHandler::game_audio->playBackgroundMusic(DataHandler::MUSIC_BIRDS_ENVIRONMENT,true);
    
    timeframe_.Start(milliseconds(3000));
    state_machine_.SetState(STATE_RUNNING);


}

InGameController::~InGameController()
{
}

void InGameController::OnEnter()
{
}

void InGameController::OnStateRunning(float delta)
{
	if (AdmobHelper::wasTryShareCalled) {
		AdmobHelper::wasTryShareCalled = false;
	}
	

    if (timeframe_.IsRunning())
    {
        return;
    }
    else if(timeframe_.WasRunning())
    {
        ai_.GenearteNewDropTimer(drop_object_speed_min_,drop_object_speed_max_,drop_interval_min_,drop_interval_max_);
    }
    
    else if(button_right_->IsPressed())
    {
        if(basket_->getPositionX() < (DataHandler::GAME_RESOLUTION_WIDTH-25)) //25 hardcodet half of basket size
        {
            basket_->setPositionX(basket_->getPositionX() + DataHandler::COLLECT_GAME_BASKET_SPEED);
        }
    }
    else if (button_left_->IsPressed())
    {
        if(basket_->getPositionX() > (0+25)) //25 hardcodet half of basket size
        {
            basket_->setPositionX(basket_->getPositionX() - DataHandler::COLLECT_GAME_BASKET_SPEED);
        }
    }
    
    ai_.Movement(squirrel_speed_,drop_object_speed_min_,drop_object_speed_max_,drop_interval_min_,drop_interval_max_,hazelnut_speed_);
    
    //COLLISION
    if(basket_collision_box_.OnBeginOverlap())
    {
        if(!basket_collision_box_.GetObject()->IsDead())
        {
            AIDropObject* drop_object_ = basket_collision_box_.GetObject();
            EDropObjectType type = drop_object_->GetType();
            
            if(type == EDropObjectType::HAZELNUT)
            {
                DataHandler::game_audio->playEffect(DataHandler::SOUND_OTHER_1, false, 1.0f, 1.0f, 1.0f);
                player_score_ += (DataHandler::COLLECT_GAME_HAZELNUT_POINTS * level_score_multiplier_);
            }
            else if(type == EDropObjectType::WASTE)
            {
                DataHandler::game_audio->playEffect(DataHandler::SOUND_PAPER_WAD, false, 1.0f, 1.0f, 1.0f);
                player_lives_--;
                scene_->subject_.Notify(EEvent::EVENT_WASTES_COLLECTED);
            }
            else if(type == EDropObjectType::APPLE)
            {
                DataHandler::game_audio->playEffect(DataHandler::SOUND_APPLE_BITE, false, 1.0f, 1.0f, 1.0f);
                player_score_ += (DataHandler::COLLECT_GAME_APPLE_POINTS * level_score_multiplier_);

                scene_->subject_.Notify(EEvent::EVENT_APPLE_COLLECTED);
            }
            else if(type == EDropObjectType::HEART)
            {
                DataHandler::game_audio->playEffect(DataHandler::SOUND_HEART_COLLECT, false, 1.0f, 1.0f, 0.7);
                if (player_lives_ < DataHandler::COLLECT_GAME_PLAYER_LIVES_MAX)
                {
                    player_lives_++;
                }
                ai_.DecreaseHeartCounter();
                
#pragma message WARN("performancep problems with particlesystem?")
                
                ParticleSystemQuad* psq = ParticleSystemQuad::createWithTotalParticles(999);
                psq->setEmitterMode(ParticleSystem::Mode::GRAVITY);
                
                psq->setTexture(Director::getInstance()->getTextureCache()->addImage(DataHandler::TEXTURE_COLLECT_GAME_HEART));
                psq->setZOrder(-1);
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
                
                basket_->addChild(psq);
                
                scene_->subject_.Notify(EEvent::EVENT_HEART_COLLECTED);
                
            }
            else if(type == EDropObjectType::COIN)
            {
                DataHandler::game_audio->playEffect(DataHandler::SOUND_COIN_COLLECT, false, 1.0f, 1.0f, 1.0f);
                player_score_ += (DataHandler::COLLECT_GAME_COIN_POINTS * level_score_multiplier_);
                
                scene_->subject_.Notify(EEvent::EVENT_COIN_COLLECTED);
            }
            
            
            basket_collision_box_.RemoveObject();
            
            //if overlap check if player advances to a new level
            lvl_system_.LevelControl(player_score_);
            lvl_system_.GetLevelSettings(squirrel_speed_, drop_object_speed_min_, drop_object_speed_max_,
                                         drop_interval_min_, drop_interval_max_, level_score_multiplier_,
                                         drop_c_hazelnut_, drop_c_waste_, drop_c_apple_, drop_c_heart_, drop_c_coin_,hazelnut_speed_);
            
            ai_.SetDropChance(drop_c_hazelnut_, drop_c_waste_, drop_c_apple_, drop_c_heart_, drop_c_coin_);
            
            if(lvl_system_.OnLevelUp())
            {
                ai_.ActivateHeartDrop();
                
                label_level_up_->setPosition(Vec2(-300,DataHandler::GAME_RESOLUTION_CENTER_HEIGHT));
                scene_->SetActiveAndVisible(label_level_up_,true);
                label_level_up_->setString("LEVEL "+std::to_string(lvl_system_.GetLevel()));
                
                MoveTo* anim_move = MoveTo::create(1.0,DataHandler::GAME_RESOLUTION_CENTER);
                label_level_up_->runAction(anim_move);

				squirrel_->setTexture(Director::getInstance()->getTextureCache()->addImage(DataHandler::TEXTURE_COLLECT_GAME_SQUIRREL_ANGRY));
				squirrel_->setTextureRect(Rect(0, 0, 104,140));
                
                //timeframe_animation_.Start(milliseconds(3000));
                
                DataHandler::game_audio->playEffect(DataHandler::SOUND_LEVEL_UP, false, 1.0f, 1.0f, 0.3f);
                
                timeframe_state_.Start(milliseconds(2000), this, &InGameController::MoveOutLevelUp);

                scene_->subject_.Notify(EEvent::EVENT_LEVEL_UP);
                state_machine_.SetState(STATE_LEVEL_UP);
            }
        }
    }
    
    if(ai_.GetHitGroundCounter() != 0)
    {
        player_lives_ -= ai_.GetHitGroundCounter();
        
        if(player_lives_ <= 0)
        {
            player_lives_ = 0;
        }
    }
    
    if(player_lives_ <= 0)
    {
        
#ifndef PERFORMANCETEST
        
        //remove all existing dropobjects from the screen
        for(int i = 0; i < ai_.GetDropObjects().size();i++)
        {
            ai_.GetDropObjects().at(i)->Remove();
        }
        
        //        scene_->CreateText("gameover", "GAME OVER", DataHandler::GAME_RESOLUTION_WIDTH / 2, DataHandler::GAME_RESOLUTION_HEIGHT / 2 + 100,100,"Qarmic sans Abridged.ttf",Color3B(100,100,100));
        Label* text_game_over = Label::createWithTTF("GAME OVER", DataHandler::FONT_QUARMIC_SANS, 100);
        text_game_over->setColor(Color3B(100,100,100));
        text_game_over->setPosition(Vec2(DataHandler::GAME_RESOLUTION_WIDTH / 2, DataHandler::GAME_RESOLUTION_HEIGHT / 2 + 150));
        scene_->addChild(text_game_over);
        
        
        //        scene_->CreateText("gameover_highscore", "Score: " + std::to_string(player_score_), DataHandler::GAME_RESOLUTION_WIDTH/2, DataHandler::GAME_RESOLUTION_HEIGHT/2 - 20, 80, "Qarmic sans Abridged.ttf", Color3B(255,255,255));
        
        Label* text_end_score = Label::createWithTTF("Score: " + std::to_string(player_score_), DataHandler::FONT_QUARMIC_SANS, 80);
        text_end_score->setPosition(Vec2(DataHandler::GAME_RESOLUTION_WIDTH/2, DataHandler::GAME_RESOLUTION_HEIGHT/2 + 60));
        text_end_score->setColor(Color3B(255,255,255));
        scene_->addChild(text_end_score);
        
        FSprite* buttonSpriteRegister = FSprite::create(DataHandler::TEXTURE_COLLECT_GAME_BUTTON_REGISTER);
        buttonRegister = FrameworkButton::create(scene_, 700, 100, buttonSpriteRegister);
        buttonRegister->SetPositionX(DataHandler::GAME_RESOLUTION_WIDTH / 2);
        buttonRegister->SetPositionY(DataHandler::GAME_RESOLUTION_HEIGHT / 2 - 175);
        buttonRegister->SetZOrder(2);
        scene_->addChild(buttonRegister);
        
        tfeUsername = TextFieldExtended::create("Input username", DataHandler::FONT_QUARMIC_SANS
                                                , 46
                                                , Vec2(scene_->getContentSize().width / 2.0f
                                                       , buttonRegister->GetTop() + 90)
                                                , 1.0);
        scene_->addChild(tfeUsername, 1);

		FSprite* buttonSpriteShareScore = FSprite::create(DataHandler::TEXTURE_COLLECT_GAME_BUTTON_SHARE_SCORE);
		buttonShareScore = FrameworkButton::create(scene_, 700, 100, buttonSpriteShareScore);
		buttonShareScore->SetPositionX(DataHandler::GAME_RESOLUTION_WIDTH / 2);
		buttonShareScore->SetPositionY(DataHandler::GAME_RESOLUTION_HEIGHT / 2 - 300);
		buttonShareScore->SetZOrder(2);
		scene_->addChild(buttonShareScore);
        
        FSprite* buttonSpriteRetry = FSprite::create(DataHandler::TEXTURE_COLLECT_GAME_BUTTON_RETRY);
        buttonRetry = FrameworkButton::create(scene_, 700, 120, buttonSpriteRetry);
        buttonRetry->SetPositionX(DataHandler::GAME_RESOLUTION_WIDTH / 2);
        buttonRetry->SetPositionY(DataHandler::GAME_RESOLUTION_HEIGHT / 2 - 425);
        buttonRetry->SetZOrder(2);
        scene_->addChild(buttonRetry);
        
        scene_->subject_.Notify(EEvent::EVENT_GAME_OVER);
        state_machine_.SetState(STATE_GAME_OVER);
        
#endif
    }
    
    UpdateTextAndLives();
}

void InGameController::OnStatePaused(float delta)
{
}

void InGameController::OnStateIdle(float delta)
{
    //DO NOTHING!
}

void InGameController::OnStateGameOver(float delta)
{
    if(!AdmobHelper::isAdScreenShowing){
        AdmobHelper::showAdScreen();
    }
    
    
#pragma message WARN("DELAY NOT NEEDED?")
    
	std::string strUsername = FUtil::trim(tfeUsername->GetTextFieldValue());
    if (buttonRetry != NULL && buttonRetry->WasPressed())
    {
        DataHandler::game_audio->playEffect(DataHandler::SOUND_BUTTON_1);
        DataHandler::game_audio->stopBackgroundMusic();
        
        
        scene_->ReloadGame();
        
        state_machine_.SetState("");
        
        AdmobHelper::hideAdScreen();
    }
    else if (!strUsername.empty() && FUtil::containsNoSpecialCharacters(strUsername) && buttonRegister != NULL && buttonRegister->WasPressed())
    {
        DataHandler::game_audio->playEffect(DataHandler::SOUND_BUTTON_1);
        
        DataHandler::game_audio->stopBackgroundMusic();
        
        
        std::string newHighscoreEntry = tfeUsername->GetTextFieldValue() + ":" + std::to_string(player_score_);
        scene_->LoadHighscoreMenu(newHighscoreEntry);
        
#pragma message WARN("SHOULD BE DONE AUTOMATICALLY WHEN LEAVING THE SCENE, UNLOAD EVERYTHING IN THE SCENE")
#pragma message WARN("USE LOADER FOR UNLOADING SOUND")
        //unload sound
        DataHandler::game_audio->unloadEffect(DataHandler::SOUND_APPLE_BITE);
        DataHandler::game_audio->unloadEffect(DataHandler::SOUND_OTHER_1);
        //        DataHandler::game_audio->unloadEffect("sound/sound_heart.mp3");
        DataHandler::game_audio->unloadEffect(DataHandler::SOUND_PAPER_WAD);
        
        DataHandler::game_audio->stopBackgroundMusic();
        
        state_machine_.SetState(STATE_IDLE);
        
        AdmobHelper::hideAdScreen();
    }
	else if (buttonShareScore != NULL && buttonShareScore->WasPressed())
	{
		AdmobHelper::tryShareScore(player_score_);
	}
}

void InGameController::OnStateLevelUp(float delta)
{
    if(timeframe_animation_.WasRunning())
    {
        timeframe_animation_2_.Start(milliseconds(2000));
    }
}

void InGameController::OnStatePopupMenu(float delta)
{
    if(popup_pause_->WasClosed())
    {
        ai_.GenearteNewDropTimer(drop_object_speed_min_,drop_object_speed_max_,drop_interval_min_,drop_interval_max_);
        CCLOG("POPUP WAS CLOSED()");
        CCLOG("PREVSTATE=%s",state_machine_.GetPreviousState().c_str());
        state_machine_.SetState(state_machine_.GetPreviousState());
    }
    else if(popup_pause_->GetExit())
    {
        Loader loader;
        loader.UnloadCollectGame();
        loader.LoadMenu();
        
        scene_->onEnterTransitionDidFinish();
        
        state_machine_.SetState("");
    }
}

void InGameController::OnStateExit(float delta)
{
    DataHandler::game_audio->stopBackgroundMusic();
    scene_->LoadMenu();
    
#pragma message WARN("SHOULD BE DONE AUTOMATICALLY")
    //unload sound
    DataHandler::game_audio->unloadEffect(DataHandler::SOUND_APPLE_BITE);
    DataHandler::game_audio->unloadEffect(DataHandler::SOUND_OTHER_1);
    //    DataHandler::game_audio->unloadEffect("sound/sound_heart.mp3");
    DataHandler::game_audio->unloadEffect(DataHandler::SOUND_PAPER_WAD);
    
    state_machine_.SetState(STATE_IDLE);
}

void InGameController::Tick(float delta)
{
    if(button_menu_->WasPressed())
    {
        if(state_machine_.GetCurrentState() != STATE_POPUP_MENU)
        {
            popup_pause_->Show();
            state_machine_.SetState(STATE_POPUP_MENU);
        }
    }
    
    CloudMovement();
    BirdMovement();
}

void InGameController::UpdateTextAndLives()
{
    if(player_score_ != prev_player_score_)
    {
        label_player_score_->setString(std::to_string(player_score_));
        prev_player_score_ = player_score_;
    }
    
    if(player_lives_ != prev_player_lives_)
    {
        UpdateLiveBar();
    }
}

void InGameController::GenerateLiveBar()
{
    //init player live sprites , which are not part of the world objects
    for (int i = 0; i < DataHandler::COLLECT_GAME_PLAYER_LIVES_MAX; i++)
    {
        FSprite* sprite = FSprite::create(DataHandler::TEXTURE_COLLECT_GAME_HEART, FUtil::GenerateETC1AlphaString(DataHandler::TEXTURE_COLLECT_GAME_HEART));
        
        sprite->setAnchorPoint(Vec2(0.5, 0.5));
        sprite->setPosition(70 + (i * 102), (DataHandler::GAME_RESOLUTION_HEIGHT / 2) + 470);
        live_bar_player_lives_.push_back(sprite);
        scene_->addChild(sprite);
        
#ifdef ETC1
        //        //Shader
        //        GLProgram* glp = new GLProgram();
        //
        //        glp->initWithVertexShaderFilename("testv.vsh", "test.fsh");
        //        glp->addAttribute(GLProgram::ATTRIBUTE_NAME_POSITION, GLProgram::VERTEX_ATTRIB_POSITION);
        //        glp->addAttribute(GLProgram::ATTRIBUTE_NAME_COLOR, GLProgram::VERTEX_ATTRIB_COLOR);
        //        glp->addAttribute(GLProgram::ATTRIBUTE_NAME_TEX_COORD, GLProgram::VERTEX_ATTRIB_TEX_COORD);
        //        glp->link();
        //        glp->updateUniforms();
        //
        //        Texture2D* tex = Director::getInstance()->getTextureCache()->addImage("Heart_alpha.pkm");
        //
        //        GL::bindTexture2DN(1, tex->getName());
        //
        //        //button_sprite_menu_popup->setBlendFunc(BlendFunc::DISABLE);
        //
        //
        //        live_bar_player_lives_[i]->setBlendFunc((ccBlendFunc) { GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA });
        //
        //        GLuint t1Location = glGetUniformLocation(glp->getProgram(), "tex1");
        //        //    GLuint t2Location = glGetUniformLocation(glp->getProgram(), "tex2");
        //
        //
        //
        //        glp->setUniformLocationWith1i(t1Location, 1);
        //        //    glp->setUniformLocationWith1i(t2Location, 0);
        //
        //
        //        live_bar_player_lives_[i]->setShaderProgram(glp);
#endif
        
    }
}

void InGameController::UpdateLiveBar()
{
    //PlayerLive objects which are not used are a little bit transparent
    for (int i = 0; i < DataHandler::COLLECT_GAME_PLAYER_LIVES_MAX; i++)
    {
        (i < player_lives_) ? live_bar_player_lives_[i]->setOpacity(255) : live_bar_player_lives_[i]->setOpacity(90);
    }
}

void InGameController::MoveOutLevelUp()
{
    MoveTo* anim_level_up = MoveTo::create(1.0, Vec2(DataHandler::GAME_RESOLUTION_WIDTH + 400, DataHandler::GAME_RESOLUTION_CENTER_HEIGHT));
    label_level_up_->runAction(anim_level_up);
    
    timeframe_state_.Start(milliseconds(2000), this, &InGameController::LevelUpEnd);
}

void InGameController::LevelUpEnd()
{
	squirrel_->setTexture(Director::getInstance()->getTextureCache()->addImage(DataHandler::TEXTURE_COLLECT_GAME_SQUIRREL));
	squirrel_->setTextureRect(Rect(0, 0, 
		104,		
		140));


    if (state_machine_.GetCurrentState() == STATE_POPUP_MENU)
    {
        state_machine_.SetState(STATE_RUNNING);
        state_machine_.SetState(STATE_POPUP_MENU);
    }
    else
    {
        state_machine_.SetState(STATE_RUNNING);
    }
}

void InGameController::CloudMovement()
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

void InGameController::BirdMovement()
{
    if (sprite_anim_bird->getPosition().x >= DataHandler::GAME_RESOLUTION_CENTER_WIDTH + 1150)
    {
        sprite_anim_bird->setPositionX(DataHandler::GAME_RESOLUTION_CENTER_WIDTH - 1150);
        sprite_anim_bird->setPositionY(DataHandler::GAME_RESOLUTION_CENTER_HEIGHT - 300 + RandomHelper::random_int(0, 600));
        MoveTo* move = MoveTo::create(RandomHelper::random_int(15,30), Vec2(DataHandler::GAME_RESOLUTION_CENTER_WIDTH + 1150, sprite_anim_bird->getPosition().y));
        sprite_anim_bird->runAction(move);
    }
    if (sprite_anim_bird1->getPosition().x <= DataHandler::GAME_RESOLUTION_CENTER_WIDTH - 1150)
    {
        sprite_anim_bird1->setPositionX(DataHandler::GAME_RESOLUTION_CENTER_WIDTH + 1150);
        sprite_anim_bird1->setPositionY(DataHandler::GAME_RESOLUTION_CENTER_HEIGHT - 300 + RandomHelper::random_int(0, 600));
        MoveTo* move = MoveTo::create(RandomHelper::random_int(15, 30), Vec2(DataHandler::GAME_RESOLUTION_CENTER_WIDTH - 1150, sprite_anim_bird1->getPosition().y));
        sprite_anim_bird1->runAction(move);
    }
}
