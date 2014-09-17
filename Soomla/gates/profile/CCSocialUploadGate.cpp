//
// Created by Shubin Fedor on 21/08/14.
// Copyright (c) 2014 SOOMLA. All rights reserved.
//

#include "CCSocialUploadGate.h"
#include "CCGateStorage.h"
#include "CCSoomlaProfile.h"

namespace soomla {

#define TAG "SOOMLA SocialUploadGate"

    CCSocialUploadGate *CCSocialUploadGate::create(cocos2d::CCString *id, CCProvider provider,
            cocos2d::CCString *fileName, cocos2d::CCString *message) {

        CCSocialUploadGate *ret = new CCSocialUploadGate();
        if (ret->init(id, provider, fileName, message)) {
            ret->autorelease();
        }
        else {
            CC_SAFE_DELETE(ret);
        }

        return ret;
    }

    bool CCSocialUploadGate::init(cocos2d::CCString *id, CCProvider provider,
            cocos2d::CCString *fileName, cocos2d::CCString *message) {

        bool result = CCSocialActionGate::init(id, provider);

        if (result) {
            setFileName(fileName);
            setMessage(message);

            return true;
        }
        return result;
    }

    bool CCSocialUploadGate::initWithDictionary(cocos2d::CCDictionary *dict) {
        bool result = CCGate::initWithDictionary(dict);
        if (result) {

            fillFileNameFromDict(dict);
            fillMessageFromDict(dict);

            return true;
        }
        return result;
    }

    cocos2d::CCDictionary *CCSocialUploadGate::toDictionary() {
        cocos2d::CCDictionary *dict = CCSoomlaEntity::toDictionary();

        putFileNameToDict(dict);
        putMessageToDict(dict);

        return dict;
    }

    const char *CCSocialUploadGate::getType() const {
        return CCLevelUpConsts::JSON_JSON_TYPE_SOCIAL_UPLOAD_GATE;
    }

    CCSocialUploadGate::~CCSocialUploadGate() {
        CC_SAFE_RELEASE(mFileName);
        CC_SAFE_RELEASE(mMessage);
    }

    bool CCSocialUploadGate::openInner() {
        if (canOpen()) {

            CCSoomlaProfile::getInstance()->uploadImage(getProvider(),
                    getMessage()->getCString(), getFileName()->getCString(), NULL, NULL);

            return true;
        }

        return false;
    }

}