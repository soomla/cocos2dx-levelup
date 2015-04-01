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

#include "CCLevelUpConsts.h"

namespace soomla {

    /** Global **/
    char const *CCLevelUpConsts::JSON_LU_ASSOCITEMID        = "associatedItemId";
    char const *CCLevelUpConsts::JSON_LU_ASSOCSCOREID       = "associatedScoreId";
    char const *CCLevelUpConsts::JSON_LU_ASSOCWORLDID       = "associatedWorldId";
    char const *CCLevelUpConsts::JSON_LU_DESIRED_RECORD     = "desiredRecord";
    char const *CCLevelUpConsts::JSON_LU_DESIRED_BALANCE    = "desiredBalance";

    /** LevelUp **/
    char const *CCLevelUpConsts::JSON_LU_MAIN_WORLD         = "mainWorld";

    /** Score **/
    char const *CCLevelUpConsts::JSON_LU_SCORES             = "scores";
    char const *CCLevelUpConsts::JSON_LU_SCORE_STARTVAL     = "startValue";
    char const *CCLevelUpConsts::JSON_LU_SCORE_HIGHBETTER   = "higherBetter";
    char const *CCLevelUpConsts::JSON_LU_SCORE_RANGE        = "range";
    char const *CCLevelUpConsts::JSON_LU_SCORE_RANGE_LOW    = "low";
    char const *CCLevelUpConsts::JSON_LU_SCORE_RANGE_HIGH   = "high";

    /** Gate **/
    char const *CCLevelUpConsts::JSON_LU_GATE               = "gate";
    char const *CCLevelUpConsts::JSON_LU_GATES              = "gates";

    /** Challenge **/
    char const *CCLevelUpConsts::JSON_LU_CHALLENGES         = "challenges";
    char const *CCLevelUpConsts::JSON_LU_MISSIONS           = "missions";

    /** World **/
    char const *CCLevelUpConsts::JSON_LU_WORLDS             = "worlds";

    /** Profile **/
    char const *CCLevelUpConsts::JSON_LU_SOCIAL_PROVIDER = "provider";
    char const *CCLevelUpConsts::JSON_LU_PAGE_NAME = "pageName";
    char const *CCLevelUpConsts::JSON_LU_STATUS = "status";
    char const *CCLevelUpConsts::JSON_LU_MESSAGE = "message";
    char const *CCLevelUpConsts::JSON_LU_STORY_NAME = "name";
    char const *CCLevelUpConsts::JSON_LU_CAPTION = "caption";
    char const *CCLevelUpConsts::JSON_LU_LINK = "link";
    char const *CCLevelUpConsts::JSON_LU_IMG_LINK = "imgLink";
    char const *CCLevelUpConsts::JSON_LU_FILE_NAME = "fileName";

    /** Types **/
    char const *CCLevelUpConsts::JSON_JSON_TYPE_MISSION     = "Mission";
    char const *CCLevelUpConsts::JSON_JSON_TYPE_BALANCE_MISSION = "BalanceMission";
    char const *CCLevelUpConsts::JSON_JSON_TYPE_CHALLENGE   = "Challenge";
    char const *CCLevelUpConsts::JSON_JSON_TYPE_PURCHASE_MISSION = "PurchasingMission";
    char const *CCLevelUpConsts::JSON_JSON_TYPE_RECORD_MISSION = "RecordMission";
    char const *CCLevelUpConsts::JSON_JSON_TYPE_WORLD_COMPLETION_MISSION = "WorldCompletionMission";
    char const *CCLevelUpConsts::JSON_JSON_TYPE_SOCIAL_LIKE_MISSION = "SocialLikeMission";
    char const *CCLevelUpConsts::JSON_JSON_TYPE_SOCIAL_STATUS_MISSION = "SocialStatusMission";
    char const *CCLevelUpConsts::JSON_JSON_TYPE_SOCIAL_STORY_MISSION = "SocialStoryMission";
    char const *CCLevelUpConsts::JSON_JSON_TYPE_SOCIAL_UPLOAD_MISSION = "SocialUploadMission";

    char const *CCLevelUpConsts::JSON_JSON_TYPE_GATE        = "Gate";
    char const *CCLevelUpConsts::JSON_JSON_TYPE_BALANCE_GATE = "BalanceGate";
    char const *CCLevelUpConsts::JSON_JSON_TYPE_GATES_LIST_AND = "GatesListAND";
    char const *CCLevelUpConsts::JSON_JSON_TYPE_GATES_LIST_OR = "GatesListOR";
    char const *CCLevelUpConsts::JSON_JSON_TYPE_PURCHASABLE_GATE = "PurchasableGate";
    char const *CCLevelUpConsts::JSON_JSON_TYPE_RECORD_GATE = "RecordGate";
    char const *CCLevelUpConsts::JSON_JSON_TYPE_SCHEDULE_GATE = "ScheduleGate";
    char const *CCLevelUpConsts::JSON_JSON_TYPE_WORLD_COMPLETION_GATE = "WorldCompletionGate";
    char const *CCLevelUpConsts::JSON_JSON_TYPE_SOCIAL_LIKE_GATE = "SocialLikeGate";
    char const *CCLevelUpConsts::JSON_JSON_TYPE_SOCIAL_STATUS_GATE = "SocialStatusGate";
    char const *CCLevelUpConsts::JSON_JSON_TYPE_SOCIAL_STORY_GATE = "SocialStoryGate";
    char const *CCLevelUpConsts::JSON_JSON_TYPE_SOCIAL_UPLOAD_GATE = "SocialUploadGate";

    char const *CCLevelUpConsts::JSON_JSON_TYPE_SCORE       = "Score";
    char const *CCLevelUpConsts::JSON_JSON_TYPE_RANGE_SCORE = "RangeScore";
    char const *CCLevelUpConsts::JSON_JSON_TYPE_VIRTUAL_ITEM_SCORE = "VirtualItemScore";

    char const *CCLevelUpConsts::JSON_JSON_TYPE_WORLD       = "World";
    char const *CCLevelUpConsts::JSON_JSON_TYPE_LEVEL       = "Level";
    
    char const *CCLevelUpConsts::DICT_ELEMENT_SCORE = "score";
    char const *CCLevelUpConsts::DICT_ELEMENT_GATE = "gate";
    char const *CCLevelUpConsts::DICT_ELEMENT_REWARD = "reward";
    char const *CCLevelUpConsts::DICT_ELEMENT_WORLD = "world";
    char const *CCLevelUpConsts::DICT_ELEMENT_MISSION = "mission";
    char const *CCLevelUpConsts::DICT_ELEMENT_LEVEL = "level";
    char const *CCLevelUpConsts::DICT_ELEMENT_INNER_WORLD = "innerWorld";

    char const *CCLevelUpConsts::EVENT_LEVEL_UP_INITIALIZED = "CCLevelUpEventHandler::onLevelUpInitialized";
    char const *CCLevelUpConsts::EVENT_SCORE_RECORD_CHANGED = "CCLevelUpEventHandler::onScoreRecordChanged";
    char const *CCLevelUpConsts::EVENT_SCORE_RECORD_REACHED = "CCLevelUpEventHandler::onScoreRecordReached";
    char const *CCLevelUpConsts::EVENT_LATEST_SCORE_CHANGED = "CCLevelUpEventHandler::onLatestScoreChanged";
    char const *CCLevelUpConsts::EVENT_GATE_OPENED = "CCLevelUpEventHandler::onGateOpened";
    char const *CCLevelUpConsts::EVENT_GATE_CLOSED = "CCLevelUpEventHandler::onGateClosed";
    char const *CCLevelUpConsts::EVENT_MISSION_COMPLETED = "CCLevelUpEventHandler::onMissionCompleted";
    char const *CCLevelUpConsts::EVENT_MISSION_COMPLETION_REVOKED = "CCLevelUpEventHandler::onMissionCompletionRevoked";
    char const *CCLevelUpConsts::EVENT_WORLD_COMPLETED = "CCLevelUpEventHandler::onWorldCompleted";
    char const *CCLevelUpConsts::EVENT_WORLD_LAST_COMPLETED_INNER_WORLD_CHANGED = "CCLevelUpEventHandler::onLastCompletedInnerWorldChanged";
    char const *CCLevelUpConsts::EVENT_WORLD_REWARD_ASSIGNED = "CCLevelUpEventHandler::onWorldRewardAssigned";
    char const *CCLevelUpConsts::EVENT_LEVEL_STARTED = "CCLevelUpEventHandler::onLevelStarted";
    char const *CCLevelUpConsts::EVENT_LEVEL_ENDED = "CCLevelUpEventHandler::onLevelEnded";

}