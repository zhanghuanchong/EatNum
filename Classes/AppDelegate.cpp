#include "AppDelegate.h"
#include "Util.h"
#include "Splash/SplashScene.h"
#include "Home/HomeScene.h"
#include "Levels/ChapterScene.h"
#include "Game/GameScene.h"

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
	auto glview = director->getOpenGLView();
	//int width = 750, height = 1334; // iPhone 4.7'
	//int width = 1080, height = 1920; // iPhone 5.5'
	//int width = 1242, height = 2208; // iPhone 5.5' Rendered
	//int width = 640, height = 1136; // iPhone 4'
	//int width = 640, height = 960; // iPhone 3.5'
	//int width = 768, height = 1024; // iPad
	//int width = 1536, height = 2048; // iPad Retina
	//int width = 480, height = 840; // Android

	//int width = 480, height = 854; // Xiaomi
	//int width = 800, height = 1280; // Nexus 7
	int width = 1600, height = 2560; // Nexus 10
	if (!glview) {
        glview = GLView::createWithRect("My Game", cocos2d::Rect(0, 0, width, height), 0.33F);
		director->setOpenGLView(glview);
		
		int designWidth = 640;
		int designHeight = 1136;
		glview->setDesignResolutionSize(designWidth, designHeight, ResolutionPolicy::FIXED_WIDTH);
	}

    // turn on display FPS
    //director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

	Util::init();

	// create a scene. it's an autorelease object
	auto scene = SplashScene::create();
	//auto scene = GameScene::createWithLevel(0, 0);
	//auto scene = ChapterScene::create();

    // run
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
