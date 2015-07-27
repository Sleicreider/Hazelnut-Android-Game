#include "FrameworkScene.h"
#include "FrameworkButton.h"

FrameworkScene* FrameworkButton::scene_ = nullptr;


FrameworkScene::FrameworkScene()
: bTouchHappened_(false)
, active_button_(nullptr)

, touch_x_(0)
, touch_y_(0)

, bReleaseHappened_(false)
, bWasPressed_(false)

, higher_z_order_(-1)
, curr_target_z_order_(-1)

, bButtonClick_(false)

, delayControlEnabled(true)
, sumDelta(0)

{
    vec_buttons_.clear();
    
    initDelayControl();
    
    auto listener = EventListenerTouchOneByOne::create();
    
    listener->onTouchBegan = CC_CALLBACK_2(FrameworkScene::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(FrameworkScene::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(FrameworkScene::onTouchEnded, this);
    listener->onTouchCancelled = CC_CALLBACK_2(FrameworkScene::onTouchCancelled, this);
    
    auto dispatcher = this->getEventDispatcher();
    dispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    this->scheduleUpdate();
}

FrameworkScene::~FrameworkScene()
{
//    for(int i = 0; i < vec_buttons_.size();i++)
//    {
//        delete vec_buttons_.at(i);
//    }
    vec_buttons_.clear();
}

void FrameworkScene::initDelayControl()
{
    sumDelta = 0;
}

bool FrameworkScene::isDelayControlEnabled()
{
    return delayControlEnabled;
}

void FrameworkScene::setDelayControlEnabled(bool value)
{
    delayControlEnabled = value;
}

bool FrameworkScene::updateDelayControl(float delta, float checkpoint){
    if (delayControlEnabled)
    {
        sumDelta += delta;
        
        if (sumDelta > checkpoint) {
            // reset sumDelta
            initDelayControl();
            
            return true;
        }
    }
    
    return false;
}

void FrameworkScene::update(float delta)
{
    /*********************/
    /****** Buttons ******/
    /*********************/
    UpdateButtons();
    
    /*********************/
    /***** Timeframe *****/
    /*********************/
    for(int i = 0; i < vec_tickables_.size(); i++)
    {
        if(vec_tickables_[i] != nullptr)
        {
            vec_tickables_[i]->Tick(delta);
        }
        else
        {
            CCLOGERROR("Timeframe %d in scene container is a nullptr could not Tick() FrameworkScene::update(float delta) LINE=%d",i,__LINE__);
        }
    }

    /*********************/
    /***** Child Tick ****/
    /*********************/
    Tick(delta);
}

void FrameworkScene::Tick(float delta)
{
}

void FrameworkScene::UpdateButtons()
{
	//active_button_ was sometimes NULL before it came to if(bReleaseHappened_)
	//maybe cocos button dispatcher change bRealeaseHappen to true straight after if(bWAsPressed)
	//therefore && !bReleaseHappened to make sure it cant make it a null p
	if (bWasPressed_ && bReleaseHappened_)
	{
		CCLOG("bWasPressed && bReleasesdHappened HERE<<<<<<<<<<<<<<<<<<<<<<<<<");
		//throw;
	}

	if (bWasPressed_ && !bReleaseHappened_)
    {
        bWasPressed_ = false;
        active_button_->SetWasPressed(false);
        active_button_ = nullptr;
        higher_z_order_ = -1;
    }
    
    if (bTouchHappened_)
    {
        for (int i = 0; i < vec_buttons_.size(); i++)
        {
            if(vec_buttons_.at(i)->IsActive())
            {
                if (touch_x_ >= vec_buttons_.at(i)->GetLeft() && touch_x_ <= vec_buttons_.at(i)->GetRight() && touch_y_ <= vec_buttons_.at(i)->GetTop() && touch_y_ >= vec_buttons_.at(i)->GetBottom())
                {
                    curr_target_z_order_ = vec_buttons_.at(i)->GetZOrder();
                    
                    if(curr_target_z_order_ > higher_z_order_)
                    {
                        if(active_button_ != nullptr)
                        {
                            active_button_->SetIsPressed(false); //Make sure to set last lower button false
                        }
                        
#pragma message WARN("TODO: active button should only be set if it is really the button with the highest z order")
                        active_button_ = vec_buttons_.at(i);
                        higher_z_order_ = curr_target_z_order_;
                        
#pragma message WARN("TODO: should be only true if it is really the hightst button // MAYBE NOT NEEDED")
                        bButtonClick_ = true;
                    }
                    
                }
#pragma message WARN("TODO: Test with mutliple overlapping Buttons, SetIsPressed should only be set if it is really the button with the highest z order.")
                if(bButtonClick_)
                {
                    active_button_->SetIsPressed(true);
                    bButtonClick_ = false;
                }
            }
        }
        bTouchHappened_ = false;
    }
    
    if(bReleaseHappened_ && (active_button_!= nullptr))
    {
		if (active_button_ == nullptr)
		{
			CCLOG("setispressed NULL");
		}
        active_button_->SetIsPressed(false);
		if (active_button_ == nullptr)
		{
			CCLOG("setwaspressed NULL");
		}
        active_button_->SetWasPressed(true);
		if (active_button_ == nullptr)
		{
			CCLOG("after set was pressed NULL");
		}
        bWasPressed_ = true;
        
        bReleaseHappened_ = false;
    }
}

//FrameworkButton* FrameworkScene::CreateButton(const int width,const int height, Sprite* sprite)
//{
//    FrameworkButton* bt = FrameworkButton::create(this, width, height, sprite);//new FrameworkButton(width, height, sprite);
//    
//#ifdef BUTTON_RECT
//    DrawNode* rectangle = DrawNode::create();
//    Vec2 vertices[] =
//    {
//        Vec2(-(width/2),height/2),
//        Vec2(width/2,height/2),
//        Vec2(width/2,-(height/2)),
//        Vec2(-(width/2),-(height/2))
//    };
//    rectangle->drawPolygon(vertices, 4, Color4F(1.0f,0.3f,0.3f,0.5f), 3, Color4F(0.2f,0.2f,0.2f,0.5f));
//    this->addChild(rectangle);
//    
//    bt->SetRect(rectangle);
//#endif
//    
////    if(sprite != nullptr)
////    {
////        this->addChild(sprite);
////    }
//    
//    addChild(bt);
//    
////    vec_buttons_.push_back(bt);
//    
//    return vec_buttons_.back();
//}


bool FrameworkScene::onTouchBegan(Touch* touch, Event* event)
{
    touch_x_ = touch->getLocation().x;
    touch_y_ = touch->getLocation().y;
    
    bTouchHappened_ = true;
    
    return true;
}

void FrameworkScene::onTouchMoved(Touch* touch, Event* event)
{
}

void FrameworkScene::onTouchEnded(Touch* touch, Event* event)
{
	if (active_button_ != nullptr)
	{
		bReleaseHappened_ = true;
	}
}

void FrameworkScene::onTouchCancelled(Touch* touch, Event* event)
{
	if (active_button_ != nullptr)
	{
		bReleaseHappened_ = true;
	}
}

//
//Sprite* FrameworkScene::CreateWorldObject(const std::string& id,const std::string& fileName, const Vec2& objectPosition)
//{
//    FSprite* sprite = FSprite::create(fileName);
//    sprite->setAnchorPoint(Vec2(0.5, 0.5));
//    sprite->cocos2d::Node::setPosition(objectPosition);
//    
//    map_world_objects_.insert(id, sprite);
//    
//    this->addChild(sprite);
//    
//    return sprite;
//}

//Label* FrameworkScene::CreateText(const std::string& id, const std::string& text, const float posX, const float posY, const int fontSize,const std::string& ttfFile,const Color3B& color)
//{
//    if(map_texts_.find(id) != map_texts_.end())
//    {
//        CCLOGERROR("Text already exists");
//        throw;
//        return nullptr;
//    }
//    else
//    {
//        Label* text_label = Label::createWithTTF(text,ttfFile, fontSize);
//        text_label->setAnchorPoint(Vec2(0.5,0.5));
//        text_label->setPosition(posX,posY);
//        text_label->setColor(color);
//        
//        map_texts_.insert(id,text_label);
//        
//        this->addChild(text_label);
//        
//        return text_label;
//    }
//}
