#ifndef __HELLOWORLD_FILE_OPERATION__
#define __HELLOWORLD_FILE_OPERATION__

#include <string>
#include "HighscoreScene.h"

class FileOperation 
{
public:
	static void saveFile(std::vector<HighscoreScene::GameUser>& userData);
	static void createFileIfNotExist();
	static bool CreateAchievementFile();
	static std::string readFile(void);
    static std::string getFilePath(const std::string& filename);
    
    static bool GetInt(const std::string& tag, int& in_val);
    static bool SetInt(const std::string& tag, int val);

	static bool FileAvailable(const std::string& filename);

public:
    
    static const std::string FILE_SAVED_DATA;
    static const std::string FiLE_DATA_TABLE;
};

#endif
