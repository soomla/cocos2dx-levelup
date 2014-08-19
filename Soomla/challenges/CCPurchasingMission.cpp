//
// Created by Shubin Fedor on 19/08/14.
// Copyright (c) 2014 SOOMLA. All rights reserved.
//

#include "CCPurchasingMission.h"
#include "CCLevelUpConsts.h"

namespace soomla {

    USING_NS_CC;

    CCPurchasingMission *CCPurchasingMission::create(cocos2d::__String *id, cocos2d::__String *name, cocos2d::__String *associatedItemId) {
        return create(id, name, NULL, associatedItemId);
    }

    CCPurchasingMission *CCPurchasingMission::create(cocos2d::__String *id, cocos2d::__String *name, cocos2d::__Array *rewards, cocos2d::__String *associatedItemId) {
        CCPurchasingMission *ret = new CCPurchasingMission();

        __Dictionary *dict = __Dictionary::create();
        dict->setObject(__String::create(CCLevelUpConsts::JSON_JSON_TYPE_PURCHASABLE_GATE),
                CCLevelUpConsts::JSON_JSON_TYPE);
        dict->setObject(associatedItemId, CCLevelUpConsts::JSON_LU_ASSOCITEMID);
        if (ret->init(id, name, rewards, dict)) {
            ret->autorelease();
        }
        else {
            CC_SAFE_DELETE(ret);
        }

        return ret;
    }

    const char *CCPurchasingMission::getType() const {
        return CCLevelUpConsts::JSON_JSON_TYPE_PURCHASE_MISSION;
    }
}