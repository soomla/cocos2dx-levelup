//
// Created by Shubin Fedor on 08/09/14.
// Copyright (c) 2014 SOOMLA. All rights reserved.
//

#include "CCSocialUploadMission.h"
#include "CCLevelUpConsts.h"

namespace soomla {

    CCSocialUploadMission *CCSocialUploadMission::create(cocos2d::CCString *id, cocos2d::CCString *name,
            CCProvider provider,
            cocos2d::CCString *fileName, cocos2d::CCString *message) {

        return CCSocialUploadMission::create(id, name, NULL, provider, fileName, message);
    }

    CCSocialUploadMission *CCSocialUploadMission::create(cocos2d::CCString *id, cocos2d::CCString *name,
            cocos2d::CCArray *rewards,
            CCProvider provider,
            cocos2d::CCString *fileName, cocos2d::CCString *message) {

        CCSocialUploadMission *ret = new CCSocialUploadMission();

        CCDictionary *dict = CCDictionary::create();
        dict->setObject(CCString::create(CCLevelUpConsts::JSON_JSON_TYPE_SOCIAL_UPLOAD_GATE),
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
