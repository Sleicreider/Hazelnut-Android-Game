//
// HighscoreScene.cpp
// Hazelnut
//
// Created by Matthias Reisner on 16.01.2015
//
//

#include "HighscoreScene.h"
#include <CCLabel.h>
#include "DataHandler.h"
#include "FileOperation.h"
#include "GameUtil.h"
#include "AdmobHelper.h"

const std::string HighscoreScene::BACKGROUND = "background";
const std::string HighscoreScene::TABLE_BACKGROUND = "table_bg";

void HighscoreScene::onExit()
{
	AdmobHelper::hideAd();
	
    Layer::onExit();
}

Scene* HighscoreScene::createMenuScene(std::string newHighscoreEntry)
{
    auto scene = Scene::create();
    auto layer = HighscoreScene::create();
    layer->registerHighscoreEntry(newHighscoreEntry);
    
    scene->addChild(layer);
    
    return scene;
}

bool HighscoreScene::init()
{
    if (!FrameworkScene::init())
    {
        return false;
    }
    
    //Background
    background_ = FSprite::create(DataHandler::TEXTURE_GAME_MAP_1
                                ,Vec2(DataHandler::GAME_RESOLUTION_WIDTH / 2,
                                 DataHandler::GAME_RESOLUTION_HEIGHT / 2));
    
    addChild(background_);
    
    background_->setZOrder(0);
    
    if(DataHandler::app_layout_ == EAppLayout::LAYOUT_IPAD)
    {
        Sprite* background_extension = FSprite::create(   DataHandler::TEXTURE_GAME_MAP_1_EXTENSION
                                                         ,Vec2(DataHandler::GAME_RESOLUTION_WIDTH/2,DataHandler::GAME_RESOLUTION_HEIGHT+180));
        background_extension->setScale(32, 6);
        
        addChild(background_extension);
    }
    else if(DataHandler::app_layout_ == EAppLayout::LAYOUT_DEFAULT)
    {
        FSprite* background_extension = FSprite::create( DataHandler::TEXTURE_GAME_MAP_1_EXTENSION
                                                         ,Vec2(DataHandler::GAME_RESOLUTION_WIDTH/2,DataHandler::GAME_RESOLUTION_HEIGHT+100));
        background_extension->setScale(32, 3.35);
        
        addChild(background_extension);
    }

    // Create the menu buttons
    highscore_ = FSprite::create(DataHandler::TEXTURE_HIGHSCORE_TABLE_BG
		,Vec2(DataHandler::GAME_RESOLUTION_WIDTH / 2,
		      DataHandler::GAME_RESOLUTION_HEIGHT / 2 + 25));
    
    highscore_->setZOrder(1);
    addChild(highscore_);
    
    FSprite* buttonSpriteBack = FSprite::create(DataHandler::TEXTURE_HIGHSCORE_BUTTON_BACK);
//    buttonExit = CreateButton(700, 120, buttonSpriteBack);
    buttonExit = FrameworkButton::create(this, 700, 100, buttonSpriteBack),
    buttonExit->SetPositionX(DataHandler::GAME_RESOLUTION_WIDTH / 2);
    buttonExit->SetPositionY(DataHandler::GAME_RESOLUTION_HEIGHT / 2 - 425);
    buttonExit->SetZOrder(2);
    addChild(buttonExit);
    
    calculateEntryPositions();
    loadHighscoreEntries();
    createEntryList();
	
	AdmobHelper::showAd();
    
    return true;
}

void HighscoreScene::registerHighscoreEntry(std::string newHighscoreEntry)
{
    if (newHighscoreEntry.size() < 1)
    {
        return;
    }
    
    std::vector<std::string> newHighscoreEntryString;
    struct HighscoreScene::GameUser user;
    
    GameUtil::split(newHighscoreEntry, ':', newHighscoreEntryString);
    
    user.username = newHighscoreEntryString[0];
    user.points = std::stoi(newHighscoreEntryString[1]);
    
    bool isInHighscore = false;
    for (int i = 0; i < this->userData.size(); ++i) {
        if (this->userData[i].points < user.points){
            isInHighscore = true;
            break;
        }
    }
    
    if (isInHighscore){
        this->userData[0] = user;
        GameUtil::SortUser(this->userData);
        FileOperation::saveFile(this->userData);
        
        loadHighscoreEntries();
        createEntryList();
    }
}

void HighscoreScene::calculateEntryPositions()
{
    float entryHeight = 40;
    int numberOfEntries = 10;
    
    float padding = 50;
    float headerHighscoreHeight = 60;
    float headerHighscoreEntryHeight = 0;
    
    // Highscore Panel
    float highscorePanelHeight = 700;
    float highscorePanelWidth = 700;
    float highscorePanelX = highscore_->getPositionX();
    float highscorePanelY = highscore_->getPositionY();
    
    // Highscore Content
    float contentHeight = highscorePanelHeight - (2 * padding);
    float contentWidth = highscorePanelWidth - (2 * padding);
    float contentX = (highscorePanelX - 700/2) + padding;
    float contentY = (highscorePanelY - 700/2) + padding;
    float contentHeightForEntryList = contentHeight - headerHighscoreHeight - headerHighscoreEntryHeight;
    
    // Calculate padding between each entry
    float entryPadding = (contentHeightForEntryList - (entryHeight * numberOfEntries)) / 9;
    int entryPaddingRounded = static_cast<int>(entryPadding);
    
    // Calculate Positions for all entries
    for (int i = 0; i < numberOfEntries; i++){
        float y = contentY + (i * entryHeight + i * entryPaddingRounded);
        
        Vec2 vector1(contentX, y);
        Vec2 vector2(contentX + contentWidth, y);
        this->entryPositionListName.insert(entryPositionListName.end(), std::move(vector1));
        this->entryPositionListPoint.insert(entryPositionListPoint.end(), std::move(vector2));
    }
}

void HighscoreScene::loadHighscoreEntries()
{
    this->userData.clear();
    
    std::string rawContent = FileOperation::readFile();
    
    std::vector<std::string> userDataString;
    GameUtil::split(rawContent, ';', userDataString);
    
    for (int i = 0; i < 10; ++i) {
        std::vector<std::string> userDataPartsString;
        struct HighscoreScene::GameUser user;
        
        if (userDataString.size() > i){
            GameUtil::split(userDataString[i], ':', userDataPartsString);
            
            user.username = userDataPartsString[0];
            user.points = std::stoi(userDataPartsString[1]);
        }
        else {
            user.username = "-";
            user.points = 0;
        }
        
        this->userData.insert(this->userData.begin(), user);
    }
    
    GameUtil::SortUser(this->userData);
}

void HighscoreScene::createEntryList()
{
    for (int i = 0; i < this->highscoreLabels.size(); i++)
    {
        this->removeChild(this->highscoreLabels[i]);
    }
    this->highscoreLabels.clear();
    
    for (int i = 0; i < this->entryPositionListName.size(); ++i)
    {
        if (this->userData.size() > i)
        {
            Label* l = Label::createWithSystemFont(this->userData[i].username, DataHandler::FONT_QUARMIC_SANS, 40);
            l->setAnchorPoint(Vec2(0, 0));
            l->setPositionX(this->entryPositionListName[i].x);
            l->setPositionY(this->entryPositionListName[i].y);
            l->setZOrder(2);
            this->highscoreLabels.insert(this->highscoreLabels.begin(), l);
            this->addChild(l);
            
            Label* l2 = Label::createWithSystemFont(std::to_string(this->userData[i].points), DataHandler::FONT_QUARMIC_SANS, 40);
            l2->setAnchorPoint(Vec2(1, 0));
            l2->setPositionX(this->entryPositionListPoint[i].x);
            l2->setPositionY(this->entryPositionListPoint[i].y);
            l2->setZOrder(2);
            this->highscoreLabels.insert(this->highscoreLabels.begin(), l2);
            this->addChild(l2);
        }
    }
}

void HighscoreScene::Tick(float delta)
{
    if (buttonExit->WasPressed())
    {
        DataHandler::game_audio->playEffect(DataHandler::SOUND_BUTTON_1);
        
        onEnterTransitionDidFinish();
        
        loader.UnloadHighscore();
        loader.LoadMenu();
    }
}
