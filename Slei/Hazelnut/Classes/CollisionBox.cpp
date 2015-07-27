//
//  CollisionBox.cpp
//  Hazelnut
//
//  Created by Dominik Reisner on 25.11.14.
//
//

#include "CollisionBox.h"

CollisionBox::CollisionBox()
{
    
}

CollisionBox::~CollisionBox()
{
    
}

#pragma message WARN("CHECK IF DROPOBJECT IS COLLIEDING WITH PLAYER OBJECT SO WE DONT NEED THE FOR LOOP")
void CollisionBox::AttatchTo(Sprite* sprite,std::vector<AIDropObject>& dropObjects,std::vector<AIDropObject>& inactiveDropObjects)
{
    this->vecDropObjects = &dropObjects;
    this->inactiveDropObjects = &inactiveDropObjects;
    this->sprite = sprite;
}

bool CollisionBox::OnBeginOverlap()
{
#pragma message WARN("NO LOOP NEEDED IF EACH DROP OBECT HAS A COLLISION BOX AND CHECKS IF IT HAS SAME POS AS USER")
    for(int i = 0; i < vecDropObjects->size() ; i++)
    {
#ifdef COLLISIONBOX_1
        
        if(vecDropObjects->at(i).GetSprite()->getPositionY() <= DataHandler::TEXTURE_COLLECT_GAME_BASKET_SIZE) //only check objects which are below y = Basket height
        {
            if((vecDropObjects->at(i).GetSprite()->getPositionY() - (vecDropObjects->at(i).GetSprite()->boundingBox().size.height / 2)) <= (sprite->getPositionY() + (sprite->boundingBox().size.height/2)))
            {
                if(((vecDropObjects->at(i).GetSprite()->getPositionX() + (vecDropObjects->at(i).GetSprite()->boundingBox().size.width/2)) >= (sprite->getPositionX() - (sprite->boundingBox().size.width/2))) && ((vecDropObjects->at(i).GetSprite()->getPositionX() + (vecDropObjects->at(i).GetSprite()->boundingBox().size.height/2)) <= (sprite->getPositionX() + (sprite->boundingBox().size.width/2))))
                {
                    collidedObject = &vecDropObjects->at(i);
                    colliedIndex = i;
                    return true;
                }
                else if(((vecDropObjects->at(i).GetSprite()->getPositionX() - (vecDropObjects->at(i).GetSprite()->boundingBox().size.width/2)) <= (sprite->getPositionX() + (sprite->boundingBox().size.width/2))) && ((vecDropObjects->at(i).GetSprite()->getPositionX() - (vecDropObjects->at(i).GetSprite()->boundingBox().size.width/2)) >= (sprite->getPositionX() - (sprite->boundingBox().size.width/2))))
                {
                    collidedObject = &vecDropObjects->at(i);
                    colliedIndex = i;
                    return true;
                }
            }
        }
        //        else if(vecDropObjects->at(i).GetSprite()->getPositionY() <= 500)
        //        {
        //            collidedObject = &vecDropObjects->at(i);
        //            colliedIndex = i;
        //            return true;
        //        }
#else
        if (!outOfScreenRangeBottom(vecDropObjects->at(i).GetSprite()) && catchAble(vecDropObjects->at(i).GetSprite(), sprite, 25, 5) && collision(vecDropObjects->at(i).GetSprite(), sprite, 0, 15))
        {
            collidedObject = &vecDropObjects->at(i);
            colliedIndex = i;
            return true;
        }
#endif
    }
    return false;
    
}

void CollisionBox::RemoveObject()
{
    vecDropObjects->at(colliedIndex).SetActive(false);
    vecDropObjects->at(colliedIndex).SetPositionX(DataHandler::COLLECT_GAME_SQUIRREL_POSY_START);
    vecDropObjects->at(colliedIndex).SetPositionY(700); /**<just above Ground */
    inactiveDropObjects->push_back(std::move(vecDropObjects->at(colliedIndex)));
    
    vecDropObjects->erase(vecDropObjects->begin() + colliedIndex);
    
}


/**
 * For checking, if an object has left the range at the bottom of the
 * container
 *
 * @param gameObject
 *            that is able to drop out of container range
 * @return false if the object is in the container
 */
bool CollisionBox::outOfScreenRangeBottom(Sprite* gameObject)
{
    if (gameObject->getPositionY() + gameObject->boundingBox().size.height/2 < 0) {
        return true;
    }
    return false;
}

/**
 * check if object1 intersects completely with object2
 *
 * @param object1
 * @param object2
 * @return true if object1 completely intersects with object2
 */
bool CollisionBox::collision(Sprite* object1, Sprite* object2, int catchOffsetTop, int catchOffsetSide)
{
    if (object1->getPositionY() + object1->boundingBox().size.height/2 < object2->getPositionY() + object2->boundingBox().size.height/2 - catchOffsetTop
        && object1->getPositionY() - object1->boundingBox().size.height/2 > object2->getPositionY() - object2->boundingBox().size.height/2) {
        if (object1->getPositionX() - object1->boundingBox().size.width/2 > object2->getPositionX() - object2->boundingBox().size.width/2 - catchOffsetSide
            && object1->getPositionX() + object1->boundingBox().size.width / 2 < object2->getPositionX() + object2->boundingBox().size.width/2
            + catchOffsetSide) {
            return true;
        }
    }
    return false;
}

/**
 * Checks if the object still can be catched from the catcher object.
 *
 * @param object1
 *            that has to be catched
 * @param object2
 *            catcher
 * @param catchOffset
 *            upwards
 * @param catchOffsetSide
 *            how many pixels have to merged with catcher
 * @return true if the item can be catched; false if the item can not be
 *         catched anymore
 */
bool CollisionBox::catchAble(Sprite* object1, Sprite* object2, int catchOffset, int catchSideOffset)
{
    if ((object1->getPositionY() - object1->boundingBox().size.height/2 < object2->getPositionY() + object2->boundingBox().size.height/2 + catchOffset
         && object1->getPositionX() + object1->boundingBox().size.width/2 < object2->getPositionX() - object2->boundingBox().size.width/2 - catchSideOffset)
        || (object1->getPositionY() - object1->boundingBox().size.height/2 < object2->getPositionY() + object2->boundingBox().size.height/2 + catchOffset
            && object1->getPositionX() - object1->boundingBox().size.width/2 > object2->getPositionX() + object2->boundingBox().size.width/2 + catchSideOffset)) 
    {
        return false;
    }
    return true;
}
