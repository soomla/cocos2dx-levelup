//
// Created by Shubin Fedor on 08/09/14.
// Copyright (c) 2014 SOOMLA. All rights reserved.
//


#ifndef __SocialStatusMission_H_
#define __SocialStatusMission_H_

#include "CCMission.h"
#include "CCUserProfileUtils.h"

namespace soomla {
    class CCSocialStatusMission: public CCMission {
    public:
        CCSocialStatusMission(): CCMission() {
        }

        static CCSocialStatusMission *create(cocos2d::__String *id, cocos2d::__String *name,
                CCProvider provider, cocos2d::__String *status);

        static CCSocialStatusMission *create(cocos2d::__String *id, cocos2d::__String *name,
                cocos2d::__Array *rewards, CCProvider provider, cocos2d::__String *status);

        SL_CREATE_WITH_DICTIONARY(CCSocialStatusMission)
        const char *getType() const;
    };
}

#endif //__SocialStatusMission_H_
