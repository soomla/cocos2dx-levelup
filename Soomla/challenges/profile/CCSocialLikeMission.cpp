//
// Created by Shubin Fedor on 08/09/14.
// Copyright (c) 2014 SOOMLA. All rights reserved.
//

#include "CCSocialLikeMission.h"
#include "CCLevelUpConsts.h"

namespace soomla {

    CCSocialLikeMission *CCSocialLikeMission::create(cocos2d::__String *id, cocos2d::__String *name, CCProvider provider, cocos2d::__String *pageName) {
        return CCSocialLikeMission::create(id, name, NULL, provider, pageName);
    }

    CCSocialLikeMission *CCSocialLikeMission::create(cocos2d::__String *id, cocos2d::__String *name, cocos2d::__Array *rewards, CCProvider provider, cocos2d::__String *pageName) {
        CCSocialLikeMission *ret = new CCSocialLikeMission();

        __Dictionary *dict = __Dictionary::create();
        dict->setObject(__String::create(CCLevelUpConsts::JSON_JSON_TYPE_SOCIAL_LIKE_GATE),
                CCLevelUpConsts::JSON_JSON_TYPE);
        dict->setObject(CCUserProfileUtils::providerEnumToString(provider), CCLevelUpConsts::JSON_LU_SOCIAL_PROVIDER);
        dict->setObject(pageName, CCLevelUpConsts::JSON_LU_PAGE_NAME);
        if (ret->init(id, name, rewards, dict)) {
            ret->autorelease();
        }
        else {
            CC_SAFE_DELETE(ret);
        }

        return ret;
    }

    const char *CCSocialLikeMission::getType() const {
        return CCLevelUpConsts::JSON_JSON_TYPE_SOCIAL_LIKE_MISSION;
    }

}
