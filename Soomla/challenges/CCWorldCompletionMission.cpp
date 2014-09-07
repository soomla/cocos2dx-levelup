//
// Created by Shubin Fedor on 19/08/14.
// Copyright (c) 2014 SOOMLA. All rights reserved.
//

#include "CCWorldCompletionMission.h"
#include "CCLevelUpConsts.h"

namespace soomla {

    USING_NS_CC;

    CCWorldCompletionMission *CCWorldCompletionMission::create(cocos2d::CCString *id, cocos2d::CCString *name, cocos2d::CCString *associatedWorldId) {
        return create(id, name, NULL, associatedWorldId);
    }

    CCWorldCompletionMission *CCWorldCompletionMission::create(cocos2d::CCString *id, cocos2d::CCString *name, cocos2d::CCArray *rewards, cocos2d::CCString *associatedWorldId) {
        CCWorldCompletionMission *ret = new CCWorldCompletionMission();

        CCDictionary *dict = CCDictionary::create();
        dict->setObject(CCString::create(CCLevelUpConsts::JSON_JSON_TYPE_WORLD_COMPLETION_GATE),
                CCLevelUpConsts::JSON_JSON_TYPE);
        dict->setObject(associatedWorldId, CCLevelUpConsts::JSON_LU_ASSOCWORLDID);
        if (ret->init(id, name, rewards, dict)) {
            ret->autorelease();
        }
        else {
            CC_SAFE_DELETE(ret);
        }

        return ret;
    }

    const char *CCWorldCompletionMission::getType() const {
        return CCLevelUpConsts::JSON_JSON_TYPE_WORLD_COMPLETION_MISSION;
    }
}