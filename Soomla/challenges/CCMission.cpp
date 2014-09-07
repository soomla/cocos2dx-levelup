//
// Created by Shubin Fedor on 19/08/14.
// Copyright (c) 2014 SOOMLA. All rights reserved.
//

#include "CCMission.h"
#include "CCLevelUpConsts.h"
#include "CCReward.h"
#include "CCDomainHelper.h"
#include "CCLevelUpEventDispatcher.h"
#include "CCMissionStorage.h"
#include "CCSoomlaUtils.h"
#include "CCDomainFactory.h"

USING_NS_CC;

namespace soomla {

#define TAG "SOOMLA Mission"

    CCMission *CCMission::create(cocos2d::CCString *id, cocos2d::CCString *name, CCArray *rewards, cocos2d::CCDictionary *gateInitParams) {
        CCMission *ret = new CCMission();
        if (ret->init(id, name, rewards, gateInitParams)) {
            ret->autorelease();
        }
        else {
            CC_SAFE_DELETE(ret);
        }

        return ret;
    }

    bool CCMission::init(cocos2d::CCString *id, cocos2d::CCString *name, CCArray *rewards, cocos2d::CCDictionary *gateInitParams) {
        bool result = CCSoomlaEntity::init(id, name, NULL);

        if (result) {
            setRewards(rewards);

            if (gateInitParams) {
                if (!gateInitParams->objectForKey(CCCoreConsts::JSON_ITEM_ITEM_ID)) {
                    gateInitParams->setObject(autoGateId(), CCCoreConsts::JSON_ITEM_ITEM_ID);
                }
                CCDomain *domain = CCDomainFactory::getInstance()->createWithDictionary(gateInitParams);

                CCGate *gate = dynamic_cast<CCGate *>(domain);
                CC_ASSERT(gate);
                setGate(gate);
            } else {
                setGate(NULL);
            }

            setSchedule(CCSchedule::createAnyTimeOnce());

            registerEvents();

            return true;
        }

        return result;
    }

    bool CCMission::initWithDictionary(cocos2d::CCDictionary *dict) {
        bool result = CCSoomlaEntity::initWithDictionary(dict);

        if (result) {
            CCObject *ref;

            // rewards
            ref = dict->objectForKey(CCLevelUpConsts::JSON_REWARDS);
            if (ref) {
                CCArray *rewardsDict = dynamic_cast<CCArray *>(ref);
                setRewards(CCDomainHelper::getInstance()->getDomainsFromDictArray(rewardsDict));
            }

            // gate
            ref = dict->objectForKey(CCLevelUpConsts::JSON_LU_GATE);
            CC_ASSERT(dynamic_cast<CCDictionary *>(ref));
            ref = CCDomainFactory::getInstance()->createWithDictionary(dynamic_cast<CCDictionary *>(ref));
            CC_ASSERT(dynamic_cast<CCGate *>(ref));
            setGate(dynamic_cast<CCGate *>(ref));

            // schedule
            ref = dict->objectForKey(CCLevelUpConsts::JSON_SCHEDULE);
            CC_ASSERT(dynamic_cast<CCDictionary *>(ref));
            setSchedule(CCSchedule::createWithDictionary(dynamic_cast<CCDictionary *>(ref)));

            registerEvents();

            return true;
        }

        return result;
    }


    cocos2d::CCDictionary *CCMission::toDictionary() {
        CCDictionary *dict = CCSoomlaEntity::toDictionary();

        if (mRewards) {
            dict->setObject(CCDomainHelper::getInstance()->getDictArrayFromDomains(mRewards), CCLevelUpConsts::JSON_REWARDS);
        }

        if (mGate) {
            dict->setObject(mGate->toDictionary(), CCLevelUpConsts::JSON_LU_GATE);
        }

        if (mSchedule) {
            dict->setObject(mSchedule->toDictionary(), CCLevelUpConsts::JSON_SCHEDULE);
        }

        return dict;
    }

    const char *CCMission::getType() const {
        return CCLevelUpConsts::JSON_JSON_TYPE_MISSION;
    }


    CCMission::~CCMission() {
        CC_SAFE_RELEASE(mRewards);
        CC_SAFE_RELEASE(mGate);
        CC_SAFE_RELEASE(mSchedule);
        CC_SAFE_RELEASE(mEventHandler);
    }


    void CCMission::registerEvents() {
        if (!isCompleted() && this->mGate != NULL) {
            setEventHandler(CCMissionEventHandler::create(this));
            CCLevelUpEventDispatcher::getInstance()->addEventHandler(mEventHandler);
        }
    }

    void CCMission::unregisterEvents() {
        if (mEventHandler) {
            CCLevelUpEventDispatcher::getInstance()->removeEventHandler(mEventHandler);
            setEventHandler(NULL);
        }
    }

    CCString *CCMission::autoGateId() {
        return CCString::createWithFormat("gate_%s", getId()->getCString());
    }

    bool CCMission::isAvailable() {
        return mGate->canOpen() && mSchedule->approve(CCMissionStorage::getInstance()->getTimesCompleted(this));
    }

    bool CCMission::isCompleted() {
        // check if completed in Mission Storage
        // this checks if the mission was ever completed... no matter how many times.
        return CCMissionStorage::getInstance()->isCompleted(this);
    }

    bool CCMission::complete() {
        if (!mSchedule->approve(CCMissionStorage::getInstance()->getTimesCompleted(this))) {
            CCSoomlaUtils::logDebug(TAG, "missions cannot be completed b/c Schedule doesn't approve.");
            return false;
        }
        CCSoomlaUtils::logDebug(TAG, CCString::createWithFormat(
                "trying opening gate to complete mission: %s", getId()->getCString())->getCString());
        return mGate->open();
    }

    // this function ignores Schedule, it's not supposed to be used in standard scenarios.
    void CCMission::forceComplete() {
        mGate->forceOpen(true);
    }

    // NOTE: We are allowing missions to be completed multiple times.
    void CCMission::setCompletedInner(bool completed) {
        // set completed in Mission Storage
        CCMissionStorage::getInstance()->setCompleted(this, completed);

        if (completed) {
            giveRewards();
        } else {
            takeRewards();
        }
    }

    void CCMission::takeRewards() {
        if (mRewards) {
            CCObject *ref;
            CCReward *reward;
            CCARRAY_FOREACH(mRewards, ref) {
                    reward = dynamic_cast<CCReward *>(ref);
                    CC_ASSERT(reward);
                    reward->take();
                }
        }
    }

    void CCMission::giveRewards() {
        if (mRewards) {
            CCObject *ref;
            CCReward *reward;
            CCARRAY_FOREACH(mRewards, ref) {
                    reward = dynamic_cast<CCReward *>(ref);
                    CC_ASSERT(reward);
                    reward->give();
                }
        }
    }

    CCMissionEventHandler *soomla::CCMissionEventHandler::create(soomla::CCMission *mission) {
        CCMissionEventHandler *ret = new CCMissionEventHandler();
        ret->autorelease();
        ret->mMission = mission;
        return ret;
    }

    void CCMissionEventHandler::onGateOpened(CCGate *gate) {
        if (mMission->mGate == gate) {
            mMission->mGate->forceOpen(false);
            mMission->setCompletedInner(true);
        }
    }

}
