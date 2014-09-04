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

#include <time.h>
#include <unistd.h>
#include "ProfileScreen.h"
#include "CCSoomlaEventDispatcher.h"
#include "CCDomainFactory.h"
#include "CCVirtualItemReward.h"
#include "MuffinRushAssets.h"

USING_NS_CC;
using namespace cocos2d::ui;

#define LOGIN_BUTTON_TAG 0
#define STATUS_BUTTON_TAG 1
#define STORY_BUTTON_TAG 2
#define UPLOAD_BUTTON_TAG 3
#define LOGOUT_BUTTON_TAG 4

#define DESIGN_WIDTH 640.0f
#define DESIGN_HEIGHT 1136.0f

cocos2d::Scene *ProfileScreen::createScene() {
    // 'scene' is an autorelease object
    auto scene = Scene::create();

    // 'layer' is an autorelease object
    auto layer = ProfileScreen::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

bool ProfileScreen::init() {
    if (!Layer::init()) {
        return false;
    }
    
    loginReward = soomla::CCVirtualItemReward::create(__String::create("login_reward"),
                                                      __String::create("Login Reward"),
                                                      __Bool::create(false), __Integer::create(100), __String::create(MUFFIN_CURRENCY_ITEM_ID));
    loginReward->retain();
    
    shareReward = soomla::CCVirtualItemReward::create(__String::create("share_reward"),
                                                      __String::create("Share Reward"),
                                                      __Bool::create(false), __Integer::create(150), __String::create(MUFFIN_CURRENCY_ITEM_ID));
    shareReward->retain();
    
    uploadReward = soomla::CCVirtualItemReward::create(__String::create("upload_reward"),
                                                      __String::create("Upload Reward"),
                                                      __Bool::create(false), __Integer::create(200), __String::create(MUFFIN_CURRENCY_ITEM_ID));
    uploadReward->retain();
    
    likePageReward = soomla::CCVirtualItemReward::create(__String::create("like_page_reward"),
                                                       __String::create("Like Page Reward"),
                                                       __Bool::create(false), __Integer::create(300), __String::create(MUFFIN_CURRENCY_ITEM_ID));
    likePageReward->retain();

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();

    Layout *layout = Layout::create();

    float vShift = visibleSize.height;
    
    ImageView *background = ui::ImageView::create("profile/BG.png");
    background->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f));
    layout->addChild(background);
    
    float scaleX = visibleSize.width / background->getSize().width;
    float scaleY = visibleSize.height / background->getSize().height;
    
    background->setScale(scaleX, scaleY);
    
    ImageView *header = ui::ImageView::create("profile/Headline.png");
    header->setAnchorPoint(Vec2(0.0f, 1.0f));
    header->setScale(scaleX, scaleY);
    header->setPosition(Vec2(0.0f, vShift));
    layout->addChild(header);
    vShift -= header->getSize().height * scaleY;
    
    vShift -= relativeY(70.0f, visibleSize.height);
    
    shareButton = createActionButton(layout,
                                     "profile/BTN-Share-Normal.png", "profile/BTN-Share-Press.png", "profile/BTN-Share-Disable.png", "I Love SOOMLA!",
                                vShift, STATUS_BUTTON_TAG, scaleX, scaleY, visibleSize);
    shareButton->retain();
    
    vShift -= shareButton->getSize().height * scaleY;
    vShift -= relativeY(60.0f, visibleSize.height);
    
    storyButton = createActionButton(layout,
                                     "profile/BTN-ShareStory-Normal.png", "profile/BTN-ShareStory-Press.png", "profile/BTN-ShareStory-Disable.png", "Full story of The SOOMBOT!",
                                vShift, STORY_BUTTON_TAG, scaleX, scaleY, visibleSize);
    storyButton->retain();
    
    vShift -= storyButton->getSize().height * scaleY;
    vShift -= relativeY(60.0f, visibleSize.height);
    
    uploadButton = createActionButton(layout,
                                      "profile/BTN-Upload-Normal.png", "profile/BTN-Upload-Press.png", "profile/BTN-Upload-Disable.png", "Screenshot",
                                vShift, UPLOAD_BUTTON_TAG, scaleX, scaleY, visibleSize);
    uploadButton->retain();
    
    vShift -= uploadButton->getSize().height * scaleY;
    vShift -= relativeY(150.0f, visibleSize.height);
    
    loginButton = ui::Button::create("profile/BTN-Connect.png", "profile/BTN-Connect-Press.png", "profile/BTN-Connect.png");
    loginButton->retain();
    loginButton->setActionTag(LOGIN_BUTTON_TAG);
    loginButton->setAnchorPoint(Vec2(0.0f, 1.0f));
    loginButton->setScale(scaleX, scaleY);
    loginButton->setPosition(Vec2(relativeX(30.0f, visibleSize.width), vShift));
    
    loginButton->setTouchEnabled(true);
    loginButton->addTouchEventListener(CC_CALLBACK_2(ProfileScreen::onClicked, this));
    layout->addChild(loginButton);
    
    logoutButton = ui::Button::create("profile/BTN-LogOut.png", "profile/BTN-LogOut-Press.png", "profile/BTN-LogOut.png");
    logoutButton->retain();
    logoutButton->setActionTag(LOGOUT_BUTTON_TAG);
    logoutButton->setAnchorPoint(Vec2(0.0f, 1.0f));
    logoutButton->setScale(scaleX, scaleY);
    logoutButton->setPosition(Vec2(relativeX(30.0f, visibleSize.width), vShift));
    
    logoutButton->setVisible(false);
    logoutButton->setTouchEnabled(true);
    logoutButton->setEnabled(false);
    logoutButton->addTouchEventListener(CC_CALLBACK_2(ProfileScreen::onClicked, this));
    layout->addChild(logoutButton);

    this->addChild(layout);

    std::function<void(EventCustom *)> handleLoginFinished = [this](EventCustom *event) {
        this->setLoggedInState();
        
        soomla::CCError *profileError = nullptr;
        soomla::CCProfileController::getInstance()->like(soomla::FACEBOOK, "The.SOOMLA.Project", likePageReward, &profileError);
        soomla::CCProfileController::getInstance()->getFeed(soomla::FACEBOOK, nullptr, &profileError);
        soomla::CCProfileController::getInstance()->getContacts(soomla::FACEBOOK, nullptr, &profileError);
    };
    
    std::function<void(EventCustom *)> handleLogoutFinished = [this](EventCustom *event) {
        logoutButton->setVisible(false);
        logoutButton->setEnabled(false);
        loginButton->setVisible(true);
        loginButton->setEnabled(true);
        
        shareButton->setEnabled(false);
        shareButton->setBright(false);
        
        storyButton->setEnabled(false);
        storyButton->setBright(false);
        
        uploadButton->setEnabled(false);
        uploadButton->setBright(false);
    };
    
    std::function<void(EventCustom *)> handleProfileUpdatedFinished = [this](EventCustom *event) {
        soomla::CCUserProfile *userProfile = (soomla::CCUserProfile *)(event->getUserData());
        
        log("%s %s has logged in", userProfile->getFirstName()->getCString(), userProfile->getLastName()->getCString());
    };
    
    getEventDispatcher()->addEventListenerWithSceneGraphPriority(EventListenerCustom::create(soomla::CCProfileConsts::EVENT_LOGIN_FINISHED, handleLoginFinished),
                                                                 this);
    
    getEventDispatcher()->addEventListenerWithSceneGraphPriority(EventListenerCustom::create(soomla::CCProfileConsts::EVENT_USER_PROFILE_UPDATED, handleProfileUpdatedFinished),
                                                                 this);
    
    getEventDispatcher()->addEventListenerWithSceneGraphPriority(EventListenerCustom::create(soomla::CCProfileConsts::EVENT_LOGOUT_FINISHED, handleLogoutFinished),
                                                                 this);
    
    soomla::CCError *profileError = nullptr;
    bool isLoggedIn =  soomla::CCProfileController::getInstance()->isLoggedIn(soomla::FACEBOOK, &profileError);
    if (profileError) {
        MessageBox(profileError->getInfo(), "Error");
    }
    else {
        if (isLoggedIn) {
            setLoggedInState();
        }
    }

    return true;
}


ProfileScreen::~ProfileScreen() {
    CC_SAFE_DELETE(shareButton);
    CC_SAFE_DELETE(storyButton);
    CC_SAFE_DELETE(uploadButton);
    CC_SAFE_DELETE(loginButton);
    CC_SAFE_DELETE(logoutButton);
}

void ProfileScreen::onClicked(cocos2d::Ref *ref, Widget::TouchEventType touchType) {
    if (touchType == Widget::TouchEventType::ENDED) {
        auto sender = static_cast<Widget *>(ref);
        soomla::CCError *profileError = nullptr;
        if (sender->getActionTag() == LOGIN_BUTTON_TAG) {
            soomla::CCProfileController::getInstance()->login(soomla::FACEBOOK, loginReward, &profileError);
        }
        else if (sender->getActionTag() == STATUS_BUTTON_TAG) {
            soomla::CCProfileController::getInstance()->updateStatus(soomla::FACEBOOK, "I love SOOMLA! http://www.soom.la", shareReward, &profileError);
        }
        else if (sender->getActionTag() == STORY_BUTTON_TAG) {
            soomla::CCProfileController::getInstance()->updateStory(soomla::FACEBOOK,
                                                                    "This is the story of a very strong and brave SOOMBOT on his jurney from SOOMBOTIA to a far away galaxy. That galaxy contains a blue planet where all human game developers love to eat food spiced with marshmallow.",
                                                                    "The story of SOOMBOT (Profile Test App)",
                                                                    "SOOMBOT Story",
                                                                    "DESCRIPTION",
                                                                    "http://about.soom.la/soombots",
                                                                    "http://about.soom.la/wp-content/uploads/2014/05/330x268-spockbot.png",
                                                                    nullptr,
                                                                    &profileError);
        }
        else if (sender->getActionTag() == UPLOAD_BUTTON_TAG) {
            screenshotPath = saveScreenshot();
            // Cocos2dx does not have a callback for saveToFile so creating a hacky solution
            this->scheduleOnce(schedule_selector(ProfileScreen::screenshotSavedCallback), 1.0f);
        }
        else if (sender->getActionTag() == LOGOUT_BUTTON_TAG) {
            soomla::CCProfileController::getInstance()->logout(soomla::FACEBOOK, &profileError);
        }
        else {
            return;
        }
        if (profileError) {
            MessageBox(profileError->getInfo(), "Error");
        }
    }
}

void ProfileScreen::screenshotSavedCallback(float dt) {
    soomla::CCError *profileError = nullptr;
    soomla::CCProfileController::getInstance()->uploadImage(soomla::FACEBOOK,
                                                            "I love SOOMLA! http://www.soom.la",
                                                            screenshotPath.c_str(),
                                                            uploadReward,
                                                            &profileError);
    if (profileError) {
        MessageBox(profileError->getInfo(), "Error");
    }
}

float ProfileScreen::relativeX(float designX, float screenWidth) {
    return (designX / DESIGN_WIDTH) * screenWidth;
}

float ProfileScreen::relativeY(float designY, float screenHeight) {
    return (designY / DESIGN_HEIGHT) * screenHeight;
}

cocos2d::ui::Button *ProfileScreen::createActionButton(cocos2d::ui::Layout *parent,
                                                       const std::string &normalImage,
                                                       const std::string& selectedImage ,
                                                       const std::string& disableImage,
                                                       const std::string& title,
                                                       float posY,
                                                       int actionTag, float scaleX, float scaleY, const Size& visibleSize) {
    
    ImageView *bar = ui::ImageView::create("profile/BG-Bar.png");
    bar->setAnchorPoint(Vec2(0.0f, 1.0f));
    bar->setScale(scaleX, scaleY);
    bar->setPosition(Vec2(relativeX(65.0f, visibleSize.width), posY - (7.0f * scaleY)));
    parent->addChild(bar);
    
    Button *button;
    
    button = ui::Button::create(normalImage, selectedImage, disableImage);
    button->setActionTag(actionTag);
    button->setAnchorPoint(Vec2(0.0f, 1.0f));
    button->setScale(scaleX, scaleY);
    button->setPosition(Vec2(relativeX(50.0f, visibleSize.width), posY));
    
    button->setTouchEnabled(true);
    button->addTouchEventListener(CC_CALLBACK_2(ProfileScreen::onClicked, this));
    button->setEnabled(false);
    button->setBright(false);
    
    parent->addChild(button);
    
    Text *label = ui::Text::create(title, "GoodDog.otf", 40);
    label->setColor(Color3B::BLACK);
    label->setAnchorPoint(Vec2(0.0f, 1.0f));
    label->setSize(Size(relativeX(280.0f, visibleSize.width), relativeY(100.0f, visibleSize.height)));
    label->ignoreContentAdaptWithSize(false);
    label->setTextHorizontalAlignment(cocos2d::TextHAlignment::LEFT);
    label->setTextVerticalAlignment(cocos2d::TextVAlignment::CENTER);
    label->setScale(scaleX, scaleY);
    label->setPosition(Vec2(relativeX(270.0f, visibleSize.width), posY - (12.0f * scaleY)));
    parent->addChild(label);
    
    return button;
}

std::string ProfileScreen::saveScreenshot() const {
    Size screen = Director::getInstance()->getWinSize();
    
    RenderTexture *tex = RenderTexture::create(int(screen.width), int(screen.height));
    tex->retain();
    
    tex->setPosition(Vec2(screen.width/2.0f, screen.height/2.0f));
    
    tex->begin();
    Director::getInstance()->getRunningScene()->visit();
    tex->end();
    
    __String *path = __String::createWithFormat("%s%d.png", "screenshot_", int(time(0)));
    tex->saveToFile(path->getCString(), Image::Format::PNG);
    
    return FileUtils::getInstance()->getWritablePath() + path->getCString();
}

void ProfileScreen::setLoggedInState() {
    logoutButton->setVisible(true);
    logoutButton->setEnabled(true);
    loginButton->setVisible(false);
    loginButton->setEnabled(false);
    
    shareButton->setEnabled(true);
    shareButton->setBright(true);
    
    storyButton->setEnabled(true);
    storyButton->setBright(true);
    
    uploadButton->setEnabled(true);
    uploadButton->setBright(true);
}