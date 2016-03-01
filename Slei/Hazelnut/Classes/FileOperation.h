#ifndef __HELLOWORLD_FILE_OPERATION__
#define __HELLOWORLD_FILE_OPERATION__

#include <string>
#include "HighscoreScene.h"

class FileOperation 
{
public:
	static void saveFile(std::vector<HighscoreScene::GameUser>& userData);
	static void createFileIfNotExist();
	static std::string readFile(void);
	static std::string getFilePath();
};

#endif
