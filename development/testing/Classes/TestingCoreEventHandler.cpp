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

#include "TestingCoreEventHandler.h"
#include "CCCoreConsts.h"

USING_NS_CC;
using namespace soomla;

TestingCoreEventHandler::TestingCoreEventHandler() {
    Director::getInstance()->getEventDispatcher()->addCustomEventListener(CCCoreConsts::EVENT_REWARD_GIVEN, CC_CALLBACK_1(TestingCoreEventHandler::onRewardGivenEvent, this));
    Director::getInstance()->getEventDispatcher()->addCustomEventListener(CCCoreConsts::EVENT_REWARD_TAKEN, CC_CALLBACK_1(TestingCoreEventHandler::onRewardTakenEvent, this));
}

TestingCoreEventHandler::~TestingCoreEventHandler() {
    Director::getInstance()->getEventDispatcher()->removeCustomEventListeners(CCCoreConsts::EVENT_REWARD_GIVEN);
    Director::getInstance()->getEventDispatcher()->removeCustomEventListeners(CCCoreConsts::EVENT_REWARD_TAKEN);
}

void TestingCoreEventHandler::onRewardGivenEvent(cocos2d::EventCustom *event) {
    __Dictionary *eventData = (__Dictionary *)event->getUserData();
    CCReward *reward = dynamic_cast<CCReward *>(eventData->objectForKey(CCCoreConsts::DICT_ELEMENT_REWARD));
    
    addToEventStack(soomla::CCCoreConsts::EVENT_REWARD_GIVEN, reward);
}

void TestingCoreEventHandler::onRewardTakenEvent(cocos2d::EventCustom *event) {
    __Dictionary *eventData = (__Dictionary *)event->getUserData();
    CCReward *reward = dynamic_cast<CCReward *>(eventData->objectForKey(CCCoreConsts::DICT_ELEMENT_REWARD));
    
    addToEventStack(soomla::CCCoreConsts::EVENT_REWARD_TAKEN, reward);
};