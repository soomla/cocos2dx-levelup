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
    char const *CCLevelUpConsts::JSON_JSON_TYPE_MISSION     = "mission";
    char const *CCLevelUpConsts::JSON_JSON_TYPE_BALANCE_MISSION = "balanceMission";
    char const *CCLevelUpConsts::JSON_JSON_TYPE_CHALLENGE   = "challenge";
    char const *CCLevelUpConsts::JSON_JSON_TYPE_PURCHASE_MISSION = "purchaseMission";
    char const *CCLevelUpConsts::JSON_JSON_TYPE_RECORD_MISSION = "recordMission";
    char const *CCLevelUpConsts::JSON_JSON_TYPE_WORLD_COMPLETION_MISSION = "worldCompletionMission";
    char const *CCLevelUpConsts::JSON_JSON_TYPE_SOCIAL_LIKE_MISSION = "socialLikeMission";
    char const *CCLevelUpConsts::JSON_JSON_TYPE_SOCIAL_STATUS_MISSION = "socialStatusMission";
    char const *CCLevelUpConsts::JSON_JSON_TYPE_SOCIAL_STORY_MISSION = "socialStoryMission";
    char const *CCLevelUpConsts::JSON_JSON_TYPE_SOCIAL_UPLOAD_MISSION = "socialUploadMission";

    char const *CCLevelUpConsts::JSON_JSON_TYPE_GATE        = "gate";
    char const *CCLevelUpConsts::JSON_JSON_TYPE_BALANCE_GATE = "balanceGate";
    char const *CCLevelUpConsts::JSON_JSON_TYPE_GATES_LIST_AND = "gatesListAnd";
    char const *CCLevelUpConsts::JSON_JSON_TYPE_GATES_LIST_OR = "gatesListOr";
    char const *CCLevelUpConsts::JSON_JSON_TYPE_PURCHASABLE_GATE = "purchasableGate";
    char const *CCLevelUpConsts::JSON_JSON_TYPE_RECORD_GATE = "recordGate";
    char const *CCLevelUpConsts::JSON_JSON_TYPE_SCHEDULE_GATE = "scheduleGate";
    char const *CCLevelUpConsts::JSON_JSON_TYPE_WORLD_COMPLETION_GATE = "worldCompletionGate";
    char const *CCLevelUpConsts::JSON_JSON_TYPE_SOCIAL_LIKE_GATE = "socialLikeGate";
    char const *CCLevelUpConsts::JSON_JSON_TYPE_SOCIAL_STATUS_GATE = "socialStatusGate";
    char const *CCLevelUpConsts::JSON_JSON_TYPE_SOCIAL_STORY_GATE = "socialStoryGate";
    char const *CCLevelUpConsts::JSON_JSON_TYPE_SOCIAL_UPLOAD_GATE = "socialUploadGate";

    char const *CCLevelUpConsts::JSON_JSON_TYPE_SCORE       = "score";
    char const *CCLevelUpConsts::JSON_JSON_TYPE_RANGE_SCORE = "rangeScore";
    char const *CCLevelUpConsts::JSON_JSON_TYPE_VIRTUAL_ITEM_SCORE = "virtualItemScore";

    char const *CCLevelUpConsts::JSON_JSON_TYPE_WORLD       = "world";
    char const *CCLevelUpConsts::JSON_JSON_TYPE_LEVEL       = "level";

    char const *CCLevelUpConsts::EVENT_LEVEL_UP_INITIALIZED = "CCLevelUpEventHandler::onLevelUpInitialized";
    char const *CCLevelUpConsts::EVENT_SCORE_RECORD_REACHED = "CCLevelUpEventHandler::onScoreRecordReached";
    char const *CCLevelUpConsts::EVENT_SCORE_RECORD_CHANGED = "CCLevelUpEventHandler::onScoreRecordChanged";
    char const *CCLevelUpConsts::EVENT_GATE_OPENED = "CCLevelUpEventHandler::onGateOpened";
    char const *CCLevelUpConsts::EVENT_MISSION_COMPLETED = "CCLevelUpEventHandler::onMissionCompleted";
    char const *CCLevelUpConsts::EVENT_MISSION_COMPLETION_REVOKED = "CCLevelUpEventHandler::onMissionCompletionRevoked";
    char const *CCLevelUpConsts::EVENT_WORLD_COMPLETED = "CCLevelUpEventHandler::onWorldCompleted";
    char const *CCLevelUpConsts::EVENT_WORLD_REWARD_ASSIGNED = "CCLevelUpEventHandler::onWorldRewardAssigned";
    char const *CCLevelUpConsts::EVENT_LEVEL_STARTED = "CCLevelUpEventHandler::onLevelStarted";
    char const *CCLevelUpConsts::EVENT_LEVEL_ENDED = "CCLevelUpEventHandler::onLevelEnded";

}