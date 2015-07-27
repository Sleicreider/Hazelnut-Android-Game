//
//  AIDropObject.cpp
//  Hazelnut
//
//  Created by Dominik Reisner on 13.11.14.
//
//

#include "AIDropObject.h"
#include "InGameScene.h"
#include "DataHandler.h"

#include "FUtil.h"

AIDropObject::AIDropObject(FrameworkScene* scene)
: scene(scene)
{
}

void AIDropObject::CreateDropObject()
{
    std::string fileName;
    
    if(dropObjectType == EDropObjectType::HAZELNUT)
    {
        fileName = DataHandler::TEXTURE_COLLECT_GAME_HAZELNUT;
    }
    else if(dropObjectType == EDropObjectType::WASTE)
    {
        fileName = DataHandler::TEXTURE_COLLECT_GAME_WASTE;
    }
    else if(dropObjectType == EDropObjectType::APPLE)
    {
        fileName = DataHandler::TEXTURE_COLLECT_GAME_APPLE;
    }
    else if(dropObjectType == EDropObjectType::HEART)
    {
        fileName = DataHandler::TEXTURE_COLLECT_GAME_HEART;
    }
    else if(dropObjectType == EDropObjectType::COIN)
    {
        fileName = DataHandler::TEXTURE_COLLECT_GAME_COIN;
    }
    
    //Position at when object is created
    dropObject = FSprite::create(fileName, FUtil::GenerateETC1AlphaString(fileName));
    dropObject->setAnchorPoint(Vec2(0.5,0.5));
    dropObject->setPositionY(DataHandler::COLLECT_GAME_SQUIRREL_POSY_START);
    dropObject->setZOrder(1);
    
    //if(dropObjectType == EDropObjectType::WASTE)
    //dropObject->setScale(3,3);
    
    //FSprite test;


    scene->addChild(dropObject);
}

bool AIDropObject::GroundCollision()
{
	if(dropObject->getPositionY() <= 0)
	{
		return true;
	}
	return false;
}

void AIDropObject::Remove()
{
    scene->removeChild(dropObject);
}