//
// Created by Shubin Fedor on 08/09/14.
// Copyright (c) 2014 SOOMLA. All rights reserved.
//

#include "CCSocialStatusMission.h"
#include "CCLevelUpConsts.h"

namespace soomla {

    CCSocialStatusMission *CCSocialStatusMission::create(cocos2d::CCString *id, cocos2d::CCString *name, CCProvider provider, cocos2d::CCString *status) {
        return CCSocialStatusMission::create(id, name, NULL, provider, status);
    }

    CCSocialStatusMission *CCSocialStatusMission::create(cocos2d::CCString *id, cocos2d::CCString *name, cocos2d::CCArray *rewards, CCProvider provider, cocos2d::CCString *status) {
        CCSocialStatusMission *ret = new CCSocialStatusMission();

        CCDictionary *dict = CCDictionary::create();
        dict->setObject(CCString::create(CCLevelUpConsts::JSON_JSON_TYPE_SOCIAL_STATUS_GATE),
                CCLevelUpConsts::JSON_JSON_TYPE);
        dict->setObject(CCUserProfileUtils::providerEnumToString(provider), CCLevelUpConsts::JSON_LU_SOCIAL_PROVIDER);
        dict->setObject(status, CCLevelUpConsts::JSON_LU_STATUS);
        if (ret->init(id, name, rewards, dict)) {
            ret->autorelease();
        }
        else {
            CC_SAFE_DELETE(ret);
        }

        return ret;
    }

    const char *CCSocialStatusMission::getType() const {
        return CCLevelUpConsts::JSON_JSON_TYPE_SOCIAL_STATUS_MISSION;
    }

}
