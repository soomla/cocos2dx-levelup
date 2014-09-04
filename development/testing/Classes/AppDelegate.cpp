/*
 Copyright (C) 2012-2014 Soomla Inc.
 
 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at
 
 http://www.apache.org/licenses/LICENSE-2.0
 
 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.
 */

#include "AppDelegate.h"
#include "ProfileScreen.h"
#include "TestScreen.h"
#include "CoreEventHandler.h"
#include "ProfileEventHandler.h"
#include "CCServiceManager.h"
#include "CCProfileService.h"
#include "MuffinRushAssets.h"
#include "CCServiceManager.h"
#include "CCStoreService.h"
#include "CCCoreEventDispatcher.h"

USING_NS_CC;

AppDelegate::AppDelegate() {
    handler = new ProfileEventHandler();
    coreHandler = new CoreEventHandler();
}

AppDelegate::~AppDelegate() 
{
    soomla::CCProfileEventDispatcher::getInstance()->removeEventHandler(handler);
    soomla::CCCoreEventDispatcher::getInstance()->removeEventHandler(coreHandler);
}

bool AppDelegate::applicationDidFinishLaunching() {
    
    __Dictionary *commonParams = __Dictionary::create();
    commonParams->setObject(__String::create("ExampleCustomSecret"), "customSecret");
    soomla::CCServiceManager::getInstance()->setCommonParams(commonParams);
    
    MuffinRushAssets *assets = MuffinRushAssets::create();
    
    __Dictionary *storeParams = __Dictionary::create();
    storeParams->setObject(__String::create("ExamplePublicKey"), "androidPublicKey");
    
    soomla::CCCoreEventDispatcher::getInstance()->addEventHandler(coreHandler);
    soomla::CCStoreService::initShared(assets, storeParams);
    
    __Dictionary *profileParams = __Dictionary::create();
    
    // initialize director
    auto director = Director::getInstance();
    
    soomla::CCProfileEventDispatcher::getInstance()->addEventHandler(handler);
    soomla::CCProfileService::initShared(profileParams);
    
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLView::create("My Game");
        director->setOpenGLView(glview);
    }

    // turn on display FPS
    director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object
    auto scene = TestScreen::createScene();

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
