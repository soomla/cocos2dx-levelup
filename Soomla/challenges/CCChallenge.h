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


#ifndef __CCChallenge_H_
#define __CCChallenge_H_

#include "CCMission.h"

namespace soomla {

    /**
     @class CCChallenge
     @brief A challenge is a specific type of `Mission` which holds a collection
     of `Mission`s. The user is required to complete all these `Mission`s in
     order to earn the `Reward` associated with the `Challenge`.
     */
    class CCChallenge: public CCMission {

        friend class CCChallengeEventHandler;

        CC_SYNTHESIZE_RETAIN(cocos2d::CCArray *, mMissions, Missions);
    public:

        CCChallenge(): CCMission(), mMissions(NULL) {
        }

        /**
         Creates an instance of `CCChallenge`.
         @param id `Challenge` ID.
         @param name `Challenge` name.
         @param missions `Mission`s that belong to this `Challenge`.
         @param rewards `Reward`s associated with this `Challenge`.
         */
        static CCChallenge *create(cocos2d::CCString *id, cocos2d::CCString *name,
                cocos2d::CCArray *missions = NULL, cocos2d::CCArray *rewards = NULL);

        SL_CREATE_WITH_DICTIONARY(CCChallenge);

        bool init(cocos2d::CCString *id, cocos2d::CCString *name,
                cocos2d::CCArray *missions = NULL, cocos2d::CCArray *rewards = NULL);

        virtual bool initWithDictionary(cocos2d::CCDictionary* dict);

        virtual ~CCChallenge();

        virtual const char *getType() const;

        /**
         Converts this `CCChallenge` to a Dictionary.
         @return The Dictionary that represents this `CCChallenge`.
         */
        virtual cocos2d::CCDictionary* toDictionary();

        /**
         Checks if this `CCChallenge` is completed.
         @return If this instance is completed returns `true`; otherwise `false`.
         */
        virtual bool isCompleted();

    protected:

        /**
         Registers relevant events: `OnMissionCompleted` and
         `OnMissionCompletionRevoked`.
         */
        void registerEvents();

        /**
         Unregisters relevant events: `OnMissionCompleted` and
         `OnMissionCompletionRevoked`.
         */
        void unregisterEvents();
    };

    class CCChallengeEventHandler: public CCSimpleLevelUpEventHandler {

    private:

        CCChallenge *mChallenge;

    public:

        CCChallengeEventHandler() : mChallenge(NULL) {
        }

        /**
         Creates an instance of `CCChallengeEventHandler`.
         @param challenge The `Challenge` for this event handler.
         */
        static CCChallengeEventHandler *create(CCChallenge *challenge);

        /**
         Handles mission-completion events. Checks if all `Mission`s included
         in this `Challenge` are completed, and if so, sets the `Challenge` as
         completed.
         @param completedMission The `Mission` that triggered the event.
         */
        void onMissionCompleted(CCMission *completedMission);

        /**
         Handles mission-revoked events. If the `Challenge` was completed
         before, but now one of its child `Mission`s is incomplete, the
         `Challenge` is revoked as well.
         @param mission The `Mission` that triggered the event.
         */
        void onMissionCompletionRevoked(CCMission *mission);
    };
}

#endif //__CCChallenge_H_
