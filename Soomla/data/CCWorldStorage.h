//
// Created by Shubin Fedor on 19/08/14.
// Copyright (c) 2014 SOOMLA. All rights reserved.
//


#ifndef __CCWorldStorage_H_
#define __CCWorldStorage_H_

#include "cocos2d.h"
#include "CCMission.h"
#include "CCWorld.h"

namespace soomla {
    class CCWorld;
    class CCWorldStorage: cocos2d::Ref {
    public:
        static CCWorldStorage *getInstance();

        bool isCompleted(CCWorld *world);
        void setCompleted(CCWorld *world, bool completed);

        void setReward(CCWorld *world, cocos2d::__String *rewardId);
        cocos2d::__String *getAssignedReward(CCWorld *world);
    };
}

#endif //__CCWorldStorage_H_
