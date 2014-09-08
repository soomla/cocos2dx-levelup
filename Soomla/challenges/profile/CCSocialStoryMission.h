//
// Created by Shubin Fedor on 08/09/14.
// Copyright (c) 2014 SOOMLA. All rights reserved.
//


#ifndef __SocialStoryMission_H_
#define __SocialStoryMission_H_

#include "CCMission.h"
#include "CCUserProfileUtils.h"

namespace soomla {
    class CCSocialStoryMission: public CCMission {
    public:
        CCSocialStoryMission(): CCMission() {
        }

        static CCSocialStoryMission *create(cocos2d::CCString *id, cocos2d::CCString *name,
                CCProvider provider, cocos2d::CCString *message,
                cocos2d::CCString *storyName, cocos2d::CCString *caption,
                cocos2d::CCString *link, cocos2d::CCString *imgUrl);

        static CCSocialStoryMission *create(cocos2d::CCString *id, cocos2d::CCString *name,
                cocos2d::CCArray *rewards, CCProvider provider, cocos2d::CCString *message,
                cocos2d::CCString *storyName, cocos2d::CCString *caption,
                cocos2d::CCString *link, cocos2d::CCString *imgUrl);

        SL_CREATE_WITH_DICTIONARY(CCSocialStoryMission);

        const char *getType() const;

    };
}

#endif //__SocialStoryMission_H_
