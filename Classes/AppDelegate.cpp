#include "cocos2d.h"
#include "CCEGLView.h"
#include "AppDelegate.h"
#include "CCLuaEngine.h"
#include "SimpleAudioEngine.h"
#include "Net.h"

using namespace CocosDenshion;

USING_NS_CC;

AppDelegate::AppDelegate()
{
}

AppDelegate::~AppDelegate()
{
    SimpleAudioEngine::end();
}

extern int luaopen_net (lua_State* tolua_S);
void registerLuas(lua_State* tolua_S)
{
	luaopen_net(tolua_S);
}

bool AppDelegate::applicationDidFinishLaunching()
{
    // initialize director
    auto director = Director::getInstance();
    director->setOpenGLView(EGLView::getInstance());

	director->setNotificationNode(Net::getInstance());

    EGLView::getInstance()->setDesignResolutionSize(640, 480, ResolutionPolicy::SHOW_ALL);

    // turn on display FPS
    director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

	std::string path = FileUtils::getInstance()->fullPathForFilename("luaScript/main.lua");
	int pos = path.find_last_of("\/");
	std::string addPath = path.substr(0, pos);
	FileUtils::getInstance()->addSearchPath(addPath.c_str());
	addPath.append("/cocoBase");
	FileUtils::getInstance()->addSearchPath(addPath.c_str());

    // register lua engine
    auto engine = LuaEngine::getInstance();
    ScriptEngineManager::getInstance()->setScriptEngine(engine);
	
	registerLuas(engine->getLuaStack()->getLuaState());
	    
	engine->executeScriptFile(path.c_str());

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
    Director::getInstance()->stopAnimation();

    SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    Director::getInstance()->startAnimation();

    SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
