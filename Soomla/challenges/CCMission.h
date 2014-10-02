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


#ifndef __CCMission_H_
#define __CCMission_H_

#include "CCSoomlaMacros.h"
#include "CCSoomlaEntity.h"
#include "CCSchedule.h"
#include "CCGate.h"
#include "CCSimpleLevelUpEventHandler.h"

namespace soomla {

    /**
     @class `CCMission`
     @brief A `Mission` is a task your users need to complete in your game. 
     Each `Mission`s is associated with a `Gate` that defines the criteria for 
     completing the `Mission`. You can optionally choose to give a `Reward` for 
     users that complete your `Mission`. Create `Mission`s and use them as 
     single, independent, entities OR you can create a `Challenge` to handle 
     several `Mission`s and monitor their completion.
     NOTE: `Mission`s can be completed multiple times.
     */
    class CCMission: public CCSoomlaEntity {
        friend class CCMissionEventHandler;
        friend class CCChallengeEventHandler;
        CC_SYNTHESIZE_RETAIN(cocos2d::CCArray *, mRewards, Rewards)
        CC_SYNTHESIZE_RETAIN(CCSchedule *, mSchedule, Schedule)
        CC_SYNTHESIZE_RETAIN(CCGate *, mGate, Gate);

        CC_SYNTHESIZE_RETAIN(CCLevelUpEventHandler *, mEventHandler, EventHandler);
        
    public:
        
        CCMission(): CCSoomlaEntity(), mRewards(NULL), mSchedule(NULL), mGate(NULL), mEventHandler(NULL) {
        }
        
        /**
         Creates an instance of `CCMission`.
         @param id ID of this `Mission`.
         @param name Name of this `Mission`.
         @param rewards `Reward`s for this `Mission`.
         @param gateInitParams Gate init parameters.
         */
        static CCMission *create(cocos2d::CCString *id, cocos2d::CCString *name,
                cocos2d::CCArray *rewards = NULL, cocos2d::CCDictionary *gateInitParams = NULL);

        SL_CREATE_WITH_DICTIONARY(CCMission);

        bool init(cocos2d::CCString *id, cocos2d::CCString *name,
                cocos2d::CCArray *rewards = NULL, cocos2d::CCDictionary *gateInitParams = NULL);
        
        virtual bool initWithDictionary(cocos2d::CCDictionary* dict);

        virtual ~CCMission();
        
        virtual const char *getType() const;
        
        /**
         Converts this `Mission` into a Dictionary.
         @return The Dictionary object.
         */
        virtual cocos2d::CCDictionary* toDictionary();
        
        /**
         Generates a gate ID for this `Mission`.
         @return "gate_" followed by this `Mission`'s ID.
         */
        cocos2d::CCString *autoGateId();
        
        /**
         Determines whether this `Mission` is available by checking the criteria
         that makes the specific `Mission` available.
         @return If this instance is available returns `true`; otherwise `false`.
         */
        virtual bool isAvailable();
        
        /**
         Checks if this `Mission` has ever been completed.
         @return If this instance is completed returns `true`; otherwise `false`.
         */
        virtual bool isCompleted();
        
        /**
         Completes this `Mission`'s by opening its `Gate`.
         @return If `Schedule` doesn't approve, the mission cannot be completed
         and thus returns `false`; otherwise opens this `Mission`'s `Gate` and 
         returns `true` if successful.
         */
        bool complete();
        
        /**
         Forces completion of this `Mission`. This function should not be used 
         in standard scenarios.
         */
        void forceComplete();
        
    protected:
        
        /**
         Registers relevant events: `OnGateOpened`.
         */
        virtual void registerEvents();
        
        /**
         Unregisters relevant events: `OnGateOpened`.
         */
        virtual void unregisterEvents();
        
        /**
         Sets this `Mission` as completed and gives or takes `Reward`s according
         to the given `completed` value.
         @param completed If set to `true` gives rewards.
         */
        void setCompletedInner(bool completed);

    private:
        
        void takeRewards();
        
        void giveRewards();
    };

    class CCMissionEventHandler: public CCSimpleLevelUpEventHandler {
        
    private:
        
        CCMission *mMission;
        
    public:
        
        CCMissionEventHandler(): mMission(NULL) {

        }
        
        /**
         Creates an instance of `CCMissionEventHandler`. 
         @param mission The `Mission` for this event handler.
         */
        static CCMissionEventHandler *create(CCMission *mission);
        
        /**
         Handles gate-opened events.
         @param gate The `Gate` that triggered the event.
         */
        virtual void onGateOpened(CCGate *gate);
    };
}

#endif //__CCMission_H_
