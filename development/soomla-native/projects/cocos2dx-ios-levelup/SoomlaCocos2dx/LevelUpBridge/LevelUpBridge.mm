
#import "LevelUpBridge.h"
#import "NdkGlue.h"
#import "LevelUpEventHandling.h"
#import "GateStorage.h"
#import "LevelStorage.h"
#import "MissionStorage.h"
#import "ScoreStorage.h"
#import "WorldStorage.h"


@interface LevelUpBridge ()
@end

@implementation LevelUpBridge {

}

+ (id)sharedLevelUpBridge {
    static LevelUpBridge *sharedLevelUpBridge = nil;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        sharedLevelUpBridge = [self alloc];
    });
    return sharedLevelUpBridge;
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
    [ndkGlue registerCallHandlerForKey:@"CCLevelUpBridge::initLevelUp" withBlock:^(NSDictionary *parameters, NSMutableDictionary *retParameters) {
        [WorldStorage initLevelUp];
        retParameters[@"return"] = @(YES);
    }];

    [ndkGlue registerCallHandlerForKey:@"CCLevelUpBridge::gateIsOpen" withBlock:^(NSDictionary *parameters, NSMutableDictionary *retParameters) {
        NSString *gateId = parameters[@"gateId"];
        retParameters[@"return"] = @([GateStorage isOpen:gateId]);
    }];

    [ndkGlue registerCallHandlerForKey:@"CCLevelUpBridge::gateSetOpen" withBlock:^(NSDictionary *parameters, NSMutableDictionary *retParameters) {
        NSString *gateId = parameters[@"gateId"];
        bool open = [parameters[@"open"] boolValue];
        bool notify = [parameters[@"notify"] boolValue];
        [GateStorage setOpen:open forGate:gateId andEvent:notify];
    }];

    [ndkGlue registerCallHandlerForKey:@"CCLevelUpBridge::levelSetSlowestDurationMillis" withBlock:^(NSDictionary *parameters, NSMutableDictionary *retParameters) {
        NSString *levelId = parameters[@"levelId"];
        long duration = [parameters[@"duration"] longValue];
        [LevelStorage setSlowestDurationMillis:duration forLevel:levelId];
    }];

    [ndkGlue registerCallHandlerForKey:@"CCLevelUpBridge::levelGetSlowestDurationMillis" withBlock:^(NSDictionary *parameters, NSMutableDictionary *retParameters) {
        NSString *levelId = parameters[@"levelId"];
        retParameters[@"return"] = @([LevelStorage getSlowestDurationMillisForLevel:levelId]);
    }];

    [ndkGlue registerCallHandlerForKey:@"CCLevelUpBridge::levelSetFastestDurationMillis" withBlock:^(NSDictionary *parameters, NSMutableDictionary *retParameters) {
        NSString *levelId = parameters[@"levelId"];
        long duration = [parameters[@"duration"] longValue];
        [LevelStorage setFastestDurationMillis:duration forLevel:levelId];
    }];

    [ndkGlue registerCallHandlerForKey:@"CCLevelUpBridge::levelGetFastestDurationMillis" withBlock:^(NSDictionary *parameters, NSMutableDictionary *retParameters) {
        NSString *levelId = parameters[@"levelId"];
        retParameters[@"return"] = @([LevelStorage getFastestDurationMillisForLevel:levelId]);
    }];

    [ndkGlue registerCallHandlerForKey:@"CCLevelUpBridge::levelIncTimesStarted" withBlock:^(NSDictionary *parameters, NSMutableDictionary *retParameters) {
        NSString *levelId = parameters[@"levelId"];
        retParameters[@"return"] = @([LevelStorage incTimesStartedForLevel:levelId]);
    }];

    [ndkGlue registerCallHandlerForKey:@"CCLevelUpBridge::levelDecTimesStarted" withBlock:^(NSDictionary *parameters, NSMutableDictionary *retParameters) {
        NSString *levelId = parameters[@"levelId"];
        retParameters[@"return"] = @([LevelStorage decTimesStartedForLevel:levelId]);
    }];

    [ndkGlue registerCallHandlerForKey:@"CCLevelUpBridge::levelGetTimesStarted" withBlock:^(NSDictionary *parameters, NSMutableDictionary *retParameters) {
        NSString *levelId = parameters[@"levelId"];
        retParameters[@"return"] = @([LevelStorage getTimesStartedForLevel:levelId]);
    }];

    [ndkGlue registerCallHandlerForKey:@"CCLevelUpBridge::levelGetTimesPlayed" withBlock:^(NSDictionary *parameters, NSMutableDictionary *retParameters) {
        NSString *levelId = parameters[@"levelId"];
        retParameters[@"return"] = @([LevelStorage getTimesPlayedForLevel:levelId]);
    }];

    [ndkGlue registerCallHandlerForKey:@"CCLevelUpBridge::levelIncTimesPlayed" withBlock:^(NSDictionary *parameters, NSMutableDictionary *retParameters) {
        NSString *levelId = parameters[@"levelId"];
        retParameters[@"return"] = @([LevelStorage incTimesPlayedForLevel:levelId]);
    }];

    [ndkGlue registerCallHandlerForKey:@"CCLevelUpBridge::levelDecTimesPlayed" withBlock:^(NSDictionary *parameters, NSMutableDictionary *retParameters) {
        NSString *levelId = parameters[@"levelId"];
        retParameters[@"return"] = @([LevelStorage decTimesPlayedForLevel:levelId]);
    }];
    
    [ndkGlue registerCallHandlerForKey:@"CCLevelUpBridge::levelGetTimesCompleted" withBlock:^(NSDictionary *parameters, NSMutableDictionary *retParameters) {
        NSString *levelId = parameters[@"levelId"];
        retParameters[@"return"] = @([LevelStorage getTimesCompletedForLevel:levelId]);
    }];
    
    [ndkGlue registerCallHandlerForKey:@"CCLevelUpBridge::levelIncTimesCompleted" withBlock:^(NSDictionary *parameters, NSMutableDictionary *retParameters) {
        NSString *levelId = parameters[@"levelId"];
        retParameters[@"return"] = @([LevelStorage incTimesCompletedForLevel:levelId]);
    }];
    
    [ndkGlue registerCallHandlerForKey:@"CCLevelUpBridge::levelDecTimesCompleted" withBlock:^(NSDictionary *parameters, NSMutableDictionary *retParameters) {
        NSString *levelId = parameters[@"levelId"];
        retParameters[@"return"] = @([LevelStorage decTimesCompletedForLevel:levelId]);
    }];

    [ndkGlue registerCallHandlerForKey:@"CCLevelUpBridge::missionSetCompleted" withBlock:^(NSDictionary *parameters, NSMutableDictionary *retParameters) {
        NSString *missionId = parameters[@"missionId"];
        bool completed = [parameters[@"completed"] boolValue];
        bool notify = [parameters[@"notify"] boolValue];
        [MissionStorage setCompleted:completed forMission:missionId andNotify:notify];
    }];

    [ndkGlue registerCallHandlerForKey:@"CCLevelUpBridge::missionGetTimesCompleted" withBlock:^(NSDictionary *parameters, NSMutableDictionary *retParameters) {
        NSString *missionId = parameters[@"missionId"];
        retParameters[@"return"] = @([MissionStorage getTimesCompleted:missionId]);
    }];

    [ndkGlue registerCallHandlerForKey:@"CCLevelUpBridge::scoreSetLatestScore" withBlock:^(NSDictionary *parameters, NSMutableDictionary *retParameters) {
        double newValue = [parameters[@"newValue"] doubleValue];
        NSString *scoreId = parameters[@"scoreId"];
        [ScoreStorage setLatest:newValue toScore:scoreId];
    }];

    [ndkGlue registerCallHandlerForKey:@"CCLevelUpBridge::scoreGetLatestScore" withBlock:^(NSDictionary *parameters, NSMutableDictionary *retParameters) {
        NSString *scoreId = parameters[@"scoreId"];
        retParameters[@"return"] = @([ScoreStorage getLatestScore:scoreId]);
    }];

    [ndkGlue registerCallHandlerForKey:@"CCLevelUpBridge::scoreSetRecordScore" withBlock:^(NSDictionary *parameters, NSMutableDictionary *retParameters) {
        NSString *scoreId = parameters[@"scoreId"];
        double newValue = [parameters[@"newValue"] doubleValue];
        [ScoreStorage setRecord:newValue toScore:scoreId];
    }];

    [ndkGlue registerCallHandlerForKey:@"CCLevelUpBridge::scoreGetRecordScore" withBlock:^(NSDictionary *parameters, NSMutableDictionary *retParameters) {
        NSString *scoreId = parameters[@"scoreId"];
        retParameters[@"return"] = @([ScoreStorage getRecordScore:scoreId]);
    }];

    [ndkGlue registerCallHandlerForKey:@"CCLevelUpBridge::worldSetCompleted" withBlock:^(NSDictionary *parameters, NSMutableDictionary *retParameters) {
        NSString *worldId = parameters[@"worldId"];
        bool completed = [parameters[@"completed"] boolValue];
        bool notify = [parameters[@"notify"] boolValue];
        [WorldStorage setCompleted:completed forWorld:worldId andNotify:notify];
    }];

    [ndkGlue registerCallHandlerForKey:@"CCLevelUpBridge::worldIsCompleted" withBlock:^(NSDictionary *parameters, NSMutableDictionary *retParameters) {
        NSString *worldId = parameters[@"worldId"];
        retParameters[@"return"] = @([WorldStorage isWorldCompleted:worldId]);
    }];

    [ndkGlue registerCallHandlerForKey:@"CCLevelUpBridge::worldSetReward" withBlock:^(NSDictionary *parameters, NSMutableDictionary *retParameters) {
        NSString *worldId = parameters[@"worldId"];
        NSString *rewardId = parameters[@"rewardId"];
        [WorldStorage setReward:rewardId forWorld:worldId];
    }];

    [ndkGlue registerCallHandlerForKey:@"CCLevelUpBridge::worldGetAssignedReward" withBlock:^(NSDictionary *parameters, NSMutableDictionary *retParameters) {
        NSString *worldId = parameters[@"worldId"];
        retParameters[@"return"] = ([WorldStorage getAssignedReward:worldId] ?: [NSNull null]);
    }];
    
    [ndkGlue registerCallHandlerForKey:@"CCLevelUpBridge::worldSetLastCompletedInnerWorld" withBlock:^(NSDictionary *parameters, NSMutableDictionary *retParameters) {
        NSString *worldId = parameters[@"worldId"];
        NSString *innerWorldId = parameters[@"innerWorldId"];
        [WorldStorage setLastCompletedInnerWorld:innerWorldId forWorld:worldId];
    }];
    
    [ndkGlue registerCallHandlerForKey:@"CCLevelUpBridge::worldGetLastCompletedInnerWorld" withBlock:^(NSDictionary *parameters, NSMutableDictionary *retParameters) {
        NSString *worldId = parameters[@"worldId"];
        retParameters[@"return"] = ([WorldStorage getLastCompletedInnerWorld:worldId] ?: [NSNull null]);
    }];

    /* -= Callback handlers =- */
    [ndkGlue registerCallbackHandlerForKey:EVENT_LEVEL_UP_INITIALIZED withBlock:^(NSNotification *notification, NSMutableDictionary *parameters) {
        parameters[@"method"] = @"CCLevelUpEventHandler::onLevelUpInitialized";
    }];
    
    [ndkGlue registerCallbackHandlerForKey:EVENT_SCORE_LATEST_CHANGED withBlock:^(NSNotification *notification, NSMutableDictionary *parameters) {
        parameters[@"method"] = @"CCLevelUpEventHandler::onLatestScoreChanged";
        parameters[@"scoreId"] = (notification.userInfo)[DICT_ELEMENT_SCORE];
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
    
    [ndkGlue registerCallbackHandlerForKey:EVENT_GATE_CLOSED withBlock:^(NSNotification *notification, NSMutableDictionary *parameters) {
        parameters[@"method"] = @"CCLevelUpEventHandler::onGateClosed";
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
    
    [ndkGlue registerCallbackHandlerForKey:EVENT_LAST_COMPLETED_INNER_WORLD_CHANGED withBlock:^(NSNotification *notification, NSMutableDictionary *parameters) {
        parameters[@"method"] = @"CCLevelUpEventHandler::onLastCompletedInnerWorldChanged";
        parameters[@"worldId"] = (notification.userInfo)[DICT_ELEMENT_WORLD];
        parameters[@"innerWorldId"] = (notification.userInfo)[DICT_ELEMENT_INNER_WORLD];
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
