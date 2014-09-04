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

//
// Created by Simon Grinberg on 24/08/14.
//

#ifndef __ProfileScreen_H_
#define __ProfileScreen_H_

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Cocos2dxProfile.h"
#include "CCReward.h"
#include "MuffinRushAssets.h"

class ProfileScreen : public cocos2d::Layer {
public:
    static cocos2d::Scene* createScene();

    ProfileScreen():
            shareButton(NULL),
            storyButton(NULL),
            uploadButton(NULL),
            loginButton(NULL),
            logoutButton(NULL),
            loginReward(NULL),
            shareReward(NULL),
            uploadReward(NULL),
            likePageReward(NULL),
            screenshotPath("")
            {}
    virtual bool init();

    CREATE_FUNC(ProfileScreen);

    virtual ~ProfileScreen();

    void onClicked(cocos2d::Ref *ref, cocos2d::ui::Widget::TouchEventType touchType);
    
private:
    
    cocos2d::ui::Button *shareButton;
    cocos2d::ui::Button *storyButton;
    cocos2d::ui::Button *uploadButton;
    cocos2d::ui::Button *loginButton;
    cocos2d::ui::Button *logoutButton;
    soomla::CCReward *loginReward;
    soomla::CCReward *shareReward;
    soomla::CCReward *uploadReward;
    soomla::CCReward *likePageReward;
    std::string screenshotPath;

    float relativeX(float designX, float screenWidth);
    float relativeY(float designY, float screenHeight);
    cocos2d::ui::Button *createActionButton(cocos2d::ui::Layout *parent,
                                            const std::string &normalImage,
                                            const std::string &selectedImage ,
                                            const std::string &disableImage,
                                            const std::string &title,
                                            float posY,
                                            int actionTag, float scaleX, float scaleY, const cocos2d::Size &visibleSize);
    std::string saveScreenshot() const;
    void screenshotSavedCallback(float dt);
    void setLoggedInState();
};


#endif //__ProfileScreen_H_
