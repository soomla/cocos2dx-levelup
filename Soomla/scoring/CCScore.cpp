//
// Created by Shubin Fedor on 21/08/14.
// Copyright (c) 2014 SOOMLA. All rights reserved.
//

#include "CCScore.h"
#include "CCScoreStorage.h"
#include "CCLevelUpEventDispatcher.h"

#define TAG "SOOMLA Score"

namespace soomla {

    USING_NS_CC;

    CCScore *CCScore::create(cocos2d::CCString *id, cocos2d::CCString *name, cocos2d::CCBool *higherBetter) {
        CCScore *ret = new CCScore();
        if (ret->init(id, name, higherBetter)) {
            ret->autorelease();
        }
        else {
            CC_SAFE_DELETE(ret);
        }

        return ret;
    }

    bool CCScore::init(cocos2d::CCString *id, cocos2d::CCString *name, cocos2d::CCBool *higherBetter) {
        bool result = CCSoomlaEntity::init(id, name);
        if (result) {
            setStartValue(CCDouble::create(0));
            setHigherBetter(higherBetter ? higherBetter : CCBool::create(true));
            return true;
        }
        return result;
    }


    bool CCScore::initWithDictionary(cocos2d::CCDictionary *dict) {
        bool result = CCSoomlaEntity::initWithDictionary(dict);
        if (result) {
            fillStartValueFromDict(dict);
            fillHigherBetterFromDict(dict);
            return true;
        }
        return result;
    }

    cocos2d::CCDictionary *CCScore::toDictionary() {
        CCDictionary *dict = CCSoomlaEntity::toDictionary();

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
            double record = CCScoreStorage::getInstance()->getRecordScore(this);
            if (hasTempReached(record)) {
                CCScoreStorage::getInstance()->setRecordScore(this, mTempScore);
                mScoreRecordReachedSent = false;
            }

            performSaveActions();

            CCScoreStorage::getInstance()->setLatestScore(this, mTempScore);
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
