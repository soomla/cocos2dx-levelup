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


#ifndef __CCMission_H_
#define __CCMission_H_

#include "CCSoomlaMacros.h"
#include "CCSoomlaEntity.h"
#include "CCSchedule.h"
#include "CCGate.h"

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
        CC_SYNTHESIZE_RETAIN(cocos2d::__Array *, mRewards, Rewards)
        CC_SYNTHESIZE_RETAIN(CCSchedule *, mSchedule, Schedule)

        CC_SYNTHESIZE_RETAIN(cocos2d::EventListener *, mEventListener, EventListener);

    public:

        CCMission(): CCSoomlaEntity(), mRewards(NULL), mSchedule(NULL), mGate(NULL), mEventListener(NULL) {
        }

        /**
         Creates an instance of `CCMission`.
         @param id ID of this `Mission`.
         @param name Name of this `Mission`.
         @param rewards `Reward`s for this `Mission`.
         @param gateInitParams Gate init parameters.
         */
        static CCMission *create(cocos2d::__String *id, cocos2d::__String *name,
                cocos2d::__Array *rewards = NULL, cocos2d::__Dictionary *gateInitParams = NULL);

        SL_CREATE_WITH_DICTIONARY(CCMission);

        bool init(cocos2d::__String *id, cocos2d::__String *name,
                cocos2d::__Array *rewards = NULL, cocos2d::__Dictionary *gateInitParams = NULL);

        virtual bool initWithDictionary(cocos2d::__Dictionary* dict);

        virtual ~CCMission();

        virtual const char *getType() const;

        /**
         Converts this `Mission` into a Dictionary.
         @return The Dictionary object.
         */
        virtual cocos2d::__Dictionary* toDictionary();

        /**
         Generates a gate ID for this `Mission`.
         @return "gate_" followed by this `Mission`'s ID.
         */
        cocos2d::__String *autoGateId();

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
        
        virtual CCGate *getGate() const;
        virtual void setGate(CCGate *gate);

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
        
        virtual void onGateOpened(cocos2d::EventCustom *event);

    private:

        void takeRewards();

        void giveRewards();
        
        CCGate *mGate;
    };
}

#endif //__CCMission_H_
