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


#include "CCScoreStorage.h"
#include "CCScore.h"
#include "CCLevelUpBridge.h"
#include "CCNativeScoreStorage.h"
#include "CCKeyValueStorage.h"
#include "CCLevelUpEventDispatcher.h"

namespace soomla {
    static CCScoreStorage *sInstance = nullptr;

#define DB_SCORE_KEY_PREFIX "soomla.levelup.scores."

    USING_NS_CC;

    CCScoreStorage *soomla::CCScoreStorage::getInstance() {
        if (!sInstance)
        {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) || (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
            sInstance = new CCNativeScoreStorage();
#else
            sInstance = new CCScoreStorage();
#endif
        }
        return sInstance;
    }

    void CCScoreStorage::setLatestScore(CCScore *score, double newValue) {
        const char *key = this->keyLatestScoreWithScoreId(score->getId()->getCString());
        const char *val = __String::createWithFormat("%f", newValue)->getCString();
        CCKeyValueStorage::getInstance()->setValue(key, val);

        CCLevelUpEventDispatcher::getInstance()->onLatestScoreChanged(score);
    }

    double CCScoreStorage::getLatestScore(CCScore *score) {
        const char *key = this->keyLatestScoreWithScoreId(score->getId()->getCString());
        const char *val = CCKeyValueStorage::getInstance()->getValue(key);
        return (val != NULL && strlen(val) > 0) ? __String::create(val)->doubleValue() : -1;
    }

    void CCScoreStorage::setRecordScore(CCScore *score, double newValue) {
        const char *key = this->keyRecordScoreWithScoreId(score->getId()->getCString());
        const char *val = __String::createWithFormat("%f", newValue)->getCString();
        CCKeyValueStorage::getInstance()->setValue(key, val);

        CCLevelUpEventDispatcher::getInstance()->onScoreRecordChanged(score);
    }

    double CCScoreStorage::getRecordScore(CCScore *score) {
        const char *key = this->keyRecordScoreWithScoreId(score->getId()->getCString());
        const char *val = CCKeyValueStorage::getInstance()->getValue(key);
        return (val != NULL && strlen(val) > 0) ? __String::create(val)->doubleValue() : -1;
    }

    char const *CCScoreStorage::keyLatestScoreWithScoreId(char const *scoreId) {
        return this->keyScoresWithScoreId(scoreId, "latest");
    }

    char const *CCScoreStorage::keyRecordScoreWithScoreId(char const *scoreId) {
        return this->keyScoresWithScoreId(scoreId, "record");
    }

    char const *CCScoreStorage::keyScoresWithScoreId(char const *scoreId, char const *postfix) {
        return __String::createWithFormat("%s%s.%s", DB_SCORE_KEY_PREFIX, scoreId, postfix)->getCString();
    }

    char const *CCScoreStorage::getKeyScorePrefix() {
        return DB_SCORE_KEY_PREFIX;
    }
}
