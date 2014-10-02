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
// Created by Fedor Shubin on 6/19/14.
//

#include "CCLevelUpEventDispatcher.h"
#include "CCSoomlaEventDispatcher.h"
#include "CCDomainFactory.h"
#include "CCLevelUp.h"

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

        if (!CCAbstractAggregatedEventHandler::init()) {
            return false;
        }

        CCSoomlaEventDispatcher *eventDispatcher = CCSoomlaEventDispatcher::getInstance();

        eventDispatcher->registerEventHandler(CCLevelUpConsts::EVENT_LEVEL_UP_INITIALIZED,
                this, (SEL_EventHandler) (&CCLevelUpEventDispatcher::handle__EVENT_LEVEL_UP_INITIALIZED));

        eventDispatcher->registerEventHandler(CCLevelUpConsts::EVENT_SCORE_RECORD_REACHED,
                this, (SEL_EventHandler) (&CCLevelUpEventDispatcher::handle__EVENT_SCORE_RECORD_REACHED));

        eventDispatcher->registerEventHandler(CCLevelUpConsts::EVENT_SCORE_RECORD_CHANGED,
                this, (SEL_EventHandler) (&CCLevelUpEventDispatcher::handle__EVENT_SCORE_RECORD_CHANGED));

        eventDispatcher->registerEventHandler(CCLevelUpConsts::EVENT_GATE_OPENED,
                this, (SEL_EventHandler) (&CCLevelUpEventDispatcher::handle__EVENT_GATE_OPENED));

        eventDispatcher->registerEventHandler(CCLevelUpConsts::EVENT_MISSION_COMPLETED,
                this, (SEL_EventHandler) (&CCLevelUpEventDispatcher::handle__EVENT_MISSION_COMPLETED));

        eventDispatcher->registerEventHandler(CCLevelUpConsts::EVENT_MISSION_COMPLETION_REVOKED,
                this, (SEL_EventHandler) (&CCLevelUpEventDispatcher::handle__EVENT_MISSION_COMPLETION_REVOKED));

        eventDispatcher->registerEventHandler(CCLevelUpConsts::EVENT_WORLD_COMPLETED,
                this, (SEL_EventHandler) (&CCLevelUpEventDispatcher::handle__EVENT_WORLD_COMPLETED));

        eventDispatcher->registerEventHandler(CCLevelUpConsts::EVENT_WORLD_REWARD_ASSIGNED,
                this, (SEL_EventHandler) (&CCLevelUpEventDispatcher::handle__EVENT_WORLD_REWARD_ASSIGNED));

        eventDispatcher->registerEventHandler(CCLevelUpConsts::EVENT_LEVEL_STARTED,
                this, (SEL_EventHandler) (&CCLevelUpEventDispatcher::handle__EVENT_LEVEL_STARTED));

        eventDispatcher->registerEventHandler(CCLevelUpConsts::EVENT_LEVEL_ENDED,
                this, (SEL_EventHandler) (&CCLevelUpEventDispatcher::handle__EVENT_LEVEL_ENDED));

        return true;
    }

    void CCLevelUpEventDispatcher::onLevelUpInitialized() {
        FOR_EACH_EVENT_HANDLER(CCLevelUpEventHandler)
            eventHandler->onLevelUpInitialized();
        }
    }

    void CCLevelUpEventDispatcher::onGateOpened(CCGate *gate) {
        lockEventHandlers();
        
        FOR_EACH_EVENT_HANDLER(CCLevelUpEventHandler)
            eventHandler->onGateOpened(gate);
        }

        unlockEventHandlers();
    }

    void CCLevelUpEventDispatcher::onMissionCompleted(CCMission *mission) {
        lockEventHandlers();
        
        FOR_EACH_EVENT_HANDLER(CCLevelUpEventHandler)
            eventHandler->onMissionCompleted(mission);
        }

        unlockEventHandlers();
    }

    void CCLevelUpEventDispatcher::onMissionCompletionRevoked(CCMission *mission) {
        lockEventHandlers();
        
        FOR_EACH_EVENT_HANDLER(CCLevelUpEventHandler)
            eventHandler->onMissionCompletionRevoked(mission);
        }

        unlockEventHandlers();
    }

    void CCLevelUpEventDispatcher::onScoreRecordReached(CCScore *score) {
        lockEventHandlers();
        
        FOR_EACH_EVENT_HANDLER(CCLevelUpEventHandler)
            eventHandler->onScoreRecordReached(score);
        }

        unlockEventHandlers();
    }

    void CCLevelUpEventDispatcher::onScoreRecordChanged(CCScore *score) {
        lockEventHandlers();
        
        FOR_EACH_EVENT_HANDLER(CCLevelUpEventHandler)
            eventHandler->onScoreRecordChanged(score);
        }

        unlockEventHandlers();
    }

    void CCLevelUpEventDispatcher::onWorldCompleted(CCWorld *world) {
        lockEventHandlers();
        
        FOR_EACH_EVENT_HANDLER(CCLevelUpEventHandler)
            eventHandler->onWorldCompleted(world);
        }

        unlockEventHandlers();
    }

    void CCLevelUpEventDispatcher::onWorldRewardAssigned(CCWorld *world) {
        lockEventHandlers();
        
        FOR_EACH_EVENT_HANDLER(CCLevelUpEventHandler)
            eventHandler->onWorldRewardAssigned(world);
        }

        unlockEventHandlers();
    }

    void CCLevelUpEventDispatcher::onLevelStarted(CCLevel *level) {
        lockEventHandlers();
        
        FOR_EACH_EVENT_HANDLER(CCLevelUpEventHandler)
            eventHandler->onLevelStarted(level);
        }

        unlockEventHandlers();
    }

    void CCLevelUpEventDispatcher::onLevelEnded(CCLevel *level) {
        lockEventHandlers();
        
        FOR_EACH_EVENT_HANDLER(CCLevelUpEventHandler)
            eventHandler->onLevelEnded(level);
        }

        unlockEventHandlers();
    }


    void CCLevelUpEventDispatcher::handle__EVENT_LEVEL_UP_INITIALIZED(cocos2d::CCDictionary *parameters) {
        this->onLevelUpInitialized();
    }

    void CCLevelUpEventDispatcher::handle__EVENT_SCORE_RECORD_REACHED(cocos2d::CCDictionary *parameters) {
        CCScore *score = CCLevelUp::getInstance()->getScore(parameters->valueForKey("scoreId")->getCString());
        CC_ASSERT(score);
        this->onScoreRecordReached(score);
    }

    void CCLevelUpEventDispatcher::handle__EVENT_SCORE_RECORD_CHANGED(cocos2d::CCDictionary *parameters) {
        CCScore *score = CCLevelUp::getInstance()->getScore(parameters->valueForKey("scoreId")->getCString());
        CC_ASSERT(score);
        this->onScoreRecordChanged(score);
    }

    void CCLevelUpEventDispatcher::handle__EVENT_GATE_OPENED(cocos2d::CCDictionary *parameters) {
        CCGate *gate = CCLevelUp::getInstance()->getGate(parameters->valueForKey("gateId")->getCString());
        CC_ASSERT(gate);
        this->onGateOpened(gate);
    }

    void CCLevelUpEventDispatcher::handle__EVENT_MISSION_COMPLETED(cocos2d::CCDictionary *parameters) {
        CCMission *mission = CCLevelUp::getInstance()->getMission(parameters->valueForKey("missionId")->getCString());
        CC_ASSERT(mission);
        this->onMissionCompleted(mission);
    }

    void CCLevelUpEventDispatcher::handle__EVENT_MISSION_COMPLETION_REVOKED(cocos2d::CCDictionary *parameters) {
        CCMission *mission = CCLevelUp::getInstance()->getMission(parameters->valueForKey("missionId")->getCString());
        CC_ASSERT(mission);
        this->onMissionCompletionRevoked(mission);
    }

    void CCLevelUpEventDispatcher::handle__EVENT_WORLD_COMPLETED(cocos2d::CCDictionary *parameters) {
        CCWorld *world = CCLevelUp::getInstance()->getWorld(parameters->valueForKey("worldId")->getCString());
        CC_ASSERT(world);
        this->onWorldCompleted(world);
    }

    void CCLevelUpEventDispatcher::handle__EVENT_WORLD_REWARD_ASSIGNED(cocos2d::CCDictionary *parameters) {
        CCWorld *world = CCLevelUp::getInstance()->getWorld(parameters->valueForKey("worldId")->getCString());
        CC_ASSERT(world);
        this->onWorldRewardAssigned(world);
    }

    void CCLevelUpEventDispatcher::handle__EVENT_LEVEL_STARTED(cocos2d::CCDictionary *parameters) {
        CCLevel *level = (CCLevel *) CCLevelUp::getInstance()->getWorld(parameters->valueForKey("levelId")->getCString());
        CC_ASSERT(level);
        this->onLevelStarted(level);
    }

    void CCLevelUpEventDispatcher::handle__EVENT_LEVEL_ENDED(cocos2d::CCDictionary *parameters) {
        CCLevel *level = (CCLevel *) CCLevelUp::getInstance()->getWorld(parameters->valueForKey("levelId")->getCString());
        CC_ASSERT(level);
        this->onLevelEnded(level);
    }
}