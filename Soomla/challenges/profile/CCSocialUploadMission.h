//
// Created by Shubin Fedor on 08/09/14.
// Copyright (c) 2014 SOOMLA. All rights reserved.
//


#ifndef __SocialUploadMission_H_
#define __SocialUploadMission_H_

#include "CCMission.h"
#include "CCUserProfileUtils.h"

namespace soomla {
    class CCSocialUploadMission: public CCMission {
    public:
        CCSocialUploadMission(): CCMission() {
        }

        static CCSocialUploadMission *create(cocos2d::__String *id, cocos2d::__String *name,
                CCProvider provider, cocos2d::__String *fileName, cocos2d::__String *message);

        static CCSocialUploadMission *create(cocos2d::__String *id, cocos2d::__String *name,
                cocos2d::__Array *rewards,
                CCProvider provider, cocos2d::__String *fileName, cocos2d::__String *message);

        SL_CREATE_WITH_DICTIONARY(CCSocialUploadMission);

        const char *getType() const;

    };
}

#endif //__SocialUploadMission_H_
