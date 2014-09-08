//
// Created by Shubin Fedor on 08/09/14.
// Copyright (c) 2014 SOOMLA. All rights reserved.
//

#include "CCSocialLikeMission.h"
#include "CCLevelUpConsts.h"

namespace soomla {

    CCSocialLikeMission *CCSocialLikeMission::create(cocos2d::CCString *id, cocos2d::CCString *name, CCProvider provider, cocos2d::CCString *pageName) {
        return CCSocialLikeMission::create(id, name, NULL, provider, pageName);
    }

    CCSocialLikeMission *CCSocialLikeMission::create(cocos2d::CCString *id, cocos2d::CCString *name, cocos2d::CCArray *rewards, CCProvider provider, cocos2d::CCString *pageName) {
        CCSocialLikeMission *ret = new CCSocialLikeMission();

        CCDictionary *dict = CCDictionary::create();
        dict->setObject(CCString::create(CCLevelUpConsts::JSON_JSON_TYPE_SOCIAL_LIKE_GATE),
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
