#include "AppDelegate.h"
#include "CCLuaEngine.h"
#include "SimpleAudioEngine.h"
#include "cocos2d.h"
#include "Net.h"

using namespace CocosDenshion;

USING_NS_CC;
using namespace std;

extern int luaopen_net (lua_State* tolua_S);
extern int luaopen_update (lua_State* tolua_S);
void registerLuas(lua_State* tolua_S)
{
	luaopen_net(tolua_S);
}

AppDelegate::AppDelegate()
{
}

AppDelegate::~AppDelegate()
{
    SimpleAudioEngine::end();
}

bool AppDelegate::applicationDidFinishLaunching()
{
    // initialize director
    auto director = Director::getInstance();
	auto glview = director->getOpenGLView();
	if(!glview) {
		glview = GLView::createWithRect("pomelo_rc", Rect(0,0,640,480));
		director->setOpenGLView(glview);
	}

    glview->setDesignResolutionSize(640, 480, ResolutionPolicy::NO_BORDER);

    // turn on display FPS
    director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);
	
	director->setNotificationNode(Net::getInstance());

	auto fileUtil = FileUtils::getInstance();
	
	//add src
	auto path = fileUtil->fullPathForFilename("src/main.lua");
	auto pos = path.find_last_of("/");
	path = path.substr(0, pos);
	fileUtil->addSearchPath(path);

	//add cocoBase
	auto cocoBasePath = path;
	cocoBasePath.append("/cocoBase");
	fileUtil->addSearchPath(cocoBasePath);

	//add Resource
	pos = path.find_last_of("/");
	path = path.substr(0, pos+1);
	fileUtil->addSearchPath(path);

	//add res
	path.append("res");
	fileUtil->addSearchPath(path);

	auto engine = LuaEngine::getInstance();
	ScriptEngineManager::getInstance()->setScriptEngine(engine);

	registerLuas(engine->getLuaStack()->getLuaState());
	/*
	auto update = Update::getInstance();
	update->resetVersion();
	update->setInfo("http://127.0.0.1:3001/src.zip", "http://127.0.0.1:3001/version.txt");
	update->startUpdate();
	*/
	engine->executeScriptFile("main.lua");

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
