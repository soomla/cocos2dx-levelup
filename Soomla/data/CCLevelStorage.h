//
// Created by Shubin Fedor on 19/08/14.
// Copyright (c) 2014 SOOMLA. All rights reserved.
//


#ifndef __CCLevelStorage_H_
#define __CCLevelStorage_H_

#include "cocos2d.h"

namespace soomla {
    class CCLevel;
    class CCLevelStorage: cocos2d::CCObject {
    public:
        static CCLevelStorage *getInstance();

        void setSlowestDurationMillis(CCLevel *level, long duration);
        long getSlowestDurationMillis(CCLevel *level);

        void setFastestDurationMillis(CCLevel *level, long duration);
        long getFastestDurationMillis(CCLevel *level);

        int incTimesStarted(CCLevel *level);
        int decTimesStarted(CCLevel *level);
        int getTimesStarted(CCLevel *level);

        int getTimesPlayed(CCLevel *level);
        int incTimesPlayed(CCLevel *level);
        int decTimesPlayed(CCLevel *level);

    private:

    };
}

#endif //__CCLevelStorage_H_
