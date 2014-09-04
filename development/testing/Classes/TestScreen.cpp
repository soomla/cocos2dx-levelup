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

#include "TestScreen.h"
#include "CocosTestReporter.h"

USING_NS_CC;

cocos2d::Scene *TestScreen::createScene() {
    // 'scene' is an autorelease object
    auto scene = Scene::create();

    // 'layer' is an autorelease object
    auto layer = TestScreen::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

bool TestScreen::init() {
    
    if (!LayerColor::initWithColor(Color4B::WHITE)) {
        return false;
    }
    
    CocosTestReporter reporter;
	TestRunner runner(reporter);
    int failCount = runner.RunTestsIf(Test::GetTestList(), NULL, True(), 0);
    
    if (failCount > 0) {
        this->setColor(Color3B::RED);
    }
    else {
        this->setColor(Color3B::GREEN);
    }

    return true;
}


TestScreen::~TestScreen() {}