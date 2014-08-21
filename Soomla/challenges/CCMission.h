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

    #define TAG "SOOMLA Mission"

    class CCMission: public CCSoomlaEntity {
        friend class CCMissionEventHandler;
        friend class CCChallengeEventHandler;
        CC_SYNTHESIZE_RETAIN(cocos2d::__Array *, mRewards, Rewards)
        CC_SYNTHESIZE_RETAIN(CCSchedule *, mSchedule, Schedule)
        CC_SYNTHESIZE_RETAIN(CCGate *, mGate, Gate);

        CC_SYNTHESIZE_RETAIN(CCLevelUpEventHandler *, mEventHandler, EventHandler);
    public:
        CCMission(): CCSoomlaEntity(), mRewards(NULL), mSchedule(NULL), mGate(NULL), mEventHandler(NULL) {
        }

        static CCMission *create(cocos2d::__String *id, cocos2d::__String *name,
                cocos2d::__Array *rewards = NULL, cocos2d::__Dictionary *gateInitParams = NULL);

        SL_CREATE_WITH_DICTIONARY(CCMission);

        bool init(cocos2d::__String *id, cocos2d::__String *name,
                cocos2d::__Array *rewards = NULL, cocos2d::__Dictionary *gateInitParams = NULL);
        virtual bool initWithDictionary(cocos2d::__Dictionary* dict);

        virtual ~CCMission();

        virtual cocos2d::__Dictionary* toDictionary();

        virtual const char *getType() const;

        cocos2d::__String *autoGateId();
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
