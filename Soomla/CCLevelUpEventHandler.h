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

#ifndef __CCLevelUpEventHandler__
#define __CCLevelUpEventHandler__

#include "cocos2d.h"

namespace soomla {
    class CCMission;
    class CCGate;
    class CCScore;
    class CCWorld;
    class CCLevel;

    class CCLevelUpEventHandler : public cocos2d::CCObject {
    public:
        virtual void onLevelUpInitialized() = 0;

        virtual void onScoreRecordReached(CCScore *score) = 0;
        virtual void onScoreRecordChanged(CCScore *score) = 0;

        virtual void onGateOpened(CCGate *gate) = 0;

        virtual void onMissionCompleted(CCMission *mission) = 0;
        virtual void onMissionCompletionRevoked(CCMission *mission) = 0;

        virtual void onWorldCompleted(CCWorld *world) = 0;
        virtual void onWorldRewardAssigned(CCWorld *world) = 0;

        virtual void onLevelStarted(CCLevel *level) = 0;
        virtual void onLevelEnded(CCLevel *level) = 0;
    };
};

#endif //__CCLevelUpEventHandler__
