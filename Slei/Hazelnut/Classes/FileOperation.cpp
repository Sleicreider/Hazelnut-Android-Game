#define COCOS2D_DEBUG 1

#include "cocos2d.h"
#include "FileOperation.h"
#include <sstream>
#include <iostream>
#include <fstream>

using namespace std;

const std::string FileOperation::FILE_SAVED_DATA = "haz_saved";
const std::string FileOperation::FiLE_DATA_TABLE = "tmpfile";

void FileOperation::saveFile(std::vector<HighscoreScene::GameUser>& userData)
{
    string path = getFilePath(FiLE_DATA_TABLE);
    FILE *fp = fopen(path.c_str(), "w");
    
    if (! fp)
    {
        CCLOGERROR("can not create file %s", path.c_str());
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
    auto check = [&](const std::string& filename)
    {
#pragma message WARN("create file")
        string path = getFilePath(filename);
        FILE *fp = fopen(path.c_str(), "r+b");
        
        bool fileExists = false;
        
        if (!fp)
        {
            CCLOGERROR("can not open file %s... will create file", path.c_str());
            fileExists = false;
        }
        else
        {
            CCLOGERROR("can open file %s... will NOT create file", path.c_str());
            fileExists = true;
			fclose(fp);
        }
        
       
        
        if (!fileExists)
        {
            FILE *fp = fopen(path.c_str(), "w+b");
            
            if (!fp)
            {
                CCLOGERROR("can not create file %s", path.c_str());
                return;
            }
            
            fputs("", fp);
            
            fclose(fp);
        }
    };
    
    check(FILE_SAVED_DATA);
    check(FiLE_DATA_TABLE);
}

std::string FileOperation::readFile()
{
    string path = getFilePath(FiLE_DATA_TABLE);
    FILE *fp = fopen(path.c_str(), "r");
    char buf[250] = {0};
    
    if (! fp)
    {
        CCLOGERROR("can not open file %s", path.c_str());
        return "error";
    }
    
    
    
    fgets(buf, 250, fp);
    CCLOGERROR("read content %s", buf);
    
    fclose(fp);
    std::string str(buf);
    return str;
}

std::string FileOperation::getFilePath(const std::string& filename)
{
    string path("");
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    // In android, every programe has a director under /data/data.
    // The path is /data/data/ + start activity package name.
    // You can save application specific data here.
    path.append("/data/data/com.Slei.Hazelnut/files/"+filename);
#endif
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
    // You can save file in anywhere if you have the permision.
    path.append("D:/"+filename);
#endif
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
    path.append("/Users/dreis/"+filename);
#endif
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WOPHONE)
    path = cocos2d::CCApplication::sharedApplication().getAppDataPath();
    
#ifdef _TRANZDA_VM_
    // If runs on WoPhone simulator, you should insert "D:/Work7" at the
    // begin. We will fix the bug in no far future.
    path = "D:/Work7" + path;
    path.append(filename);
#endif
    
#endif
    
    CCLOGERROR("path is %s", path.c_str());
    
    return path;
}

bool FileOperation::GetInt(const std::string& tag, int& in_val)
{
    auto path = std::string{ getFilePath(FILE_SAVED_DATA) };
    auto fp = fopen(path.c_str(), "r");
    
    char line[255];
    
    
    
    
    if(fp == nullptr)
    {
        CCLOGERROR("failed to open file  FileOperation::GetInt LINE=%d",__LINE__);
        return -1;
    }
    
    
    while(fgets(line, 255, fp))
    {
        int linesize = 0;
        for(auto i = 0; i < 255; i++)
        {
            if(line[i] == '\0')
            {
                linesize = i;
                break;
            }
        }
        
        stringstream ss(line);
        
        std::string first;
        
        ss >> first;
        
        if(first == tag)
        {
            int pos = 0;
            for(auto i = 0lu; i < 255; i++)
            {
                if(line[i] == '=')
                {
                    // '=' + space == i+2
                    pos = i+2;
                    break;
                }
            }
            
            std::string str = line;
            str = str.substr(pos, linesize);
            
            in_val = std::stoi(str);
            
            return true;
        }
        
    }
    return false;
}

bool FileOperation::SetInt(const std::string& tag, int val)
{
#pragma message WARN("write if not already in file!!")
    auto path = std::string { getFilePath(FILE_SAVED_DATA) };
    auto fp = fopen(path.c_str(), "r+");
    
    char line[255];
    
    if(fp == nullptr)
    {
        CCLOGERROR("failed to open file  FileOperation::GetInt LINE=%d",__LINE__);
        return -1;
    }
    
    //rewrite full file
    // WORKS
    std::vector<std::string> comp_file;
    
	auto bAvailable = false;

    while(fgets(line, 255, fp))
    {
        stringstream ss (line);
        std::string first;
        ss >> first;
        
        if(first == tag)
        {
			bAvailable = true;

            for(int i = 0; i < 255; i++)
            {
                if(line[i] == '=')
                {
                    std::string tmp = line;
                    tmp = tmp.substr(0, i+2);
                    tmp += std::to_string(val);
                    tmp += "\n";
                    comp_file.push_back(tmp);
                    break;
                }
            }
            
            std::cout << "write: " << comp_file[comp_file.size()-1] << std::endl;
        }
        else
        {
            comp_file.push_back(line);
        }
    }

	if (!bAvailable)
	{
		comp_file.push_back(tag + " = " + std::to_string(val) + "\n");
	}
    
    fclose(fp);
    
    fp = fopen(path.c_str(), "w");
    
    for(auto i = 0lu ; i < comp_file.size(); i++)
    {
        fputs(comp_file[i].c_str(),fp);
    }
    
    fclose(fp);
    
    return true;
}

bool FileOperation::FileAvailable(const std::string& filename)
{
#pragma message WARN("create file")
	string path = getFilePath(filename);
	FILE *fp = fopen(path.c_str(), "r+b");

	bool fileExists = false;

	if (!fp)
	{
		CCLOGERROR("can not open file %s... will create file", path.c_str());
		fileExists = false;
	}
	else
	{
		CCLOGERROR("can open file %s... will NOT create file", path.c_str());
		fileExists = true;
		fclose(fp);
	}
	return fileExists;
}
