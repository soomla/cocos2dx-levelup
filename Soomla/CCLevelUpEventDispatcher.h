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
    class CCLevelUpEventDispatcher : public cocos2d::CCObject {
    public:
        /**
        This class is singleton, access it with this function.
        */
        static CCLevelUpEventDispatcher *getInstance();

        bool init();

        /**
         Fired when initialization has been completed.
         
         Event Name - CCLevelUpConsts::EVENT_LEVEL_UP_INITIALIZED
         */
        virtual void onLevelUpInitialized();

        /**
         Fired when a CCGate has been opened.
         
         Event Name - CCLevelUpConsts::EVENT_GATE_OPENED
         Event Data (__Dictionary):
         CCLevelUpConsts::DICT_ELEMENT_GATE - CCGate - The gate which was opened
         */
        virtual void onGateOpened(CCGate *gate);
        /**
         Fired when a CCGate has been closed.
         
         Event Name - CCLevelUpConsts::EVENT_GATE_CLOSED
         Event Data (__Dictionary):
         CCLevelUpConsts::DICT_ELEMENT_GATE - CCGate - The gate which was closed
         balance has changed.
         */
        virtual void onGateClosed(CCGate *gate);

        /**
         Fired when a CCMission has been completed.
         
         Event Name - CCLevelUpConsts::EVENT_MISSION_COMPLETED
         Event Data (__Dictionary):
         CCLevelUpConsts::DICT_ELEMENT_MISSION - CCMission - the mission that 
         was completed.
         */
        virtual void onMissionCompleted(CCMission *mission);
        /**
         Fired when CCMission completion has been revoked.
         For example, you can decide to revoke a mission if the condition for 
         completing it is no longer valid
         
         Event Name - CCLevelUpConsts::EVENT_MISSION_COMPLETION_REVOKED
         Event Data (__Dictionary):
         CCLevelUpConsts::DICT_ELEMENT_MISSION - CCMission - the mission to be
         revoked.
         */
        virtual void onMissionCompletionRevoked(CCMission *mission);

        /**
         Fired when a latest score is changed.
         
         Event Name - CCLevelUpConsts::EVENT_SCORE_RECORD_CHANGED
         Event Data (__Dictionary):
         CCLevelUpConsts::DICT_ELEMENT_SCORE - CCScore - the score which has 
         been changed.
         */
        virtual void onLatestScoreChanged(CCScore *score);
        /**
         Fired when a new record has been reached for a score.
         
         Event Name - CCLevelUpConsts::EVENT_SCORE_RECORD_REACHED
         Event Data (__Dictionary):
         CCLevelUpConsts::DICT_ELEMENT_SCORE - CCScore - the score which has 
         reached a new record.
         */
        virtual void onScoreRecordReached(CCScore *score);
        /**
         Fired when a score's record is changed.
         
         Event Name - CCLevelUpConsts::EVENT_SCORE_RECORD_CHANGED
         Event Data (__Dictionary):
         CCLevelUpConsts::DICT_ELEMENT_SCORE - CCScore - the score which 
         has been changed.
         */
        virtual void onScoreRecordChanged(CCScore *score);

        /**
         Fired when a CCWorld has been completed.
         
         Event Name - CCLevelUpConsts::EVENT_WORLD_COMPLETED
         Event Data (__Dictionary):
         CCLevelUpConsts::DICT_ELEMENT_WORLD - CCWorld - the world which was 
         completed.
         */
        virtual void onWorldCompleted(CCWorld *world);
        /**
         Fired when the last completed world inside a world has changed.
         
         Event Name - CCLevelUpConsts::EVENT_WORLD_LAST_COMPLETED_INNER_WORLD_CHANGED
         Event Data (__Dictionary):
         CCLevelUpConsts::DICT_ELEMENT_WORLD - CCWorld - the world which had 
         last completed world changed.
         CCLevelUpConsts::DICT_ELEMENT_INNER_WORLD - __String - The inner world 
         ID which was last completed.
         */
        virtual void onLastCompletedInnerWorldChanged(CCWorld *world, cocos2d::CCString *innerWorldId);
        /**
         Fired when a CCWorld is being assigned a reward.
         
         Event Name - CCLevelUpConsts::EVENT_WORLD_REWARD_ASSIGNED
         Event Data (__Dictionary):
         CCLevelUpConsts::DICT_ELEMENT_WORLD - CCWorld - the World whose
         reward has changed.
         */
        virtual void onWorldRewardAssigned(CCWorld *world);

        /**
         Fired when a level has started, i.e. when start is called on an 
         instance of CCLevel
         
         Event Name - CCLevelUpConsts::EVENT_GOOD_BALANCE_CHANGED
         Event Data (__Dictionary):
         CCLevelUpConsts::EVENT_LEVEL_STARTED - CCLevel - the level which just 
         started.
         */
        virtual void onLevelStarted(CCLevel *level);
        /**
         Fired when a level has ended, i.e. when end is called on an
         instance of CCLevel
         
         Event Name - CCLevelUpConsts::EVENT_LEVEL_ENDED
         Event Data (__Dictionary):
         CCLevelUpConsts::EVENT_LEVEL_STARTED - CCLevel - the level which just 
         ended.
         */
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
