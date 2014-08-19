//
// Created by Shubin Fedor on 19/08/14.
// Copyright (c) 2014 SOOMLA. All rights reserved.
//

#include "CCBalanceMission.h"
#include "CCLevelUpConsts.h"

USING_NS_CC;

namespace soomla {
    CCBalanceMission *CCBalanceMission::create(cocos2d::__String *id, cocos2d::__String *name, cocos2d::__String *associatedItemId, cocos2d::__Integer *desiredBalance) {
        return CCBalanceMission::create(id, name, NULL, associatedItemId, desiredBalance);
    }

    CCBalanceMission *CCBalanceMission::create(cocos2d::__String *id, cocos2d::__String *name, cocos2d::__Array *rewards, cocos2d::__String *associatedItemId, cocos2d::__Integer *desiredBalance) {
        CCBalanceMission *ret = new CCBalanceMission();

        __Dictionary *dict = __Dictionary::create();
        dict->setObject(__String::create(CCLevelUpConsts::JSON_JSON_TYPE_BALANCE_GATE),
                CCLevelUpConsts::JSON_JSON_TYPE);
        dict->setObject(associatedItemId, CCLevelUpConsts::JSON_LU_ASSOCITEMID);
        dict->setObject(desiredBalance, CCLevelUpConsts::JSON_LU_DESIRED_BALANCE);
        if (ret->init(id, name, rewards, dict)) {
            ret->autorelease();
        }
        else {
            CC_SAFE_DELETE(ret);
        }

        return ret;
    }

    const char *CCBalanceMission::getType() const {
        return CCLevelUpConsts::JSON_JSON_TYPE_BALANCE_MISSION;
    }
}
