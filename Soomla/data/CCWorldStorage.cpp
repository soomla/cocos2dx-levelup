//
// Created by Shubin Fedor on 19/08/14.
// Copyright (c) 2014 SOOMLA. All rights reserved.
//

#include "CCWorldStorage.h"
#include "CCWorld.h"

namespace soomla {
    static CCWorldStorage *sInstance = nullptr;

    CCWorldStorage *soomla::CCWorldStorage::getInstance() {
        if (!sInstance)
        {
            sInstance = new CCWorldStorage();
            sInstance->retain();
        }
        return sInstance;
    }

    bool CCWorldStorage::isCompleted(CCWorld *world) {
        return false;
    }

    void CCWorldStorage::setCompleted(CCWorld *world, bool completed) {
    }

    void CCWorldStorage::setReward(CCWorld *world, cocos2d::__String *rewardId) {

    }

    cocos2d::__String *CCWorldStorage::getAssignedReward(CCWorld *world) {
        return NULL;
    }
}
