//
// Created by Fedor Shubin on 6/19/14.
//

#include "CCLevelUpEventDispatcher.h"
#include "CCSoomlaEventDispatcher.h"
#include "CCScore.h"

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

//        eventDispatcher->registerEventHandler(CCLevelUpConsts::EVENT_BILLING_NOT_SUPPORTED,
//                [this](__Dictionary *parameters) {
//                    this->onBillingNotSupported();
//                });
        return true;
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


}