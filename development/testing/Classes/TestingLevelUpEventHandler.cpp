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

void TestingLevelUpEventHandler::onLevelUpInitialized() {
    addToEventStack(soomla::CCLevelUpConsts::EVENT_LEVEL_UP_INITIALIZED, cocos2d::__String::create(""));
}

void TestingLevelUpEventHandler::onScoreRecordReached(soomla::CCScore *score) {
    addToEventStack(soomla::CCLevelUpConsts::EVENT_SCORE_RECORD_REACHED, score);
}

void TestingLevelUpEventHandler::onScoreRecordChanged(soomla::CCScore *score) {
    addToEventStack(soomla::CCLevelUpConsts::EVENT_SCORE_RECORD_CHANGED, score);
}

void TestingLevelUpEventHandler::onGateOpened(soomla::CCGate *gate) {
    addToEventStack(soomla::CCLevelUpConsts::EVENT_GATE_OPENED, gate);
}

void TestingLevelUpEventHandler::onMissionCompleted(soomla::CCMission *mission) {
    addToEventStack(soomla::CCLevelUpConsts::EVENT_MISSION_COMPLETED, mission);
}

void TestingLevelUpEventHandler::onMissionCompletionRevoked(soomla::CCMission *mission) {
    addToEventStack(soomla::CCLevelUpConsts::EVENT_MISSION_COMPLETION_REVOKED, mission);
}

void TestingLevelUpEventHandler::onWorldCompleted(soomla::CCWorld *world) {
    addToEventStack(soomla::CCLevelUpConsts::EVENT_WORLD_COMPLETED, world);
}

void TestingLevelUpEventHandler::onWorldRewardAssigned(soomla::CCWorld *world) {
    addToEventStack(soomla::CCLevelUpConsts::EVENT_WORLD_REWARD_ASSIGNED, world);
}

void TestingLevelUpEventHandler::onLevelStarted(soomla::CCLevel *level) {
    addToEventStack(soomla::CCLevelUpConsts::EVENT_LEVEL_STARTED, level);
}

void TestingLevelUpEventHandler::onLevelEnded(soomla::CCLevel *level) {
    addToEventStack(soomla::CCLevelUpConsts::EVENT_LEVEL_ENDED, level);
}