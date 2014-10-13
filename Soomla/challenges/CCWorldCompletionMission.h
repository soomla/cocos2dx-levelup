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



#ifndef __CCWorldCompletionMission_H_
#define __CCWorldCompletionMission_H_

#include "CCMission.h"

namespace soomla {

    /**
     @class `CCWorldCompletionMission`
     @brief A specific type of `Mission` that has an associated `World`.
     The `Mission` is complete once the `World` has been completed.
     */
    class CCWorldCompletionMission: public CCMission {
    public:
        CCWorldCompletionMission(): CCMission() {
        }

        /**
         Creates an instance of `CCWorldCompletionMission`.
         @param id ID.
         @param name Name.
         @param associatedWorldId World that needs to be completed.
         */
        static CCWorldCompletionMission *create(cocos2d::__String *id, cocos2d::__String *name,
                cocos2d::__String *associatedWorldId);

        /**
         Creates an instance of `CCWorldCompletionMission`.
         @param id ID.
         @param name Name.
         @param rewards Rewards for this mission.
         @param associatedWorldId World that needs to be completed.
         */
        static CCWorldCompletionMission *create(cocos2d::__String *id, cocos2d::__String *name,
                cocos2d::__Array *rewards, cocos2d::__String *associatedWorldId);

        SL_CREATE_WITH_DICTIONARY(CCWorldCompletionMission);

        virtual const char *getType() const;
    };

}

#endif //__CCWorldCompletionMission_H_
