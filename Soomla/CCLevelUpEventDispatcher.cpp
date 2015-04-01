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


#include "CCLevelUpEventDispatcher.h"
#include "CCSoomlaEventDispatcher.h"
#include "CCDomainFactory.h"
#include "CCSoomlaLevelUp.h"

namespace soomla {

    USING_NS_CC;

    static CCLevelUpEventDispatcher *s_SharedInstance = NULL;

    CCLevelUpEventDispatcher *CCLevelUpEventDispatcher::getInstance() {
        if (!s_SharedInstance) {
            s_SharedInstance = new CCLevelUpEventDispatcher();
            s_SharedInstance->init();
        }

        return s_SharedInstance;
    }

    bool CCLevelUpEventDispatcher::init() {

        CCSoomlaEventDispatcher *eventDispatcher = CCSoomlaEventDispatcher::getInstance();

        eventDispatcher->registerEventHandler(CCLevelUpConsts::EVENT_LEVEL_UP_INITIALIZED,
                [this](__Dictionary *parameters) {
                    this->onLevelUpInitialized();
                });
        
        eventDispatcher->registerEventHandler(CCLevelUpConsts::EVENT_LATEST_SCORE_CHANGED,
                [this](__Dictionary *parameters) {
                    CCScore *score = CCSoomlaLevelUp::getInstance()->getScore(parameters->valueForKey("scoreId")->getCString());
                    CC_ASSERT(score);
                    this->onLatestScoreChanged(score);
                });

        eventDispatcher->registerEventHandler(CCLevelUpConsts::EVENT_SCORE_RECORD_REACHED,
                [this](__Dictionary *parameters) {
                    CCScore *score = CCSoomlaLevelUp::getInstance()->getScore(parameters->valueForKey("scoreId")->getCString());
                    CC_ASSERT(score);
                    this->onScoreRecordReached(score);
                });

        eventDispatcher->registerEventHandler(CCLevelUpConsts::EVENT_SCORE_RECORD_CHANGED,
                [this](__Dictionary *parameters) {
                    CCScore *score = CCSoomlaLevelUp::getInstance()->getScore(parameters->valueForKey("scoreId")->getCString());
                    CC_ASSERT(score);
                    this->onScoreRecordChanged(score);
                });

        eventDispatcher->registerEventHandler(CCLevelUpConsts::EVENT_GATE_OPENED,
                [this](__Dictionary *parameters) {
                    CCGate *gate = CCSoomlaLevelUp::getInstance()->getGate(parameters->valueForKey("gateId")->getCString());
                    CC_ASSERT(gate);
                    this->onGateOpened(gate);
                });
        
        eventDispatcher->registerEventHandler(CCLevelUpConsts::EVENT_GATE_CLOSED,
                [this](__Dictionary *parameters) {
                    CCGate *gate = CCSoomlaLevelUp::getInstance()->getGate(parameters->valueForKey("gateId")->getCString());
                    CC_ASSERT(gate);
                    this->onGateClosed(gate);
                });

        eventDispatcher->registerEventHandler(CCLevelUpConsts::EVENT_MISSION_COMPLETED,
                [this](__Dictionary *parameters) {
                    CCMission *mission = CCSoomlaLevelUp::getInstance()->getMission(parameters->valueForKey("missionId")->getCString());
                    CC_ASSERT(mission);
                    this->onMissionCompleted(mission);
                });

        eventDispatcher->registerEventHandler(CCLevelUpConsts::EVENT_MISSION_COMPLETION_REVOKED,
                [this](__Dictionary *parameters) {
                    CCMission *mission = CCSoomlaLevelUp::getInstance()->getMission(parameters->valueForKey("missionId")->getCString());
                    CC_ASSERT(mission);
                    this->onMissionCompletionRevoked(mission);
                });

        eventDispatcher->registerEventHandler(CCLevelUpConsts::EVENT_WORLD_COMPLETED,
                [this](__Dictionary *parameters) {
                    CCWorld *world = CCSoomlaLevelUp::getInstance()->getWorld(parameters->valueForKey("worldId")->getCString());
                    CC_ASSERT(world);
                    this->onWorldCompleted(world);
                });
        
        eventDispatcher->registerEventHandler(CCLevelUpConsts::EVENT_WORLD_LAST_COMPLETED_INNER_WORLD_CHANGED,
                [this](__Dictionary *parameters) {
                    CCWorld *world = CCSoomlaLevelUp::getInstance()->getWorld(parameters->valueForKey("worldId")->getCString());
                    CC_ASSERT(world);
                    const __String *innerWorldId = parameters->valueForKey("innerWorldId");
                    CC_ASSERT(innerWorldId);
                    this->onLastCompletedInnerWorldChanged(world, innerWorldId->clone());
                });

        eventDispatcher->registerEventHandler(CCLevelUpConsts::EVENT_WORLD_REWARD_ASSIGNED,
                [this](__Dictionary *parameters) {
                    CCWorld *world = CCSoomlaLevelUp::getInstance()->getWorld(parameters->valueForKey("worldId")->getCString());
                    CC_ASSERT(world);
                    this->onWorldRewardAssigned(world);
                });

        eventDispatcher->registerEventHandler(CCLevelUpConsts::EVENT_LEVEL_STARTED,
                [this](__Dictionary *parameters) {
                    CCLevel *level = (CCLevel *) CCSoomlaLevelUp::getInstance()->getWorld(parameters->valueForKey("levelId")->getCString());
                    CC_ASSERT(level);
                    this->onLevelStarted(level);
                });

        eventDispatcher->registerEventHandler(CCLevelUpConsts::EVENT_LEVEL_ENDED,
                [this](__Dictionary *parameters) {
                    CCLevel *level = (CCLevel *) CCSoomlaLevelUp::getInstance()->getWorld(parameters->valueForKey("levelId")->getCString());
                    CC_ASSERT(level);
                    this->onLevelEnded(level);
                });

        return true;
    }

    void CCLevelUpEventDispatcher::onLevelUpInitialized() {
        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(CCLevelUpConsts::EVENT_LEVEL_UP_INITIALIZED);
    }

    void CCLevelUpEventDispatcher::onGateOpened(CCGate *gate) {
        __Dictionary *eventData = __Dictionary::create();
        eventData->setObject(gate, CCLevelUpConsts::DICT_ELEMENT_GATE);
        
        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(CCLevelUpConsts::EVENT_GATE_OPENED, eventData);
    }

    void CCLevelUpEventDispatcher::onGateClosed(CCGate *gate) {
        __Dictionary *eventData = __Dictionary::create();
        eventData->setObject(gate, CCLevelUpConsts::DICT_ELEMENT_GATE);
        
        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(CCLevelUpConsts::EVENT_GATE_CLOSED, eventData);
    }

    void CCLevelUpEventDispatcher::onMissionCompleted(CCMission *mission) {
        __Dictionary *eventData = __Dictionary::create();
        eventData->setObject(mission, CCLevelUpConsts::DICT_ELEMENT_MISSION);
        
        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(CCLevelUpConsts::EVENT_MISSION_COMPLETED, eventData);
    }

    void CCLevelUpEventDispatcher::onMissionCompletionRevoked(CCMission *mission) {
        __Dictionary *eventData = __Dictionary::create();
        eventData->setObject(mission, CCLevelUpConsts::DICT_ELEMENT_MISSION);
        
        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(CCLevelUpConsts::EVENT_MISSION_COMPLETION_REVOKED, eventData);
    }

    void CCLevelUpEventDispatcher::onLatestScoreChanged(CCScore *score) {
        __Dictionary *eventData = __Dictionary::create();
        eventData->setObject(score, CCLevelUpConsts::DICT_ELEMENT_SCORE);
        
        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(CCLevelUpConsts::EVENT_LATEST_SCORE_CHANGED, eventData);
    }

    void CCLevelUpEventDispatcher::onScoreRecordReached(CCScore *score) {
        __Dictionary *eventData = __Dictionary::create();
        eventData->setObject(score, CCLevelUpConsts::DICT_ELEMENT_SCORE);
        
        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(CCLevelUpConsts::EVENT_SCORE_RECORD_REACHED, eventData);
    }

    void CCLevelUpEventDispatcher::onScoreRecordChanged(CCScore *score) {
        __Dictionary *eventData = __Dictionary::create();
        eventData->setObject(score, CCLevelUpConsts::DICT_ELEMENT_SCORE);
        
        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(CCLevelUpConsts::EVENT_SCORE_RECORD_CHANGED, eventData);
    }

    void CCLevelUpEventDispatcher::onWorldCompleted(CCWorld *world) {
        __Dictionary *eventData = __Dictionary::create();
        eventData->setObject(world, CCLevelUpConsts::DICT_ELEMENT_WORLD);
        
        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(CCLevelUpConsts::EVENT_WORLD_COMPLETED, eventData);
    }

    void CCLevelUpEventDispatcher::onLastCompletedInnerWorldChanged(CCWorld *world, cocos2d::__String *innerWorldId) {
        __Dictionary *eventData = __Dictionary::create();
        eventData->setObject(world, CCLevelUpConsts::DICT_ELEMENT_WORLD);
        eventData->setObject(innerWorldId, CCLevelUpConsts::DICT_ELEMENT_INNER_WORLD);
        
        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(CCLevelUpConsts::EVENT_WORLD_LAST_COMPLETED_INNER_WORLD_CHANGED, eventData);
    }

    void CCLevelUpEventDispatcher::onWorldRewardAssigned(CCWorld *world) {
        __Dictionary *eventData = __Dictionary::create();
        eventData->setObject(world, CCLevelUpConsts::DICT_ELEMENT_WORLD);
        
        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(CCLevelUpConsts::EVENT_WORLD_REWARD_ASSIGNED, eventData);
    }

    void CCLevelUpEventDispatcher::onLevelStarted(CCLevel *level) {
        __Dictionary *eventData = __Dictionary::create();
        eventData->setObject(level, CCLevelUpConsts::DICT_ELEMENT_LEVEL);
        
        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(CCLevelUpConsts::EVENT_LEVEL_STARTED, eventData);
    }

    void CCLevelUpEventDispatcher::onLevelEnded(CCLevel *level) {
        __Dictionary *eventData = __Dictionary::create();
        eventData->setObject(level, CCLevelUpConsts::DICT_ELEMENT_LEVEL);
        
        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(CCLevelUpConsts::EVENT_LEVEL_ENDED, eventData);
    }
}
