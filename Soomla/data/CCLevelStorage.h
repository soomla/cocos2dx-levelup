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


#ifndef __CCLevelStorage_H_
#define __CCLevelStorage_H_

#include "cocos2d.h"

namespace soomla {

    class CCLevel;

    /**
     @class `CCLevelStorage`
     @brief A utility class for persisting and querying the state of `Level`s.
     Use this class to get or set information about a `Level`, such as the play
     duration, start or end time, etc.
     */
    class CCLevelStorage: cocos2d::Ref {

    public:

        static CCLevelStorage *getInstance();

        /**
         Sets the slowest (given) duration for the given level.
         @param level `Level` to set slowest duration.</param>
         @param duration Duration to set.
         */
        void setSlowestDurationMillis(CCLevel *level, long duration);

        /**
         Retrieves the slowest duration for the given level.
         @return The slowest duration of the given `Level`.
         @param level `Level` to get slowest duration.
         */
        long getSlowestDurationMillis(CCLevel *level);

        /**
         Sets the fastest (given) duration for the given `Level`.
         @param level `Level` to set fastest duration.
         @param duration Duration to set.
         */
        void setFastestDurationMillis(CCLevel *level, long duration);

        /**
         Retrieves the fastest duration for the given `Level`.
         @param level `Level` to get fastest duration.
         @return The fastest duration of the given `Level`.
         */
        long getFastestDurationMillis(CCLevel *level);

        /**
         Increases by 1 the number of times the given `Level` has been started.
         @param level `Level` to increase its times started.
         @return The number of times started after increasing.
         */
        int incTimesStarted(CCLevel *level);

        /**
         Decreases by 1 the number of times the given `Level` has been started.
         @param level `Level` to decrease its times started.
         @return The number of times started after decreasing.
         */
        int decTimesStarted(CCLevel *level);

        /**
         Retrieves the number of times this `Level` has been started.
         @param level `Level` whose times started is to be retrieved.
         @return The number of times started.
         */
        int getTimesStarted(CCLevel *level);

        /**
         Retrieves the number of times this `Level` has been played.
         @param level `Level` whose times played is to be retrieved.
         @return The number of times played.
         */
        int getTimesPlayed(CCLevel *level);

        /**
         Increases by 1 the number of times the given `Level` has been played.
         @param level `Level` to increase its times played.
         @return The number of times played after increasing.
         */
        int incTimesPlayed(CCLevel *level);

        /**
         Decreases by 1 the number of times the given `Level` has been played.
         @param level `Level` to decrease its times played.
         @return The number of times played after decreasing.
         */
        int decTimesPlayed(CCLevel *level);
        
        /**
         Retrieves the number of times this `Level` has been completed.
         @param level `Level` whose times completed is to be retrieved.
         @return The number of times completed.
         */
        int getTimesCompleted(CCLevel *level);
        
        /**
         Increases by 1 the number of times the given `Level` has been completed.
         @param level `Level` to increase its times completed.
         @return The number of times completed after increasing.
         */
        int incTimesCompleted(CCLevel *level);
        
        /**
         Decreases by 1 the number of times the given `Level` has been completed.
         @param level `Level` to decrease its times completed.
         @return The number of times completed after decreasing.
         */
        int decTimesCompleted(CCLevel *level);

    private:

    };
}

#endif //__CCLevelStorage_H_
