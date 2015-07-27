//
//  FUtil.h
//  Hazelnut
//
//  Created by Dominik Reisner on 19.06.15.
//
//

#ifndef __Hazelnut__FUtil__
#define __Hazelnut__FUtil__

#include <cocos2d.h>

USING_NS_CC;

namespace FUtil
{
    void SetActiveAndVisible(Node* node, bool active_and_visible);
    void NodeRecursion(Node* node, bool active_and_visible);
    
    // changes *.pkm to *_alpha.pkm
    std::string GenerateETC1AlphaString(const std::string& filename);
};

inline std::string FUtil::GenerateETC1AlphaString(const std::string& filename)
{
    std::string alpha_filename = filename;
    alpha_filename.insert(filename.size()-4,"_alpha");
    return alpha_filename;
}

#endif /* defined(__Hazelnut__FUtil__) */
