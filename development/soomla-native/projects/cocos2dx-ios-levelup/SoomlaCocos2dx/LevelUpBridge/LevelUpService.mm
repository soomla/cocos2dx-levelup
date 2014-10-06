//
// Created by Fedor Shubin on 6/12/14.
//

#import "LevelUpService.h"
#import "NdkGlue.h"
#import "LevelUpEventHandling.h"
#import "GateStorage.h"
#import "LevelStorage.h"
#import "MissionStorage.h"
#import "ScoreStorage.h"
#import "WorldStorage.h"


@interface LevelUpService ()
@end

@implementation LevelUpService {

}

+ (id)sharedLevelUpService {
    static LevelUpService *sharedProfileService = nil;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        sharedProfileService = [self alloc];
    });
    return sharedProfileService;
}

+ (void)initialize {
    [super initialize];
    [self initGlue];
    [self initDomainHelper];
}

+ (void)initDomainHelper {
    // Nothing to do here!

//    [[DomainHelper sharedDomainHelper] registerType:@"mission"
//                                      withClassName:NSStringFromClass([Mission class])
//                                           andBlock:^id(NSDictionary *dict) {
//                                               return [[[Mission alloc] initWithDictionary:dict] autorelease];
//                                           }];

}


- (id)init {
    self = [super init];
    if (self) {
        [LevelUpEventHandling observeAllEventsWithObserver:[NdkGlue sharedInstance]
                                       withSelector:@selector(dispatchNdkCallback:)];
    }

    return self;
}

+ (void)initGlue {
    NdkGlue *ndkGlue = [NdkGlue sharedInstance];

    /* -= Call handlers =- */
    [ndkGlue registerCallHandlerForKey:@"CCLevelUpService::initLevelUp" withBlock:^(NSDictionary *parameters, NSMutableDictionary *retParameters) {
        BOOL res = [[LevelUpService sharedLevelUpService] init] != nil;
        if (res) {
            [WorldStorage initLevelUp];
        }
        retParameters[@"return"] = @(res);
    }];

    [ndkGlue registerCallHandlerForKey:@"CCLevelUpService::gateIsOpen" withBlock:^(NSDictionary *parameters, NSMutableDictionary *retParameters) {
        NSString *gateId = parameters[@"gateId"];
        retParameters[@"return"] = @([GateStorage isOpen:gateId]);
    }];

    [ndkGlue registerCallHandlerForKey:@"CCLevelUpService::gateSetOpen" withBlock:^(NSDictionary *parameters, NSMutableDictionary *retParameters) {
        NSString *gateId = parameters[@"gateId"];
        bool open = [parameters[@"open"] boolValue];
        bool notify = [parameters[@"notify"] boolValue];
        [GateStorage setOpen:open forGate:gateId andEvent:notify];
    }];

    [ndkGlue registerCallHandlerForKey:@"CCLevelUpService::levelSetSlowestDurationMillis" withBlock:^(NSDictionary *parameters, NSMutableDictionary *retParameters) {
        NSString *levelId = parameters[@"levelId"];
        long duration = [parameters[@"duration"] longValue];
        [LevelStorage setSlowestDurationMillis:duration forLevel:levelId];
    }];

    [ndkGlue registerCallHandlerForKey:@"CCLevelUpService::levelGetSlowestDurationMillis" withBlock:^(NSDictionary *parameters, NSMutableDictionary *retParameters) {
        NSString *levelId = parameters[@"levelId"];
        retParameters[@"return"] = @([LevelStorage getSlowestDurationMillisForLevel:levelId]);
    }];

    [ndkGlue registerCallHandlerForKey:@"CCLevelUpService::levelSetFastestDurationMillis" withBlock:^(NSDictionary *parameters, NSMutableDictionary *retParameters) {
        NSString *levelId = parameters[@"levelId"];
        long duration = [parameters[@"duration"] longValue];
        [LevelStorage setFastestDurationMillis:duration forLevel:levelId];
    }];

    [ndkGlue registerCallHandlerForKey:@"CCLevelUpService::levelGetFastestDurationMillis" withBlock:^(NSDictionary *parameters, NSMutableDictionary *retParameters) {
        NSString *levelId = parameters[@"levelId"];
        retParameters[@"return"] = @([LevelStorage getFastestDurationMillisForLevel:levelId]);
    }];

    [ndkGlue registerCallHandlerForKey:@"CCLevelUpService::levelIncTimesStarted" withBlock:^(NSDictionary *parameters, NSMutableDictionary *retParameters) {
        NSString *levelId = parameters[@"levelId"];
        retParameters[@"return"] = @([LevelStorage incTimesStartedForLevel:levelId]);
    }];

    [ndkGlue registerCallHandlerForKey:@"CCLevelUpService::levelDecTimesStarted" withBlock:^(NSDictionary *parameters, NSMutableDictionary *retParameters) {
        NSString *levelId = parameters[@"levelId"];
        retParameters[@"return"] = @([LevelStorage decTimesStartedForLevel:levelId]);
    }];

    [ndkGlue registerCallHandlerForKey:@"CCLevelUpService::levelGetTimesStarted" withBlock:^(NSDictionary *parameters, NSMutableDictionary *retParameters) {
        NSString *levelId = parameters[@"levelId"];
        retParameters[@"return"] = @([LevelStorage getTimesStartedForLevel:levelId]);
    }];

    [ndkGlue registerCallHandlerForKey:@"CCLevelUpService::levelGetTimesPlayed" withBlock:^(NSDictionary *parameters, NSMutableDictionary *retParameters) {
        NSString *levelId = parameters[@"levelId"];
        retParameters[@"return"] = @([LevelStorage getTimesPlayedForLevel:levelId]);
    }];

    [ndkGlue registerCallHandlerForKey:@"CCLevelUpService::levelIncTimesPlayed" withBlock:^(NSDictionary *parameters, NSMutableDictionary *retParameters) {
        NSString *levelId = parameters[@"levelId"];
        retParameters[@"return"] = @([LevelStorage incTimesPlayedForLevel:levelId]);
    }];

    [ndkGlue registerCallHandlerForKey:@"CCLevelUpService::levelDecTimesPlayed" withBlock:^(NSDictionary *parameters, NSMutableDictionary *retParameters) {
        NSString *levelId = parameters[@"levelId"];
        retParameters[@"return"] = @([LevelStorage decTimesPlayedForLevel:levelId]);
    }];

    [ndkGlue registerCallHandlerForKey:@"CCLevelUpService::missionSetCompleted" withBlock:^(NSDictionary *parameters, NSMutableDictionary *retParameters) {
        NSString *missionId = parameters[@"missionId"];
        bool completed = [parameters[@"completed"] boolValue];
        bool notify = [parameters[@"notify"] boolValue];
        [MissionStorage setCompleted:completed forMission:missionId andNotify:notify];
    }];

    [ndkGlue registerCallHandlerForKey:@"CCLevelUpService::missionGetTimesCompleted" withBlock:^(NSDictionary *parameters, NSMutableDictionary *retParameters) {
        NSString *missionId = parameters[@"missionId"];
        retParameters[@"return"] = @([MissionStorage getTimesCompleted:missionId]);
    }];

    [ndkGlue registerCallHandlerForKey:@"CCLevelUpService::scoreSetLatestScore" withBlock:^(NSDictionary *parameters, NSMutableDictionary *retParameters) {
        double newValue = [parameters[@"newValue"] doubleValue];
        NSString *scoreId = parameters[@"scoreId"];
        [ScoreStorage setLatest:newValue toScore:scoreId];
    }];

    [ndkGlue registerCallHandlerForKey:@"CCLevelUpService::scoreGetLatestScore" withBlock:^(NSDictionary *parameters, NSMutableDictionary *retParameters) {
        NSString *scoreId = parameters[@"scoreId"];
        retParameters[@"return"] = @([ScoreStorage getLatestScore:scoreId]);
    }];

    [ndkGlue registerCallHandlerForKey:@"CCLevelUpService::scoreSetRecordScore" withBlock:^(NSDictionary *parameters, NSMutableDictionary *retParameters) {
        NSString *scoreId = parameters[@"scoreId"];
        double newValue = [parameters[@"newValue"] doubleValue];
        [ScoreStorage setRecord:newValue toScore:scoreId];
    }];

    [ndkGlue registerCallHandlerForKey:@"CCLevelUpService::scoreGetRecordScore" withBlock:^(NSDictionary *parameters, NSMutableDictionary *retParameters) {
        NSString *scoreId = parameters[@"scoreId"];
        retParameters[@"return"] = @([ScoreStorage getRecordScore:scoreId]);
    }];

    [ndkGlue registerCallHandlerForKey:@"CCLevelUpService::worldSetCompleted" withBlock:^(NSDictionary *parameters, NSMutableDictionary *retParameters) {
        NSString *worldId = parameters[@"worldId"];
        bool completed = [parameters[@"completed"] boolValue];
        bool notify = [parameters[@"notify"] boolValue];
        [WorldStorage setCompleted:completed forWorld:worldId andNotify:notify];
    }];

    [ndkGlue registerCallHandlerForKey:@"CCLevelUpService::worldIsCompleted" withBlock:^(NSDictionary *parameters, NSMutableDictionary *retParameters) {
        NSString *worldId = parameters[@"worldId"];
        retParameters[@"return"] = @([WorldStorage isWorldCompleted:worldId]);
    }];

    [ndkGlue registerCallHandlerForKey:@"CCLevelUpService::worldSetReward" withBlock:^(NSDictionary *parameters, NSMutableDictionary *retParameters) {
        NSString *worldId = parameters[@"worldId"];
        NSString *rewardId = parameters[@"rewardId"];
        [WorldStorage setReward:rewardId forWorld:worldId];
    }];

    [ndkGlue registerCallHandlerForKey:@"CCLevelUpService::worldGetAssignedReward" withBlock:^(NSDictionary *parameters, NSMutableDictionary *retParameters) {
        NSString *worldId = parameters[@"worldId"];
        retParameters[@"return"] = ([WorldStorage getAssignedReward:worldId] ?: [NSNull null]);
    }];

    /* -= Callback handlers =- */
    [ndkGlue registerCallbackHandlerForKey:EVENT_LEVEL_UP_INITIALIZED withBlock:^(NSNotification *notification, NSMutableDictionary *parameters) {
        parameters[@"method"] = @"CCLevelUpEventHandler::onLevelUpInitialized";
    }];

    [ndkGlue registerCallbackHandlerForKey:EVENT_SCORE_RECORD_REACHED withBlock:^(NSNotification *notification, NSMutableDictionary *parameters) {
        parameters[@"method"] = @"CCLevelUpEventHandler::onScoreRecordReached";
        parameters[@"scoreId"] = (notification.userInfo)[DICT_ELEMENT_SCORE];
    }];

    [ndkGlue registerCallbackHandlerForKey:EVENT_SCORE_RECORD_CHANGED withBlock:^(NSNotification *notification, NSMutableDictionary *parameters) {
        parameters[@"method"] = @"CCLevelUpEventHandler::onScoreRecordChanged";
        parameters[@"scoreId"] = (notification.userInfo)[DICT_ELEMENT_SCORE];
    }];

    [ndkGlue registerCallbackHandlerForKey:EVENT_GATE_OPENED withBlock:^(NSNotification *notification, NSMutableDictionary *parameters) {
        parameters[@"method"] = @"CCLevelUpEventHandler::onGateOpened";
        parameters[@"gateId"] = (notification.userInfo)[DICT_ELEMENT_GATE];
    }];

    [ndkGlue registerCallbackHandlerForKey:EVENT_MISSION_COMPLETED withBlock:^(NSNotification *notification, NSMutableDictionary *parameters) {
        parameters[@"method"] = @"CCLevelUpEventHandler::onMissionCompleted";
        parameters[@"missionId"] = (notification.userInfo)[DICT_ELEMENT_MISSION];
    }];

    [ndkGlue registerCallbackHandlerForKey:EVENT_MISSION_COMPLETION_REVOKED withBlock:^(NSNotification *notification, NSMutableDictionary *parameters) {
        parameters[@"method"] = @"CCLevelUpEventHandler::onMissionCompletionRevoked";
        parameters[@"missionId"] = (notification.userInfo)[DICT_ELEMENT_MISSION];
    }];

    [ndkGlue registerCallbackHandlerForKey:EVENT_WORLD_COMPLETED withBlock:^(NSNotification *notification, NSMutableDictionary *parameters) {
        parameters[@"method"] = @"CCLevelUpEventHandler::onWorldCompleted";
        parameters[@"worldId"] = (notification.userInfo)[DICT_ELEMENT_WORLD];
    }];

    [ndkGlue registerCallbackHandlerForKey:EVENT_WORLD_REWARD_ASSIGNED withBlock:^(NSNotification *notification, NSMutableDictionary *parameters) {
        parameters[@"method"] = @"CCLevelUpEventHandler::onWorldRewardAssigned";
        parameters[@"worldId"] = (notification.userInfo)[DICT_ELEMENT_WORLD];
    }];

    [ndkGlue registerCallbackHandlerForKey:EVENT_LEVEL_STARTED withBlock:^(NSNotification *notification, NSMutableDictionary *parameters) {
        parameters[@"method"] = @"CCLevelUpEventHandler::onLevelStarted";
        parameters[@"levelId"] = (notification.userInfo)[DICT_ELEMENT_LEVEL];
    }];

    [ndkGlue registerCallbackHandlerForKey:EVENT_LEVEL_ENDED withBlock:^(NSNotification *notification, NSMutableDictionary *parameters) {
        parameters[@"method"] = @"CCLevelUpEventHandler::onLevelEnded";
        parameters[@"levelId"] = (notification.userInfo)[DICT_ELEMENT_LEVEL];
    }];

}

@end