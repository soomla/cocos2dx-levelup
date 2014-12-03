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


#include "CCLevel.h"
#include "CCLevelStorage.h"
#include "CCSoomlaUtils.h"

namespace soomla {

    #define TAG "SOOMLA Level"

    USING_NS_CC;

    CCLevel *CCLevel::create(cocos2d::CCString *id) {
        CCLevel *ret = new CCLevel();
        if (ret->init(id)) {
            ret->autorelease();
        }
        else {
            CC_SAFE_DELETE(ret);
        }

        return ret;
    }

    CCLevel *CCLevel::create(cocos2d::CCString *id, CCGate *gate, cocos2d::CCDictionary *scores, cocos2d::CCArray *missions) {
        CCLevel *ret = new CCLevel();
        if (ret->init(id, gate, NULL, scores, missions)) {
            ret->autorelease();
        }
        else {
            CC_SAFE_DELETE(ret);
        }

        return ret;
    }

    CCLevel *CCLevel::create(cocos2d::CCString *id, CCGate *gate, cocos2d::CCDictionary *innerWorlds, cocos2d::CCDictionary *scores, cocos2d::CCArray *missions) {
        CCLevel *ret = new CCLevel();
        if (ret->init(id, gate, innerWorlds, scores, missions)) {
            ret->autorelease();
        }
        else {
            CC_SAFE_DELETE(ret);
        }

        return ret;
    }

    char const *CCLevel::getType() const {
        return CCLevelUpConsts::JSON_JSON_TYPE_LEVEL;
    }

    CCLevel::~CCLevel() {

    }

    int CCLevel::getTimesStarted() {
        return CCLevelStorage::getInstance()->getTimesStarted(this);
    }

    int CCLevel::getTimesPlayed() {
        return CCLevelStorage::getInstance()->getTimesPlayed(this);
    }

    long CCLevel::getSlowestDurationMillis() {
        return CCLevelStorage::getInstance()->getSlowestDurationMillis(this);
    }

    long CCLevel::getFastestDurationMillis() {
        return CCLevelStorage::getInstance()->getFastestDurationMillis(this);
    }

    bool CCLevel::start() {
        if (mState == Running) {
            CCSoomlaUtils::logError(TAG, "Can't start a level that is already running.");
            return false;
        }

        CCSoomlaUtils::logDebug(TAG,
                CCString::createWithFormat("Starting level with world id: %s", getId()->getCString())->getCString());

        if (!this->canStart()) {
            return false;
        }

        if (mState != Paused) {
            mElapsed = 0;
            CCLevelStorage::getInstance()->incTimesStarted(this);
        }

        mStartTime = getCurrentTimeMs();
        mState = Running;
        return true;
    }

    void CCLevel::pause() {
        if (mState != Running) {
            CCSoomlaUtils::logError(TAG, "Can't pause a level that is not running.");
            return;
        }

        long now = getCurrentTimeMs();
        mElapsed += now - mStartTime;
        mStartTime = 0;

        mState = Paused;
    }

    long CCLevel::getPlayDurationMillis() {

        long now = getCurrentTimeMs();
        long duration = mElapsed;
        if (mStartTime != 0) {
            duration += now - mStartTime;
        }

        return duration;
    }


    void CCLevel::end(bool completed) {

        // check end() called without matching start(),
        // i.e, the level is not running nor paused
        if(mState != Running && mState != Paused) {
            CCSoomlaUtils::logError(TAG, "end() called without prior start()! ignoring.");
            return;
        }

        mState = Ended;

        if (completed) {
            long duration = getPlayDurationMillis();

            // Calculate the slowest \ fastest durations of level play

            if (duration > getSlowestDurationMillis()) {
                CCLevelStorage::getInstance()->setSlowestDurationMillis(this, duration);
            }

            if (duration < getFastestDurationMillis()) {
                CCLevelStorage::getInstance()->setFastestDurationMillis(this, duration);
            }

            CCDictElement* el = NULL;
            CCScore *score;
            CCDictionary *scoresDict = getScores();
            CCDICT_FOREACH(scoresDict, el) {
                    score = (CCScore *) el->getObject();
                    score->reset(true); // resetting scores
                }

            // Count number of times this level was played
            CCLevelStorage::getInstance()->incTimesPlayed(this);

            setCompleted(true);
        }
        
        // reset timers
        mStartTime = 0;
        mElapsed = 0;
    }

    void CCLevel::restart(bool completed) {
        if (mState == Running || mState == Paused) {
            end(completed);
        }
        start();
    }

    void CCLevel::setCompleted(bool completed) {
        mState = Completed;
        CCWorld::setCompleted(completed);
    }

    long CCLevel::getCurrentTimeMs() {
        struct timeval now;
        gettimeofday(&now, NULL);

        return (long) (1000 * now.tv_sec + now.tv_usec / 1000.0f);
    }
}
