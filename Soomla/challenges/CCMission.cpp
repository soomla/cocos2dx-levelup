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

    CCMission *CCMission::create(cocos2d::__String *id, cocos2d::__String *name, __Array *rewards, cocos2d::__Dictionary *gateInitParams) {
        CCMission *ret = new CCMission();
        if (ret->init(id, name, rewards, gateInitParams)) {
            ret->autorelease();
        }
        else {
            CC_SAFE_DELETE(ret);
        }

        return ret;
    }

    bool CCMission::init(cocos2d::__String *id, cocos2d::__String *name, __Array *rewards, cocos2d::__Dictionary *gateInitParams) {
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

    bool CCMission::initWithDictionary(cocos2d::__Dictionary *dict) {
        bool result = CCSoomlaEntity::initWithDictionary(dict);

        if (result) {
            Ref *ref;

            // rewards
            ref = dict->objectForKey(CCCoreConsts::JSON_REWARDS);
            if (ref) {
                __Array *rewardsDict = dynamic_cast<__Array *>(ref);
                setRewards(CCDomainHelper::getInstance()->getDomainsFromDictArray(rewardsDict));
            }

            // gate
            ref = dict->objectForKey(CCLevelUpConsts::JSON_LU_GATE);
            __Dictionary *gateDict = dynamic_cast<__Dictionary *>(ref);
            if (gateDict != NULL) {
                ref = CCDomainFactory::getInstance()->createWithDictionary(dynamic_cast<__Dictionary *>(ref));
                CC_ASSERT(dynamic_cast<CCGate *>(ref));
                setGate(dynamic_cast<CCGate *>(ref));
            }

            // schedule
            ref = dict->objectForKey(CCCoreConsts::JSON_SCHEDULE);
            CC_ASSERT(dynamic_cast<__Dictionary *>(ref));
            setSchedule(CCSchedule::createWithDictionary(dynamic_cast<__Dictionary *>(ref)));

            registerEvents();

            return true;
        }

        return result;
    }


    cocos2d::__Dictionary *CCMission::toDictionary() {
        __Dictionary *dict = CCSoomlaEntity::toDictionary();

        if (mRewards) {
            dict->setObject(CCDomainHelper::getInstance()->getDictArrayFromDomains(mRewards), CCCoreConsts::JSON_REWARDS);
        }

        if (mGate) {
            dict->setObject(mGate->toDictionary(), CCLevelUpConsts::JSON_LU_GATE);
        }

        if (mSchedule) {
            dict->setObject(mSchedule->toDictionary(), CCCoreConsts::JSON_SCHEDULE);
        }

        return dict;
    }
    
    CCGate *CCMission::getGate() const {
        return mGate;
    }
    
    void CCMission::setGate(CCGate *gate) {
        if (mGate != gate)
        {
            if (mGate != NULL) {
                mGate->onDetached();
            }
            
            CC_SAFE_RETAIN(gate);
            CC_SAFE_RELEASE(mGate);
            mGate = gate;
            
            if (mGate != NULL) {
                mGate->onAttached();
            }
        }
    }

    const char *CCMission::getType() const {
        return CCLevelUpConsts::JSON_JSON_TYPE_MISSION;
    }


    CCMission::~CCMission() {
        CC_SAFE_RELEASE(mRewards);
        CC_SAFE_RELEASE(mGate);
        CC_SAFE_RELEASE(mSchedule);
        CC_SAFE_RELEASE(mEventListener);
    }


    void CCMission::registerEvents() {
        if (!isCompleted() && this->mGate != NULL) {
            setEventListener(Director::getInstance()->getEventDispatcher()->addCustomEventListener(CCLevelUpConsts::EVENT_GATE_OPENED,
                                                                                                  CC_CALLBACK_1(CCMission::onGateOpened, this)));
        }
    }

    void CCMission::unregisterEvents() {
        if (mEventListener) {
            Director::getInstance()->getEventDispatcher()->removeEventListener(mEventListener);
            setEventListener(NULL);
        }
    }

    __String *CCMission::autoGateId() {
        return __String::createWithFormat("gate_%s", getId()->getCString());
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
        CCSoomlaUtils::logDebug(TAG, __String::createWithFormat(
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
            Ref *ref;
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
            Ref *ref;
            CCReward *reward;
            CCARRAY_FOREACH(mRewards, ref) {
                    reward = dynamic_cast<CCReward *>(ref);
                    CC_ASSERT(reward);
                    reward->give();
                }
        }
    }
    
    void CCMission::onGateOpened(cocos2d::EventCustom *event) {
        __Dictionary *eventData = (__Dictionary *)event->getUserData();
        CCGate *gate = dynamic_cast<CCGate *>(eventData->objectForKey(CCLevelUpConsts::DICT_ELEMENT_GATE));
        CC_ASSERT(gate);
        
        if (mGate == gate) {
            mGate->forceOpen(false);
            setCompletedInner(true);
        }
    }
}
