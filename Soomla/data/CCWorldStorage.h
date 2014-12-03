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


#ifndef __CCWorldStorage_H_
#define __CCWorldStorage_H_

#include "cocos2d.h"
#include "CCMission.h"
#include "CCWorld.h"

namespace soomla {

    class CCWorld;

    /**
     @class `CCWorldStorage`
     @brief A utility class for persisting and querying `World`s.
     Use this class to get or set the completion of `World`s and assign rewards.
     */
    class CCWorldStorage: cocos2d::CCObject {

    public:

        static CCWorldStorage *getInstance();

        /**
         Sets the given `World` as completed if `completed` is `true`.
         @param world `World` to set as completed.
         @param completed If set to `true` the `World` will be set
         as completed.
         @param notify If set to `true` trigger events.
         */
        void setCompleted(CCWorld *world, bool completed, bool notify);
        void setCompleted(CCWorld *world, bool completed);

        /**
         Determines if the given `World` is completed.
         @param world `World` to determine if completed.
         @return If the given `World` is completed returns `true`;
         otherwise `false`.
         */
        bool isCompleted(CCWorld *world);

        /**
         Assigns the reward with the given reward ID to the given `World`.
         @param world `World` to assign a reward to.
         @param rewardId ID of reward to assign.
         */
        void setReward(CCWorld *world, cocos2d::CCString *rewardId);

        /**
         Retrieves the given `World`'s assigned reward.
         @param world `World` whose reward is to be retrieved.
         @return The assigned reward to retrieve.
         */
        cocos2d::CCString *getAssignedReward(CCWorld *world);
    };
}

#endif //__CCWorldStorage_H_
