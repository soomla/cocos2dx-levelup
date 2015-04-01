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

#include "TestingLevelUpEventHandler.h"
#include "CCScore.h"
#include "CCGate.h"
#include "CCMission.h"
#include "CCWorld.h"
#include "CCLevel.h"

USING_NS_CC;
using namespace soomla;

TestingLevelUpEventHandler::TestingLevelUpEventHandler() {
    Director::getInstance()->getEventDispatcher()->addCustomEventListener(CCLevelUpConsts::EVENT_LEVEL_UP_INITIALIZED,
                                                                                                    CC_CALLBACK_1(TestingLevelUpEventHandler::onLevelUpInitialized, this));
    Director::getInstance()->getEventDispatcher()->addCustomEventListener(CCLevelUpConsts::EVENT_SCORE_RECORD_REACHED, CC_CALLBACK_1(TestingLevelUpEventHandler::onScoreRecordReached, this));
    Director::getInstance()->getEventDispatcher()->addCustomEventListener(CCLevelUpConsts::EVENT_SCORE_RECORD_CHANGED, CC_CALLBACK_1(TestingLevelUpEventHandler::onScoreRecordChanged, this));
    Director::getInstance()->getEventDispatcher()->addCustomEventListener(CCLevelUpConsts::EVENT_GATE_OPENED, CC_CALLBACK_1(TestingLevelUpEventHandler::onGateOpened, this));
    Director::getInstance()->getEventDispatcher()->addCustomEventListener(CCLevelUpConsts::EVENT_MISSION_COMPLETED, CC_CALLBACK_1(TestingLevelUpEventHandler::onMissionCompleted, this));
    Director::getInstance()->getEventDispatcher()->addCustomEventListener(CCLevelUpConsts::EVENT_MISSION_COMPLETION_REVOKED, CC_CALLBACK_1(TestingLevelUpEventHandler::onMissionCompletionRevoked, this));
    Director::getInstance()->getEventDispatcher()->addCustomEventListener(CCLevelUpConsts::EVENT_WORLD_COMPLETED, CC_CALLBACK_1(TestingLevelUpEventHandler::onWorldCompleted, this));
    Director::getInstance()->getEventDispatcher()->addCustomEventListener(CCLevelUpConsts::EVENT_WORLD_REWARD_ASSIGNED, CC_CALLBACK_1(TestingLevelUpEventHandler::onWorldRewardAssigned, this));
    Director::getInstance()->getEventDispatcher()->addCustomEventListener(CCLevelUpConsts::EVENT_LEVEL_STARTED, CC_CALLBACK_1(TestingLevelUpEventHandler::onLevelStarted, this));
    Director::getInstance()->getEventDispatcher()->addCustomEventListener(CCLevelUpConsts::EVENT_LEVEL_ENDED, CC_CALLBACK_1(TestingLevelUpEventHandler::onLevelEnded, this));
}

TestingLevelUpEventHandler::~TestingLevelUpEventHandler() {
    Director::getInstance()->getEventDispatcher()->removeCustomEventListeners(CCLevelUpConsts::EVENT_LEVEL_UP_INITIALIZED);
    Director::getInstance()->getEventDispatcher()->removeCustomEventListeners(CCLevelUpConsts::EVENT_SCORE_RECORD_REACHED);
    Director::getInstance()->getEventDispatcher()->removeCustomEventListeners(CCLevelUpConsts::EVENT_SCORE_RECORD_CHANGED);
    Director::getInstance()->getEventDispatcher()->removeCustomEventListeners(CCLevelUpConsts::EVENT_GATE_OPENED);
    Director::getInstance()->getEventDispatcher()->removeCustomEventListeners(CCLevelUpConsts::EVENT_MISSION_COMPLETED);
    Director::getInstance()->getEventDispatcher()->removeCustomEventListeners(CCLevelUpConsts::EVENT_MISSION_COMPLETION_REVOKED);
    Director::getInstance()->getEventDispatcher()->removeCustomEventListeners(CCLevelUpConsts::EVENT_WORLD_COMPLETED);
    Director::getInstance()->getEventDispatcher()->removeCustomEventListeners(CCLevelUpConsts::EVENT_WORLD_REWARD_ASSIGNED);
    Director::getInstance()->getEventDispatcher()->removeCustomEventListeners(CCLevelUpConsts::EVENT_LEVEL_STARTED);
    Director::getInstance()->getEventDispatcher()->removeCustomEventListeners(CCLevelUpConsts::EVENT_LEVEL_ENDED);
}

void TestingLevelUpEventHandler::onLevelUpInitialized(EventCustom *event) {
    addToEventStack(soomla::CCLevelUpConsts::EVENT_LEVEL_UP_INITIALIZED, cocos2d::__String::create(""));
}

void TestingLevelUpEventHandler::onScoreRecordReached(EventCustom *event) {
    __Dictionary *eventData = (__Dictionary *)event->getUserData();
    CCScore *score = dynamic_cast<CCScore *>(eventData->objectForKey(CCLevelUpConsts::DICT_ELEMENT_SCORE));
    addToEventStack(soomla::CCLevelUpConsts::EVENT_SCORE_RECORD_REACHED, score);
}

void TestingLevelUpEventHandler::onScoreRecordChanged(EventCustom *event) {
    __Dictionary *eventData = (__Dictionary *)event->getUserData();
    CCScore *score = dynamic_cast<CCScore *>(eventData->objectForKey(CCLevelUpConsts::DICT_ELEMENT_SCORE));
    addToEventStack(soomla::CCLevelUpConsts::EVENT_SCORE_RECORD_CHANGED, score);
}

void TestingLevelUpEventHandler::onGateOpened(EventCustom *event) {
    __Dictionary *eventData = (__Dictionary *)event->getUserData();
    CCGate *gate = dynamic_cast<CCGate *>(eventData->objectForKey(CCLevelUpConsts::DICT_ELEMENT_GATE));
    addToEventStack(soomla::CCLevelUpConsts::EVENT_GATE_OPENED, gate);
}

void TestingLevelUpEventHandler::onMissionCompleted(EventCustom *event) {
    __Dictionary *eventData = (__Dictionary *)event->getUserData();
    CCMission *mission = dynamic_cast<CCMission *>(eventData->objectForKey(CCLevelUpConsts::DICT_ELEMENT_MISSION));
    addToEventStack(soomla::CCLevelUpConsts::EVENT_MISSION_COMPLETED, mission);
}

void TestingLevelUpEventHandler::onMissionCompletionRevoked(EventCustom *event) {
    __Dictionary *eventData = (__Dictionary *)event->getUserData();
    CCMission *mission = dynamic_cast<CCMission *>(eventData->objectForKey(CCLevelUpConsts::DICT_ELEMENT_MISSION));
    addToEventStack(soomla::CCLevelUpConsts::EVENT_MISSION_COMPLETION_REVOKED, mission);
}

void TestingLevelUpEventHandler::onWorldCompleted(EventCustom *event) {
    __Dictionary *eventData = (__Dictionary *)event->getUserData();
    CCWorld *world = dynamic_cast<CCWorld *>(eventData->objectForKey(CCLevelUpConsts::DICT_ELEMENT_WORLD));
    addToEventStack(soomla::CCLevelUpConsts::EVENT_WORLD_COMPLETED, world);
}

void TestingLevelUpEventHandler::onWorldRewardAssigned(EventCustom *event) {
    __Dictionary *eventData = (__Dictionary *)event->getUserData();
    CCWorld *world = dynamic_cast<CCWorld *>(eventData->objectForKey(CCLevelUpConsts::DICT_ELEMENT_WORLD));
    addToEventStack(soomla::CCLevelUpConsts::EVENT_WORLD_REWARD_ASSIGNED, world);
}

void TestingLevelUpEventHandler::onLevelStarted(EventCustom *event) {
    __Dictionary *eventData = (__Dictionary *)event->getUserData();
    CCLevel *level = dynamic_cast<CCLevel *>(eventData->objectForKey(CCLevelUpConsts::DICT_ELEMENT_LEVEL));
    addToEventStack(soomla::CCLevelUpConsts::EVENT_LEVEL_STARTED, level);
}

void TestingLevelUpEventHandler::onLevelEnded(EventCustom *event) {
    __Dictionary *eventData = (__Dictionary *)event->getUserData();
    CCLevel *level = dynamic_cast<CCLevel *>(eventData->objectForKey(CCLevelUpConsts::DICT_ELEMENT_LEVEL));
    addToEventStack(soomla::CCLevelUpConsts::EVENT_LEVEL_ENDED, level);
}