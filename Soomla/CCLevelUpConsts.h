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

#ifndef __CCLevelUpConsts_H__
#define __CCLevelUpConsts_H__

/**
* This class contains all static const String names of the keys/vals in the
* JSON being parsed all around the SDK.
*/
#include "CCCoreConsts.h"

namespace soomla {
    class CCLevelUpConsts : public CCCoreConsts {
    public:
        /** Global **/
        static char const *JSON_LU_ASSOCITEMID;
        static char const *JSON_LU_ASSOCSCOREID;
        static char const *JSON_LU_ASSOCWORLDID;
        static char const *JSON_LU_DESIRED_RECORD;
        static char const *JSON_LU_DESIRED_BALANCE;
        static char const *JSON_LU_NAME;

        /** LevelUp **/
        static char const *JSON_LU_MAIN_WORLD;

        /** Score **/
        static char const *JSON_LU_SCORES;
        static char const *JSON_LU_SCORE_STARTVAL;
        static char const *JSON_LU_SCORE_HIGHBETTER;
        static char const *JSON_LU_SCORE_RANGE;
        static char const *JSON_LU_SCORE_RANGE_LOW;
        static char const *JSON_LU_SCORE_RANGE_HIGH;

        /** Gate **/
        static char const *JSON_LU_GATE;
        static char const *JSON_LU_GATES;

        /** Challenge **/
        static char const *JSON_LU_CHALLENGES;
        static char const *JSON_LU_MISSIONS;

        /** World **/
        static char const *JSON_LU_WORLDS;

        static char const *JSON_JSON_TYPE_MISSION;
        static char const *JSON_JSON_TYPE_BALANCE_MISSION;
        static char const *JSON_JSON_TYPE_CHALLENGE;
        static char const *JSON_JSON_TYPE_PURCHASE_MISSION;
        static char const *JSON_JSON_TYPE_RECORD_MISSION;
        static char const *JSON_JSON_TYPE_WORLD_COMPLETION_MISSION;

        static char const *JSON_JSON_TYPE_GATE;
        static char const *JSON_JSON_TYPE_BALANCE_GATE;
        static char const *JSON_JSON_TYPE_GATES_LIST_AND;
        static char const *JSON_JSON_TYPE_GATES_LIST_OR;
        static char const *JSON_JSON_TYPE_PURCHASABLE_GATE;
        static char const *JSON_JSON_TYPE_RECORD_GATE;
        static char const *JSON_JSON_TYPE_SCHEDULE_GATE;
        static char const *JSON_JSON_TYPE_WORLD_COMPLETION_GATE;

        static char const *JSON_JSON_TYPE_SCORE;

        static char const *JSON_JSON_TYPE_WORLD;
        static char const *JSON_JSON_TYPE_LEVEL;

        static char const *EVENT_LEVEL_UP_INITIALIZED;
        static char const *EVENT_SCORE_RECORD_REACHED;
        static char const *EVENT_SCORE_RECORD_CHANGED;
        static char const *EVENT_GATE_OPENED;
        static char const *EVENT_MISSION_COMPLETED;
        static char const *EVENT_MISSION_COMPLETION_REVOKED;
        static char const *EVENT_WORLD_COMPLETED;
        static char const *EVENT_WORLD_REWARD_ASSIGNED;
        static char const *EVENT_LEVEL_STARTED;
        static char const *EVENT_LEVEL_ENDED;

    };
}

#endif /* __CCLevelUpConsts_H__ */
