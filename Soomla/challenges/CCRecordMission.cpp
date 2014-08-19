//
// Created by Shubin Fedor on 19/08/14.
// Copyright (c) 2014 SOOMLA. All rights reserved.
//

#include "CCRecordMission.h"
#include "CCLevelUpConsts.h"

namespace soomla {

    USING_NS_CC;

    CCRecordMission *CCRecordMission::create(cocos2d::__String *id, cocos2d::__String *name, cocos2d::__String *associatedScoreId, cocos2d::__Double *desiredRecord) {
        return create(id, name, NULL, associatedScoreId, desiredRecord);
    }

    CCRecordMission *CCRecordMission::create(cocos2d::__String *id, cocos2d::__String *name, cocos2d::__Array *rewards, cocos2d::__String *associatedScoreId, cocos2d::__Double *desiredRecord) {
        CCRecordMission *ret = new CCRecordMission();

        __Dictionary *dict = __Dictionary::create();
        dict->setObject(__String::create(CCLevelUpConsts::JSON_JSON_TYPE_RECORD_GATE),
                CCLevelUpConsts::JSON_JSON_TYPE);
        dict->setObject(associatedScoreId, CCLevelUpConsts::JSON_LU_ASSOCSCOREID);
        dict->setObject(desiredRecord, CCLevelUpConsts::JSON_LU_DESIRED_RECORD);
        if (ret->init(id, name, rewards, dict)) {
            ret->autorelease();
        }
        else {
            CC_SAFE_DELETE(ret);
        }

        return ret;
    }

    const char *CCRecordMission::getType() const {
        return CCLevelUpConsts::JSON_JSON_TYPE_RECORD_MISSION;
    }
}