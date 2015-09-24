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
#include "CCKeyValueStorage.h"
#include "CCLevelUpEventDispatcher.h"
#include "CCNativeWorldStorage.h"

namespace soomla {
    static CCWorldStorage *sInstance = NULL;

    USING_NS_CC;

#define DB_WORLD_KEY_PREFIX "soomla.levelup.worlds."

    CCWorldStorage *soomla::CCWorldStorage::getInstance() {
        if (!sInstance)
        {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) || (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
            sInstance = new CCNativeWorldStorage();
#else
            sInstance = new CCWorldStorage();
#endif
        }
        return sInstance;
    }

    void CCWorldStorage::initLevelUp() {
        CCLevelUpEventDispatcher::getInstance()->onLevelUpInitialized();
    }

    void CCWorldStorage::setCompleted(CCWorld *world, bool completed, bool notify) {
        const char *key = this->keyWorldCompletedWithWorldId(world->getId()->getCString());

        if (completed) {
            CCKeyValueStorage::getInstance()->setValue(key, "yes");

            if (notify) {
                CCLevelUpEventDispatcher::getInstance()->onWorldCompleted(world);
            }
        } else {
            CCKeyValueStorage::getInstance()->deleteKeyValue(key);
        }
    }

    void CCWorldStorage::setCompleted(CCWorld *world, bool completed) {
        setCompleted(world, completed, true);
    }

    bool CCWorldStorage::isCompleted(CCWorld *world) {
        const char *key = this->keyWorldCompletedWithWorldId(world->getId()->getCString());
        const char *val = CCKeyValueStorage::getInstance()->getValue(key);
        return (val != NULL && strlen(val) > 0);
    }

    void CCWorldStorage::setReward(CCWorld *world, cocos2d::__String *rewardId) {
        const char *key = this->keyRewardWithWorldId(world->getId()->getCString());

        if (rewardId != NULL && rewardId->length() > 0) {
            CCKeyValueStorage::getInstance()->setValue(key, rewardId->getCString());
        } else {
            CCKeyValueStorage::getInstance()->deleteKeyValue(key);
        }
    }

    cocos2d::__String *CCWorldStorage::getAssignedReward(CCWorld *world) {
        const char *key = this->keyRewardWithWorldId(world->getId()->getCString());
        const char *val = CCKeyValueStorage::getInstance()->getValue(key);
        return val != NULL ? __String::create(val) : NULL;
    }
    
    void CCWorldStorage::setLastCompletedInnerWorld(CCWorld *world, cocos2d::__String *innerWorldId) {
        const char *key = this->keyLastCompletedInnerWorldWithWorldId(world->getId()->getCString());

        if (innerWorldId != NULL && innerWorldId->length() > 0) {
            CCKeyValueStorage::getInstance()->setValue(key, innerWorldId->getCString());
        } else {
            CCKeyValueStorage::getInstance()->deleteKeyValue(key);
        }
    }
    
    cocos2d::__String *CCWorldStorage::getLastCompletedInnerWorld(CCWorld *world) {
        const char *key = this->keyLastCompletedInnerWorldWithWorldId(world->getId()->getCString());
        const char *val = CCKeyValueStorage::getInstance()->getValue(key);
        return val != NULL ? __String::create(val) : NULL;
    }

    char const *CCWorldStorage::keyWorldCompletedWithWorldId(char const *worldId) {
        return this->keyWorldsWithWorldId(worldId, "completed");
    }

    char const *CCWorldStorage::keyRewardWithWorldId(char const *worldId) {
        return this->keyWorldsWithWorldId(worldId, "assignedReward");
    }

    char const *CCWorldStorage::keyLastCompletedInnerWorldWithWorldId(char const *worldId) {
        return this->keyWorldsWithWorldId(worldId, "lastCompletedInnerWorld");
    }

    char const *CCWorldStorage::keyWorldsWithWorldId(char const *worldId, char const *postfix) {
        return __String::createWithFormat("%s%s.%s", DB_WORLD_KEY_PREFIX, worldId, postfix)->getCString();
    }

    char const *CCWorldStorage::getKeyWorldPrefix() {
        return DB_WORLD_KEY_PREFIX;
    }
}
