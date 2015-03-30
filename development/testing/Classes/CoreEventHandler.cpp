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

#include "CoreEventHandler.h"
#include "Cocos2dxCore.h"

#define TAG "CoreEventHandler >>>"

USING_NS_CC;
using namespace soomla;

CoreEventHandler::CoreEventHandler() {
    Director::getInstance()->getEventDispatcher()->addCustomEventListener(CCCoreConsts::EVENT_REWARD_GIVEN, CC_CALLBACK_1(CoreEventHandler::onRewardGivenEvent, this));
    Director::getInstance()->getEventDispatcher()->addCustomEventListener(CCCoreConsts::EVENT_REWARD_TAKEN, CC_CALLBACK_1(CoreEventHandler::onRewardTakenEvent, this));
    Director::getInstance()->getEventDispatcher()->addCustomEventListener(CCCoreConsts::EVENT_CUSTOM, CC_CALLBACK_1(CoreEventHandler::onCustomEvent, this));
}

void CoreEventHandler::onRewardGivenEvent(cocos2d::EventCustom *event) {
    __Dictionary *eventData = (__Dictionary *)event->getUserData();
    CCReward *reward = dynamic_cast<CCReward *>(eventData->objectForKey(CCCoreConsts::DICT_ELEMENT_REWARD));
    CCSoomlaUtils::logDebug(TAG, __String::createWithFormat("Reward %s was given", reward->getName()->getCString())->getCString());
}

void CoreEventHandler::onRewardTakenEvent(cocos2d::EventCustom *event) {
    __Dictionary *eventData = (__Dictionary *)event->getUserData();
    CCReward *reward = dynamic_cast<CCReward *>(eventData->objectForKey(CCCoreConsts::DICT_ELEMENT_REWARD));
    CCSoomlaUtils::logDebug(TAG, __String::createWithFormat("Reward %s was taken", reward->getName()->getCString())->getCString());
}

void CoreEventHandler::onCustomEvent(cocos2d::EventCustom *event) {
    __Dictionary *eventData = (__Dictionary *)event->getUserData();
    __String *name = dynamic_cast<__String *>(eventData->objectForKey(CCCoreConsts::DICT_ELEMENT_NAME));
//    __Dictionary *extra = dynamic_cast<__Dictionary *>(eventData->objectForKey(CCCoreConsts::DICT_ELEMENT_EXTRA));
    CCSoomlaUtils::logDebug(TAG, __String::createWithFormat("Custom event arrived %s", name->getCString())->getCString());
}