//
// Created by Fedor Shubin on 6/12/14.
//

#import "LevelUpService.h"
#import "NdkGlue.h"
#import "LevelUpEventHandling.h"
#import "DomainFactory.h"
#import "GateStorage.h"
#import "LevelStorage.h"
#import "MissionStorage.h"
#import "ScoreStorage.h"
#import "WorldStorage.h"
#import "DomainHelper.h"
#import "Mission.h"
#import "BalanceMission.h"
#import "Challenge.h"
#import "PurchasingMission.h"
#import "RecordMission.h"
//#import "WorldCompletionMission.h"
#import "BalanceGate.h"
#import "GatesListAND.h"
#import "GatesListOR.h"
#import "PurchasableGate.h"
#import "RecordGate.h"
//#import "ScheduleGate.h"
#import "WorldCompletionGate.h"
#import "Score.h"
#import "World.h"
#import "Level.h"


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
    [[DomainHelper sharedDomainHelper] registerType:@"mission"
                                      withClassName:NSStringFromClass([Mission class])
                                           andBlock:^id(NSDictionary *dict) {
                                               return [[[Mission alloc] initWithDictionary:dict] autorelease];
                                           }];

    [[DomainHelper sharedDomainHelper] registerType:@"balanceMission"
                                      withClassName:NSStringFromClass([BalanceMission class])
                                           andBlock:^id(NSDictionary *dict) {
                                               return [[[BalanceMission alloc] initWithDictionary:dict] autorelease];
                                           }];

    [[DomainHelper sharedDomainHelper] registerType:@"challenge"
                                      withClassName:NSStringFromClass([Challenge class])
                                           andBlock:^id(NSDictionary *dict) {
                                               return [[[Challenge alloc] initWithDictionary:dict] autorelease];
                                           }];

    [[DomainHelper sharedDomainHelper] registerType:@"purchasingMission"
                                      withClassName:NSStringFromClass([PurchasingMission class])
                                           andBlock:^id(NSDictionary *dict) {
                                               return [[[PurchasingMission alloc] initWithDictionary:dict] autorelease];
                                           }];

    [[DomainHelper sharedDomainHelper] registerType:@"recordMission"
                                      withClassName:NSStringFromClass([RecordMission class])
                                           andBlock:^id(NSDictionary *dict) {
                                               return [[[RecordMission alloc] initWithDictionary:dict] autorelease];
                                           }];

//    [[DomainHelper sharedDomainHelper] registerType:@"worldCompletionMission"
//                                      withClassName:NSStringFromClass([WorldCompletionMission class])
//                                           andBlock:^id(NSDictionary *dict) {
//                                               return [[[WorldCompletionMission alloc] initWithDictionary:dict] autorelease];
//                                           }];
//
    [[DomainHelper sharedDomainHelper] registerType:@"balanceGate"
                                      withClassName:NSStringFromClass([BalanceGate class])
                                           andBlock:^id(NSDictionary *dict) {
                                               return [[[BalanceGate alloc] initWithDictionary:dict] autorelease];
                                           }];

    [[DomainHelper sharedDomainHelper] registerType:@"gatesListAnd"
                                      withClassName:NSStringFromClass([GatesListAND class])
                                           andBlock:^id(NSDictionary *dict) {
                                               return [[[GatesListAND alloc] initWithDictionary:dict] autorelease];
                                           }];

    [[DomainHelper sharedDomainHelper] registerType:@"gatesListOr"
                                      withClassName:NSStringFromClass([GatesListOR class])
                                           andBlock:^id(NSDictionary *dict) {
                                               return [[[GatesListOR alloc] initWithDictionary:dict] autorelease];
                                           }];

    [[DomainHelper sharedDomainHelper] registerType:@"purchasableGate"
                                      withClassName:NSStringFromClass([PurchasableGate class])
                                           andBlock:^id(NSDictionary *dict) {
                                               return [[[PurchasableGate alloc] initWithDictionary:dict] autorelease];
                                           }];

    [[DomainHelper sharedDomainHelper] registerType:@"recordGate"
                                      withClassName:NSStringFromClass([RecordGate class])
                                           andBlock:^id(NSDictionary *dict) {
                                               return [[[RecordGate alloc] initWithDictionary:dict] autorelease];
                                           }];

//    [[DomainHelper sharedDomainHelper] registerType:@"scheduleGate"
//                                      withClassName:NSStringFromClass([ScheduleGate class])
//                                           andBlock:^id(NSDictionary *dict) {
//                                               return [[[ScheduleGate alloc] initWithDictionary:dict] autorelease];
//                                           }];
//
    [[DomainHelper sharedDomainHelper] registerType:@"worldCompletionGate"
                                      withClassName:NSStringFromClass([WorldCompletionGate class])
                                           andBlock:^id(NSDictionary *dict) {
                                               return [[[WorldCompletionGate alloc] initWithDictionary:dict] autorelease];
                                           }];

    [[DomainHelper sharedDomainHelper] registerType:@"score"
                                      withClassName:NSStringFromClass([Score class])
                                           andBlock:^id(NSDictionary *dict) {
                                               return [[[Score alloc] initWithDictionary:dict] autorelease];
                                           }];

    [[DomainHelper sharedDomainHelper] registerType:@"world"
                                      withClassName:NSStringFromClass([World class])
                                           andBlock:^id(NSDictionary *dict) {
                                               return [[[World alloc] initWithDictionary:dict] autorelease];
                                           }];

    [[DomainHelper sharedDomainHelper] registerType:@"level"
                                      withClassName:NSStringFromClass([Level class])
                                           andBlock:^id(NSDictionary *dict) {
                                               return [[[Level alloc] initWithDictionary:dict] autorelease];
                                           }];

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
    [ndkGlue registerCallHandlerForKey:@"CCLevelUpService::gateIsOpen" withBlock:^(NSDictionary *parameters, NSMutableDictionary *retParameters) {
        retParameters[@"return"] = @([GateStorage isOpen:parameters[@"gateId"]]);
    }];

    [ndkGlue registerCallHandlerForKey:@"CCLevelUpService::gateSetOpen" withBlock:^(NSDictionary *parameters, NSMutableDictionary *retParameters) {
        bool open = [parameters[@"open"] boolValue];
        bool notify = [parameters[@"notify"] boolValue];
        [GateStorage setOpen:open forGate:parameters[@"gateId"] andEvent:notify];
    }];

    [ndkGlue registerCallHandlerForKey:@"CCLevelUpService::levelSetSlowestDurationMillis" withBlock:^(NSDictionary *parameters, NSMutableDictionary *retParameters) {
        Level *level = [[DomainFactory sharedDomainFactory] createWithDict:];
        long duration = [parameters[@"duration"] longValue];
        [LevelStorage setSlowestDurationMillis:duration forLevel:parameters[@"levelId"]];
    }];

    [ndkGlue registerCallHandlerForKey:@"CCLevelUpService::levelGetSlowestDurationMillis" withBlock:^(NSDictionary *parameters, NSMutableDictionary *retParameters) {
        retParameters[@"return"] = @([LevelStorage getSlowestDurationMillisForLevel:parameters[@"levelId"]]);
    }];

    [ndkGlue registerCallHandlerForKey:@"CCLevelUpService::levelSetFastestDurationMillis" withBlock:^(NSDictionary *parameters, NSMutableDictionary *retParameters) {
        long duration = [parameters[@"duration"] longValue];
        [LevelStorage setFastestDurationMillis:duration forLevel:parameters[@"levelId"]];
    }];

    [ndkGlue registerCallHandlerForKey:@"CCLevelUpService::levelGetFastestDurationMillis" withBlock:^(NSDictionary *parameters, NSMutableDictionary *retParameters) {
        retParameters[@"return"] = @([LevelStorage getFastestDurationMillisForLevel:parameters[@"levelId"]]);
    }];

    [ndkGlue registerCallHandlerForKey:@"CCLevelUpService::levelIncTimesStarted" withBlock:^(NSDictionary *parameters, NSMutableDictionary *retParameters) {
        retParameters[@"return"] = @([LevelStorage incTimesStartedForLevel:parameters[@"levelId"]]);
    }];

    [ndkGlue registerCallHandlerForKey:@"CCLevelUpService::levelDecTimesStarted" withBlock:^(NSDictionary *parameters, NSMutableDictionary *retParameters) {
        retParameters[@"return"] = @([LevelStorage decTimesStartedForLevel:parameters[@"levelId"]]);
    }];

    [ndkGlue registerCallHandlerForKey:@"CCLevelUpService::levelGetTimesStarted" withBlock:^(NSDictionary *parameters, NSMutableDictionary *retParameters) {
        retParameters[@"return"] = @([LevelStorage getTimesStartedForLevel:parameters[@"levelId"]]);
    }];

    [ndkGlue registerCallHandlerForKey:@"CCLevelUpService::levelGetTimesPlayed" withBlock:^(NSDictionary *parameters, NSMutableDictionary *retParameters) {
        retParameters[@"return"] = @([LevelStorage getTimesPlayedForLevel:parameters[@"levelId"]]);
    }];

    [ndkGlue registerCallHandlerForKey:@"CCLevelUpService::levelIncTimesPlayed" withBlock:^(NSDictionary *parameters, NSMutableDictionary *retParameters) {
        retParameters[@"return"] = @([LevelStorage incTimesPlayedForLevel:parameters[@"levelId"]]);
    }];

    [ndkGlue registerCallHandlerForKey:@"CCLevelUpService::levelDecTimesPlayed" withBlock:^(NSDictionary *parameters, NSMutableDictionary *retParameters) {
        retParameters[@"return"] = @([LevelStorage decTimesPlayedForLevel:parameters[@"levelId"]]);
    }];

    [ndkGlue registerCallHandlerForKey:@"CCLevelUpService::missionSetCompleted" withBlock:^(NSDictionary *parameters, NSMutableDictionary *retParameters) {
        bool completed = [parameters[@"completed"] boolValue];
        bool notify = [parameters[@"notify"] boolValue];
        [MissionStorage setCompleted:completed forMission:parameters[@"missionId"] andNotify:notify];
    }];

    [ndkGlue registerCallHandlerForKey:@"CCLevelUpService::missionGetTimesCompleted" withBlock:^(NSDictionary *parameters, NSMutableDictionary *retParameters) {
        retParameters[@"return"] = @([MissionStorage getTimesCompleted:parameters[@"missionId"]]);
    }];

    [ndkGlue registerCallHandlerForKey:@"CCLevelUpService::scoreSetLatestScore" withBlock:^(NSDictionary *parameters, NSMutableDictionary *retParameters) {
        double newValue = [parameters[@"newValue"] doubleValue];
        [ScoreStorage setLatest:newValue toScore:parameters[@"scoreId"]];
    }];

    [ndkGlue registerCallHandlerForKey:@"CCLevelUpService::scoreGetLatestScore" withBlock:^(NSDictionary *parameters, NSMutableDictionary *retParameters) {
        retParameters[@"return"] = @([ScoreStorage getLatestScore:parameters[@"scoreId"]]);
    }];

    [ndkGlue registerCallHandlerForKey:@"CCLevelUpService::scoreSetRecordScore" withBlock:^(NSDictionary *parameters, NSMutableDictionary *retParameters) {
        Score *score = [[DomainFactory sharedDomainFactory] createWithDict:parameters[@"score"]];
        double newValue = [parameters[@"newValue"] doubleValue];
        [ScoreStorage setRecord:newValue toScore:score];
    }];

    [ndkGlue registerCallHandlerForKey:@"CCLevelUpService::scoreGetRecordScore" withBlock:^(NSDictionary *parameters, NSMutableDictionary *retParameters) {
        retParameters[@"return"] = @([ScoreStorage getRecordScore:parameters[@"scoreId"]]);
    }];

    [ndkGlue registerCallHandlerForKey:@"CCLevelUpService::worldSetCompleted" withBlock:^(NSDictionary *parameters, NSMutableDictionary *retParameters) {
        bool completed = [parameters[@"completed"] boolValue];
        bool notify = [parameters[@"notify"] boolValue];
        [WorldStorage setCompleted:completed forWorld:parameters[@"worldId"] andNotify:notify];
    }];

    [ndkGlue registerCallHandlerForKey:@"CCLevelUpService::worldIsCompleted" withBlock:^(NSDictionary *parameters, NSMutableDictionary *retParameters) {
        retParameters[@"return"] = @([WorldStorage isWorldCompleted:parameters[@"worldId"]]);
    }];

    [ndkGlue registerCallHandlerForKey:@"CCLevelUpService::worldSetReward" withBlock:^(NSDictionary *parameters, NSMutableDictionary *retParameters) {
        NSString *rewardId = parameters[@"rewardId"];
        [WorldStorage setReward:rewardId forWorld:parameters[@"worldId"]];
    }];

    [ndkGlue registerCallHandlerForKey:@"CCLevelUpService::worldGetAssignedReward" withBlock:^(NSDictionary *parameters, NSMutableDictionary *retParameters) {
        retParameters[@"return"] = [WorldStorage getAssignedReward:parameters[@"worldId"]];
    }];

    /* -= Callback handlers =- */
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