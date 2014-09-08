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

        static CCBalanceMission *create(cocos2d::CCString *id, cocos2d::CCString *name,
                cocos2d::CCString *associatedItemId, cocos2d::CCInteger *desiredBalance);

        static CCBalanceMission *create(cocos2d::CCString *id, cocos2d::CCString *name,
                cocos2d::CCArray *rewards, cocos2d::CCString *associatedItemId, cocos2d::CCInteger *desiredBalance);

        SL_CREATE_WITH_DICTIONARY(CCBalanceMission);

        virtual const char *getType() const;
    };
}

#endif //__CCBalanceMission_H_
