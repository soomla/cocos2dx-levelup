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
// Created by Shubin Fedor on 19/08/14.
// Copyright (c) 2014 SOOMLA. All rights reserved.
//


#ifndef __CCSimpleLevelUpEventHandler_H_
#define __CCSimpleLevelUpEventHandler_H_

#include "CCLevelUpEventHandler.h"

namespace soomla {
    
    /**
     @class 
     @brief This class implements the functions in `CCLevelUpEventHandler` so 
     that if you want to implement only some, not all, of the functions in that
     class you can just use this class instead. 
     */
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
