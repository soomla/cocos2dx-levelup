//
// Created by Shubin Fedor on 08/09/14.
// Copyright (c) 2014 SOOMLA. All rights reserved.
//


#ifndef __CCSocialLikeMission_H_
#define __CCSocialLikeMission_H_

#include "CCMission.h"
#include "CCUserProfileUtils.h"

namespace soomla {
    class CCSocialLikeMission: public CCMission {
    public:
        CCSocialLikeMission(): CCMission() {
        }

        static CCSocialLikeMission *create(cocos2d::CCString *id, cocos2d::CCString *name,
                CCProvider provider, cocos2d::CCString *pageName);

        static CCSocialLikeMission *create(cocos2d::CCString *id, cocos2d::CCString *name,
                cocos2d::CCArray *rewards, CCProvider provider, cocos2d::CCString *pageName);

        SL_CREATE_WITH_DICTIONARY(CCSocialLikeMission);

        virtual const char *getType() const;
    };
}

#endif //__CCSocialLikeMission_H_
