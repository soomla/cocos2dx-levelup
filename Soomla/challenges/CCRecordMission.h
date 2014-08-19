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

        static CCRecordMission *create(cocos2d::__String *id, cocos2d::__String *name,
                cocos2d::__String *associatedScoreId, cocos2d::__Double *desiredRecord);

        static CCRecordMission *create(cocos2d::__String *id, cocos2d::__String *name,
                cocos2d::__Array *rewards, cocos2d::__String *associatedScoreId, cocos2d::__Double *desiredRecord);

        SL_CREATE_WITH_DICTIONARY(CCRecordMission);

        virtual const char *getType() const;
    };
}

#endif //__CCRecordMission_H_
