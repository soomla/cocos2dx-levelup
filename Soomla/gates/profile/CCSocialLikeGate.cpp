//
// Created by Shubin Fedor on 21/08/14.
// Copyright (c) 2014 SOOMLA. All rights reserved.
//

#include "CCSocialLikeGate.h"
#include "CCGateStorage.h"
#include "CCSoomlaProfile.h"

namespace soomla {

#define TAG "SOOMLA SocialLikeGate"

    CCSocialLikeGate *CCSocialLikeGate::create(cocos2d::__String *id, CCProvider provider, cocos2d::__String *pageName) {
        CCSocialLikeGate *ret = new CCSocialLikeGate();
        if (ret->init(id, provider, pageName)) {
            ret->autorelease();
        }
        else {
            CC_SAFE_DELETE(ret);
        }

        return ret;
    }

    bool CCSocialLikeGate::init(cocos2d::__String *id, CCProvider provider, cocos2d::__String *pageName) {
        bool result = CCSocialActionGate::init(id, provider);
        if (result) {

            setPageName(pageName);

            return true;
        }
        return result;
    }

    bool CCSocialLikeGate::initWithDictionary(cocos2d::__Dictionary *dict) {
        bool result = CCGate::initWithDictionary(dict);
        if (result) {

            fillPageNameFromDict(dict);

            return true;
        }
        return result;
    }

    cocos2d::__Dictionary *CCSocialLikeGate::toDictionary() {
        cocos2d::__Dictionary *dict = CCSoomlaEntity::toDictionary();

        putPageNameToDict(dict);

        return dict;
    }

    const char *CCSocialLikeGate::getType() const {
        return CCLevelUpConsts::JSON_JSON_TYPE_SOCIAL_LIKE_GATE;
    }

    CCSocialLikeGate::~CCSocialLikeGate() {
        CC_SAFE_RELEASE(mPageName);
    }

    bool CCSocialLikeGate::openInner() {
        if (canOpen()) {

            CCSoomlaProfile::getInstance()->like(getProvider(), getPageName()->getCString(), NULL, NULL);

            return true;
        }

        return false;
    }

}