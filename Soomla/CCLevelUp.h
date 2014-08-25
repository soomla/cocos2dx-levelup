//
// Created by Shubin Fedor on 25/08/14.
// Copyright (c) 2014 SOOMLA. All rights reserved.
//

#ifndef __CCLevelUp_H_
#define __CCLevelUp_H_

#include "cocos2d.h"
#include "CCWorld.h"

namespace soomla {

    class CCLevelUp: public cocos2d::Ref {
    private:
        CCWorld *mInitialWorld;
        cocos2d::__Dictionary *mRewards;

        CCLevelUp(): mInitialWorld(NULL), mRewards(NULL) {
        }

    public:
        static CCLevelUp *getInstance();

        virtual cocos2d::__Dictionary *toDictionary();

        virtual ~CCLevelUp();

        void initialize(CCWorld *initialWorld, cocos2d::__Array *rewards);

        CCReward *getReward(char const *rewardId);

        CCScore *getScore(char const *scoreId);

        CCWorld *getWorld(char const *worldId);

        int getLevelCount();

        int getLevelCountInWorld(CCWorld *world);

        int getWorldCount(bool withLevels);

        int getCompletedLevelCount();

        int getCompletedWorldCount();

    private:
        CCWorld *fetchWorld(char const *worldId, cocos2d::__Dictionary *worlds);

        CCScore *fetchScoreFromWorlds(char const *scoreId, cocos2d::__Dictionary *worlds);

        int getRecursiveCount(CCWorld *world, bool (*isAccepted)(CCWorld *));

    };

}


#endif //__CCLevelUp_H_
