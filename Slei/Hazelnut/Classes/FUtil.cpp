//
//  FUtil.cpp
//  Hazelnut
//
//  Created by Dominik Reisner on 19.06.15.
//
//

#include "FUtil.h"

void FUtil::SetActiveAndVisible(Node* node, bool active_and_visible)
{
    if(node == nullptr) { CCLOGERROR("SetActiveAndVisible didn't work, node is a nullptr"); return; }
   
    NodeRecursion(node, active_and_visible);

}

void FUtil::NodeRecursion(Node* node, bool active_and_visible)
{
    if(!active_and_visible)
    {
        node->pause();
        node->setVisible(false);
    }
    else
    {
        node->resume();
        node->setVisible(true);
    }
    
    auto& children = node->getChildren();
    for (size_t i = 0; i < children.size(); i++)
    {
        NodeRecursion(children.at(i), active_and_visible);
    }
}
