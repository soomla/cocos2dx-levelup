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

#include "CCLevelStorage.h"
#include "CCLevel.h"
#include "CCNativeLevelStorage.h"
#include "CCKeyValueStorage.h"
#include "CCLevelUpEventDispatcher.h"

namespace soomla {

    USING_NS_CC;

#define DB_LEVEL_KEY_PREFIX "soomla.levelup.levels."

    static CCLevelStorage *sInstance = nullptr;

    CCLevelStorage *soomla::CCLevelStorage::getInstance() {
        if (!sInstance)
        {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) || (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
            sInstance = new CCNativeLevelStorage();
#else
            sInstance = new CCLevelStorage();
#endif
        }
        return sInstance;
    }
    
    void CCLevelStorage::setLastDurationMillis(CCLevel *level, long duration) {
        const char *key = this->keyLastDurationWithLevelId(level->getId()->getCString());
        const char *val = __String::createWithFormat("%ld", duration)->getCString();
        CCKeyValueStorage::getInstance()->setValue(key, val);
    }
    
    long CCLevelStorage::getLastDurationMillis(CCLevel *level) {
        const char *key = this->keyLastDurationWithLevelId(level->getId()->getCString());
        const char *val = CCKeyValueStorage::getInstance()->getValue(key);
        return (val != NULL && strlen(val) > 0) ? __String::create(val)->intValue() : 0;
    }

    void CCLevelStorage::setSlowestDurationMillis(CCLevel *level, long duration) {
        const char *key = this->keySlowestDurationWithLevelId(level->getId()->getCString());
        const char *val = __String::createWithFormat("%ld", duration)->getCString();
        CCKeyValueStorage::getInstance()->setValue(key, val);
    }

    long CCLevelStorage::getSlowestDurationMillis(CCLevel *level) {
        const char *key = this->keySlowestDurationWithLevelId(level->getId()->getCString());
        const char *val = CCKeyValueStorage::getInstance()->getValue(key);
        return (val != NULL && strlen(val) > 0) ? __String::create(val)->intValue() : 0;
    }

    void CCLevelStorage::setFastestDurationMillis(CCLevel *level, long duration) {
        const char *key = this->keyFastestDurationWithLevelId(level->getId()->getCString());
        const char *val = __String::createWithFormat("%ld", duration)->getCString();
        CCKeyValueStorage::getInstance()->setValue(key, val);
    }

    long CCLevelStorage::getFastestDurationMillis(CCLevel *level) {
        const char *key = this->keyFastestDurationWithLevelId(level->getId()->getCString());
        const char *val = CCKeyValueStorage::getInstance()->getValue(key);
        return (val != NULL && strlen(val) > 0) ? __String::create(val)->intValue() : 0;
    }

    int CCLevelStorage::incTimesStarted(CCLevel *level) {
        int started = this->getTimesStarted(level);
        if (started < 0) { /* can't be negative */
            started = 0;
        }
        started++;

        this->setTimesStarted(level, started);

        // Notify level has started
        CCLevelUpEventDispatcher::getInstance()->onLevelStarted(level);

        return started;
    }

    int CCLevelStorage::decTimesStarted(CCLevel *level) {
        int started = this->getTimesStarted(level);
        if (started <= 0) { /* can't be negative or zero */
            started = 0;
        }
        started--;

        this->setTimesStarted(level, started);

        return started;
    }

    int CCLevelStorage::getTimesStarted(CCLevel *level) {
        const char *key = this->keyTimesStartedWithLevelId(level->getId()->getCString());
        const char *val = CCKeyValueStorage::getInstance()->getValue(key);
        return (val != NULL && strlen(val) > 0) ? __String::create(val)->intValue() : 0;
    }

    int CCLevelStorage::getTimesPlayed(CCLevel *level) {
        const char *key = this->keyTimesPlayedWithLevelId(level->getId()->getCString());
        const char *val = CCKeyValueStorage::getInstance()->getValue(key);
        return (val != NULL && strlen(val) > 0) ? __String::create(val)->intValue() : 0;
    }

    int CCLevelStorage::incTimesPlayed(CCLevel *level) {
        int played = this->getTimesPlayed(level);
        if (played < 0) { /* can't be negative */
            played = 0;
        }
        played++;

        this->setTimesPlayed(level, played);

        // Notify level has ended
        CCLevelUpEventDispatcher::getInstance()->onLevelEnded(level);

        return played;
    }

    int CCLevelStorage::decTimesPlayed(CCLevel *level) {
        int played = this->getTimesPlayed(level);
        if (played <= 0) { /* can't be negative or zero */
            return 0;
        }
        played--;

        this->setTimesPlayed(level, played);
        return played;
    }
    
    int CCLevelStorage::getTimesCompleted(CCLevel *level) {
        const char *key = this->keyTimesCompletedWithLevelId(level->getId()->getCString());
        const char *val = CCKeyValueStorage::getInstance()->getValue(key);
        return (val != NULL && strlen(val) > 0) ? __String::create(val)->intValue() : 0;
    }
    
    int CCLevelStorage::incTimesCompleted(CCLevel *level) {
        int played = this->getTimesCompleted(level);
        if (played < 0) { /* can't be negative */
            played = 0;
        }
        played++;

        this->setTimesCompleted(level, played);

        return played;
    }
    
    int CCLevelStorage::decTimesCompleted(CCLevel *level) {
        int played = this->getTimesCompleted(level);
        if (played <= 0) { /* can't be negative or zero */
            played = 0;
        }
        played--;

        this->setTimesCompleted(level, played);

        return played;
    }

    void CCLevelStorage::setTimesStarted(CCLevel *level, int started) {
        const char *key = this->keyTimesCompletedWithLevelId(level->getId()->getCString());
        const char *val = __String::createWithFormat("%d", started)->getCString();
        CCKeyValueStorage::getInstance()->setValue(key, val);
    }

    void CCLevelStorage::setTimesPlayed(CCLevel *level, int played) {
        const char *key = this->keyTimesPlayedWithLevelId(level->getId()->getCString());
        const char *val = __String::createWithFormat("%d", played)->getCString();
        CCKeyValueStorage::getInstance()->setValue(key, val);
    }

    void CCLevelStorage::setTimesCompleted(CCLevel *level, int timesCompleted) {
        const char *key = this->keyTimesCompletedWithLevelId(level->getId()->getCString());
        const char *val = __String::createWithFormat("%d", timesCompleted)->getCString();
        CCKeyValueStorage::getInstance()->setValue(key, val);
    }

    char const *CCLevelStorage::keyTimesStartedWithLevelId(char const *levelId) {
        return this->keyLevelsWithLevelId(levelId, "started");
    }

    char const *CCLevelStorage::keyTimesCompletedWithLevelId(char const *levelId) {
        return this->keyLevelsWithLevelId(levelId, "timesCompleted");
    }

    char const *CCLevelStorage::keyTimesPlayedWithLevelId(char const *levelId) {
        return this->keyLevelsWithLevelId(levelId, "played");
    }
    
    char const *CCLevelStorage::keyLastDurationWithLevelId(char const *levelId) {
        return this->keyLevelsWithLevelId(levelId, "last");
    }

    char const *CCLevelStorage::keySlowestDurationWithLevelId(char const *levelId) {
        return this->keyLevelsWithLevelId(levelId, "slowest");
    }

    char const *CCLevelStorage::keyFastestDurationWithLevelId(char const *levelId) {
        return this->keyLevelsWithLevelId(levelId, "fastest");
    }

    char const *CCLevelStorage::keyLevelsWithLevelId(char const *levelId, char const *postfix) {
        return __String::createWithFormat("%s%s.%s", DB_LEVEL_KEY_PREFIX, levelId, postfix)->getCString();

    }

    char const *CCLevelStorage::getKeyLevelPrefix() {
        return DB_LEVEL_KEY_PREFIX;
    }
}
