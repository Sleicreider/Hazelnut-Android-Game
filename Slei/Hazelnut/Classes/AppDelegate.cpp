#include "AppDelegate.h"
#include "MenuScene.h"
#include "FileOperation.h"
#include "DataHandler.h"

USING_NS_CC;

EAppLayout  DataHandler::app_layout_ = EAppLayout::LAYOUT_WIDESCREEN;
Size        DataHandler::app_screen_size_ = Size(Vec2(0,0));
SBasket     DataHandler::COSMETIC_BASKET = SBasket{"",""};

//#ifdef ETC1
//	std::string DataHandler::extension = "pkm";
//
//#else
//	std::string DataHandler::extension = "png";
//#endif

AppDelegate::AppDelegate() 
{
    
}

AppDelegate::~AppDelegate()
{
}

//if you want a different context,just modify the value of glContextAttrs
//it will takes effect on all platforms
void AppDelegate::initGLContextAttrs()
{
    //set OpenGL context attributions,now can only set six attributions:
    //red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};
    
    GLView::setGLContextAttrs(glContextAttrs);
}

typedef struct tagResource
{
    cocos2d::Size size;
    char directory[100];
}Resource;


static Resource smallResource  =  { cocos2d::Size(480, 320),   "iphone" };
static Resource mediumResource =  { cocos2d::Size(1024, 768),  "ipad"   };
static Resource largeResource  =  { cocos2d::Size(2048, 1536), "ipadhd" };
static Resource largeResourceS5  =  { cocos2d::Size(1920, 1080), "galaxyS5" };
static cocos2d::Size designResolutionSize = cocos2d::Size(1920, 1080);

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLViewImpl::create("Hazelnut");
        director->setOpenGLView(glview);
    }
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 || CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
//	    glview->setFrameSize(1920, 1080); //HD
	//glview->setFrameSize(1280, 800);  //HD READY
	//    glview->setFrameSize(1024, 768);  //iPad
	//glview->setFrameSize(2048, 1536);   //iPad 3
  glview->setFrameSize(960, 640);   //iPhone4
	//    glview->setFrameSize(1136, 640);  //iPhone5
	//
	//    glview->setFrameSize(858, 480);   // Samsung Galaxy S1
	//glview->setFrameSize(1920, 1080); // Samsung Galaxy S4
	//    glview->setFrameSize(1280, 754);  // Samsung 10" Tablet
	    //glview->setFrameSize(480, 320);   // Samsung Galaxy Ace
	//    glview->setFrameSize(1024, 600);  // Kindle Fire
	//    glview->setFrameSize(960, 540);   // HD READY
	//    glview->setFrameSize(780, 480);   // HD READY
	//    glview->setFrameSize(1190, 720);   // HD READY
	//    glview->setFrameSize(780, 480);   // Motorola Nexus
	//    glview->setFrameSize(2048, 1440);   // Nexus 6/9 Tablet
	//glview->setFrameSize(1024, 720);   // Nexus 6/9 Tablet small



#endif

    // Set the design resolution
    glview->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, ResolutionPolicy::FIXED_WIDTH);
    
    
    Size frameSize = glview->getFrameSize();
    DataHandler::app_screen_size_ = glview->getFrameSize();//director->getOpenGLView()->getFrameSize();

    
    
    if (frameSize.height > largeResourceS5.size.height)
    {
        //searchPath.push_back(largeResource.directory);
        director->setContentScaleFactor(largeResource.size.height/designResolutionSize.height);
        //glview->setFrameSize(2048, 1536);
    }
    else if (frameSize.height > mediumResource.size.height)
    {
        director->setContentScaleFactor(largeResourceS5.size.height/designResolutionSize.height);
        //glview->setFrameSize(1920, 1080);
    }
    // if the frame's height is larger than the height of small resource size, select medium resource.
    else if (frameSize.height > smallResource.size.height)
    {
        //searchPath.push_back(mediumResource.directory);
        director->setContentScaleFactor(mediumResource.size.height/designResolutionSize.height);
        //glview->setFrameSize(800, 480);
    }
    // if the frame's height is smaller than the height of medium resource size, select small resource.
    else
    {
        //searchPath.push_back(smallResource.directory);
        director->setContentScaleFactor(smallResource.size.height/designResolutionSize.height);
        //glview->setFrameSize(800, 480);
    }
    
    director->setContentScaleFactor(largeResourceS5.size.height/designResolutionSize.height);
    
    
    
    float ratio = frameSize.width / frameSize.height;
    
    if(ratio > 1.72)
    {
        CCLOG("no black widescreen");
        DataHandler::app_layout_ = EAppLayout::LAYOUT_WIDESCREEN;
    }
    else if(ratio <= 1.72 && ratio >= 1.5)
    {
#pragma message WARN("SOME ARE IPAD LAYOUT")
        CCLOG("BLACK TOP USE DEFAULT");
        DataHandler::app_layout_ = EAppLayout::LAYOUT_DEFAULT;
    }
    else
    {
        CCLOG("BLACK TOP USE ipad<<");
        DataHandler::app_layout_ = EAppLayout::LAYOUT_IPAD;
    }
    
	std::string path = "";

#ifdef ETC1
	path = "ETC1/";
#else
	path = "PNG/";
#endif

    std::vector<std::string> search_paths;
    
    if(frameSize.width <= 1280)
    {
        search_paths.push_back(path + "MID");
		//FileUtils::getInstance()->addSearchPath(path + "MID");
        FileUtils::getInstance()->setSearchResolutionsOrder(search_paths);
		
        director->setContentScaleFactor(540/designResolutionSize.height);
    }
    else
    {
		search_paths.push_back(path + "HI");
		//FileUtils::getInstance()->addSearchPath(path + "HI");
		FileUtils::getInstance()->setSearchResolutionsOrder(search_paths);

        director->setContentScaleFactor(1080/designResolutionSize.height);
    }
    
    // turn on display FPS
    director->setDisplayStats(false);
    
    // set FPS. the default value is 1.0/60 if you don't call this
    //director->setAnimationInterval(1.0 / 60);

#ifdef DEBUG
    //doesnt working in ifdef somehow
//    // turn on display FPS
//    director->setDisplayStats(true);
//    
//    // set FPS. the default value is 1.0/60 if you don't call this
//    director->setAnimationInterval(1.0 / 60);
#endif
    
    
    // create a scene. it's an autorelease object
    Loader loader;
    loader.LoadGame();
//    loader.LoadMenu();
    auto scene = MenuScene::createMenuScene();
    
    auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
    // audio initialization/preloads
    
    audio->preloadEffect(DataHandler::SOUND_BUTTON_1);
    
    // set the background music and continuously play it.

	auto bInitFile = false;
	if(!FileOperation::FileAvailable(FileOperation::FILE_SAVED_DATA))
	{ 
		bInitFile = true;
	}
    
    // Create file
    FileOperation::createFileIfNotExist();
    
	if (bInitFile)
	{
		AchievementManager::GetInstance()->InitAchievementsFile();
	}

    AchievementManager::GetInstance()->LoadAchievmentsFromFile();


    // run
    director->runWithScene(scene);
    
    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();
}
