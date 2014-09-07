//
// Created by Shubin Fedor on 19/08/14.
// Copyright (c) 2014 SOOMLA. All rights reserved.
//

#include "CCWorldStorage.h"
#include "CCWorld.h"
#include "CCLevelUpService.h"

namespace soomla {
    static CCWorldStorage *sInstance = NULL;

    CCWorldStorage *soomla::CCWorldStorage::getInstance() {
        if (!sInstance)
        {
            sInstance = new CCWorldStorage();
            sInstance->retain();
        }
        return sInstance;
    }

    void CCWorldStorage::setCompleted(CCWorld *world, bool completed, bool notify) {
        bool currentStatus = isCompleted(world);
        if (currentStatus == completed) {
            // we don't need to set the status of a world to the same status over and over again.
            // couldn't only cause trouble.
            return;
        }
        CCLevelUpService::getInstance()->worldSetCompleted(world, completed, notify);
    }

    void CCWorldStorage::setCompleted(CCWorld *world, bool completed) {
        setCompleted(world, completed, true);
    }

    bool CCWorldStorage::isCompleted(CCWorld *world) {
        return CCLevelUpService::getInstance()->worldIsCompleted(world);
    }

    void CCWorldStorage::setReward(CCWorld *world, cocos2d::CCString *rewardId) {
        CCLevelUpService::getInstance()->worldSetReward(world, rewardId);
    }

    cocos2d::CCString *CCWorldStorage::getAssignedReward(CCWorld *world) {
        return CCLevelUpService::getInstance()->worldGetAssignedReward(world);
    }
}
