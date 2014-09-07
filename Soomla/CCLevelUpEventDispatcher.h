//
// Created by Fedor Shubin on 6/19/14.
//

#ifndef __CCLevelUpEventDispatcher_H_
#define __CCLevelUpEventDispatcher_H_

#include "CCLevelUpEventHandler.h"
#include "CCAbstractAggregatedEventHandler.h"
#include "CCScore.h"
#include "CCWorld.h"
#include "CCLevel.h"

namespace soomla {
    class CCLevelUpEventDispatcher
            : public CCAbstractAggregatedEventHandler<CCLevelUpEventHandler>, public CCLevelUpEventHandler {
    public:
        /**
        This class is singleton, access it with this function.
        */
        static CCLevelUpEventDispatcher *getInstance();

        bool init();


        virtual void onLevelUpInitialized();

        virtual void onGateOpened(CCGate *gate);

        virtual void onMissionCompleted(CCMission *mission);
        virtual void onMissionCompletionRevoked(CCMission *mission);

        virtual void onScoreRecordReached(CCScore *score);
        virtual void onScoreRecordChanged(CCScore *score);

        virtual void onWorldCompleted(CCWorld *world);
        virtual void onWorldRewardAssigned(CCWorld *world);

        virtual void onLevelStarted(CCLevel *level);
        virtual void onLevelEnded(CCLevel *level);

    private:
        void handle__EVENT_LEVEL_UP_INITIALIZED(cocos2d::CCDictionary *parameters);
        void handle__EVENT_SCORE_RECORD_REACHED(cocos2d::CCDictionary *parameters);
        void handle__EVENT_SCORE_RECORD_CHANGED(cocos2d::CCDictionary *parameters);
        void handle__EVENT_GATE_OPENED(cocos2d::CCDictionary *parameters);
        void handle__EVENT_MISSION_COMPLETED(cocos2d::CCDictionary *parameters);
        void handle__EVENT_MISSION_COMPLETION_REVOKED(cocos2d::CCDictionary *parameters);
        void handle__EVENT_WORLD_COMPLETED(cocos2d::CCDictionary *parameters);
        void handle__EVENT_WORLD_REWARD_ASSIGNED(cocos2d::CCDictionary *parameters);
        void handle__EVENT_LEVEL_STARTED(cocos2d::CCDictionary *parameters);
        void handle__EVENT_LEVEL_ENDED(cocos2d::CCDictionary *parameters);
    };
}


#endif //__CCLevelUpEventDispatcher_H_
