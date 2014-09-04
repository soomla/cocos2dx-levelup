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
    };
}


#endif //__CCLevelUpEventDispatcher_H_
