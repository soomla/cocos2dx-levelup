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

    static CCLevelUpBridge *sInstance = nullptr;

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

        domainFactory->registerCreator(CCLevelUpConsts::JSON_JSON_TYPE_MISSION, CCMission::createWithDictionary);
        domainFactory->registerCreator(CCLevelUpConsts::JSON_JSON_TYPE_BALANCE_MISSION, CCBalanceMission::createWithDictionary);
        domainFactory->registerCreator(CCLevelUpConsts::JSON_JSON_TYPE_CHALLENGE, CCChallenge::createWithDictionary);
        domainFactory->registerCreator(CCLevelUpConsts::JSON_JSON_TYPE_PURCHASE_MISSION, CCPurchasingMission::createWithDictionary);
        domainFactory->registerCreator(CCLevelUpConsts::JSON_JSON_TYPE_RECORD_MISSION, CCRecordMission::createWithDictionary);
        domainFactory->registerCreator(CCLevelUpConsts::JSON_JSON_TYPE_WORLD_COMPLETION_MISSION, CCWorldCompletionMission::createWithDictionary);
        domainFactory->registerCreator(CCLevelUpConsts::JSON_JSON_TYPE_SOCIAL_LIKE_MISSION, CCSocialLikeMission::createWithDictionary);
        domainFactory->registerCreator(CCLevelUpConsts::JSON_JSON_TYPE_SOCIAL_STATUS_MISSION, CCSocialStatusMission::createWithDictionary);
        domainFactory->registerCreator(CCLevelUpConsts::JSON_JSON_TYPE_SOCIAL_STORY_MISSION, CCSocialStoryMission::createWithDictionary);
        domainFactory->registerCreator(CCLevelUpConsts::JSON_JSON_TYPE_SOCIAL_UPLOAD_MISSION, CCSocialUploadMission::createWithDictionary);
        domainFactory->registerCreator(CCLevelUpConsts::JSON_JSON_TYPE_BALANCE_GATE, CCBalanceGate::createWithDictionary);
        domainFactory->registerCreator(CCLevelUpConsts::JSON_JSON_TYPE_GATES_LIST_AND, CCGatesListAnd::createWithDictionary);
        domainFactory->registerCreator(CCLevelUpConsts::JSON_JSON_TYPE_GATES_LIST_OR, CCGatesListOr::createWithDictionary);
        domainFactory->registerCreator(CCLevelUpConsts::JSON_JSON_TYPE_PURCHASABLE_GATE, CCPurchasableGate::createWithDictionary);
        domainFactory->registerCreator(CCLevelUpConsts::JSON_JSON_TYPE_RECORD_GATE, CCRecordGate::createWithDictionary);
        domainFactory->registerCreator(CCLevelUpConsts::JSON_JSON_TYPE_SCHEDULE_GATE, CCScheduleGate::createWithDictionary);
        domainFactory->registerCreator(CCLevelUpConsts::JSON_JSON_TYPE_WORLD_COMPLETION_GATE, CCWorldCompletionGate::createWithDictionary);
        domainFactory->registerCreator(CCLevelUpConsts::JSON_JSON_TYPE_SOCIAL_LIKE_GATE, CCSocialLikeGate::createWithDictionary);
        domainFactory->registerCreator(CCLevelUpConsts::JSON_JSON_TYPE_SOCIAL_STATUS_GATE, CCSocialStatusGate::createWithDictionary);
        domainFactory->registerCreator(CCLevelUpConsts::JSON_JSON_TYPE_SOCIAL_STORY_GATE, CCSocialStoryGate::createWithDictionary);
        domainFactory->registerCreator(CCLevelUpConsts::JSON_JSON_TYPE_SOCIAL_UPLOAD_GATE, CCSocialUploadGate::createWithDictionary);
        domainFactory->registerCreator(CCLevelUpConsts::JSON_JSON_TYPE_SCORE, CCScore::createWithDictionary);
        domainFactory->registerCreator(CCLevelUpConsts::JSON_JSON_TYPE_RANGE_SCORE, CCRangeScore::createWithDictionary);
        domainFactory->registerCreator(CCLevelUpConsts::JSON_JSON_TYPE_VIRTUAL_ITEM_SCORE, CCVirtualItemScore::createWithDictionary);
        domainFactory->registerCreator(CCLevelUpConsts::JSON_JSON_TYPE_WORLD, CCWorld::createWithDictionary);
        domainFactory->registerCreator(CCLevelUpConsts::JSON_JSON_TYPE_LEVEL, CCLevel::createWithDictionary);

        return true;
    }

    bool CCLevelUpBridge::initLevelUp() {

        CCSoomlaUtils::logDebug(TAG, "call init");

        __Dictionary *metadata = __Dictionary::create();

        SL_CREATE_PARAMS_FOR_METHOD(params, "CCLevelUpBridge::initLevelUp");
        params->setObject(metadata, "metadata");

        CCError *error = NULL;
        __Dictionary *retParams = (__Dictionary *) CCNdkBridge::callNative (params, &error);

        if (error) {
            CCSoomlaUtils::logError(TAG, __String::createWithFormat(
                    "call init failed with error: %s", error->getInfo())->getCString());
            return false;
        }

        SL_EXTRACT_FROM_RETURN(__Bool, ret, retParams);

        return ret->getValue();
    }

    bool CCLevelUpBridge::gateIsOpen(CCGate *gate) {
        CCSoomlaUtils::logDebug(TAG,
                __String::createWithFormat("call gateIsOpen with gate: %s", gate->getId()->getCString())->getCString());

        SL_CREATE_PARAMS_FOR_METHOD(params, "CCLevelUpBridge::gateIsOpen");
        params->setObject(gate->getId(), "gateId");

        CCError *error = NULL;
        __Dictionary *retParams = (__Dictionary *) CCNdkBridge::callNative (params, &error);

        if (error) {
            CCSoomlaUtils::logError(TAG, __String::createWithFormat(
                    "call gateIsOpen failed with error: %s", error->getInfo())->getCString());
            return false;
        }

        SL_EXTRACT_FROM_RETURN(__Bool, ret, retParams);

        return ret->getValue();
    }

    void CCLevelUpBridge::gateSetOpen(CCGate *gate, bool open, bool notify) {
        CCSoomlaUtils::logDebug(TAG,
                __String::createWithFormat("call gateSetOpen with gate: %s", gate->getId()->getCString())->getCString());

        SL_CREATE_PARAMS_FOR_METHOD(params, "CCLevelUpBridge::gateSetOpen");
        params->setObject(gate->getId(), "gateId");
        params->setObject(__Bool::create(open), "open");
        params->setObject(__Bool::create(notify), "notify");

        CCError *error = NULL;
        CCNdkBridge::callNative (params, &error);

        if (error) {
            CCSoomlaUtils::logError(TAG, __String::createWithFormat(
                    "call gateIsOpen failed with error: %s", error->getInfo())->getCString());
        }
    }


    void CCLevelUpBridge::levelSetSlowestDurationMillis(CCLevel *level, long duration) {
        CCSoomlaUtils::logDebug(TAG,
                __String::createWithFormat("call levelSetSlowestDurationMillis with level: %s", level->getId()->getCString())->getCString());

        SL_CREATE_PARAMS_FOR_METHOD(params, "CCLevelUpBridge::levelSetSlowestDurationMillis");
        params->setObject(level->getId(), "levelId");
        params->setObject(__Integer::create(duration), "duration");

        CCError *error = NULL;
        CCNdkBridge::callNative (params, &error);

        if (error) {
            CCSoomlaUtils::logError(TAG, __String::createWithFormat(
                    "call levelSetSlowestDurationMillis failed with error: %s", error->getInfo())->getCString());
        }
    }

    long CCLevelUpBridge::levelGetSlowestDurationMillis(CCLevel *level) {
        CCSoomlaUtils::logDebug(TAG,
                __String::createWithFormat("call levelGetSlowestDurationMillis with level: %s", level->getId()->getCString())->getCString());

        SL_CREATE_PARAMS_FOR_METHOD(params, "CCLevelUpBridge::levelGetSlowestDurationMillis");
        params->setObject(level->getId(), "levelId");

        CCError *error = NULL;
        __Dictionary *retParams = (__Dictionary *) CCNdkBridge::callNative (params, &error);

        if (error) {
            CCSoomlaUtils::logError(TAG, __String::createWithFormat(
                    "call levelGetSlowestDurationMillis failed with error: %s", error->getInfo())->getCString());
            return false;
        }

        SL_EXTRACT_FROM_RETURN(__Integer, ret, retParams);

        return ret->getValue();
    }


    void CCLevelUpBridge::levelSetFastestDurationMillis(CCLevel *level, long duration) {
        CCSoomlaUtils::logDebug(TAG,
                __String::createWithFormat("call levelSetFastestDurationMillis with level: %s", level->getId()->getCString())->getCString());

        SL_CREATE_PARAMS_FOR_METHOD(params, "CCLevelUpBridge::levelSetFastestDurationMillis");
        params->setObject(level->getId(), "levelId");
        params->setObject(__Integer::create(duration), "duration");

        CCError *error = NULL;
        CCNdkBridge::callNative (params, &error);

        if (error) {
            CCSoomlaUtils::logError(TAG, __String::createWithFormat(
                    "call levelSetFastestDurationMillis failed with error: %s", error->getInfo())->getCString());
        }
    }

    long CCLevelUpBridge::levelGetFastestDurationMillis(CCLevel *level) {
        CCSoomlaUtils::logDebug(TAG,
                __String::createWithFormat("call levelGetFastestDurationMillis with level: %s", level->getId()->getCString())->getCString());

        SL_CREATE_PARAMS_FOR_METHOD(params, "CCLevelUpBridge::levelGetFastestDurationMillis");
        params->setObject(level->getId(), "levelId");

        CCError *error = NULL;
        __Dictionary *retParams = (__Dictionary *) CCNdkBridge::callNative (params, &error);

        if (error) {
            CCSoomlaUtils::logError(TAG, __String::createWithFormat(
                    "call levelGetFastestDurationMillis failed with error: %s", error->getInfo())->getCString());
            return false;
        }

        SL_EXTRACT_FROM_RETURN(__Integer, ret, retParams);

        return ret->getValue();
    }


    int CCLevelUpBridge::levelIncTimesStarted(CCLevel *level) {
        CCSoomlaUtils::logDebug(TAG,
                __String::createWithFormat("call levelIncTimesStarted with level: %s", level->getId()->getCString())->getCString());

        SL_CREATE_PARAMS_FOR_METHOD(params, "CCLevelUpBridge::levelIncTimesStarted");
        params->setObject(level->getId(), "levelId");

        CCError *error = NULL;
        __Dictionary *retParams = (__Dictionary *) CCNdkBridge::callNative (params, &error);

        if (error) {
            CCSoomlaUtils::logError(TAG, __String::createWithFormat(
                    "call levelIncTimesStarted failed with error: %s", error->getInfo())->getCString());
            return false;
        }

        SL_EXTRACT_FROM_RETURN(__Integer, ret, retParams);

        return ret->getValue();
    }

    int CCLevelUpBridge::levelDecTimesStarted(CCLevel *level) {
        CCSoomlaUtils::logDebug(TAG,
                __String::createWithFormat("call levelDecTimesStarted with level: %s", level->getId()->getCString())->getCString());

        SL_CREATE_PARAMS_FOR_METHOD(params, "CCLevelUpBridge::levelDecTimesStarted");
        params->setObject(level->getId(), "levelId");

        CCError *error = NULL;
        __Dictionary *retParams = (__Dictionary *) CCNdkBridge::callNative (params, &error);

        if (error) {
            CCSoomlaUtils::logError(TAG, __String::createWithFormat(
                    "call levelDecTimesStarted failed with error: %s", error->getInfo())->getCString());
            return false;
        }

        SL_EXTRACT_FROM_RETURN(__Integer, ret, retParams);

        return ret->getValue();
    }

    int CCLevelUpBridge::levelGetTimesStarted(CCLevel *level) {
        CCSoomlaUtils::logDebug(TAG,
                __String::createWithFormat("call levelGetTimesStarted with level: %s", level->getId()->getCString())->getCString());

        SL_CREATE_PARAMS_FOR_METHOD(params, "CCLevelUpBridge::levelGetTimesStarted");
        params->setObject(level->getId(), "levelId");

        CCError *error = NULL;
        __Dictionary *retParams = (__Dictionary *) CCNdkBridge::callNative (params, &error);

        if (error) {
            CCSoomlaUtils::logError(TAG, __String::createWithFormat(
                    "call levelGetTimesStarted failed with error: %s", error->getInfo())->getCString());
            return false;
        }

        SL_EXTRACT_FROM_RETURN(__Integer, ret, retParams);

        return ret->getValue();
    }


    int CCLevelUpBridge::levelGetTimesPlayed(CCLevel *level) {
        CCSoomlaUtils::logDebug(TAG,
                __String::createWithFormat("call levelGetTimesPlayed with level: %s", level->getId()->getCString())->getCString());

        SL_CREATE_PARAMS_FOR_METHOD(params, "CCLevelUpBridge::levelGetTimesPlayed");
        params->setObject(level->getId(), "levelId");

        CCError *error = NULL;
        __Dictionary *retParams = (__Dictionary *) CCNdkBridge::callNative (params, &error);

        if (error) {
            CCSoomlaUtils::logError(TAG, __String::createWithFormat(
                    "call levelGetTimesPlayed failed with error: %s", error->getInfo())->getCString());
            return false;
        }

        SL_EXTRACT_FROM_RETURN(__Integer, ret, retParams);

        return ret->getValue();
    }

    int CCLevelUpBridge::levelIncTimesPlayed(CCLevel *level) {
        CCSoomlaUtils::logDebug(TAG,
                __String::createWithFormat("call levelIncTimesPlayed with level: %s", level->getId()->getCString())->getCString());

        SL_CREATE_PARAMS_FOR_METHOD(params, "CCLevelUpBridge::levelIncTimesPlayed");
        params->setObject(level->getId(), "levelId");

        CCError *error = NULL;
        __Dictionary *retParams = (__Dictionary *) CCNdkBridge::callNative (params, &error);

        if (error) {
            CCSoomlaUtils::logError(TAG, __String::createWithFormat(
                    "call levelIncTimesPlayed failed with error: %s", error->getInfo())->getCString());
            return false;
        }

        SL_EXTRACT_FROM_RETURN(__Integer, ret, retParams);

        return ret->getValue();
    }

    int CCLevelUpBridge::levelDecTimesPlayed(CCLevel *level) {
        CCSoomlaUtils::logDebug(TAG,
                __String::createWithFormat("call levelDecTimesPlayed with level: %s", level->getId()->getCString())->getCString());

        SL_CREATE_PARAMS_FOR_METHOD(params, "CCLevelUpBridge::levelDecTimesPlayed");
        params->setObject(level->getId(), "levelId");

        CCError *error = NULL;
        __Dictionary *retParams = (__Dictionary *) CCNdkBridge::callNative (params, &error);

        if (error) {
            CCSoomlaUtils::logError(TAG, __String::createWithFormat(
                    "call levelDecTimesPlayed failed with error: %s", error->getInfo())->getCString());
            return false;
        }

        SL_EXTRACT_FROM_RETURN(__Integer, ret, retParams);

        return ret->getValue();
    }
    
    int CCLevelUpBridge::levelGetTimesCompleted(CCLevel *level) {
        CCSoomlaUtils::logDebug(TAG,
                                __String::createWithFormat("call levelGetTimesCompleted with level: %s", level->getId()->getCString())->getCString());
        
        SL_CREATE_PARAMS_FOR_METHOD(params, "CCLevelUpBridge::levelGetTimesCompleted");
        params->setObject(level->getId(), "levelId");
        
        CCError *error = NULL;
        __Dictionary *retParams = (__Dictionary *) CCNdkBridge::callNative (params, &error);
        
        if (error) {
            CCSoomlaUtils::logError(TAG, __String::createWithFormat(
                                                                    "call levelGetTimesCompleted failed with error: %s", error->getInfo())->getCString());
            return false;
        }
        
        SL_EXTRACT_FROM_RETURN(__Integer, ret, retParams);
        
        return ret->getValue();
    }
    
    int CCLevelUpBridge::levelIncTimesCompleted(CCLevel *level) {
        CCSoomlaUtils::logDebug(TAG,
                                __String::createWithFormat("call levelIncTimesCompleted with level: %s", level->getId()->getCString())->getCString());
        
        SL_CREATE_PARAMS_FOR_METHOD(params, "CCLevelUpBridge::levelIncTimesCompleted");
        params->setObject(level->getId(), "levelId");
        
        CCError *error = NULL;
        __Dictionary *retParams = (__Dictionary *) CCNdkBridge::callNative (params, &error);
        
        if (error) {
            CCSoomlaUtils::logError(TAG, __String::createWithFormat(
                                                                    "call levelIncTimesCompleted failed with error: %s", error->getInfo())->getCString());
            return false;
        }
        
        SL_EXTRACT_FROM_RETURN(__Integer, ret, retParams);
        
        return ret->getValue();
    }
    
    int CCLevelUpBridge::levelDecTimesCompleted(CCLevel *level) {
        CCSoomlaUtils::logDebug(TAG,
                                __String::createWithFormat("call levelDecTimesCompleted with level: %s", level->getId()->getCString())->getCString());
        
        SL_CREATE_PARAMS_FOR_METHOD(params, "CCLevelUpBridge::levelDecTimesCompleted");
        params->setObject(level->getId(), "levelId");
        
        CCError *error = NULL;
        __Dictionary *retParams = (__Dictionary *) CCNdkBridge::callNative (params, &error);
        
        if (error) {
            CCSoomlaUtils::logError(TAG, __String::createWithFormat(
                                                                    "call levelDecTimesCompleted failed with error: %s", error->getInfo())->getCString());
            return false;
        }
        
        SL_EXTRACT_FROM_RETURN(__Integer, ret, retParams);
        
        return ret->getValue();
    }

    void CCLevelUpBridge::missionSetCompleted(CCMission *mission, bool completed, bool notify) {
        CCSoomlaUtils::logDebug(TAG,
                __String::createWithFormat("call missionSetCompleted with mission: %s", mission->getId()->getCString())->getCString());

        SL_CREATE_PARAMS_FOR_METHOD(params, "CCLevelUpBridge::missionSetCompleted");
        params->setObject(mission->getId(), "missionId");
        params->setObject(__Bool::create(completed), "completed");
        params->setObject(__Bool::create(notify), "notify");

        CCError *error = NULL;
        CCNdkBridge::callNative (params, &error);

        if (error) {
            CCSoomlaUtils::logError(TAG, __String::createWithFormat(
                    "call missionSetCompleted failed with error: %s", error->getInfo())->getCString());
        }
    }

    int CCLevelUpBridge::missionGetTimesCompleted(CCMission *mission) {
        CCSoomlaUtils::logDebug(TAG,
                __String::createWithFormat("call missionGetTimesCompleted with mission: %s", mission->getId()->getCString())->getCString());

        SL_CREATE_PARAMS_FOR_METHOD(params, "CCLevelUpBridge::missionGetTimesCompleted");
        params->setObject(mission->getId(), "missionId");

        CCError *error = NULL;
        __Dictionary *retParams = (__Dictionary *) CCNdkBridge::callNative (params, &error);

        if (error) {
            CCSoomlaUtils::logError(TAG, __String::createWithFormat(
                    "call missionGetTimesCompleted failed with error: %s", error->getInfo())->getCString());
            return false;
        }

        SL_EXTRACT_FROM_RETURN(__Integer, ret, retParams);

        return ret->getValue();
    }

    void CCLevelUpBridge::scoreSetLatestScore(CCScore *score, double newValue) {
        CCSoomlaUtils::logDebug(TAG,
                __String::createWithFormat("call scoreSetLatestScore with score: %s", score->getId()->getCString())->getCString());

        SL_CREATE_PARAMS_FOR_METHOD(params, "CCLevelUpBridge::scoreSetLatestScore");
        params->setObject(score->getId(), "scoreId");
        params->setObject(__Double::create(newValue), "newValue");

        CCError *error = NULL;
        CCNdkBridge::callNative (params, &error);

        if (error) {
            CCSoomlaUtils::logError(TAG, __String::createWithFormat(
                    "call scoreSetLatestScore failed with error: %s", error->getInfo())->getCString());
        }
    }

    double CCLevelUpBridge::scoreGetLatestScore(CCScore *score) {
        CCSoomlaUtils::logDebug(TAG,
                __String::createWithFormat("call scoreGetLatestScore with score: %s", score->getId()->getCString())->getCString());

        SL_CREATE_PARAMS_FOR_METHOD(params, "CCLevelUpBridge::scoreGetLatestScore");
        params->setObject(score->getId(), "scoreId");

        CCError *error = NULL;
        __Dictionary *retParams = (__Dictionary *) CCNdkBridge::callNative (params, &error);

        if (error) {
            CCSoomlaUtils::logError(TAG, __String::createWithFormat(
                    "call scoreGetLatestScore failed with error: %s", error->getInfo())->getCString());
            return false;
        }

        SL_EXTRACT_DOUBLE_FROM_RETURN(ret, retParams);

        return ret->getValue();
    }

    void CCLevelUpBridge::scoreSetRecordScore(CCScore *score, double newValue) {
        CCSoomlaUtils::logDebug(TAG,
                __String::createWithFormat("call scoreSetRecordScore with score: %s", score->getId()->getCString())->getCString());

        SL_CREATE_PARAMS_FOR_METHOD(params, "CCLevelUpBridge::scoreSetRecordScore");
        params->setObject(score->getId(), "scoreId");
        params->setObject(__Double::create(newValue), "newValue");

        CCError *error = NULL;
        CCNdkBridge::callNative (params, &error);

        if (error) {
            CCSoomlaUtils::logError(TAG, __String::createWithFormat(
                    "call scoreSetRecordScore failed with error: %s", error->getInfo())->getCString());
        }
    }

    double CCLevelUpBridge::scoreGetRecordScore(CCScore *score) {
        CCSoomlaUtils::logDebug(TAG,
                __String::createWithFormat("call scoreGetRecordScore with score: %s", score->getId()->getCString())->getCString());

        SL_CREATE_PARAMS_FOR_METHOD(params, "CCLevelUpBridge::scoreGetRecordScore");
        params->setObject(score->getId(), "scoreId");

        CCError *error = NULL;
        __Dictionary *retParams = (__Dictionary *) CCNdkBridge::callNative (params, &error);

        if (error) {
            CCSoomlaUtils::logError(TAG, __String::createWithFormat(
                    "call scoreGetRecordScore failed with error: %s", error->getInfo())->getCString());
            return false;
        }

        SL_EXTRACT_DOUBLE_FROM_RETURN(ret, retParams);

        return ret->getValue();
    }

    void CCLevelUpBridge::worldSetCompleted(CCWorld *world, bool completed, bool notify) {
        CCSoomlaUtils::logDebug(TAG,
                __String::createWithFormat("call worldSetCompleted with world: %s", world->getId()->getCString())->getCString());

        SL_CREATE_PARAMS_FOR_METHOD(params, "CCLevelUpBridge::worldSetCompleted");
        params->setObject(world->getId(), "worldId");
        params->setObject(__Bool::create(completed), "completed");
        params->setObject(__Bool::create(notify), "notify");

        CCError *error = NULL;
        CCNdkBridge::callNative (params, &error);

        if (error) {
            CCSoomlaUtils::logError(TAG, __String::createWithFormat(
                    "call worldSetCompleted failed with error: %s", error->getInfo())->getCString());
        }
    }

    bool CCLevelUpBridge::worldIsCompleted(CCWorld *world) {
        CCSoomlaUtils::logDebug(TAG,
                __String::createWithFormat("call worldIsCompleted with world: %s", world->getId()->getCString())->getCString());

        SL_CREATE_PARAMS_FOR_METHOD(params, "CCLevelUpBridge::worldIsCompleted");
        params->setObject(world->getId(), "worldId");

        CCError *error = NULL;
        __Dictionary *retParams = (__Dictionary *) CCNdkBridge::callNative (params, &error);

        if (error) {
            CCSoomlaUtils::logError(TAG, __String::createWithFormat(
                    "call worldIsCompleted failed with error: %s", error->getInfo())->getCString());
            return false;
        }

        SL_EXTRACT_FROM_RETURN(__Bool, ret, retParams);

        return ret->getValue();
    }

    void CCLevelUpBridge::worldSetReward(CCWorld *world, cocos2d::__String *rewardId) {
        CCSoomlaUtils::logDebug(TAG,
                __String::createWithFormat("call worldSetReward with world: %s", world->getId()->getCString())->getCString());

        SL_CREATE_PARAMS_FOR_METHOD(params, "CCLevelUpBridge::worldSetReward");
        params->setObject(world->getId(), "worldId");
        params->setObject(rewardId, "rewardId");

        CCError *error = NULL;
        CCNdkBridge::callNative (params, &error);

        if (error) {
            CCSoomlaUtils::logError(TAG, __String::createWithFormat(
                    "call worldSetReward failed with error: %s", error->getInfo())->getCString());
        }
    }

    cocos2d::__String *CCLevelUpBridge::worldGetAssignedReward(CCWorld *world) {
        CCSoomlaUtils::logDebug(TAG,
                __String::createWithFormat("call worldGetAssignedReward with world: %s", world->getId()->getCString())->getCString());

        SL_CREATE_PARAMS_FOR_METHOD(params, "CCLevelUpBridge::worldGetAssignedReward");
        params->setObject(world->getId(), "worldId");

        CCError *error = NULL;
        __Dictionary *retParams = (__Dictionary *) CCNdkBridge::callNative (params, &error);

        if (error) {
            CCSoomlaUtils::logError(TAG, __String::createWithFormat(
                    "call worldGetAssignedReward failed with error: %s", error->getInfo())->getCString());
            return NULL;
        }

        if ((retParams == NULL) || (retParams->count() == 0)) {
            return NULL;
        }

        SL_EXTRACT_FROM_RETURN(__String, ret, retParams);
        return ret;
    }
    
    void CCLevelUpBridge::worldSetLastCompletedInnerWorld(CCWorld *world, cocos2d::__String *innerWorldId) {
        CCSoomlaUtils::logDebug(TAG,
                                __String::createWithFormat("call worldSetLastCompletedInnerWorld with world: %s", world->getId()->getCString())->getCString());
        
        SL_CREATE_PARAMS_FOR_METHOD(params, "CCLevelUpBridge::worldSetLastCompletedInnerWorld");
        params->setObject(world->getId(), "worldId");
        params->setObject(innerWorldId, "innerWorldId");
        
        CCError *error = NULL;
        CCNdkBridge::callNative (params, &error);
        
        if (error) {
            CCSoomlaUtils::logError(TAG, __String::createWithFormat(
                                                                    "call worldSetLastCompletedInnerWorld failed with error: %s", error->getInfo())->getCString());
        }
    }
    
    cocos2d::__String *CCLevelUpBridge::worldGetLastCompletedInnerWorld(CCWorld *world) {
        CCSoomlaUtils::logDebug(TAG,
                                __String::createWithFormat("call worldGetLastCompletedInnerWorld with world: %s", world->getId()->getCString())->getCString());
        
        SL_CREATE_PARAMS_FOR_METHOD(params, "CCLevelUpBridge::worldGetLastCompletedInnerWorld");
        params->setObject(world->getId(), "worldId");
        
        CCError *error = NULL;
        __Dictionary *retParams = (__Dictionary *) CCNdkBridge::callNative (params, &error);
        
        if (error) {
            CCSoomlaUtils::logError(TAG, __String::createWithFormat(
                                                                    "call worldGetLastCompletedInnerWorld failed with error: %s", error->getInfo())->getCString());
            return NULL;
        }
        
        if ((retParams == NULL) || (retParams->count() == 0)) {
            return NULL;
        }
        
        SL_EXTRACT_FROM_RETURN(__String, ret, retParams);
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
