//
// Created by Shubin Fedor on 19/08/14.
// Copyright (c) 2014 SOOMLA. All rights reserved.
//

#ifndef __CCBalanceMission_H_
#define __CCBalanceMission_H_

#include "CCMission.h"

namespace soomla {
    class CCBalanceMission: public CCMission {
    public:
        CCBalanceMission(): CCMission() {
        }

        static CCBalanceMission *create(cocos2d::__String *id, cocos2d::__String *name,
                cocos2d::__String *associatedItemId, cocos2d::__Integer *desiredBalance);

        static CCBalanceMission *create(cocos2d::__String *id, cocos2d::__String *name,
                cocos2d::__Array *rewards, cocos2d::__String *associatedItemId, cocos2d::__Integer *desiredBalance);

        SL_CREATE_WITH_DICTIONARY(CCBalanceMission);

        virtual const char *getType() const;
    };
}

#endif //__CCBalanceMission_H_
