//
// Created by Shubin Fedor on 19/08/14.
// Copyright (c) 2014 SOOMLA. All rights reserved.
//


#ifndef __CCLevelStorage_H_
#define __CCLevelStorage_H_

#include "cocos2d.h"
#include "CCMission.h"
#include "CCWorld.h"

namespace soomla {
    class CCLevel;
    class CCLevelStorage: cocos2d::Ref {
    public:
        static CCLevelStorage *getInstance();

        int getTimesStarted(CCLevel *level);
        int getTimesPlayed(CCLevel *level);
        int getSlowestDurationMillis(CCLevel *level);
        int getFastestDurationMillis(CCLevel *level);
        void incTimesStarted(CCLevel *level);
        void setSlowestDurationMillis(CCLevel *level, long duration);
        void setFastestDurationMillis(CCLevel *level, long duration);

        void incTimesPlayed(CCLevel *level);
    };
}

#endif //__CCLevelStorage_H_
