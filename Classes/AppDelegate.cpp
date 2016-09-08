
#include "AppDelegate.h"
#include "MainMenu.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;


AppDelegate::AppDelegate() {}

AppDelegate::~AppDelegate() {}


void AppDelegate::initGLContextAttrs()
{
    // set OpenGL context attributions: red, green, blue, alpha, depth, stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};
    GLView::setGLContextAttrs(glContextAttrs);
}

bool AppDelegate::applicationDidFinishLaunching()
{
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if (!glview) {
        glview = GLViewImpl::createWithRect("PlanetConqueror", Rect(0, 0, 1136, 640));
        director->setOpenGLView(glview);
    }

    director->getOpenGLView()->setDesignResolutionSize(1136, 640, ResolutionPolicy::NO_BORDER);

    // turn on display FPS
    //director->setDisplayStats(true);

    // 60 frames per second
    director->setAnimationInterval(1.0/60.0);

    // Main menu scene
    auto mainMenu = MainMenu::createMainMenuScene();
    director->runWithScene(mainMenu);

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
