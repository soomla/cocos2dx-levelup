//
// Created by Shubin Fedor on 19/08/14.
// Copyright (c) 2014 SOOMLA. All rights reserved.
//

#include "CCWorldCompletionMission.h"
#include "CCLevelUpConsts.h"

namespace soomla {

    USING_NS_CC;

    CCWorldCompletionMission *CCWorldCompletionMission::create(cocos2d::__String *id, cocos2d::__String *name, cocos2d::__String *associatedWorldId) {
        return create(id, name, NULL, associatedWorldId);
    }

    CCWorldCompletionMission *CCWorldCompletionMission::create(cocos2d::__String *id, cocos2d::__String *name, cocos2d::__Array *rewards, cocos2d::__String *associatedWorldId) {
        CCWorldCompletionMission *ret = new CCWorldCompletionMission();

        __Dictionary *dict = __Dictionary::create();
        dict->setObject(__String::create(CCLevelUpConsts::JSON_JSON_TYPE_WORLD_COMPLETION_GATE),
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