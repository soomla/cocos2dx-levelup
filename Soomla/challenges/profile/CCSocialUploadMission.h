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

        static CCSocialUploadMission *create(cocos2d::CCString *id, cocos2d::CCString *name,
                CCProvider provider, cocos2d::CCString *fileName, cocos2d::CCString *message);

        static CCSocialUploadMission *create(cocos2d::CCString *id, cocos2d::CCString *name,
                cocos2d::CCArray *rewards,
                CCProvider provider, cocos2d::CCString *fileName, cocos2d::CCString *message);

        SL_CREATE_WITH_DICTIONARY(CCSocialUploadMission);

        const char *getType() const;

    };
}

#endif //__SocialUploadMission_H_
