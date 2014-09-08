//
// Created by Shubin Fedor on 08/09/14.
// Copyright (c) 2014 SOOMLA. All rights reserved.
//

#include "CCSocialStatusMission.h"
#include "CCLevelUpConsts.h"

namespace soomla {

    CCSocialStatusMission *CCSocialStatusMission::create(cocos2d::__String *id, cocos2d::__String *name, CCProvider provider, cocos2d::__String *status) {
        return CCSocialStatusMission::create(id, name, NULL, provider, status);
    }

    CCSocialStatusMission *CCSocialStatusMission::create(cocos2d::__String *id, cocos2d::__String *name, cocos2d::__Array *rewards, CCProvider provider, cocos2d::__String *status) {
        CCSocialStatusMission *ret = new CCSocialStatusMission();

        __Dictionary *dict = __Dictionary::create();
        dict->setObject(__String::create(CCLevelUpConsts::JSON_JSON_TYPE_SOCIAL_STATUS_GATE),
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
