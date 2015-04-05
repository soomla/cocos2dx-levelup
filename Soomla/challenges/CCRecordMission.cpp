
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


#include "CCRecordMission.h"
#include "CCLevelUpConsts.h"

namespace soomla {

    USING_NS_CC;

    CCRecordMission *CCRecordMission::create(cocos2d::CCString *id, cocos2d::CCString *name, cocos2d::CCString *associatedScoreId, cocos2d::CCDouble *desiredRecord) {
        return create(id, name, NULL, associatedScoreId, desiredRecord);
    }

    CCRecordMission *CCRecordMission::create(cocos2d::CCString *id, cocos2d::CCString *name, cocos2d::CCArray *rewards, cocos2d::CCString *associatedScoreId, cocos2d::CCDouble *desiredRecord) {
        CCRecordMission *ret = new CCRecordMission();

        CCDictionary *dict = CCDictionary::create();
        dict->setObject(CCString::create(CCLevelUpConsts::JSON_JSON_TYPE_RECORD_GATE),
                CCCoreConsts::JSON_JSON_TYPE);
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
