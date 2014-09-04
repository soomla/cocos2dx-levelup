//
// Created by Shubin Fedor on 19/08/14.
// Copyright (c) 2014 SOOMLA. All rights reserved.
//


#ifndef __CCSimpleLevelUpEventHandler_H_
#define __CCSimpleLevelUpEventHandler_H_

#include "CCLevelUpEventHandler.h"

namespace soomla {
    class CCSimpleLevelUpEventHandler: public CCLevelUpEventHandler {
    public:
        virtual void onLevelUpInitialized();

        virtual void onGateOpened(CCGate* gate);

        virtual void onMissionCompleted(CCMission* completedMission);
        virtual void onMissionCompletionRevoked(CCMission* mission);

        virtual void onScoreRecordReached(CCScore *score);
        virtual void onScoreRecordChanged(CCScore *score);

        virtual void onWorldCompleted(CCWorld *world);
        virtual void onWorldRewardAssigned(CCWorld *world);

        virtual void onLevelStarted(CCLevel *level);
        virtual void onLevelEnded(CCLevel *level);
    };
}

#endif //__CCSimpleLevelUpEventHandler_H_
