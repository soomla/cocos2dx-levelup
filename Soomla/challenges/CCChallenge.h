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
        CC_SYNTHESIZE_RETAIN(cocos2d::__Array *, mMissions, Missions);
    public:
        CCChallenge(): CCMission(), mMissions(NULL) {
        }

        static CCChallenge *create(cocos2d::__String *id, cocos2d::__String *name,
                cocos2d::__Array *missions = NULL, cocos2d::__Array *rewards = NULL);

        SL_CREATE_WITH_DICTIONARY(CCChallenge);

        bool init(cocos2d::__String *id, cocos2d::__String *name,
                cocos2d::__Array *missions = NULL, cocos2d::__Array *rewards = NULL);
        virtual bool initWithDictionary(cocos2d::__Dictionary* dict);

        virtual ~CCChallenge();

        virtual cocos2d::__Dictionary* toDictionary();

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
