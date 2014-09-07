//
// Created by Shubin Fedor on 19/08/14.
// Copyright (c) 2014 SOOMLA. All rights reserved.
//


#ifndef __CCMission_H_
#define __CCMission_H_

#include "CCSoomlaMacros.h"
#include "CCSoomlaEntity.h"
#include "CCSchedule.h"
#include "CCGate.h"
#include "CCSimpleLevelUpEventHandler.h"

namespace soomla {

    class CCMission: public CCSoomlaEntity {
        friend class CCMissionEventHandler;
        friend class CCChallengeEventHandler;
        CC_SYNTHESIZE_RETAIN(cocos2d::CCArray *, mRewards, Rewards)
        CC_SYNTHESIZE_RETAIN(CCSchedule *, mSchedule, Schedule)
        CC_SYNTHESIZE_RETAIN(CCGate *, mGate, Gate);

        CC_SYNTHESIZE_RETAIN(CCLevelUpEventHandler *, mEventHandler, EventHandler);
    public:
        CCMission(): CCSoomlaEntity(), mRewards(NULL), mSchedule(NULL), mGate(NULL), mEventHandler(NULL) {
        }

        static CCMission *create(cocos2d::CCString *id, cocos2d::CCString *name,
                cocos2d::CCArray *rewards = NULL, cocos2d::CCDictionary *gateInitParams = NULL);

        SL_CREATE_WITH_DICTIONARY(CCMission);

        bool init(cocos2d::CCString *id, cocos2d::CCString *name,
                cocos2d::CCArray *rewards = NULL, cocos2d::CCDictionary *gateInitParams = NULL);
        virtual bool initWithDictionary(cocos2d::CCDictionary* dict);

        virtual ~CCMission();

        virtual cocos2d::CCDictionary* toDictionary();

        virtual const char *getType() const;

        cocos2d::CCString *autoGateId();
        virtual bool isAvailable();
        virtual bool isCompleted();
        bool complete();
        void forceComplete();
    protected:
        virtual void registerEvents();
        virtual void unregisterEvents();

        void setCompletedInner(bool completed);

    private:
        void takeRewards();
        void giveRewards();
    };

    class CCMissionEventHandler: public CCSimpleLevelUpEventHandler {
    private:
        CCMission *mMission;
    public:
        CCMissionEventHandler(): mMission(NULL) {

        }
        static CCMissionEventHandler *create(CCMission *mission);

        virtual void onGateOpened(CCGate *gate);
    };
}

#endif //__CCMission_H_
