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

// trim from start
std::string FUtil::ltrim(std::string s) {
	s.erase(s.begin(), std::find_if(s.begin(), s.end(),
		std::not1(std::ptr_fun<int, int>(std::isspace))));
	return s;
}

// trim from end
std::string FUtil::rtrim(std::string s) {
	s.erase(std::find_if(s.rbegin(), s.rend(),
		std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
	return s;
}

// trim from both ends
std::string FUtil::trim(std::string s) {
	return FUtil::ltrim(rtrim(s));
}
