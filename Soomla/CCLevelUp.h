//
// Created by Shubin Fedor on 25/08/14.
// Copyright (c) 2014 SOOMLA. All rights reserved.
//

#ifndef __CCLevelUp_H_
#define __CCLevelUp_H_

#include "cocos2d.h"
#include "CCGate.h"
#include "CCMission.h"

namespace soomla {

    class CCWorld;
    class CCReward;
    class CCScore;
    class CCGate;
    class CCMission;
    class CCLevel;

    class CCLevelUp: public cocos2d::CCObject {
    private:
        CCWorld *mInitialWorld;
        cocos2d::CCDictionary *mRewards;

        CCLevelUp(): mInitialWorld(NULL), mRewards(NULL) {
        }

    public:
        static CCLevelUp *getInstance();

        virtual cocos2d::CCDictionary *toDictionary();

        virtual ~CCLevelUp();

        void initialize(CCWorld *initialWorld, cocos2d::CCArray *rewards = NULL);

        CCReward *getReward(char const *rewardId);

        CCScore *getScore(char const *scoreId);

        CCWorld *getWorld(char const *worldId);
        
        CCLevel *getLevel(char const *levelId);

        CCGate *getGate(char const *gateId);

        CCMission *getMission(char const *missionId);

        int getLevelCount();

        int getLevelCountInWorld(CCWorld *world);

        int getWorldCount(bool withLevels);

        int getCompletedLevelCount();

        int getCompletedWorldCount();

    private:
        CCWorld *fetchWorld(char const *worldId, cocos2d::CCDictionary *worlds);

        CCScore *fetchScoreFromWorlds(char const *scoreId, cocos2d::CCDictionary *worlds);

        CCGate *fetchGate(char const *gateId, cocos2d::CCDictionary *worlds);

        CCGate *fetchGateFromMissions(char const *gateId, cocos2d::CCArray *missions);

        int getRecursiveCount(CCWorld *world, bool (*isAccepted)(CCWorld *));

        CCMission *fetchMission(char const *missionId, cocos2d::CCDictionary *worlds);
    };

}


#endif //__CCLevelUp_H_
