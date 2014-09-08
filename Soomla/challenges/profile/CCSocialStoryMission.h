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

        static CCSocialStoryMission *create(cocos2d::__String *id, cocos2d::__String *name,
                CCProvider provider, cocos2d::__String *message,
                cocos2d::__String *storyName, cocos2d::__String *caption,
                cocos2d::__String *link, cocos2d::__String *imgUrl);

        static CCSocialStoryMission *create(cocos2d::__String *id, cocos2d::__String *name,
                cocos2d::__Array *rewards, CCProvider provider, cocos2d::__String *message,
                cocos2d::__String *storyName, cocos2d::__String *caption,
                cocos2d::__String *link, cocos2d::__String *imgUrl);

        SL_CREATE_WITH_DICTIONARY(CCSocialStoryMission);

        const char *getType() const;

    };
}

#endif //__SocialStoryMission_H_
