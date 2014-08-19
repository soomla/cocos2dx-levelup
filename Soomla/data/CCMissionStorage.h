//
// Created by Shubin Fedor on 19/08/14.
// Copyright (c) 2014 SOOMLA. All rights reserved.
//


#ifndef __CCMissionStorage_H_
#define __CCMissionStorage_H_

#include "cocos2d.h"
#include "CCMission.h"

namespace soomla {
    class CCMissionStorage: cocos2d::Ref {
    public:
        static CCMissionStorage *getInstance();

        bool isCompleted(CCMission *mission);
        int getTimesCompleted(CCMission *mission);
        int setCompleted(CCMission *mission, bool completed);
    };
}

#endif //__CCMissionStorage_H_
