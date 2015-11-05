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
#include "CCLevel.h"

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
         Sets the last (given) duration for the given `Level`.
         @param level `Level` to set last duration.
         @param duration Duration to set.
         */
        virtual void setLastDurationMillis(CCLevel *level, long duration);
        
        /**
         Retrieves the last duration for the given `Level`.
         @param level `Level` to get last duration.
         @return The last duration of the given `Level`.
         */
        virtual long getLastDurationMillis(CCLevel *level);
        
        /**
         Sets the slowest (given) duration for the given level.
         @param level `Level` to set slowest duration.</param>
         @param duration Duration to set.
         */
        virtual void setSlowestDurationMillis(CCLevel *level, long duration);

        /**
         Retrieves the slowest duration for the given level.
         @return The slowest duration of the given `Level`.
         @param level `Level` to get slowest duration.
         */
        virtual long getSlowestDurationMillis(CCLevel *level);

        /**
         Sets the fastest (given) duration for the given `Level`.
         @param level `Level` to set fastest duration.
         @param duration Duration to set.
         */
        virtual void setFastestDurationMillis(CCLevel *level, long duration);

        /**
         Retrieves the fastest duration for the given `Level`.
         @param level `Level` to get fastest duration.
         @return The fastest duration of the given `Level`.
         */
        virtual long getFastestDurationMillis(CCLevel *level);

        /**
         Increases by 1 the number of times the given `Level` has been started.
         @param level `Level` to increase its times started.
         @return The number of times started after increasing.
         */
        virtual int incTimesStarted(CCLevel *level);

        /**
         Decreases by 1 the number of times the given `Level` has been started.
         @param level `Level` to decrease its times started.
         @return The number of times started after decreasing.
         */
        virtual int decTimesStarted(CCLevel *level);

        /**
         Retrieves the number of times this `Level` has been started.
         @param level `Level` whose times started is to be retrieved.
         @return The number of times started.
         */
        virtual int getTimesStarted(CCLevel *level);

        /**
         Retrieves the number of times this `Level` has been played.
         @param level `Level` whose times played is to be retrieved.
         @return The number of times played.
         */
        virtual int getTimesPlayed(CCLevel *level);

        /**
         Increases by 1 the number of times the given `Level` has been played.
         @param level `Level` to increase its times played.
         @return The number of times played after increasing.
         */
        virtual int incTimesPlayed(CCLevel *level);

        /**
         Decreases by 1 the number of times the given `Level` has been played.
         @param level `Level` to decrease its times played.
         @return The number of times played after decreasing.
         */
        virtual int decTimesPlayed(CCLevel *level);
        
        /**
         Retrieves the number of times this `Level` has been completed.
         @param level `Level` whose times completed is to be retrieved.
         @return The number of times completed.
         */
        virtual int getTimesCompleted(CCLevel *level);
        
        /**
         Increases by 1 the number of times the given `Level` has been completed.
         @param level `Level` to increase its times completed.
         @return The number of times completed after increasing.
         */
        virtual int incTimesCompleted(CCLevel *level);
        
        /**
         Decreases by 1 the number of times the given `Level` has been completed.
         @param level `Level` to decrease its times completed.
         @return The number of times completed after decreasing.
         */
        virtual int decTimesCompleted(CCLevel *level);

        static char const *getKeyLevelPrefix();

    private:

        void setTimesStarted(CCLevel *level, int started);

        void setTimesPlayed(CCLevel *level, int played);

        void setTimesCompleted(CCLevel *level, int timesCompleted);

        char const *keyLastDurationWithLevelId(char const *levelId);
        
        char const *keySlowestDurationWithLevelId(char const *levelId);

        char const *keyFastestDurationWithLevelId(char const *levelId);

        char const *keyLevelsWithLevelId(char const *levelId, char const *postfix);

        char const *keyTimesCompletedWithLevelId(char const *levelId);

        char const *keyTimesStartedWithLevelId(char const *levelId);

        char const *keyTimesPlayedWithLevelId(char const *levelId);
    };
}

#endif //__CCLevelStorage_H_
