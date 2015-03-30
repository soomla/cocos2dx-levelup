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
    class CCLevelUpConsts {
    public:
        /** Global **/
        static char const *JSON_LU_ASSOCITEMID;
        static char const *JSON_LU_ASSOCSCOREID;
        static char const *JSON_LU_ASSOCWORLDID;
        static char const *JSON_LU_DESIRED_RECORD;
        static char const *JSON_LU_DESIRED_BALANCE;

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

        /** Profile **/
        static char const *JSON_LU_SOCIAL_PROVIDER;
        static char const *JSON_LU_PAGE_NAME;
        static char const *JSON_LU_STATUS;
        static char const *JSON_LU_MESSAGE;
        static char const *JSON_LU_STORY_NAME;
        static char const *JSON_LU_CAPTION;
        static char const *JSON_LU_LINK;
        static char const *JSON_LU_IMG_LINK;
        static char const *JSON_LU_FILE_NAME;

        static char const *JSON_JSON_TYPE_MISSION;
        static char const *JSON_JSON_TYPE_BALANCE_MISSION;
        static char const *JSON_JSON_TYPE_CHALLENGE;
        static char const *JSON_JSON_TYPE_PURCHASE_MISSION;
        static char const *JSON_JSON_TYPE_RECORD_MISSION;
        static char const *JSON_JSON_TYPE_WORLD_COMPLETION_MISSION;
        static char const *JSON_JSON_TYPE_SOCIAL_LIKE_MISSION;
        static char const *JSON_JSON_TYPE_SOCIAL_STATUS_MISSION;
        static char const *JSON_JSON_TYPE_SOCIAL_STORY_MISSION;
        static char const *JSON_JSON_TYPE_SOCIAL_UPLOAD_MISSION;

        static char const *JSON_JSON_TYPE_GATE;
        static char const *JSON_JSON_TYPE_BALANCE_GATE;
        static char const *JSON_JSON_TYPE_GATES_LIST_AND;
        static char const *JSON_JSON_TYPE_GATES_LIST_OR;
        static char const *JSON_JSON_TYPE_PURCHASABLE_GATE;
        static char const *JSON_JSON_TYPE_RECORD_GATE;
        static char const *JSON_JSON_TYPE_SCHEDULE_GATE;
        static char const *JSON_JSON_TYPE_WORLD_COMPLETION_GATE;
        static char const *JSON_JSON_TYPE_SOCIAL_LIKE_GATE;
        static char const *JSON_JSON_TYPE_SOCIAL_STATUS_GATE;
        static char const *JSON_JSON_TYPE_SOCIAL_STORY_GATE;
        static char const *JSON_JSON_TYPE_SOCIAL_UPLOAD_GATE;

        static char const *JSON_JSON_TYPE_SCORE;
        static char const *JSON_JSON_TYPE_RANGE_SCORE;
        static char const *JSON_JSON_TYPE_VIRTUAL_ITEM_SCORE;

        static char const *JSON_JSON_TYPE_WORLD;
        static char const *JSON_JSON_TYPE_LEVEL;
        
        /** Events **/
        
        static char const *DICT_ELEMENT_SCORE;
        static char const *DICT_ELEMENT_GATE;
        static char const *DICT_ELEMENT_REWARD;
        static char const *DICT_ELEMENT_WORLD;
        static char const *DICT_ELEMENT_MISSION;
        static char const *DICT_ELEMENT_LEVEL;
        static char const *DICT_ELEMENT_INNER_WORLD;

        static char const *EVENT_LEVEL_UP_INITIALIZED;
        static char const *EVENT_LATEST_SCORE_CHANGED;
        static char const *EVENT_SCORE_RECORD_REACHED;
        static char const *EVENT_SCORE_RECORD_CHANGED;
        static char const *EVENT_GATE_OPENED;
        static char const *EVENT_GATE_CLOSED;
        static char const *EVENT_MISSION_COMPLETED;
        static char const *EVENT_MISSION_COMPLETION_REVOKED;
        static char const *EVENT_WORLD_COMPLETED;
        static char const *EVENT_WORLD_LAST_COMPLETED_INNER_WORLD_CHANGED;
        static char const *EVENT_WORLD_REWARD_ASSIGNED;
        static char const *EVENT_LEVEL_STARTED;
        static char const *EVENT_LEVEL_ENDED;

    };
}

#endif /* __CCLevelUpConsts_H__ */
