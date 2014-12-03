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


#ifndef __CCScoreStorage_H_
#define __CCScoreStorage_H_

#include "cocos2d.h"
#include "CCMission.h"

namespace soomla {

    class CCScore;

    /**
     @class `CCScoreStorage`
     @brief A utility class for persisting and querying `Score`s and records.
     Use this class to get or set the values of `Score`s and records.
     */
    class CCScoreStorage: cocos2d::CCObject {

    public:

        static CCScoreStorage *getInstance();

        /**
         Sets the given `Score` to the given value.
         @param score `Score` to set.
         @param latest The value to set for the `Score`.
         */
        void setLatestScore(CCScore *score, double newValue);

        /**
         Retrieves the most recently saved value of the given `Score`.
         @param score Score whose most recent value it to be retrieved.
         @return The latest `Score`.
         */
        double getLatestScore(CCScore *score);

        /**
         Sets the given record for the given `Score`.
         @param score `Score` whose record is to change.
         @param record The new record.
         */
        void setRecordScore(CCScore *score, double newValue);

        /**
         Retrieves the record of the given `Score`.
         @param score `Score` whose record is to be retrieved.
         @return The record value of the given `Score`.
         */
        double getRecordScore(CCScore *score);
    };
}

#endif //__CCGateStorage_H_
