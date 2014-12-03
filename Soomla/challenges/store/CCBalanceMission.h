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


#ifndef __CCBalanceMission_H_
#define __CCBalanceMission_H_

#include "CCMission.h"

namespace soomla {

    class CCBalanceMission: public CCMission {

    public:
        /**
         @class `CCBalanceMission`
         @brief A specific type of `Mission` that has an associated virtual
         item and a desired balance. The `Mission` is complete once the item's
         balance reaches the desired balance.
         */
        CCBalanceMission(): CCMission() {
        }
        /**
         Creates an instance of `CCBalanceMission`.
         @param id `Mission` ID.
         @param name `Mission` name.
         @param associatedItemId ID of the item who's balance is examined.
         @param desiredBalance Desired balance.
         */
        static CCBalanceMission *create(cocos2d::CCString *id, cocos2d::CCString *name,
                cocos2d::CCString *associatedItemId, cocos2d::CCInteger *desiredBalance);

        /**
         Creates an instance of `CCBalanceMission`.
         @param id `Mission` ID.
         @param name `Mission` name.
         @param rewards `Reward`s for this `Mission`.
         @param associatedItemId ID of the item who's balance is examined.
         @param desiredBalance Desired balance.
         */
        static CCBalanceMission *create(cocos2d::CCString *id, cocos2d::CCString *name,
                cocos2d::CCArray *rewards, cocos2d::CCString *associatedItemId, cocos2d::CCInteger *desiredBalance);

        SL_CREATE_WITH_DICTIONARY(CCBalanceMission);

        virtual const char *getType() const;
    };
}

#endif //__CCBalanceMission_H_
