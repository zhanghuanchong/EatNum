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
    if(!glview) {
        glview = GLView::createWithRect("My Game", Rect(0, 0, 640, 960), 0.7F);
		director->setOpenGLView(glview);
		glview->setDesignResolutionSize(640, 960, ResolutionPolicy::FIXED_WIDTH);
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
