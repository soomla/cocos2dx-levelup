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
