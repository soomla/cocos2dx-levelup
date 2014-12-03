/*
 Copyright (C) 2012-2014 Soomla Inc.

 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at

 http://www.apache.org/licenses/LICENSE-2.0

 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.
 */


#include "CCBalanceMission.h"
#include "CCLevelUpConsts.h"

USING_NS_CC;

namespace soomla {
    CCBalanceMission *CCBalanceMission::create(cocos2d::CCString *id, cocos2d::CCString *name, cocos2d::CCString *associatedItemId, cocos2d::CCInteger *desiredBalance) {
        return CCBalanceMission::create(id, name, NULL, associatedItemId, desiredBalance);
    }

    CCBalanceMission *CCBalanceMission::create(cocos2d::CCString *id, cocos2d::CCString *name, cocos2d::CCArray *rewards, cocos2d::CCString *associatedItemId, cocos2d::CCInteger *desiredBalance) {
        CCBalanceMission *ret = new CCBalanceMission();

        CCDictionary *dict = CCDictionary::create();
        dict->setObject(CCString::create(CCLevelUpConsts::JSON_JSON_TYPE_BALANCE_GATE),
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
