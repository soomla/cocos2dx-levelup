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



#ifndef __CCLevelUpEventDispatcher_H_
#define __CCLevelUpEventDispatcher_H_

#include "CCScore.h"
#include "CCWorld.h"
#include "CCLevel.h"

namespace soomla {

    /**
     @class CCLevelUpEventDispatcher
     @brief Fires event when recieved from the native implementation.

     Signs up to native LevelUp events. 
     When the events arrive this class fires the repective event through
     the Cocos2dx Event Dispatcher.
     */
    class CCLevelUpEventDispatcher : public cocos2d::Ref {
    public:
        /**
        This class is singleton, access it with this function.
        */
        static CCLevelUpEventDispatcher *getInstance();

        bool init();

        virtual void onLevelUpInitialized();

        virtual void onGateOpened(CCGate *gate);
        virtual void onGateClosed(CCGate *gate);

        virtual void onMissionCompleted(CCMission *mission);
        virtual void onMissionCompletionRevoked(CCMission *mission);

        virtual void onLatestScoreChanged(CCScore *score);
        virtual void onScoreRecordReached(CCScore *score);
        virtual void onScoreRecordChanged(CCScore *score);

        virtual void onWorldCompleted(CCWorld *world);
        virtual void onLastCompletedInnerWorldChanged(CCWorld *world, cocos2d::__String *innerWorldId);
        virtual void onWorldRewardAssigned(CCWorld *world);

        virtual void onLevelStarted(CCLevel *level);
        virtual void onLevelEnded(CCLevel *level);
    };
}


#endif //__CCLevelUpEventDispatcher_H_
