//
//  GameUtil.cpp
//  Hazelnut
//
//  Created by Matthias Reisner
//
//

#include "GameUtil.h"

void GameUtil::split(const string& s, char c,vector<string>& v) 
{
	string::size_type i = 0;
	string::size_type j = s.find(c);

	while (j != string::npos) {
		v.push_back(s.substr(i, j - i));
		i = ++j;
		j = s.find(c, j);

		if (j == string::npos)
			v.push_back(s.substr(i, s.length()));
	}
}

bool GameUtil::cmd(const HighscoreScene::GameUser& struct1, const HighscoreScene::GameUser& struct2)
{
	return (struct1.points < struct2.points);
}

void GameUtil::SortUser(std::vector<HighscoreScene::GameUser>& userData)
{
    std::sort(userData.begin(), userData.end(), cmd);
}
