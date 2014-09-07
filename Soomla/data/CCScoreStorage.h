//
// Created by Shubin Fedor on 19/08/14.
// Copyright (c) 2014 SOOMLA. All rights reserved.
//


#ifndef __CCScoreStorage_H_
#define __CCScoreStorage_H_

#include "cocos2d.h"
#include "CCMission.h"

namespace soomla {
    class CCScore;

    class CCScoreStorage: cocos2d::CCObject {
    public:
        static CCScoreStorage *getInstance();

        void setLatestScore(CCScore *score, double newValue);
        double getLatestScore(CCScore *score);
        void setRecordScore(CCScore *score, double newValue);
        double getRecordScore(CCScore *score);
    };
}

#endif //__CCGateStorage_H_
