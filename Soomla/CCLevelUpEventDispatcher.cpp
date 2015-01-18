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

        if (!CCAbstractAggregatedEventHandler::init()) {
            return false;
        }

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

    void CCLevelUpEventDispatcher::onGateClosed(CCGate *gate) {
        lockEventHandlers();
        
        FOR_EACH_EVENT_HANDLER(CCLevelUpEventHandler)
            eventHandler->onGateClosed(gate);
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

    void CCLevelUpEventDispatcher::onLatestScoreChanged(CCScore *score) {
        lockEventHandlers();
        
        FOR_EACH_EVENT_HANDLER(CCLevelUpEventHandler)
            eventHandler->onLatestScoreChanged(score);
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
}
