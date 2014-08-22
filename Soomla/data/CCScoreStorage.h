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

    class CCScoreStorage: cocos2d::Ref {
    public:
        static CCScoreStorage *getInstance();

        double getRecordScore(CCScore *score);
        double getLatestScore(CCScore *score);
        void setRecordScore(CCScore *score, double newValue);
        void setLatestScore(CCScore *score, double newValue);
    };
}

#endif //__CCGateStorage_H_
