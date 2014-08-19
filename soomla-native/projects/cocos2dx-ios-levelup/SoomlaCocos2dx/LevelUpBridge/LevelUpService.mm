//
// Created by Fedor Shubin on 6/12/14.
//

#import "LevelUpService.h"
#import "NdkGlue.h"
#import "LevelUpEventHandling.h"

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
//    [[DomainHelper sharedDomainHelper] registerType:@"virtualGood"
//                                      withClassName:NSStringFromClass([VirtualGood class])];
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
//    [ndkGlue registerCallHandlerForKey:@"CCStoreAssets::init" withBlock:^(NSDictionary *parameters, NSMutableDictionary *retParameters) {
//        NSNumber *version = (NSNumber *) [parameters objectForKey:@"version"];
//        NSDictionary *storeAssetsDict = (NSDictionary *) [parameters objectForKey:@"storeAssets"];
//        [[StoreAssetsBridge sharedInstance] initializeWithStoreAssetsDict:storeAssetsDict andVersion:version.intValue];
//    }];

    /* -= Exception handlers =- */
//    void (^exceptionHandler)(NSException *, NSDictionary *, NSMutableDictionary *) = ^(NSException *exception, NSDictionary *parameters, NSMutableDictionary *retParameters) {
//        [retParameters setObject: NSStringFromClass([exception class]) forKey: @"errorInfo"];
//    };
//    [ndkGlue registerExceptionHandlerForKey:NSStringFromClass([VirtualItemNotFoundException class]) withBlock:exceptionHandler];
//    [ndkGlue registerExceptionHandlerForKey:NSStringFromClass([InsufficientFundsException class]) withBlock:exceptionHandler];
//    [ndkGlue registerExceptionHandlerForKey:NSStringFromClass([NotEnoughGoodsException class]) withBlock:exceptionHandler];

    /* -= Callback handlers =- */
//    [ndkGlue registerCallbackHandlerForKey:EVENT_BILLING_NOT_SUPPORTED withBlock:^(NSNotification *notification, NSMutableDictionary *parameters) {
//        [parameters setObject:@"CCLevelUpEventHandler::onBillingNotSupported" forKey:@"method"];
//    }];
//
}

@end