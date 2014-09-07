//
// Created by Shubin Fedor on 19/08/14.
// Copyright (c) 2014 SOOMLA. All rights reserved.
//


#ifndef __CCWorldCompletionMission_H_
#define __CCWorldCompletionMission_H_

#include "CCMission.h"

namespace soomla {

    class CCWorldCompletionMission: public CCMission {
    public:
        CCWorldCompletionMission(): CCMission() {
        }

        static CCWorldCompletionMission *create(cocos2d::CCString *id, cocos2d::CCString *name,
                cocos2d::CCString *associatedWorldId);

        static CCWorldCompletionMission *create(cocos2d::CCString *id, cocos2d::CCString *name,
                cocos2d::CCArray *rewards, cocos2d::CCString *associatedWorldId);

        SL_CREATE_WITH_DICTIONARY(CCWorldCompletionMission);

        virtual const char *getType() const;
    };

}

#endif //__CCWorldCompletionMission_H_
