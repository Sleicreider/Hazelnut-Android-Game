// to enable CCLOG()
#define COCOS2D_DEBUG 1

#include "cocos2d.h"
#include "FileOperation.h"

using namespace std;

void FileOperation::saveFile(std::vector<HighscoreScene::GameUser> userData)
{
	string path = getFilePath();
	FILE *fp = fopen(path.c_str(), "w");
    
	if (! fp)
	{
		CCLOG("can not create file %s", path.c_str());
		return;
	}

	
	for (int i = 0; i < userData.size(); ++i) {
		if (i == 0){
			std::string str1 = userData[i].username + ":" + std::to_string(userData[i].points);
			fputs(str1.c_str(), fp);
		}
		else
		{
		std:string str2 = ";" + userData[i].username + ":" + std::to_string(userData[i].points);
			fputs(str2.c_str(), fp);
		}
	}

	fclose(fp);
}

void FileOperation::createFileIfNotExist()
{
	string path = getFilePath();
	FILE *fp = fopen(path.c_str(), "r");
	char buf[250] = { 0 };

	bool fileExists = false;

	if (!fp)
	{
		CCLOG("can not open file %s... will create file", path.c_str());
		fileExists = false;
	}
	else
	{
		CCLOG("can open file %s... will NOT create file", path.c_str());
		fileExists = true;
	}

	fclose(fp);

	if (!fileExists)
	{
		FILE *fp = fopen(path.c_str(), "w");

		if (!fp)
		{
			CCLOG("can not create file %s", path.c_str());
			return;
		}

		fputs("", fp);

		fclose(fp);
	}
}

std::string FileOperation::readFile()
{
	string path = getFilePath();
	FILE *fp = fopen(path.c_str(), "r");
	char buf[250] = {0};

	if (! fp)
	{
		CCLOG("can not open file %s", path.c_str());
		return "error";
	}

	fgets(buf, 250, fp);
	CCLOG("read content %s", buf);

	fclose(fp);

	return string(buf);
}

string FileOperation::getFilePath()
{
	string path("");

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	// In android, every programe has a director under /data/data.
	// The path is /data/data/ + start activity package name.
	// You can save application specific data here.
	path.append("/data/data/com.Slei.Hazelnut/files/tmpfile");
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	// You can save file in anywhere if you have the permision.
	path.append("D:/tmpfile");
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WOPHONE)
	path = cocos2d::CCApplication::sharedApplication().getAppDataPath();

#ifdef _TRANZDA_VM_
	// If runs on WoPhone simulator, you should insert "D:/Work7" at the
	// begin. We will fix the bug in no far future.
	path = "D:/Work7" + path;
	path.append("tmpfile");
#endif

#endif

	return path;
}