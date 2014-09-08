//
// Created by Shubin Fedor on 21/08/14.
// Copyright (c) 2014 SOOMLA. All rights reserved.
//

#include "CCSocialStatusGate.h"
#include "CCGateStorage.h"
#include "CCProfileController.h"

namespace soomla {

#define TAG "SOOMLA SocialStatusGate"

    CCSocialStatusGate *CCSocialStatusGate::create(cocos2d::CCString *id, CCProvider provider, cocos2d::CCString *pageName) {
        CCSocialStatusGate *ret = new CCSocialStatusGate();
        if (ret->init(id, provider, pageName)) {
            ret->autorelease();
        }
        else {
            CC_SAFE_DELETE(ret);
        }

        return ret;
    }

    bool CCSocialStatusGate::init(cocos2d::CCString *id, CCProvider provider, cocos2d::CCString *pageName) {
        bool result = CCSocialActionGate::init(id, provider);
        if (result) {

            setStatus(pageName);

            return true;
        }
        return result;
    }

    bool CCSocialStatusGate::initWithDictionary(cocos2d::CCDictionary *dict) {
        bool result = CCGate::initWithDictionary(dict);
        if (result) {

            fillStatusFromDict(dict);

            return true;
        }
        return result;
    }

    cocos2d::CCDictionary *CCSocialStatusGate::toDictionary() {
        cocos2d::CCDictionary *dict = CCSoomlaEntity::toDictionary();

        putStatusToDict(dict);

        return dict;
    }

    const char *CCSocialStatusGate::getType() const {
        return CCLevelUpConsts::JSON_JSON_TYPE_SOCIAL_STATUS_GATE;
    }

    CCSocialStatusGate::~CCSocialStatusGate() {
        CC_SAFE_RELEASE(mStatus);
    }

    bool CCSocialStatusGate::openInner() {
        if (canOpen()) {

            CCProfileController::getInstance()->updateStatus(getProvider(), getStatus()->getCString(), NULL, NULL);

            return true;
        }

        return false;
    }

}