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


#include "CCScore.h"
#include "CCScoreStorage.h"
#include "CCLevelUpEventDispatcher.h"

#define TAG "SOOMLA Score"

namespace soomla {

    USING_NS_CC;

    CCScore *CCScore::create(cocos2d::__String *id, cocos2d::__String *name, cocos2d::__Bool *higherBetter) {
        CCScore *ret = new CCScore();
        if (ret->init(id, name, higherBetter)) {
            ret->autorelease();
        }
        else {
            CC_SAFE_DELETE(ret);
        }

        return ret;
    }

    bool CCScore::init(cocos2d::__String *id, cocos2d::__String *name, cocos2d::__Bool *higherBetter) {
        bool result = CCSoomlaEntity::init(id, name);
        if (result) {
            setStartValue(__Double::create(0));
            setHigherBetter(higherBetter ? higherBetter : __Bool::create(true));
            return true;
        }
        return result;
    }


    bool CCScore::initWithDictionary(cocos2d::__Dictionary *dict) {
        bool result = CCSoomlaEntity::initWithDictionary(dict);
        if (result) {
            fillStartValueFromDict(dict);
            fillHigherBetterFromDict(dict);
            return true;
        }
        return result;
    }

    cocos2d::__Dictionary *CCScore::toDictionary() {
        __Dictionary *dict = CCSoomlaEntity::toDictionary();

        putStartValueToDict(dict);
        putHigherBetterToDict(dict);

        return dict;
    }

    char const *CCScore::getType() const {
        return CCLevelUpConsts::JSON_JSON_TYPE_SCORE;
    }


    void CCScore::inc(double amount) {
        setTempScore(mTempScore + amount);
    }

    void CCScore::dec(double amount) {
        setTempScore(mTempScore - amount);
    }

    void CCScore::reset(bool save) {
        if (save) {
            CCScoreStorage::getInstance()->setLatestScore(this, mTempScore);
            
            double record = CCScoreStorage::getInstance()->getRecordScore(this);
            if ((record == -1) || hasTempReached(record)) {
                CCScoreStorage::getInstance()->setRecordScore(this, mTempScore);
                mScoreRecordReachedSent = false;
            }

            performSaveActions();
        }

        setTempScore(mStartValue->getValue());
    }


    bool CCScore::hasTempReached(double scoreVal) {
        return hasScoreReached(mTempScore, scoreVal);
    }

    bool CCScore::hasRecordReached(double scoreVal) {
        double record = CCScoreStorage::getInstance()->getRecordScore(this);
        return hasScoreReached(record, scoreVal);
    }

    void CCScore::performSaveActions() {
    }


    bool CCScore::hasScoreReached(double score1, double score2) {
        return this->mHigherBetter->getValue() ?
                (score1 >= score2) :
                (score1 <= score2);
    }


    void CCScore::setTempScore(double score) {
        setTempScore(score, false);
    }

    void CCScore::setTempScore(double score, bool onlyIfBetter) {
        if (onlyIfBetter && !hasScoreReached(score, mTempScore)) {
            return;
        }
        if (!mScoreRecordReachedSent && hasScoreReached(score, mTempScore)) {
            CCLevelUpEventDispatcher::getInstance()->onScoreRecordReached(this);
            mScoreRecordReachedSent = true;
        }
        mTempScore = score;
    }

    double CCScore::getTempScore() {
        return mTempScore;
    }

    double CCScore::getRecord() {
        return CCScoreStorage::getInstance()->getRecordScore(this);
    }

    double CCScore::getLatest() {
        return CCScoreStorage::getInstance()->getLatestScore(this);
    }
}
