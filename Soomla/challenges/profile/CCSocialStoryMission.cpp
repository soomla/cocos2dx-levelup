//
// Created by Shubin Fedor on 08/09/14.
// Copyright (c) 2014 SOOMLA. All rights reserved.
//

#import <unistd.h>
#include "CCSocialStoryMission.h"
#include "CCLevelUpConsts.h"

namespace soomla {

    CCSocialStoryMission *CCSocialStoryMission::create(cocos2d::__String *id, cocos2d::__String *name,
            CCProvider provider,
            cocos2d::__String *message,
            cocos2d::__String *storyName, cocos2d::__String *caption,
            cocos2d::__String *link, cocos2d::__String *imgUrl) {
        return CCSocialStoryMission::create(id, name, NULL, provider, message, storyName, caption, link, imgUrl);
    }

    CCSocialStoryMission *CCSocialStoryMission::create(cocos2d::__String *id, cocos2d::__String *name,
            cocos2d::__Array *rewards,
            CCProvider provider,
            cocos2d::__String *message,
            cocos2d::__String *storyName, cocos2d::__String *caption,
            cocos2d::__String *link, cocos2d::__String *imgUrl) {

        CCSocialStoryMission *ret = new CCSocialStoryMission();

        __Dictionary *dict = __Dictionary::create();
        dict->setObject(__String::create(CCLevelUpConsts::JSON_JSON_TYPE_SOCIAL_STORY_GATE),
                CCLevelUpConsts::JSON_JSON_TYPE);
        dict->setObject(CCUserProfileUtils::providerEnumToString(provider), CCLevelUpConsts::JSON_LU_SOCIAL_PROVIDER);
        dict->setObject(message, CCLevelUpConsts::JSON_LU_MESSAGE);
        dict->setObject(storyName, CCLevelUpConsts::JSON_LU_STORY_NAME);
        dict->setObject(caption, CCLevelUpConsts::JSON_LU_CAPTION);
        dict->setObject(link, CCLevelUpConsts::JSON_LU_LINK);
        dict->setObject(imgUrl, CCLevelUpConsts::JSON_LU_IMG_LINK);
        if (ret->init(id, name, rewards, dict)) {
            ret->autorelease();
        }
        else {
            CC_SAFE_DELETE(ret);
        }

        return ret;
    }

    const char *CCSocialStoryMission::getType() const {
        return CCLevelUpConsts::JSON_JSON_TYPE_SOCIAL_STORY_MISSION;
    }

}
