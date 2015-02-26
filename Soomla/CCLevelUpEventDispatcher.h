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

#include "CCLevelUpEventHandler.h"
#include "CCAbstractAggregatedEventHandler.h"
#include "CCScore.h"
#include "CCWorld.h"
#include "CCLevel.h"

namespace soomla {

    /**
     @class CCLevelUpEventDispatcher
     @brief Calls event handler functions when events are fired

     Signs up to native LevelUp events. When the events arrive, this class calls
     event handler functions. To do that you must call addEventHandler().
     */
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
        virtual void onGateClosed(CCGate *gate);

        virtual void onMissionCompleted(CCMission *mission);
        virtual void onMissionCompletionRevoked(CCMission *mission);

        virtual void onLatestScoreChanged(CCScore *score);
        virtual void onScoreRecordReached(CCScore *score);
        virtual void onScoreRecordChanged(CCScore *score);

        virtual void onWorldCompleted(CCWorld *world);
        virtual void onLastCompletedInnerWorldChanged(CCWorld *world, cocos2d::CCString *innerWorldId);
        virtual void onWorldRewardAssigned(CCWorld *world);

        virtual void onLevelStarted(CCLevel *level);
        virtual void onLevelEnded(CCLevel *level);

    private:
        void handle__EVENT_LEVEL_UP_INITIALIZED(cocos2d::CCDictionary *parameters);
        void handle__EVENT_LATEST_SCORE_CHANGED(cocos2d::CCDictionary *parameters);
        void handle__EVENT_SCORE_RECORD_REACHED(cocos2d::CCDictionary *parameters);
        void handle__EVENT_SCORE_RECORD_CHANGED(cocos2d::CCDictionary *parameters);
        void handle__EVENT_GATE_OPENED(cocos2d::CCDictionary *parameters);
        void handle__EVENT_GATE_CLOSED(cocos2d::CCDictionary *parameters);
        void handle__EVENT_MISSION_COMPLETED(cocos2d::CCDictionary *parameters);
        void handle__EVENT_MISSION_COMPLETION_REVOKED(cocos2d::CCDictionary *parameters);
        void handle__EVENT_WORLD_COMPLETED(cocos2d::CCDictionary *parameters);
        void handle__EVENT_WORLD_LAST_COMPLETED_INNER_WORLD_CHANGED(cocos2d::CCDictionary *parameters);
        void handle__EVENT_WORLD_REWARD_ASSIGNED(cocos2d::CCDictionary *parameters);
        void handle__EVENT_LEVEL_STARTED(cocos2d::CCDictionary *parameters);
        void handle__EVENT_LEVEL_ENDED(cocos2d::CCDictionary *parameters);
    };
}


#endif //__CCLevelUpEventDispatcher_H_
