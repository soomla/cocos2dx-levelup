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


#ifndef __CCMissionStorage_H_
#define __CCMissionStorage_H_

#include "cocos2d.h"
#include "CCMission.h"

namespace soomla {

    /**
     @class
     @brief A utility class for persisting and querying the state of `Mission`s.
     Use this class to check if a certain `Mission` is complete, or to set its
     completion status.
     */
    class CCMissionStorage: cocos2d::CCObject {

    public:

        static CCMissionStorage *getInstance();

        /**
         Increases the number of times the given `Mission` has been completed
         if the given paramter `up` is `true`; otherwise decreases the number
         of times completed.
         @param mission `Mission` to set as completed.
         @param up If set to `true` add 1 to the number of times completed,
         otherwise subtract 1.
         @param notify If set to `true` trigger the relevant event according
         to the value of `up`.
         */
        void setCompleted(CCMission *mission, bool completed);
        void setCompleted(CCMission *mission, bool completed, bool notify);

        /**
         Determines if the given `Mission` is complete.
         @param mission `Mission` to determine if complete.
         @return If the given `Mission` is completed returns `true`;
         otherwise `false`.
         */
        bool isCompleted(CCMission *mission);

        /**
         Retrieves the number of times the given `Mission` has been completed.
         @param mission Mission.
         @return The number of times the given mission has been completed.
         */
        int getTimesCompleted(CCMission *mission);
    };
}

#endif //__CCMissionStorage_H_
