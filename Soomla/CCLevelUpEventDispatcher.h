//
// Created by Fedor Shubin on 6/19/14.
//

#ifndef __CCLevelUpEventDispatcher_H_
#define __CCLevelUpEventDispatcher_H_

#include "CCLevelUpEventHandler.h"
#include "CCAbstractAggregatedEventHandler.h"
#include "CCScore.h"
#include "CCWorld.h"

namespace soomla {
    class CCLevelUpEventDispatcher
            : public CCAbstractAggregatedEventHandler<CCLevelUpEventHandler>, public CCLevelUpEventHandler {
    public:
        /**
        This class is singleton, access it with this function.
        */
        static CCLevelUpEventDispatcher *getInstance();

        bool init();

        virtual void onGateOpened(CCGate *gate);

        virtual void onMissionCompleted(CCMission *mission);
        virtual void onMissionCompletionRevoked(CCMission *mission);

        virtual void onScoreRecordReached(CCScore *score);
        virtual void onScoreRecordChanged(CCScore *score);

        virtual void onWorldCompleted(CCWorld *world);
    };
}


#endif //__CCLevelUpEventDispatcher_H_
