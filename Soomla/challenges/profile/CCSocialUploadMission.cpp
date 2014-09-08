//
// Created by Shubin Fedor on 08/09/14.
// Copyright (c) 2014 SOOMLA. All rights reserved.
//

#include "CCSocialUploadMission.h"
#include "CCLevelUpConsts.h"

namespace soomla {

    CCSocialUploadMission *CCSocialUploadMission::create(cocos2d::__String *id, cocos2d::__String *name,
            CCProvider provider,
            cocos2d::__String *fileName, cocos2d::__String *message) {

        return CCSocialUploadMission::create(id, name, NULL, provider, fileName, message);
    }

    CCSocialUploadMission *CCSocialUploadMission::create(cocos2d::__String *id, cocos2d::__String *name,
            cocos2d::__Array *rewards,
            CCProvider provider,
            cocos2d::__String *fileName, cocos2d::__String *message) {

        CCSocialUploadMission *ret = new CCSocialUploadMission();

        __Dictionary *dict = __Dictionary::create();
        dict->setObject(__String::create(CCLevelUpConsts::JSON_JSON_TYPE_SOCIAL_UPLOAD_GATE),
                CCLevelUpConsts::JSON_JSON_TYPE);
        dict->setObject(CCUserProfileUtils::providerEnumToString(provider), CCLevelUpConsts::JSON_LU_SOCIAL_PROVIDER);
        dict->setObject(fileName, CCLevelUpConsts::JSON_LU_FILE_NAME);
        dict->setObject(message, CCLevelUpConsts::JSON_LU_MESSAGE);
        if (ret->init(id, name, rewards, dict)) {
            ret->autorelease();
        }
        else {
            CC_SAFE_DELETE(ret);
        }

        return ret;
    }

    const char *CCSocialUploadMission::getType() const {
        return CCLevelUpConsts::JSON_JSON_TYPE_SOCIAL_UPLOAD_MISSION;
    }

}
