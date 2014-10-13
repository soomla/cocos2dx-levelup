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

#ifndef __CCRecordMission_H_
#define __CCRecordMission_H_

#include "CCMission.h"

namespace soomla {

    /**
     @class `CCRecordMission`
     @brief A specific type of `Mission` that has an associated score and a desired
     record. The `Mission` is complete once the player achieves the desired
     record for the given score.
     */
    class CCRecordMission: public CCMission {

    public:

        CCRecordMission(): CCMission() {
        }

        /**
         Creates
         @param id ID.
         @param name Name.
         @param associatedScoreId ID of the score examined.
         @param desiredRecord Desired record.
         */
        static CCRecordMission *create(cocos2d::__String *id, cocos2d::__String *name,
                cocos2d::__String *associatedScoreId, cocos2d::__Double *desiredRecord);

        /**
         Constructor for `Mission` with rewards.
         @param id ID.
         @param name Name.
         @param rewards Rewards.
         @param associatedScoreId ID of the score examined.
         @param desiredRecord Desired record.
         */
        static CCRecordMission *create(cocos2d::__String *id, cocos2d::__String *name,
                cocos2d::__Array *rewards, cocos2d::__String *associatedScoreId, cocos2d::__Double *desiredRecord);

        SL_CREATE_WITH_DICTIONARY(CCRecordMission);

        virtual const char *getType() const;
    };
}

#endif //__CCRecordMission_H_
