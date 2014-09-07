//
// Created by Shubin Fedor on 19/08/14.
// Copyright (c) 2014 SOOMLA. All rights reserved.
//

#ifndef __CCChallenge_H_
#define __CCChallenge_H_

#include "CCMission.h"

namespace soomla {
    class CCChallenge: public CCMission {
        friend class CCChallengeEventHandler;
        CC_SYNTHESIZE_RETAIN(cocos2d::CCArray *, mMissions, Missions);
    public:
        CCChallenge(): CCMission(), mMissions(NULL) {
        }

        static CCChallenge *create(cocos2d::CCString *id, cocos2d::CCString *name,
                cocos2d::CCArray *missions = NULL, cocos2d::CCArray *rewards = NULL);

        SL_CREATE_WITH_DICTIONARY(CCChallenge);

        bool init(cocos2d::CCString *id, cocos2d::CCString *name,
                cocos2d::CCArray *missions = NULL, cocos2d::CCArray *rewards = NULL);
        virtual bool initWithDictionary(cocos2d::CCDictionary* dict);

        virtual ~CCChallenge();

        virtual cocos2d::CCDictionary* toDictionary();

        virtual const char *getType() const;

        virtual bool isCompleted();

    protected:
        void registerEvents();
        void unregisterEvents();
    };

    class CCChallengeEventHandler: public CCSimpleLevelUpEventHandler {
    private:
        CCChallenge *mChallenge;
    public:
        CCChallengeEventHandler() : mChallenge(NULL) {
        }

        static CCChallengeEventHandler *create(CCChallenge *challenge);

        void onMissionCompleted(CCMission *completedMission);
        void onMissionCompletionRevoked(CCMission *mission);
    };
}

#endif //__CCChallenge_H_
