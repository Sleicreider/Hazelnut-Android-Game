//
//  GameUtil.h
//  Hazelnut
//
//  Created by Matthias Reisner
//
//

#ifndef __Hazelnut__GameUtil__
#define __Hazelnut__GameUtil__

#include <string>
#include <vector>
#include <functional>
#include <iostream>
#include "HighscoreScene.h"

using namespace std;

class GameUtil
{
public:
	static void split(const string& s, char c, vector<string>& v);
	static void SortUser(std::vector<HighscoreScene::GameUser>& userData);
	static bool cmd(const HighscoreScene::GameUser& struct1, const HighscoreScene::GameUser& struct2);
};

#endif /* defined(__Hazelnut__GameUtil__) */
