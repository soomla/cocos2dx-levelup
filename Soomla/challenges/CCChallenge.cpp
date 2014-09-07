//
// Created by Shubin Fedor on 19/08/14.
// Copyright (c) 2014 SOOMLA. All rights reserved.
//

#include "CCChallenge.h"
#include "CCDomainHelper.h"
#include "CCLevelUpConsts.h"
#include "CCSoomlaUtils.h"
#include "CCLevelUpEventDispatcher.h"
#include "CCMissionStorage.h"

namespace soomla {
    
    USING_NS_CC;
    
    #define TAG "SOOMLA Challenge"

    CCChallenge *CCChallenge::create(cocos2d::CCString *id, cocos2d::CCString *name, cocos2d::CCArray *missions, cocos2d::CCArray *rewards) {
        CCChallenge *ret = new CCChallenge();
        if (ret->init(id, name, missions, rewards)) {
            ret->autorelease();
        }
        else {
            CC_SAFE_DELETE(ret);
        }

        return ret;
    }

    bool CCChallenge::init(cocos2d::CCString *id, cocos2d::CCString *name, cocos2d::CCArray *missions, cocos2d::CCArray *rewards) {
        bool result = CCMission::init(id, name, rewards);
        if (result) {
            setMissions(missions);
            return true;
        }
        return result;
    }

    bool CCChallenge::initWithDictionary(cocos2d::CCDictionary *dict) {
        bool result = CCMission::initWithDictionary(dict);
        if (result) {
            CCObject *ref = dict->objectForKey(CCLevelUpConsts::JSON_LU_MISSIONS);
            if (ref) {
                CCArray *missionsDict = dynamic_cast<CCArray *>(ref);
                setMissions(CCDomainHelper::getInstance()->getDomainsFromDictArray(missionsDict));
            }
            return true;
        }
        return result;
    }

    cocos2d::CCDictionary *CCChallenge::toDictionary() {
        CCDictionary *dict = CCMission::toDictionary();

        if (mMissions) {
            dict->setObject(CCDomainHelper::getInstance()->getDictArrayFromDomains(mMissions), CCLevelUpConsts::JSON_LU_MISSIONS);
        }

        return dict;
    }

    const char *CCChallenge::getType() const {
        return CCLevelUpConsts::JSON_JSON_TYPE_CHALLENGE;
    }

    CCChallenge::~CCChallenge() {
        CC_SAFE_RELEASE(mMissions);
    }

    bool CCChallenge::isCompleted() {
        // could happen in construction
        // need to return false in order to register for child events
        if (mMissions == NULL || mMissions->count() == 0) {
            return false;
        }

        CCObject *ref;
        CCMission *mission;
        CCARRAY_FOREACH(mMissions, ref) {
                mission = dynamic_cast<CCMission *>(ref);
                if (!mission->isCompleted()) {
                    return false;
                }
            }

        return true;
    }

    CCChallengeEventHandler *CCChallengeEventHandler::create(CCChallenge *challenge) {
        CCChallengeEventHandler *ret = new CCChallengeEventHandler();
        ret->autorelease();
        ret->mChallenge = challenge;
        return ret;
    }

    void CCChallenge::registerEvents() {
        CCSoomlaUtils::logDebug (TAG, "registerEvents called");
        if (!this->isCompleted()) {
            CCSoomlaUtils::logDebug (TAG, "registering!");
            // register for events
            setEventHandler(CCChallengeEventHandler::create(this));
            CCLevelUpEventDispatcher::getInstance()->addEventHandler(getEventHandler());
        }
    }

    void CCChallenge::unregisterEvents() {
        if (getEventHandler()) {
            CCLevelUpEventDispatcher::getInstance()->removeEventHandler(getEventHandler());
            setEventHandler(NULL);
        }
    }

    void CCChallengeEventHandler::onMissionCompleted(CCMission *completedMission) {
        CCSoomlaUtils::logDebug (TAG, "onMissionCompleted");
        if (mChallenge->mMissions->containsObject(completedMission)) {
            CCSoomlaUtils::logDebug (TAG, CCString::createWithFormat("Mission %s is part of challenge %s (%zi) total",
                    completedMission->getId()->getCString(),
                    mChallenge->getId()->getCString(),
                    mChallenge->mMissions->count())->getCString());
            bool completed = true;
            CCObject *ref;
            CCMission *mission;
            CCARRAY_FOREACH(mChallenge->mMissions, ref) {
                    mission = dynamic_cast<CCMission *>(ref);
                    CC_ASSERT(mission);
                    if (!mission->isCompleted()) {
                        CCSoomlaUtils::logDebug(TAG, CCString::createWithFormat(
                                "challenge mission not completed?=%s",
                                mission->getId()->getCString()
                        )->getCString());
                        completed = false;
                        break;
                    }
                }

            if (completed) {
                CCSoomlaUtils::logDebug(TAG, CCString::createWithFormat(
                        "Challenge %s completed!", mChallenge->getId()->getCString())->getCString());
                mChallenge->setCompletedInner(true);
            }
        }
    }

    void CCChallengeEventHandler::onMissionCompletionRevoked(CCMission *mission) {
        if (mChallenge->mMissions->containsObject(mission)) {
            // if the challenge was completed before, but now one of its child missions
            // was uncompleted - the challenge is revoked as well
            if (CCMissionStorage::getInstance()->isCompleted(mChallenge)) {
                mChallenge->setCompletedInner(false);
            }
        }
    }

}