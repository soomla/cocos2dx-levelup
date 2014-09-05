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

TestingLevelUpEventHandler::TestingLevelUpEventHandler() {
    eventStack = cocos2d::__Dictionary::create();
    eventStack->retain();
}

TestingLevelUpEventHandler::~TestingLevelUpEventHandler() {
    CC_SAFE_RELEASE(eventStack);
}

void TestingLevelUpEventHandler::onLevelUpInitialized() {
    eventStack->setObject(cocos2d::__String::create(""), soomla::CCLevelUpConsts::EVENT_LEVEL_UP_INITIALIZED);
}

void TestingLevelUpEventHandler::onScoreRecordReached(soomla::CCScore *score) {
    eventStack->setObject(score, soomla::CCLevelUpConsts::EVENT_SCORE_RECORD_REACHED);
}

void TestingLevelUpEventHandler::onScoreRecordChanged(soomla::CCScore *score) {
    eventStack->setObject(score, soomla::CCLevelUpConsts::EVENT_SCORE_RECORD_CHANGED);
}

void TestingLevelUpEventHandler::onGateOpened(soomla::CCGate *gate) {
    eventStack->setObject(gate, soomla::CCLevelUpConsts::EVENT_GATE_OPENED);
}

void TestingLevelUpEventHandler::onMissionCompleted(soomla::CCMission *mission) {
    eventStack->setObject(mission, soomla::CCLevelUpConsts::EVENT_MISSION_COMPLETED);
}

void TestingLevelUpEventHandler::onMissionCompletionRevoked(soomla::CCMission *mission) {
    eventStack->setObject(mission, soomla::CCLevelUpConsts::EVENT_MISSION_COMPLETION_REVOKED);
}

void TestingLevelUpEventHandler::onWorldCompleted(soomla::CCWorld *world) {
    eventStack->setObject(world, soomla::CCLevelUpConsts::EVENT_WORLD_COMPLETED);
}

void TestingLevelUpEventHandler::onWorldRewardAssigned(soomla::CCWorld *world) {
    eventStack->setObject(world, soomla::CCLevelUpConsts::EVENT_WORLD_REWARD_ASSIGNED);
}

void TestingLevelUpEventHandler::onLevelStarted(soomla::CCLevel *level) {
    eventStack->setObject(level, soomla::CCLevelUpConsts::EVENT_LEVEL_STARTED);
}

void TestingLevelUpEventHandler::onLevelEnded(soomla::CCLevel *level) {
    eventStack->setObject(level, soomla::CCLevelUpConsts::EVENT_LEVEL_ENDED);
}

cocos2d::Ref *TestingLevelUpEventHandler::getEventData(const std::string& eventName) {
    return eventStack->objectForKey(eventName);
}

bool TestingLevelUpEventHandler::checkEventFired(const std::string& eventName) {
    return (getEventData(eventName) != NULL);
}