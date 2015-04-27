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


#include "CCNativeWorldStorage.h"
#include "CCLevelUpBridge.h"

namespace soomla {

    void CCNativeWorldStorage::initLevelUp() {
        // This is like this since we need to register DomainFactory
        // Before the developer can create an initial world
        CCLevelUpBridge::initShared();
    }

    void CCNativeWorldStorage::setCompleted(CCWorld *world, bool completed, bool notify) {
        CCLevelUpBridge::getInstance()->worldSetCompleted(world, completed, notify);
    }

    bool CCNativeWorldStorage::isCompleted(CCWorld *world) {
        return CCLevelUpBridge::getInstance()->worldIsCompleted(world);
    }

    void CCNativeWorldStorage::setReward(CCWorld *world, cocos2d::__String *rewardId) {
        CCLevelUpBridge::getInstance()->worldSetReward(world, rewardId);
    }

    cocos2d::__String *CCNativeWorldStorage::getAssignedReward(CCWorld *world) {
        return CCLevelUpBridge::getInstance()->worldGetAssignedReward(world);
    }
    
    void CCNativeWorldStorage::setLastCompletedInnerWorld(CCWorld *world, cocos2d::__String *innerWorldId) {
        CCLevelUpBridge::getInstance()->worldSetLastCompletedInnerWorld(world, innerWorldId);
    }
    
    cocos2d::__String *CCNativeWorldStorage::getLastCompletedInnerWorld(CCWorld *world) {
        return CCLevelUpBridge::getInstance()->worldGetLastCompletedInnerWorld(world);
    }
}
