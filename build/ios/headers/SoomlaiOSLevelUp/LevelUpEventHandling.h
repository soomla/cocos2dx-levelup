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

// Events
#define EVENT_SCORE_RECORD_CHANGED           @"lu_score_record_changed"
#define EVENT_SCORE_RECORD_REACHED           @"lu_score_record_reached"
#define EVENT_GATE_OPENED                    @"lu_gate_opened"
#define EVENT_MISSION_COMPLETED              @"lu_mission_completed"
#define EVENT_MISSION_COMPLETION_REVOKED     @"lu_mission_completeion_revoked"
#define EVENT_WORLD_COMPLETED                @"lu_world_completed"
#define EVENT_LEVEL_STARTED                  @"lu_level_started"
#define EVENT_LEVEL_ENDED                    @"lu_level_ended"
#define EVENT_WORLD_REWARD_ASSIGNED          @"lu_world_reward_assigned"
#define EVENT_LEVEL_UP_INITIALIZED           @"lu_level_up_initialized"


// UserInfo Elements
#define DICT_ELEMENT_SCORE                   @"score"
#define DICT_ELEMENT_GATE                    @"gate"
#define DICT_ELEMENT_REWARD                  @"reward"
#define DICT_ELEMENT_WORLD                   @"world"
#define DICT_ELEMENT_MISSION                 @"mission"
#define DICT_ELEMENT_LEVEL                   @"level"
#define DICT_ELEMENT_IS_CHALLENGE            @"isChallenge"
#define DICT_ELEMENT_IS_BADGE                @"isBadge"
#define DICT_ELEMENT_METADATA                @"metadata"


@interface LevelUpEventHandling : NSObject


+ (void)observeAllEventsWithObserver:(id)observer withSelector:(SEL)selector;

+ (void)postScoreRecordChanged:(NSString *)scoreId;

+ (void)postScoreRecordReached:(NSString *)scoreId;

+ (void)postGateOpened:(NSString *)gateId;

+ (void)postMissionCompleted:(NSString *)missionId;

+ (void)postMissionCompletionRevoked:(NSString *)missionId;

+ (void)postWorldCompleted:(NSString *)worldId;

+ (void)postWorldRewardAssigned:(NSString *)worldId;

+ (void)postLevelStarted:(NSString *)levelId;

+ (void)postLevelEnded:(NSString *)levelId;

+ (void)postLevelUpInitialized:(NSDictionary *)metadata;
@end
