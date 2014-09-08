//
// Created by Fedor Shubin on 6/19/14.
//

#include "CCLevelUpService.h"
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
#include "CCLevelUp.h"
#include "CCDomainHelper.h"
#include "CCRangeScore.h"
#include "CCVirtualItemScore.h"

USING_NS_CC;


namespace soomla {

#define TAG "SOOMLA CCLevelUpService"

    static CCLevelUpService *sInstance = nullptr;

    CCLevelUpService *CCLevelUpService::getInstance() {
        if (!sInstance)
        {
            sInstance = new CCLevelUpService();
            sInstance->retain();
        }
        return sInstance;
    }

    void CCLevelUpService::initShared() {
        CCLevelUpService *levelUpService = CCLevelUpService::getInstance();
        if (!levelUpService->init()) {
            exit(1);
        }
    }

    CCLevelUpService::CCLevelUpService() {
    }

    bool CCLevelUpService::init() {

        CCLevelUpEventDispatcher::getInstance();    // to get sure it's inited

        CCDomainFactory *domainFactory = CCDomainFactory::getInstance();

        domainFactory->registerCreator(CCLevelUpConsts::JSON_JSON_TYPE_MISSION, CCMission::createWithDictionary);
        domainFactory->registerCreator(CCLevelUpConsts::JSON_JSON_TYPE_BALANCE_MISSION, CCBalanceMission::createWithDictionary);
        domainFactory->registerCreator(CCLevelUpConsts::JSON_JSON_TYPE_CHALLENGE, CCChallenge::createWithDictionary);
        domainFactory->registerCreator(CCLevelUpConsts::JSON_JSON_TYPE_PURCHASE_MISSION, CCPurchasingMission::createWithDictionary);
        domainFactory->registerCreator(CCLevelUpConsts::JSON_JSON_TYPE_RECORD_MISSION, CCRecordMission::createWithDictionary);
        domainFactory->registerCreator(CCLevelUpConsts::JSON_JSON_TYPE_WORLD_COMPLETION_MISSION, CCWorldCompletionMission::createWithDictionary);
        domainFactory->registerCreator(CCLevelUpConsts::JSON_JSON_TYPE_BALANCE_GATE, CCBalanceGate::createWithDictionary);
        domainFactory->registerCreator(CCLevelUpConsts::JSON_JSON_TYPE_GATES_LIST_AND, CCGatesListAnd::createWithDictionary);
        domainFactory->registerCreator(CCLevelUpConsts::JSON_JSON_TYPE_GATES_LIST_OR, CCGatesListOr::createWithDictionary);
        domainFactory->registerCreator(CCLevelUpConsts::JSON_JSON_TYPE_PURCHASABLE_GATE, CCPurchasableGate::createWithDictionary);
        domainFactory->registerCreator(CCLevelUpConsts::JSON_JSON_TYPE_RECORD_GATE, CCRecordGate::createWithDictionary);
        domainFactory->registerCreator(CCLevelUpConsts::JSON_JSON_TYPE_SCHEDULE_GATE, CCScheduleGate::createWithDictionary);
        domainFactory->registerCreator(CCLevelUpConsts::JSON_JSON_TYPE_WORLD_COMPLETION_GATE, CCWorldCompletionGate::createWithDictionary);
        domainFactory->registerCreator(CCLevelUpConsts::JSON_JSON_TYPE_SCORE, CCScore::createWithDictionary);
        domainFactory->registerCreator(CCLevelUpConsts::JSON_JSON_TYPE_RANGE_SCORE, CCRangeScore::createWithDictionary);
        domainFactory->registerCreator(CCLevelUpConsts::JSON_JSON_TYPE_VIRTUAL_ITEM_SCORE, CCVirtualItemScore::createWithDictionary);
        domainFactory->registerCreator(CCLevelUpConsts::JSON_JSON_TYPE_WORLD, CCWorld::createWithDictionary);
        domainFactory->registerCreator(CCLevelUpConsts::JSON_JSON_TYPE_LEVEL, CCLevel::createWithDictionary);

        return true;
    }

    bool CCLevelUpService::initLevelUp(CCWorld *initialWorld, __Array *rewards) {

        CCSoomlaUtils::logDebug(TAG, "call init");

        __Dictionary *metadata = __Dictionary::create();
        metadata->setObject(initialWorld->toDictionary(), "initialWorld");
        if (rewards) {
            metadata->setObject(CCDomainHelper::getInstance()->getDictArrayFromDomains(rewards), "rewards");
        }

        SL_CREATE_PARAMS_FOR_METHOD(params, "CCLevelUpService::initLevelUp");
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

    bool CCLevelUpService::gateIsOpen(CCGate *gate) {
        CCSoomlaUtils::logDebug(TAG,
                __String::createWithFormat("call gateIsOpen with gate: %s", gate->getId()->getCString())->getCString());

        SL_CREATE_PARAMS_FOR_METHOD(params, "CCLevelUpService::gateIsOpen");
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

    void CCLevelUpService::gateSetOpen(CCGate *gate, bool open, bool notify) {
        CCSoomlaUtils::logDebug(TAG,
                __String::createWithFormat("call gateSetOpen with gate: %s", gate->getId()->getCString())->getCString());

        SL_CREATE_PARAMS_FOR_METHOD(params, "CCLevelUpService::gateSetOpen");
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


    void CCLevelUpService::levelSetSlowestDurationMillis(CCLevel *level, long duration) {
        CCSoomlaUtils::logDebug(TAG,
                __String::createWithFormat("call levelSetSlowestDurationMillis with level: %s", level->getId()->getCString())->getCString());

        SL_CREATE_PARAMS_FOR_METHOD(params, "CCLevelUpService::levelSetSlowestDurationMillis");
        params->setObject(level->getId(), "levelId");
        params->setObject(__Integer::create(duration), "duration");

        CCError *error = NULL;
        CCNdkBridge::callNative (params, &error);

        if (error) {
            CCSoomlaUtils::logError(TAG, __String::createWithFormat(
                    "call levelSetSlowestDurationMillis failed with error: %s", error->getInfo())->getCString());
        }
    }

    long CCLevelUpService::levelGetSlowestDurationMillis(CCLevel *level) {
        CCSoomlaUtils::logDebug(TAG,
                __String::createWithFormat("call levelGetSlowestDurationMillis with level: %s", level->getId()->getCString())->getCString());

        SL_CREATE_PARAMS_FOR_METHOD(params, "CCLevelUpService::levelGetSlowestDurationMillis");
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


    void CCLevelUpService::levelSetFastestDurationMillis(CCLevel *level, long duration) {
        CCSoomlaUtils::logDebug(TAG,
                __String::createWithFormat("call levelSetFastestDurationMillis with level: %s", level->getId()->getCString())->getCString());

        SL_CREATE_PARAMS_FOR_METHOD(params, "CCLevelUpService::levelSetFastestDurationMillis");
        params->setObject(level->getId(), "gateId");
        params->setObject(__Integer::create(duration), "duration");

        CCError *error = NULL;
        CCNdkBridge::callNative (params, &error);

        if (error) {
            CCSoomlaUtils::logError(TAG, __String::createWithFormat(
                    "call levelSetFastestDurationMillis failed with error: %s", error->getInfo())->getCString());
        }
    }

    long CCLevelUpService::levelGetFastestDurationMillis(CCLevel *level) {
        CCSoomlaUtils::logDebug(TAG,
                __String::createWithFormat("call levelGetFastestDurationMillis with level: %s", level->getId()->getCString())->getCString());

        SL_CREATE_PARAMS_FOR_METHOD(params, "CCLevelUpService::levelGetFastestDurationMillis");
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


    int CCLevelUpService::levelIncTimesStarted(CCLevel *level) {
        CCSoomlaUtils::logDebug(TAG,
                __String::createWithFormat("call levelIncTimesStarted with level: %s", level->getId()->getCString())->getCString());

        SL_CREATE_PARAMS_FOR_METHOD(params, "CCLevelUpService::levelIncTimesStarted");
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

    int CCLevelUpService::levelDecTimesStarted(CCLevel *level) {
        CCSoomlaUtils::logDebug(TAG,
                __String::createWithFormat("call levelDecTimesStarted with level: %s", level->getId()->getCString())->getCString());

        SL_CREATE_PARAMS_FOR_METHOD(params, "CCLevelUpService::levelDecTimesStarted");
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

    int CCLevelUpService::levelGetTimesStarted(CCLevel *level) {
        CCSoomlaUtils::logDebug(TAG,
                __String::createWithFormat("call levelGetTimesStarted with level: %s", level->getId()->getCString())->getCString());

        SL_CREATE_PARAMS_FOR_METHOD(params, "CCLevelUpService::levelGetTimesStarted");
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


    int CCLevelUpService::levelGetTimesPlayed(CCLevel *level) {
        CCSoomlaUtils::logDebug(TAG,
                __String::createWithFormat("call levelGetTimesPlayed with level: %s", level->getId()->getCString())->getCString());

        SL_CREATE_PARAMS_FOR_METHOD(params, "CCLevelUpService::levelGetTimesPlayed");
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

    int CCLevelUpService::levelIncTimesPlayed(CCLevel *level) {
        CCSoomlaUtils::logDebug(TAG,
                __String::createWithFormat("call levelIncTimesPlayed with level: %s", level->getId()->getCString())->getCString());

        SL_CREATE_PARAMS_FOR_METHOD(params, "CCLevelUpService::levelIncTimesPlayed");
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

    int CCLevelUpService::levelDecTimesPlayed(CCLevel *level) {
        CCSoomlaUtils::logDebug(TAG,
                __String::createWithFormat("call levelDecTimesPlayed with level: %s", level->getId()->getCString())->getCString());

        SL_CREATE_PARAMS_FOR_METHOD(params, "CCLevelUpService::levelDecTimesPlayed");
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


    void CCLevelUpService::missionSetCompleted(CCMission *mission, bool completed, bool notify) {
        CCSoomlaUtils::logDebug(TAG,
                __String::createWithFormat("call missionSetCompleted with mission: %s", mission->getId()->getCString())->getCString());

        SL_CREATE_PARAMS_FOR_METHOD(params, "CCLevelUpService::missionSetCompleted");
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

    int CCLevelUpService::missionGetTimesCompleted(CCMission *mission) {
        CCSoomlaUtils::logDebug(TAG,
                __String::createWithFormat("call missionGetTimesCompleted with mission: %s", mission->getId()->getCString())->getCString());

        SL_CREATE_PARAMS_FOR_METHOD(params, "CCLevelUpService::missionGetTimesCompleted");
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

    void CCLevelUpService::scoreSetLatestScore(CCScore *score, double newValue) {
        CCSoomlaUtils::logDebug(TAG,
                __String::createWithFormat("call scoreSetLatestScore with score: %s", score->getId()->getCString())->getCString());

        SL_CREATE_PARAMS_FOR_METHOD(params, "CCLevelUpService::scoreSetLatestScore");
        params->setObject(score->getId(), "scoreId");
        params->setObject(__Double::create(newValue), "newValue");

        CCError *error = NULL;
        CCNdkBridge::callNative (params, &error);

        if (error) {
            CCSoomlaUtils::logError(TAG, __String::createWithFormat(
                    "call scoreSetLatestScore failed with error: %s", error->getInfo())->getCString());
        }
    }

    double CCLevelUpService::scoreGetLatestScore(CCScore *score) {
        CCSoomlaUtils::logDebug(TAG,
                __String::createWithFormat("call scoreGetLatestScore with score: %s", score->getId()->getCString())->getCString());

        SL_CREATE_PARAMS_FOR_METHOD(params, "CCLevelUpService::scoreGetLatestScore");
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

    void CCLevelUpService::scoreSetRecordScore(CCScore *score, double newValue) {
        CCSoomlaUtils::logDebug(TAG,
                __String::createWithFormat("call scoreSetRecordScore with score: %s", score->getId()->getCString())->getCString());

        SL_CREATE_PARAMS_FOR_METHOD(params, "CCLevelUpService::scoreSetRecordScore");
        params->setObject(score->getId(), "scoreId");
        params->setObject(__Double::create(newValue), "newValue");

        CCError *error = NULL;
        CCNdkBridge::callNative (params, &error);

        if (error) {
            CCSoomlaUtils::logError(TAG, __String::createWithFormat(
                    "call scoreSetRecordScore failed with error: %s", error->getInfo())->getCString());
        }
    }

    double CCLevelUpService::scoreGetRecordScore(CCScore *score) {
        CCSoomlaUtils::logDebug(TAG,
                __String::createWithFormat("call scoreGetRecordScore with score: %s", score->getId()->getCString())->getCString());

        SL_CREATE_PARAMS_FOR_METHOD(params, "CCLevelUpService::scoreGetRecordScore");
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

    void CCLevelUpService::worldSetCompleted(CCWorld *world, bool completed, bool notify) {
        CCSoomlaUtils::logDebug(TAG,
                __String::createWithFormat("call worldSetCompleted with world: %s", world->getId()->getCString())->getCString());

        SL_CREATE_PARAMS_FOR_METHOD(params, "CCLevelUpService::worldSetCompleted");
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

    bool CCLevelUpService::worldIsCompleted(CCWorld *world) {
        CCSoomlaUtils::logDebug(TAG,
                __String::createWithFormat("call worldIsCompleted with world: %s", world->getId()->getCString())->getCString());

        SL_CREATE_PARAMS_FOR_METHOD(params, "CCLevelUpService::worldIsCompleted");
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

    void CCLevelUpService::worldSetReward(CCWorld *world, cocos2d::__String *rewardId) {
        CCSoomlaUtils::logDebug(TAG,
                __String::createWithFormat("call worldSetReward with world: %s", world->getId()->getCString())->getCString());

        SL_CREATE_PARAMS_FOR_METHOD(params, "CCLevelUpService::worldSetReward");
        params->setObject(world->getId(), "worldId");
        params->setObject(rewardId, "rewardId");

        CCError *error = NULL;
        CCNdkBridge::callNative (params, &error);

        if (error) {
            CCSoomlaUtils::logError(TAG, __String::createWithFormat(
                    "call worldSetReward failed with error: %s", error->getInfo())->getCString());
        }
    }

    cocos2d::__String *CCLevelUpService::worldGetAssignedReward(CCWorld *world) {
        CCSoomlaUtils::logDebug(TAG,
                __String::createWithFormat("call worldGetAssignedReward with world: %s", world->getId()->getCString())->getCString());

        SL_CREATE_PARAMS_FOR_METHOD(params, "CCLevelUpService::worldGetAssignedReward");
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
}
