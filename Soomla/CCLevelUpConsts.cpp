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
    char const *CCLevelUpConsts::JSON_LU_NAME               = "name";

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

    /** Types **/
    char const *CCLevelUpConsts::JSON_JSON_TYPE_MISSION     = "mission";
    char const *CCLevelUpConsts::JSON_JSON_TYPE_BALANCE_MISSION = "balanceMission";
    char const *CCLevelUpConsts::JSON_JSON_TYPE_CHALLENGE   = "challenge";
    char const *CCLevelUpConsts::JSON_JSON_TYPE_PURCHASE_MISSION = "purchaseMission";
    char const *CCLevelUpConsts::JSON_JSON_TYPE_RECORD_MISSION = "recordMission";
    char const *CCLevelUpConsts::JSON_JSON_TYPE_WORLD_COMPLETION_MISSION = "worldCompletionMission";
    char const *CCLevelUpConsts::JSON_JSON_TYPE_GATE        = "gate";
    char const *CCLevelUpConsts::JSON_JSON_TYPE_BALANCE_GATE = "balanceGate";
    char const *CCLevelUpConsts::JSON_JSON_TYPE_PURCHASABLE_GATE = "purchasableGate";
    char const *CCLevelUpConsts::JSON_JSON_TYPE_RECORD_GATE = "recordGate";
    char const *CCLevelUpConsts::JSON_JSON_TYPE_WORLD_COMPLETION_GATE = "worldCompletionGate";

//    char const *CCLevelUpConsts::EVENT_BILLING_NOT_SUPPORTED = "CCLevelUpEventHandler::onBillingNotSupported";
//
}