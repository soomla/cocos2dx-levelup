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
                [this](__Dictionary *parameters) {
                    this->onLevelUpInitialized();
                });

        eventDispatcher->registerEventHandler(CCLevelUpConsts::EVENT_SCORE_RECORD_REACHED,
                [this](__Dictionary *parameters) {
                    CCScore *score = CCLevelUp::getInstance()->getScore(parameters->valueForKey("scoreId")->getCString());
                    CC_ASSERT(score);
                    this->onScoreRecordReached(score);
                });

        eventDispatcher->registerEventHandler(CCLevelUpConsts::EVENT_SCORE_RECORD_CHANGED,
                [this](__Dictionary *parameters) {
                    CCScore *score = CCLevelUp::getInstance()->getScore(parameters->valueForKey("scoreId")->getCString());
                    CC_ASSERT(score);
                    this->onScoreRecordChanged(score);
                });

        eventDispatcher->registerEventHandler(CCLevelUpConsts::EVENT_GATE_OPENED,
                [this](__Dictionary *parameters) {
                    CCGate *gate = CCLevelUp::getInstance()->getGate(parameters->valueForKey("gateId")->getCString());
                    CC_ASSERT(gate);
                    this->onGateOpened(gate);
                });

        eventDispatcher->registerEventHandler(CCLevelUpConsts::EVENT_MISSION_COMPLETED,
                [this](__Dictionary *parameters) {
                    CCMission *mission = CCLevelUp::getInstance()->getMission(parameters->valueForKey("missionId")->getCString());
                    CC_ASSERT(mission);
                    this->onMissionCompleted(mission);
                });

        eventDispatcher->registerEventHandler(CCLevelUpConsts::EVENT_MISSION_COMPLETION_REVOKED,
                [this](__Dictionary *parameters) {
                    CCMission *mission = CCLevelUp::getInstance()->getMission(parameters->valueForKey("missionId")->getCString());
                    CC_ASSERT(mission);
                    this->onMissionCompletionRevoked(mission);
                });

        eventDispatcher->registerEventHandler(CCLevelUpConsts::EVENT_WORLD_COMPLETED,
                [this](__Dictionary *parameters) {
                    CCWorld *world = CCLevelUp::getInstance()->getWorld(parameters->valueForKey("worldId")->getCString());
                    CC_ASSERT(world);
                    this->onWorldCompleted(world);
                });

        eventDispatcher->registerEventHandler(CCLevelUpConsts::EVENT_WORLD_REWARD_ASSIGNED,
                [this](__Dictionary *parameters) {
                    CCWorld *world = CCLevelUp::getInstance()->getWorld(parameters->valueForKey("worldId")->getCString());
                    CC_ASSERT(world);
                    this->onWorldRewardAssigned(world);
                });

        eventDispatcher->registerEventHandler(CCLevelUpConsts::EVENT_LEVEL_STARTED,
                [this](__Dictionary *parameters) {
                    CCLevel *level = (CCLevel *) CCLevelUp::getInstance()->getWorld(parameters->valueForKey("levelId")->getCString());
                    CC_ASSERT(level);
                    this->onLevelStarted(level);
                });

        eventDispatcher->registerEventHandler(CCLevelUpConsts::EVENT_LEVEL_ENDED,
                [this](__Dictionary *parameters) {
                    CCLevel *level = (CCLevel *) CCLevelUp::getInstance()->getWorld(parameters->valueForKey("levelId")->getCString());
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
        FOR_EACH_EVENT_HANDLER(CCLevelUpEventHandler)
            eventHandler->onGateOpened(gate);
        }
    }

    void CCLevelUpEventDispatcher::onMissionCompleted(CCMission *mission) {
        FOR_EACH_EVENT_HANDLER(CCLevelUpEventHandler)
            eventHandler->onMissionCompleted(mission);
        }
    }

    void CCLevelUpEventDispatcher::onMissionCompletionRevoked(CCMission *mission) {
        FOR_EACH_EVENT_HANDLER(CCLevelUpEventHandler)
            eventHandler->onMissionCompletionRevoked(mission);
        }
    }

    void CCLevelUpEventDispatcher::onScoreRecordReached(CCScore *score) {
        FOR_EACH_EVENT_HANDLER(CCLevelUpEventHandler)
            eventHandler->onScoreRecordReached(score);
        }
    }

    void CCLevelUpEventDispatcher::onScoreRecordChanged(CCScore *score) {
        FOR_EACH_EVENT_HANDLER(CCLevelUpEventHandler)
            eventHandler->onScoreRecordChanged(score);
        }
    }

    void CCLevelUpEventDispatcher::onWorldCompleted(CCWorld *world) {
        FOR_EACH_EVENT_HANDLER(CCLevelUpEventHandler)
            eventHandler->onWorldCompleted(world);
        }
    }

    void CCLevelUpEventDispatcher::onWorldRewardAssigned(CCWorld *world) {
        FOR_EACH_EVENT_HANDLER(CCLevelUpEventHandler)
            eventHandler->onWorldRewardAssigned(world);
        }
    }

    void CCLevelUpEventDispatcher::onLevelStarted(CCLevel *level) {
        FOR_EACH_EVENT_HANDLER(CCLevelUpEventHandler)
            eventHandler->onLevelStarted(level);
        }
    }

    void CCLevelUpEventDispatcher::onLevelEnded(CCLevel *level) {
        FOR_EACH_EVENT_HANDLER(CCLevelUpEventHandler)
            eventHandler->onLevelEnded(level);
        }
    }
}