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
                this, (SEL_EventHandler) (&CCLevelUpEventDispatcher::handle__EVENT_LEVEL_UP_INITIALIZED));
        
        eventDispatcher->registerEventHandler(CCLevelUpConsts::EVENT_LATEST_SCORE_CHANGED,
                this, (SEL_EventHandler) (&CCLevelUpEventDispatcher::handle__EVENT_LATEST_SCORE_CHANGED));

        eventDispatcher->registerEventHandler(CCLevelUpConsts::EVENT_SCORE_RECORD_REACHED,
                this, (SEL_EventHandler) (&CCLevelUpEventDispatcher::handle__EVENT_SCORE_RECORD_REACHED));

        eventDispatcher->registerEventHandler(CCLevelUpConsts::EVENT_SCORE_RECORD_CHANGED,
                this, (SEL_EventHandler) (&CCLevelUpEventDispatcher::handle__EVENT_SCORE_RECORD_CHANGED));

        eventDispatcher->registerEventHandler(CCLevelUpConsts::EVENT_GATE_OPENED,
                this, (SEL_EventHandler) (&CCLevelUpEventDispatcher::handle__EVENT_GATE_OPENED));
        
        eventDispatcher->registerEventHandler(CCLevelUpConsts::EVENT_GATE_CLOSED,
                this, (SEL_EventHandler) (&CCLevelUpEventDispatcher::handle__EVENT_GATE_CLOSED));

        eventDispatcher->registerEventHandler(CCLevelUpConsts::EVENT_MISSION_COMPLETED,
                this, (SEL_EventHandler) (&CCLevelUpEventDispatcher::handle__EVENT_MISSION_COMPLETED));

        eventDispatcher->registerEventHandler(CCLevelUpConsts::EVENT_MISSION_COMPLETION_REVOKED,
                this, (SEL_EventHandler) (&CCLevelUpEventDispatcher::handle__EVENT_MISSION_COMPLETION_REVOKED));

        eventDispatcher->registerEventHandler(CCLevelUpConsts::EVENT_WORLD_COMPLETED,
                this, (SEL_EventHandler) (&CCLevelUpEventDispatcher::handle__EVENT_WORLD_COMPLETED));
        
        eventDispatcher->registerEventHandler(CCLevelUpConsts::EVENT_WORLD_LAST_COMPLETED_INNER_WORLD_CHANGED,
                this, (SEL_EventHandler) (&CCLevelUpEventDispatcher::handle__EVENT_WORLD_LAST_COMPLETED_INNER_WORLD_CHANGED));

        eventDispatcher->registerEventHandler(CCLevelUpConsts::EVENT_WORLD_REWARD_ASSIGNED,
                this, (SEL_EventHandler) (&CCLevelUpEventDispatcher::handle__EVENT_WORLD_REWARD_ASSIGNED));

        eventDispatcher->registerEventHandler(CCLevelUpConsts::EVENT_LEVEL_STARTED,
                this, (SEL_EventHandler) (&CCLevelUpEventDispatcher::handle__EVENT_LEVEL_STARTED));

        eventDispatcher->registerEventHandler(CCLevelUpConsts::EVENT_LEVEL_ENDED,
                this, (SEL_EventHandler) (&CCLevelUpEventDispatcher::handle__EVENT_LEVEL_ENDED));

        return true;
    }

    void CCLevelUpEventDispatcher::onLevelUpInitialized() {
        CCNotificationCenter::sharedNotificationCenter()->postNotification(CCLevelUpConsts::EVENT_LEVEL_UP_INITIALIZED);
    }

    void CCLevelUpEventDispatcher::onGateOpened(CCGate *gate) {
        CCDictionary *eventData = CCDictionary::create();
        eventData->setObject(gate, CCLevelUpConsts::DICT_ELEMENT_GATE);
        
        CCNotificationCenter::sharedNotificationCenter()->postNotification(CCLevelUpConsts::EVENT_GATE_OPENED, eventData);
    }

    void CCLevelUpEventDispatcher::onGateClosed(CCGate *gate) {
        CCDictionary *eventData = CCDictionary::create();
        eventData->setObject(gate, CCLevelUpConsts::DICT_ELEMENT_GATE);
        
        CCNotificationCenter::sharedNotificationCenter()->postNotification(CCLevelUpConsts::EVENT_GATE_CLOSED, eventData);
    }

    void CCLevelUpEventDispatcher::onMissionCompleted(CCMission *mission) {
        CCDictionary *eventData = CCDictionary::create();
        eventData->setObject(mission, CCLevelUpConsts::DICT_ELEMENT_MISSION);
        
        CCNotificationCenter::sharedNotificationCenter()->postNotification(CCLevelUpConsts::EVENT_MISSION_COMPLETED, eventData);
    }

    void CCLevelUpEventDispatcher::onMissionCompletionRevoked(CCMission *mission) {
        CCDictionary *eventData = CCDictionary::create();
        eventData->setObject(mission, CCLevelUpConsts::DICT_ELEMENT_MISSION);
        
        CCNotificationCenter::sharedNotificationCenter()->postNotification(CCLevelUpConsts::EVENT_MISSION_COMPLETION_REVOKED, eventData);
    }

    void CCLevelUpEventDispatcher::onLatestScoreChanged(CCScore *score) {
        CCDictionary *eventData = CCDictionary::create();
        eventData->setObject(score, CCLevelUpConsts::DICT_ELEMENT_SCORE);
        
        CCNotificationCenter::sharedNotificationCenter()->postNotification(CCLevelUpConsts::EVENT_LATEST_SCORE_CHANGED, eventData);
    }

    void CCLevelUpEventDispatcher::onScoreRecordReached(CCScore *score) {
        CCDictionary *eventData = CCDictionary::create();
        eventData->setObject(score, CCLevelUpConsts::DICT_ELEMENT_SCORE);
        
        CCNotificationCenter::sharedNotificationCenter()->postNotification(CCLevelUpConsts::EVENT_SCORE_RECORD_REACHED, eventData);
    }

    void CCLevelUpEventDispatcher::onScoreRecordChanged(CCScore *score) {
        CCDictionary *eventData = CCDictionary::create();
        eventData->setObject(score, CCLevelUpConsts::DICT_ELEMENT_SCORE);
        
        CCNotificationCenter::sharedNotificationCenter()->postNotification(CCLevelUpConsts::EVENT_SCORE_RECORD_CHANGED, eventData);
    }

    void CCLevelUpEventDispatcher::onWorldCompleted(CCWorld *world) {
        CCDictionary *eventData = CCDictionary::create();
        eventData->setObject(world, CCLevelUpConsts::DICT_ELEMENT_WORLD);
        
        CCNotificationCenter::sharedNotificationCenter()->postNotification(CCLevelUpConsts::EVENT_WORLD_COMPLETED, eventData);
    }

    void CCLevelUpEventDispatcher::onLastCompletedInnerWorldChanged(CCWorld *world, cocos2d::CCString *innerWorldId) {
        CCDictionary *eventData = CCDictionary::create();
        eventData->setObject(world, CCLevelUpConsts::DICT_ELEMENT_WORLD);
        eventData->setObject(innerWorldId, CCLevelUpConsts::DICT_ELEMENT_INNER_WORLD);
        
        CCNotificationCenter::sharedNotificationCenter()->postNotification(CCLevelUpConsts::EVENT_WORLD_LAST_COMPLETED_INNER_WORLD_CHANGED, eventData);
    }

    void CCLevelUpEventDispatcher::onWorldRewardAssigned(CCWorld *world) {
        CCDictionary *eventData = CCDictionary::create();
        eventData->setObject(world, CCLevelUpConsts::DICT_ELEMENT_WORLD);
        
        CCNotificationCenter::sharedNotificationCenter()->postNotification(CCLevelUpConsts::EVENT_WORLD_REWARD_ASSIGNED, eventData);
    }

    void CCLevelUpEventDispatcher::onLevelStarted(CCLevel *level) {
        CCDictionary *eventData = CCDictionary::create();
        eventData->setObject(level, CCLevelUpConsts::DICT_ELEMENT_LEVEL);
        
        CCNotificationCenter::sharedNotificationCenter()->postNotification(CCLevelUpConsts::EVENT_LEVEL_STARTED, eventData);
    }

    void CCLevelUpEventDispatcher::onLevelEnded(CCLevel *level) {
        CCDictionary *eventData = CCDictionary::create();
        eventData->setObject(level, CCLevelUpConsts::DICT_ELEMENT_LEVEL);
        
        CCNotificationCenter::sharedNotificationCenter()->postNotification(CCLevelUpConsts::EVENT_LEVEL_ENDED, eventData);
    }


    void CCLevelUpEventDispatcher::handle__EVENT_LEVEL_UP_INITIALIZED(cocos2d::CCDictionary *parameters) {
        this->onLevelUpInitialized();
    }

    void CCLevelUpEventDispatcher::handle__EVENT_LATEST_SCORE_CHANGED(cocos2d::CCDictionary *parameters) {
        CCScore *score = CCSoomlaLevelUp::getInstance()->getScore(parameters->valueForKey("scoreId")->getCString());
        CC_ASSERT(score);
        this->onLatestScoreChanged(score);
    }

    void CCLevelUpEventDispatcher::handle__EVENT_SCORE_RECORD_REACHED(cocos2d::CCDictionary *parameters) {
        CCScore *score = CCSoomlaLevelUp::getInstance()->getScore(parameters->valueForKey("scoreId")->getCString());
        CC_ASSERT(score);
        this->onScoreRecordReached(score);
    }

    void CCLevelUpEventDispatcher::handle__EVENT_SCORE_RECORD_CHANGED(cocos2d::CCDictionary *parameters) {
        CCScore *score = CCSoomlaLevelUp::getInstance()->getScore(parameters->valueForKey("scoreId")->getCString());
        CC_ASSERT(score);
        this->onScoreRecordChanged(score);
    }

    void CCLevelUpEventDispatcher::handle__EVENT_GATE_OPENED(cocos2d::CCDictionary *parameters) {
        CCGate *gate = CCSoomlaLevelUp::getInstance()->getGate(parameters->valueForKey("gateId")->getCString());
        CC_ASSERT(gate);
        this->onGateOpened(gate);
    }

    void CCLevelUpEventDispatcher::handle__EVENT_GATE_CLOSED(cocos2d::CCDictionary *parameters) {
        CCGate *gate = CCSoomlaLevelUp::getInstance()->getGate(parameters->valueForKey("gateId")->getCString());
        CC_ASSERT(gate);
        this->onGateClosed(gate);
    }

    void CCLevelUpEventDispatcher::handle__EVENT_MISSION_COMPLETED(cocos2d::CCDictionary *parameters) {
        CCMission *mission = CCSoomlaLevelUp::getInstance()->getMission(parameters->valueForKey("missionId")->getCString());
        CC_ASSERT(mission);
        this->onMissionCompleted(mission);
    }

    void CCLevelUpEventDispatcher::handle__EVENT_MISSION_COMPLETION_REVOKED(cocos2d::CCDictionary *parameters) {
        CCMission *mission = CCSoomlaLevelUp::getInstance()->getMission(parameters->valueForKey("missionId")->getCString());
        CC_ASSERT(mission);
        this->onMissionCompletionRevoked(mission);
    }

    void CCLevelUpEventDispatcher::handle__EVENT_WORLD_COMPLETED(cocos2d::CCDictionary *parameters) {
        CCWorld *world = CCSoomlaLevelUp::getInstance()->getWorld(parameters->valueForKey("worldId")->getCString());
        CC_ASSERT(world);
        this->onWorldCompleted(world);
    }

    void CCLevelUpEventDispatcher::handle__EVENT_WORLD_LAST_COMPLETED_INNER_WORLD_CHANGED(cocos2d::CCDictionary *parameters) {
        CCWorld *world = CCSoomlaLevelUp::getInstance()->getWorld(parameters->valueForKey("worldId")->getCString());
        CC_ASSERT(world);
        const CCString *innerWorldId = parameters->valueForKey("innerWorldId");
        CC_ASSERT(innerWorldId);
        this->onLastCompletedInnerWorldChanged(world, CCString::create(innerWorldId->getCString()));
    }

    void CCLevelUpEventDispatcher::handle__EVENT_WORLD_REWARD_ASSIGNED(cocos2d::CCDictionary *parameters) {
        CCWorld *world = CCSoomlaLevelUp::getInstance()->getWorld(parameters->valueForKey("worldId")->getCString());
        CC_ASSERT(world);
        this->onWorldRewardAssigned(world);
    }

    void CCLevelUpEventDispatcher::handle__EVENT_LEVEL_STARTED(cocos2d::CCDictionary *parameters) {
        CCLevel *level = (CCLevel *) CCSoomlaLevelUp::getInstance()->getWorld(parameters->valueForKey("levelId")->getCString());
        CC_ASSERT(level);
        this->onLevelStarted(level);
    }

    void CCLevelUpEventDispatcher::handle__EVENT_LEVEL_ENDED(cocos2d::CCDictionary *parameters) {
        CCLevel *level = (CCLevel *) CCSoomlaLevelUp::getInstance()->getWorld(parameters->valueForKey("levelId")->getCString());
        CC_ASSERT(level);
        this->onLevelEnded(level);
    }
}
