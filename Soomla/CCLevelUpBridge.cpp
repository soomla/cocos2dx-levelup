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


#include "CCLevelUpBridge.h"
#include "CCDomainFactory.h"
#include "CCLevelUpConsts.h"
#include "CCNdkBridge.h"
#include "CCSoomlaUtils.h"
#include "CCLevelUpEventDispatcher.h"
#include "CCChallenge.h"
#include "CCBalanceMission.h"
#include "CCWorldCompletionMission.h"
#include "CCBalanceGate.h"
#include "CCGatesListAnd.h"
#include "CCPurchasableGate.h"
#include "CCRecordGate.h"
#include "CCScheduleGate.h"
#include "CCWorldCompletionGate.h"
#include "CCGatesListOr.h"
#include "CCRecordMission.h"
#include "CCPurchasingMission.h"
#include "CCDomainHelper.h"
#include "CCRangeScore.h"
#include "CCVirtualItemScore.h"
#include "CCSocialLikeGate.h"
#include "CCSocialStatusGate.h"
#include "CCSocialStoryGate.h"
#include "CCSocialUploadGate.h"
#include "CCSocialLikeMission.h"
#include "CCSocialStatusMission.h"
#include "CCSocialStoryMission.h"
#include "CCSocialUploadMission.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "platform/android/jni/JniHelper.h"
#include <jni.h>
#include <string>

#define CLASS_NAME "com/soomla/cocos2dx/levelup/LevelUpBridgeBinder"
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

#include "CCLevelUpBridgeBinderIos.h"

#endif

USING_NS_CC;


namespace soomla {

#define TAG "SOOMLA CCLevelUpBridge"

    static CCLevelUpBridge *sInstance = NULL;

    CCLevelUpBridge *CCLevelUpBridge::getInstance() {
        if (!sInstance)
        {
            sInstance = new CCLevelUpBridge();
            sInstance->retain();
        }
        return sInstance;
    }

    void CCLevelUpBridge::initShared() {
        CCLevelUpBridge *levelUpService = CCLevelUpBridge::getInstance();
        if (!levelUpService->init()) {
            exit(1);
        }
    }

    CCLevelUpBridge::CCLevelUpBridge() {
        // Just bind to native before initing
        this->bindNative();
    }

    bool CCLevelUpBridge::init() {

        CCLevelUpEventDispatcher::getInstance();

        CCDomainFactory *domainFactory = CCDomainFactory::getInstance();

        domainFactory->registerCreator(CCLevelUpConsts::JSON_JSON_TYPE_MISSION, (SEL_DomainCreator)CCMission::createWithDictionary);
        domainFactory->registerCreator(CCLevelUpConsts::JSON_JSON_TYPE_BALANCE_MISSION, (SEL_DomainCreator)CCBalanceMission::createWithDictionary);
        domainFactory->registerCreator(CCLevelUpConsts::JSON_JSON_TYPE_CHALLENGE, (SEL_DomainCreator)CCChallenge::createWithDictionary);
        domainFactory->registerCreator(CCLevelUpConsts::JSON_JSON_TYPE_PURCHASE_MISSION, (SEL_DomainCreator)CCPurchasingMission::createWithDictionary);
        domainFactory->registerCreator(CCLevelUpConsts::JSON_JSON_TYPE_RECORD_MISSION, (SEL_DomainCreator)CCRecordMission::createWithDictionary);
        domainFactory->registerCreator(CCLevelUpConsts::JSON_JSON_TYPE_WORLD_COMPLETION_MISSION, (SEL_DomainCreator)CCWorldCompletionMission::createWithDictionary);
        domainFactory->registerCreator(CCLevelUpConsts::JSON_JSON_TYPE_SOCIAL_LIKE_MISSION, (SEL_DomainCreator)CCSocialLikeMission::createWithDictionary);
        domainFactory->registerCreator(CCLevelUpConsts::JSON_JSON_TYPE_SOCIAL_STATUS_MISSION, (SEL_DomainCreator)CCSocialStatusMission::createWithDictionary);
        domainFactory->registerCreator(CCLevelUpConsts::JSON_JSON_TYPE_SOCIAL_STORY_MISSION, (SEL_DomainCreator)CCSocialStoryMission::createWithDictionary);
        domainFactory->registerCreator(CCLevelUpConsts::JSON_JSON_TYPE_SOCIAL_UPLOAD_MISSION, (SEL_DomainCreator)CCSocialUploadMission::createWithDictionary);
        domainFactory->registerCreator(CCLevelUpConsts::JSON_JSON_TYPE_BALANCE_GATE, (SEL_DomainCreator)CCBalanceGate::createWithDictionary);
        domainFactory->registerCreator(CCLevelUpConsts::JSON_JSON_TYPE_GATES_LIST_AND, (SEL_DomainCreator)CCGatesListAnd::createWithDictionary);
        domainFactory->registerCreator(CCLevelUpConsts::JSON_JSON_TYPE_GATES_LIST_OR, (SEL_DomainCreator)CCGatesListOr::createWithDictionary);
        domainFactory->registerCreator(CCLevelUpConsts::JSON_JSON_TYPE_PURCHASABLE_GATE, (SEL_DomainCreator)CCPurchasableGate::createWithDictionary);
        domainFactory->registerCreator(CCLevelUpConsts::JSON_JSON_TYPE_RECORD_GATE, (SEL_DomainCreator)CCRecordGate::createWithDictionary);
        domainFactory->registerCreator(CCLevelUpConsts::JSON_JSON_TYPE_SCHEDULE_GATE, (SEL_DomainCreator)CCScheduleGate::createWithDictionary);
        domainFactory->registerCreator(CCLevelUpConsts::JSON_JSON_TYPE_WORLD_COMPLETION_GATE, (SEL_DomainCreator)CCWorldCompletionGate::createWithDictionary);
        domainFactory->registerCreator(CCLevelUpConsts::JSON_JSON_TYPE_SOCIAL_LIKE_GATE, (SEL_DomainCreator)CCSocialLikeGate::createWithDictionary);
        domainFactory->registerCreator(CCLevelUpConsts::JSON_JSON_TYPE_SOCIAL_STATUS_GATE, (SEL_DomainCreator)CCSocialStatusGate::createWithDictionary);
        domainFactory->registerCreator(CCLevelUpConsts::JSON_JSON_TYPE_SOCIAL_STORY_GATE, (SEL_DomainCreator)CCSocialStoryGate::createWithDictionary);
        domainFactory->registerCreator(CCLevelUpConsts::JSON_JSON_TYPE_SOCIAL_UPLOAD_GATE, (SEL_DomainCreator)CCSocialUploadGate::createWithDictionary);
        domainFactory->registerCreator(CCLevelUpConsts::JSON_JSON_TYPE_SCORE, (SEL_DomainCreator)CCScore::createWithDictionary);
        domainFactory->registerCreator(CCLevelUpConsts::JSON_JSON_TYPE_RANGE_SCORE, (SEL_DomainCreator)CCRangeScore::createWithDictionary);
        domainFactory->registerCreator(CCLevelUpConsts::JSON_JSON_TYPE_VIRTUAL_ITEM_SCORE, (SEL_DomainCreator)CCVirtualItemScore::createWithDictionary);
        domainFactory->registerCreator(CCLevelUpConsts::JSON_JSON_TYPE_WORLD, (SEL_DomainCreator)CCWorld::createWithDictionary);
        domainFactory->registerCreator(CCLevelUpConsts::JSON_JSON_TYPE_LEVEL, (SEL_DomainCreator)CCLevel::createWithDictionary);

        return true;
    }

    bool CCLevelUpBridge::initLevelUp() {

        CCSoomlaUtils::logDebug(TAG, "call init");

        CCDictionary *metadata = CCDictionary::create();

        SL_CREATE_PARAMS_FOR_METHOD(params, "CCLevelUpBridge::initLevelUp");
        params->setObject(metadata, "metadata");

        CCError *error = NULL;
        CCDictionary *retParams = (CCDictionary *) CCNdkBridge::callNative (params, &error);

        if (error) {
            CCSoomlaUtils::logError(TAG, CCString::createWithFormat(
                    "call init failed with error: %s", error->getInfo())->getCString());
            return false;
        }

        SL_EXTRACT_FROM_RETURN(CCBool, ret, retParams);

        return ret->getValue();
    }

    bool CCLevelUpBridge::gateIsOpen(CCGate *gate) {
        CCSoomlaUtils::logDebug(TAG,
                CCString::createWithFormat("call gateIsOpen with gate: %s", gate->getId()->getCString())->getCString());

        SL_CREATE_PARAMS_FOR_METHOD(params, "CCLevelUpBridge::gateIsOpen");
        params->setObject(gate->getId(), "gateId");

        CCError *error = NULL;
        CCDictionary *retParams = (CCDictionary *) CCNdkBridge::callNative (params, &error);

        if (error) {
            CCSoomlaUtils::logError(TAG, CCString::createWithFormat(
                    "call gateIsOpen failed with error: %s", error->getInfo())->getCString());
            return false;
        }

        SL_EXTRACT_FROM_RETURN(CCBool, ret, retParams);

        return ret->getValue();
    }

    void CCLevelUpBridge::gateSetOpen(CCGate *gate, bool open, bool notify) {
        CCSoomlaUtils::logDebug(TAG,
                CCString::createWithFormat("call gateSetOpen with gate: %s", gate->getId()->getCString())->getCString());

        SL_CREATE_PARAMS_FOR_METHOD(params, "CCLevelUpBridge::gateSetOpen");
        params->setObject(gate->getId(), "gateId");
        params->setObject(CCBool::create(open), "open");
        params->setObject(CCBool::create(notify), "notify");

        CCError *error = NULL;
        CCNdkBridge::callNative (params, &error);

        if (error) {
            CCSoomlaUtils::logError(TAG, CCString::createWithFormat(
                    "call gateIsOpen failed with error: %s", error->getInfo())->getCString());
        }
    }


    void CCLevelUpBridge::levelSetSlowestDurationMillis(CCLevel *level, long duration) {
        CCSoomlaUtils::logDebug(TAG,
                CCString::createWithFormat("call levelSetSlowestDurationMillis with level: %s", level->getId()->getCString())->getCString());

        SL_CREATE_PARAMS_FOR_METHOD(params, "CCLevelUpBridge::levelSetSlowestDurationMillis");
        params->setObject(level->getId(), "levelId");
        params->setObject(CCInteger::create(duration), "duration");

        CCError *error = NULL;
        CCNdkBridge::callNative (params, &error);

        if (error) {
            CCSoomlaUtils::logError(TAG, CCString::createWithFormat(
                    "call levelSetSlowestDurationMillis failed with error: %s", error->getInfo())->getCString());
        }
    }

    long CCLevelUpBridge::levelGetSlowestDurationMillis(CCLevel *level) {
        CCSoomlaUtils::logDebug(TAG,
                CCString::createWithFormat("call levelGetSlowestDurationMillis with level: %s", level->getId()->getCString())->getCString());

        SL_CREATE_PARAMS_FOR_METHOD(params, "CCLevelUpBridge::levelGetSlowestDurationMillis");
        params->setObject(level->getId(), "levelId");

        CCError *error = NULL;
        CCDictionary *retParams = (CCDictionary *) CCNdkBridge::callNative (params, &error);

        if (error) {
            CCSoomlaUtils::logError(TAG, CCString::createWithFormat(
                    "call levelGetSlowestDurationMillis failed with error: %s", error->getInfo())->getCString());
            return false;
        }

        SL_EXTRACT_FROM_RETURN(CCInteger, ret, retParams);

        return ret->getValue();
    }


    void CCLevelUpBridge::levelSetFastestDurationMillis(CCLevel *level, long duration) {
        CCSoomlaUtils::logDebug(TAG,
                CCString::createWithFormat("call levelSetFastestDurationMillis with level: %s", level->getId()->getCString())->getCString());

        SL_CREATE_PARAMS_FOR_METHOD(params, "CCLevelUpBridge::levelSetFastestDurationMillis");
        params->setObject(level->getId(), "levelId");
        params->setObject(CCInteger::create(duration), "duration");

        CCError *error = NULL;
        CCNdkBridge::callNative (params, &error);

        if (error) {
            CCSoomlaUtils::logError(TAG, CCString::createWithFormat(
                    "call levelSetFastestDurationMillis failed with error: %s", error->getInfo())->getCString());
        }
    }

    long CCLevelUpBridge::levelGetFastestDurationMillis(CCLevel *level) {
        CCSoomlaUtils::logDebug(TAG,
                CCString::createWithFormat("call levelGetFastestDurationMillis with level: %s", level->getId()->getCString())->getCString());

        SL_CREATE_PARAMS_FOR_METHOD(params, "CCLevelUpBridge::levelGetFastestDurationMillis");
        params->setObject(level->getId(), "levelId");

        CCError *error = NULL;
        CCDictionary *retParams = (CCDictionary *) CCNdkBridge::callNative (params, &error);

        if (error) {
            CCSoomlaUtils::logError(TAG, CCString::createWithFormat(
                    "call levelGetFastestDurationMillis failed with error: %s", error->getInfo())->getCString());
            return false;
        }

        SL_EXTRACT_FROM_RETURN(CCInteger, ret, retParams);

        return ret->getValue();
    }


    int CCLevelUpBridge::levelIncTimesStarted(CCLevel *level) {
        CCSoomlaUtils::logDebug(TAG,
                CCString::createWithFormat("call levelIncTimesStarted with level: %s", level->getId()->getCString())->getCString());

        SL_CREATE_PARAMS_FOR_METHOD(params, "CCLevelUpBridge::levelIncTimesStarted");
        params->setObject(level->getId(), "levelId");

        CCError *error = NULL;
        CCDictionary *retParams = (CCDictionary *) CCNdkBridge::callNative (params, &error);

        if (error) {
            CCSoomlaUtils::logError(TAG, CCString::createWithFormat(
                    "call levelIncTimesStarted failed with error: %s", error->getInfo())->getCString());
            return false;
        }

        SL_EXTRACT_FROM_RETURN(CCInteger, ret, retParams);

        return ret->getValue();
    }

    int CCLevelUpBridge::levelDecTimesStarted(CCLevel *level) {
        CCSoomlaUtils::logDebug(TAG,
                CCString::createWithFormat("call levelDecTimesStarted with level: %s", level->getId()->getCString())->getCString());

        SL_CREATE_PARAMS_FOR_METHOD(params, "CCLevelUpBridge::levelDecTimesStarted");
        params->setObject(level->getId(), "levelId");

        CCError *error = NULL;
        CCDictionary *retParams = (CCDictionary *) CCNdkBridge::callNative (params, &error);

        if (error) {
            CCSoomlaUtils::logError(TAG, CCString::createWithFormat(
                    "call levelDecTimesStarted failed with error: %s", error->getInfo())->getCString());
            return false;
        }

        SL_EXTRACT_FROM_RETURN(CCInteger, ret, retParams);

        return ret->getValue();
    }

    int CCLevelUpBridge::levelGetTimesStarted(CCLevel *level) {
        CCSoomlaUtils::logDebug(TAG,
                CCString::createWithFormat("call levelGetTimesStarted with level: %s", level->getId()->getCString())->getCString());

        SL_CREATE_PARAMS_FOR_METHOD(params, "CCLevelUpBridge::levelGetTimesStarted");
        params->setObject(level->getId(), "levelId");

        CCError *error = NULL;
        CCDictionary *retParams = (CCDictionary *) CCNdkBridge::callNative (params, &error);

        if (error) {
            CCSoomlaUtils::logError(TAG, CCString::createWithFormat(
                    "call levelGetTimesStarted failed with error: %s", error->getInfo())->getCString());
            return false;
        }

        SL_EXTRACT_FROM_RETURN(CCInteger, ret, retParams);

        return ret->getValue();
    }


    int CCLevelUpBridge::levelGetTimesPlayed(CCLevel *level) {
        CCSoomlaUtils::logDebug(TAG,
                CCString::createWithFormat("call levelGetTimesPlayed with level: %s", level->getId()->getCString())->getCString());

        SL_CREATE_PARAMS_FOR_METHOD(params, "CCLevelUpBridge::levelGetTimesPlayed");
        params->setObject(level->getId(), "levelId");

        CCError *error = NULL;
        CCDictionary *retParams = (CCDictionary *) CCNdkBridge::callNative (params, &error);

        if (error) {
            CCSoomlaUtils::logError(TAG, CCString::createWithFormat(
                    "call levelGetTimesPlayed failed with error: %s", error->getInfo())->getCString());
            return false;
        }

        SL_EXTRACT_FROM_RETURN(CCInteger, ret, retParams);

        return ret->getValue();
    }

    int CCLevelUpBridge::levelIncTimesPlayed(CCLevel *level) {
        CCSoomlaUtils::logDebug(TAG,
                CCString::createWithFormat("call levelIncTimesPlayed with level: %s", level->getId()->getCString())->getCString());

        SL_CREATE_PARAMS_FOR_METHOD(params, "CCLevelUpBridge::levelIncTimesPlayed");
        params->setObject(level->getId(), "levelId");

        CCError *error = NULL;
        CCDictionary *retParams = (CCDictionary *) CCNdkBridge::callNative (params, &error);

        if (error) {
            CCSoomlaUtils::logError(TAG, CCString::createWithFormat(
                    "call levelIncTimesPlayed failed with error: %s", error->getInfo())->getCString());
            return false;
        }

        SL_EXTRACT_FROM_RETURN(CCInteger, ret, retParams);

        return ret->getValue();
    }

    int CCLevelUpBridge::levelDecTimesPlayed(CCLevel *level) {
        CCSoomlaUtils::logDebug(TAG,
                CCString::createWithFormat("call levelDecTimesPlayed with level: %s", level->getId()->getCString())->getCString());

        SL_CREATE_PARAMS_FOR_METHOD(params, "CCLevelUpBridge::levelDecTimesPlayed");
        params->setObject(level->getId(), "levelId");

        CCError *error = NULL;
        CCDictionary *retParams = (CCDictionary *) CCNdkBridge::callNative (params, &error);

        if (error) {
            CCSoomlaUtils::logError(TAG, CCString::createWithFormat(
                    "call levelDecTimesPlayed failed with error: %s", error->getInfo())->getCString());
            return false;
        }

        SL_EXTRACT_FROM_RETURN(CCInteger, ret, retParams);

        return ret->getValue();
    }
    
    int CCLevelUpBridge::levelGetTimesCompleted(CCLevel *level) {
        CCSoomlaUtils::logDebug(TAG,
                                CCString::createWithFormat("call levelGetTimesCompleted with level: %s", level->getId()->getCString())->getCString());
        
        SL_CREATE_PARAMS_FOR_METHOD(params, "CCLevelUpBridge::levelGetTimesCompleted");
        params->setObject(level->getId(), "levelId");
        
        CCError *error = NULL;
        CCDictionary *retParams = (CCDictionary *) CCNdkBridge::callNative (params, &error);
        
        if (error) {
            CCSoomlaUtils::logError(TAG, CCString::createWithFormat(
                                                                    "call levelGetTimesCompleted failed with error: %s", error->getInfo())->getCString());
            return false;
        }
        
        SL_EXTRACT_FROM_RETURN(CCInteger, ret, retParams);
        
        return ret->getValue();
    }
    
    int CCLevelUpBridge::levelIncTimesCompleted(CCLevel *level) {
        CCSoomlaUtils::logDebug(TAG,
                                CCString::createWithFormat("call levelIncTimesCompleted with level: %s", level->getId()->getCString())->getCString());
        
        SL_CREATE_PARAMS_FOR_METHOD(params, "CCLevelUpBridge::levelIncTimesCompleted");
        params->setObject(level->getId(), "levelId");
        
        CCError *error = NULL;
        CCDictionary *retParams = (CCDictionary *) CCNdkBridge::callNative (params, &error);
        
        if (error) {
            CCSoomlaUtils::logError(TAG, CCString::createWithFormat(
                                                                    "call levelIncTimesCompleted failed with error: %s", error->getInfo())->getCString());
            return false;
        }
        
        SL_EXTRACT_FROM_RETURN(CCInteger, ret, retParams);
        
        return ret->getValue();
    }
    
    int CCLevelUpBridge::levelDecTimesCompleted(CCLevel *level) {
        CCSoomlaUtils::logDebug(TAG,
                                CCString::createWithFormat("call levelDecTimesCompleted with level: %s", level->getId()->getCString())->getCString());
        
        SL_CREATE_PARAMS_FOR_METHOD(params, "CCLevelUpBridge::levelDecTimesCompleted");
        params->setObject(level->getId(), "levelId");
        
        CCError *error = NULL;
        CCDictionary *retParams = (CCDictionary *) CCNdkBridge::callNative (params, &error);
        
        if (error) {
            CCSoomlaUtils::logError(TAG, CCString::createWithFormat(
                                                                    "call levelDecTimesCompleted failed with error: %s", error->getInfo())->getCString());
            return false;
        }
        
        SL_EXTRACT_FROM_RETURN(CCInteger, ret, retParams);
        
        return ret->getValue();
    }

    void CCLevelUpBridge::missionSetCompleted(CCMission *mission, bool completed, bool notify) {
        CCSoomlaUtils::logDebug(TAG,
                CCString::createWithFormat("call missionSetCompleted with mission: %s", mission->getId()->getCString())->getCString());

        SL_CREATE_PARAMS_FOR_METHOD(params, "CCLevelUpBridge::missionSetCompleted");
        params->setObject(mission->getId(), "missionId");
        params->setObject(CCBool::create(completed), "completed");
        params->setObject(CCBool::create(notify), "notify");

        CCError *error = NULL;
        CCNdkBridge::callNative (params, &error);

        if (error) {
            CCSoomlaUtils::logError(TAG, CCString::createWithFormat(
                    "call missionSetCompleted failed with error: %s", error->getInfo())->getCString());
        }
    }

    int CCLevelUpBridge::missionGetTimesCompleted(CCMission *mission) {
        CCSoomlaUtils::logDebug(TAG,
                CCString::createWithFormat("call missionGetTimesCompleted with mission: %s", mission->getId()->getCString())->getCString());

        SL_CREATE_PARAMS_FOR_METHOD(params, "CCLevelUpBridge::missionGetTimesCompleted");
        params->setObject(mission->getId(), "missionId");

        CCError *error = NULL;
        CCDictionary *retParams = (CCDictionary *) CCNdkBridge::callNative (params, &error);

        if (error) {
            CCSoomlaUtils::logError(TAG, CCString::createWithFormat(
                    "call missionGetTimesCompleted failed with error: %s", error->getInfo())->getCString());
            return false;
        }

        SL_EXTRACT_FROM_RETURN(CCInteger, ret, retParams);

        return ret->getValue();
    }

    void CCLevelUpBridge::scoreSetLatestScore(CCScore *score, double newValue) {
        CCSoomlaUtils::logDebug(TAG,
                CCString::createWithFormat("call scoreSetLatestScore with score: %s", score->getId()->getCString())->getCString());

        SL_CREATE_PARAMS_FOR_METHOD(params, "CCLevelUpBridge::scoreSetLatestScore");
        params->setObject(score->getId(), "scoreId");
        params->setObject(CCDouble::create(newValue), "newValue");

        CCError *error = NULL;
        CCNdkBridge::callNative (params, &error);

        if (error) {
            CCSoomlaUtils::logError(TAG, CCString::createWithFormat(
                    "call scoreSetLatestScore failed with error: %s", error->getInfo())->getCString());
        }
    }

    double CCLevelUpBridge::scoreGetLatestScore(CCScore *score) {
        CCSoomlaUtils::logDebug(TAG,
                CCString::createWithFormat("call scoreGetLatestScore with score: %s", score->getId()->getCString())->getCString());

        SL_CREATE_PARAMS_FOR_METHOD(params, "CCLevelUpBridge::scoreGetLatestScore");
        params->setObject(score->getId(), "scoreId");

        CCError *error = NULL;
        CCDictionary *retParams = (CCDictionary *) CCNdkBridge::callNative (params, &error);

        if (error) {
            CCSoomlaUtils::logError(TAG, CCString::createWithFormat(
                    "call scoreGetLatestScore failed with error: %s", error->getInfo())->getCString());
            return false;
        }

        SL_EXTRACT_DOUBLE_FROM_RETURN(ret, retParams);

        return ret->getValue();
    }

    void CCLevelUpBridge::scoreSetRecordScore(CCScore *score, double newValue) {
        CCSoomlaUtils::logDebug(TAG,
                CCString::createWithFormat("call scoreSetRecordScore with score: %s", score->getId()->getCString())->getCString());

        SL_CREATE_PARAMS_FOR_METHOD(params, "CCLevelUpBridge::scoreSetRecordScore");
        params->setObject(score->getId(), "scoreId");
        params->setObject(CCDouble::create(newValue), "newValue");

        CCError *error = NULL;
        CCNdkBridge::callNative (params, &error);

        if (error) {
            CCSoomlaUtils::logError(TAG, CCString::createWithFormat(
                    "call scoreSetRecordScore failed with error: %s", error->getInfo())->getCString());
        }
    }

    double CCLevelUpBridge::scoreGetRecordScore(CCScore *score) {
        CCSoomlaUtils::logDebug(TAG,
                CCString::createWithFormat("call scoreGetRecordScore with score: %s", score->getId()->getCString())->getCString());

        SL_CREATE_PARAMS_FOR_METHOD(params, "CCLevelUpBridge::scoreGetRecordScore");
        params->setObject(score->getId(), "scoreId");

        CCError *error = NULL;
        CCDictionary *retParams = (CCDictionary *) CCNdkBridge::callNative (params, &error);

        if (error) {
            CCSoomlaUtils::logError(TAG, CCString::createWithFormat(
                    "call scoreGetRecordScore failed with error: %s", error->getInfo())->getCString());
            return false;
        }

        SL_EXTRACT_DOUBLE_FROM_RETURN(ret, retParams);

        return ret->getValue();
    }

    void CCLevelUpBridge::worldSetCompleted(CCWorld *world, bool completed, bool notify) {
        CCSoomlaUtils::logDebug(TAG,
                CCString::createWithFormat("call worldSetCompleted with world: %s", world->getId()->getCString())->getCString());

        SL_CREATE_PARAMS_FOR_METHOD(params, "CCLevelUpBridge::worldSetCompleted");
        params->setObject(world->getId(), "worldId");
        params->setObject(CCBool::create(completed), "completed");
        params->setObject(CCBool::create(notify), "notify");

        CCError *error = NULL;
        CCNdkBridge::callNative (params, &error);

        if (error) {
            CCSoomlaUtils::logError(TAG, CCString::createWithFormat(
                    "call worldSetCompleted failed with error: %s", error->getInfo())->getCString());
        }
    }

    bool CCLevelUpBridge::worldIsCompleted(CCWorld *world) {
        CCSoomlaUtils::logDebug(TAG,
                CCString::createWithFormat("call worldIsCompleted with world: %s", world->getId()->getCString())->getCString());

        SL_CREATE_PARAMS_FOR_METHOD(params, "CCLevelUpBridge::worldIsCompleted");
        params->setObject(world->getId(), "worldId");

        CCError *error = NULL;
        CCDictionary *retParams = (CCDictionary *) CCNdkBridge::callNative (params, &error);

        if (error) {
            CCSoomlaUtils::logError(TAG, CCString::createWithFormat(
                    "call worldIsCompleted failed with error: %s", error->getInfo())->getCString());
            return false;
        }

        SL_EXTRACT_FROM_RETURN(CCBool, ret, retParams);

        return ret->getValue();
    }

    void CCLevelUpBridge::worldSetReward(CCWorld *world, cocos2d::CCString *rewardId) {
        CCSoomlaUtils::logDebug(TAG,
                CCString::createWithFormat("call worldSetReward with world: %s", world->getId()->getCString())->getCString());

        SL_CREATE_PARAMS_FOR_METHOD(params, "CCLevelUpBridge::worldSetReward");
        params->setObject(world->getId(), "worldId");
        params->setObject(rewardId, "rewardId");

        CCError *error = NULL;
        CCNdkBridge::callNative (params, &error);

        if (error) {
            CCSoomlaUtils::logError(TAG, CCString::createWithFormat(
                    "call worldSetReward failed with error: %s", error->getInfo())->getCString());
        }
    }

    cocos2d::CCString *CCLevelUpBridge::worldGetAssignedReward(CCWorld *world) {
        CCSoomlaUtils::logDebug(TAG,
                CCString::createWithFormat("call worldGetAssignedReward with world: %s", world->getId()->getCString())->getCString());

        SL_CREATE_PARAMS_FOR_METHOD(params, "CCLevelUpBridge::worldGetAssignedReward");
        params->setObject(world->getId(), "worldId");

        CCError *error = NULL;
        CCDictionary *retParams = (CCDictionary *) CCNdkBridge::callNative (params, &error);

        if (error) {
            CCSoomlaUtils::logError(TAG, CCString::createWithFormat(
                    "call worldGetAssignedReward failed with error: %s", error->getInfo())->getCString());
            return NULL;
        }

        if ((retParams == NULL) || (retParams->count() == 0)) {
            return NULL;
        }

        SL_EXTRACT_FROM_RETURN(CCString, ret, retParams);
        return ret;
    }
    
    void CCLevelUpBridge::worldSetLastCompletedInnerWorld(CCWorld *world, cocos2d::CCString *innerWorldId) {
        CCSoomlaUtils::logDebug(TAG,
                                CCString::createWithFormat("call worldSetLastCompletedInnerWorld with world: %s", world->getId()->getCString())->getCString());
        
        SL_CREATE_PARAMS_FOR_METHOD(params, "CCLevelUpBridge::worldSetLastCompletedInnerWorld");
        params->setObject(world->getId(), "worldId");
        params->setObject(innerWorldId, "innerWorldId");
        
        CCError *error = NULL;
        CCNdkBridge::callNative (params, &error);
        
        if (error) {
            CCSoomlaUtils::logError(TAG, CCString::createWithFormat(
                                                                    "call worldSetLastCompletedInnerWorld failed with error: %s", error->getInfo())->getCString());
        }
    }
    
    cocos2d::CCString *CCLevelUpBridge::worldGetLastCompletedInnerWorld(CCWorld *world) {
        CCSoomlaUtils::logDebug(TAG,
                                CCString::createWithFormat("call worldGetLastCompletedInnerWorld with world: %s", world->getId()->getCString())->getCString());
        
        SL_CREATE_PARAMS_FOR_METHOD(params, "CCLevelUpBridge::worldGetLastCompletedInnerWorld");
        params->setObject(world->getId(), "worldId");
        
        CCError *error = NULL;
        CCDictionary *retParams = (CCDictionary *) CCNdkBridge::callNative (params, &error);
        
        if (error) {
            CCSoomlaUtils::logError(TAG, CCString::createWithFormat(
                                                                    "call worldGetLastCompletedInnerWorld failed with error: %s", error->getInfo())->getCString());
            return NULL;
        }
        
        if ((retParams == NULL) || (retParams->count() == 0)) {
            return NULL;
        }
        
        SL_EXTRACT_FROM_RETURN(CCString, ret, retParams);
        return ret;
    }
    
    void CCLevelUpBridge::bindNative() {
        CCSoomlaUtils::logDebug(TAG, "Binding to native platform LevelUp bridge...");
        
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        JniMethodInfo minfo;
        
        bool exists = JniHelper::getStaticMethodInfo(minfo, CLASS_NAME, "bind", "()V");
        
        if (exists)
        {
            minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID);
        }
        else {
            CCSoomlaUtils::logError(TAG, "Unable to bind native LevelUp bridge on Android");
        }
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        soomla::CCLevelUpBridgeBinderIos::bind();
#endif
    }
}
