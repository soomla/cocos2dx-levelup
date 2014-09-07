//
// Created by Shubin Fedor on 19/08/14.
// Copyright (c) 2014 SOOMLA. All rights reserved.
//

#ifndef __CCRecordMission_H_
#define __CCRecordMission_H_

#include "CCMission.h"

namespace soomla {
    class CCRecordMission: public CCMission {
    public:
        CCRecordMission(): CCMission() {
        }

        static CCRecordMission *create(cocos2d::CCString *id, cocos2d::CCString *name,
                cocos2d::CCString *associatedScoreId, cocos2d::CCDouble *desiredRecord);

        static CCRecordMission *create(cocos2d::CCString *id, cocos2d::CCString *name,
                cocos2d::CCArray *rewards, cocos2d::CCString *associatedScoreId, cocos2d::CCDouble *desiredRecord);

        SL_CREATE_WITH_DICTIONARY(CCRecordMission);

        virtual const char *getType() const;
    };
}

#endif //__CCRecordMission_H_
