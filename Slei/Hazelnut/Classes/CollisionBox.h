//
//  CollisionBox.h
//  Hazelnut
//
//  Created by Dominik Reisner on 25.11.14.
//
//

#ifndef __Hazelnut__CollisionBox__
#define __Hazelnut__CollisionBox__

#include <stdio.h>
#include <cocos2d.h>
#include <vector>
#include "AIDropObject.h"
#include "DataHandler.h"

USING_NS_CC;

#define COLLISIONBOX_1 //full box


class CollisionBox
{
public:
    CollisionBox();
    ~CollisionBox();
    bool OnBeginOverlap();
    void AttatchTo(Sprite* sprite,std::vector<std::unique_ptr<AIDropObject>>& dropObjects,std::vector<std::unique_ptr<AIDropObject>>& inactiveDropObjects);
    AIDropObject* GetObject();
    void RemoveObject();
    
	static bool outOfScreenRangeBottom(Sprite* gameObject);
	static bool collision(Sprite* object1, Sprite* object2, int catchOffsetTop, int catchOffsetSide);
	static bool catchAble(Sprite* object1, Sprite* object2, int catchOffset, int catchSideOffset);
    
private:
    Sprite* sprite;
    std::vector<std::unique_ptr<AIDropObject>>* vecDropObjects;
    std::vector<std::unique_ptr<AIDropObject>>* inactiveDropObjects;
    AIDropObject* collidedObject;
    int32_t colliedIndex;
};

inline AIDropObject* CollisionBox::GetObject(){ return collidedObject; }

#endif /* defined(__Hazelnut__CollisionBox__) */
