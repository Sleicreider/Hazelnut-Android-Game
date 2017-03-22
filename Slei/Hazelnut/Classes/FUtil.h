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
#include <algorithm> 
#include <functional> 
#include <cctype>
#include <locale>
#include <string>
#include <regex>

USING_NS_CC;

namespace FUtil
{
    void SetActiveAndVisible(Node* node, bool active_and_visible);
    void NodeRecursion(Node* node, bool active_and_visible);
    
    // changes *.pkm to *_alpha.pkm
    std::string GenerateETC1AlphaString(const std::string& filename);
	static std::string ltrim(std::string s);
	static std::string rtrim(std::string s);
	std::string trim(std::string s);
	static bool containsNoSpecialCharacters(std::string& s);
};

// eheck if no special charactores contained in string
static inline bool FUtil::containsNoSpecialCharacters(std::string &s) {
	std::string pattern = "[A-Za-z0-9]*";

	bool isMatching = std::regex_match(s, std::regex(pattern));

	return isMatching;
}

inline std::string FUtil::GenerateETC1AlphaString(const std::string& filename)
{
    std::string alpha_filename = filename;
    alpha_filename.insert(filename.size()-4,"_alpha");
    return alpha_filename;
}

#endif /* defined(__Hazelnut__FUtil__) */
