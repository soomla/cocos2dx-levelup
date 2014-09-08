//
// Created by Shubin Fedor on 22/08/14.
// Copyright (c) 2014 SOOMLA. All rights reserved.
//

#include "CCRangeScore.h"

namespace soomla {

    CCRangeScore *CCRangeScore::create(cocos2d::CCString *id, CCSRange *range) {
        return CCRangeScore::create(id, NULL, NULL, range);
    }

    CCRangeScore *CCRangeScore::create(cocos2d::CCString *id, cocos2d::CCString *name, cocos2d::CCBool *higherBetter, CCSRange *range) {
        CCRangeScore *ret = new CCRangeScore();
        if (ret->init(id, name, higherBetter, range)) {
            ret->autorelease();
        }
        else {
            CC_SAFE_DELETE(ret);
        }

        return ret;
    }

    bool CCRangeScore::init(cocos2d::CCString *id, cocos2d::CCString *name, cocos2d::CCBool *higherBetter, CCSRange *range) {
        bool result = CCScore::init(id, name, higherBetter);
        if (result) {
            setRange(range);
            return true;
        }
        return result;
    }

    bool CCRangeScore::initWithDictionary(cocos2d::CCDictionary *dict) {
        bool result = CCScore::initWithDictionary(dict);
        if (result) {
            cocos2d::CCDictionary *rangeDict = dynamic_cast<cocos2d::CCDictionary *>(
                    dict->objectForKey(CCLevelUpConsts::JSON_LU_SCORE_RANGE));
            if (rangeDict) {
                setRange(CCSRange::createWithDictionary(rangeDict));
            }
            return true;
        }
        return result;
    }

    cocos2d::CCDictionary *CCRangeScore::toDictionary() {
        cocos2d::CCDictionary *dict = CCScore::toDictionary();

        if (mRange) {
            dict->setObject(mRange->toDictionary(), CCLevelUpConsts::JSON_LU_SCORE_RANGE);
        }

        return dict;
    }


    void CCRangeScore::inc(double amount) {
        // Don't increment if we've hit the range's highest value
        if (mTempScore >= mRange->mHigh) {
            return;
        }

        if ((mTempScore+amount) > mRange->mHigh) {
            amount = mRange->mHigh - mTempScore;
        }

        CCScore::inc(amount);
    }

    void CCRangeScore::dec(double amount) {
        // Don't dencrement if we've hit the range's lowest value
        if (mTempScore <= mRange->mLow) {
            return;
        }

        if ((mTempScore-amount) < mRange->mLow) {
            amount = mTempScore - mRange->mLow;
        }

        CCScore::dec(amount);
    }

    void CCRangeScore::setTempScore(double score, bool onlyIfBetter) {
        if (score > mRange->mHigh) {
            score = mRange->mHigh;
        }
        if (score < mRange->mLow) {
            score = mRange->mLow;
        }

        CCScore::setTempScore(score, onlyIfBetter);
    }

    CCSRange *CCSRange::create(double low, double high) {
        CCSRange *ret = new CCSRange();
        if (ret->init(low, high)) {
            ret->autorelease();
        }
        else {
            CC_SAFE_DELETE(ret);
        }

        return ret;
    }

    bool CCSRange::init(double low, double high) {
        this->mLow = low;
        this->mHigh = high;
        return true;
    }

    bool CCSRange::initWithDictionary(cocos2d::CCDictionary *dict) {
        cocos2d::CCObject *ref;
        cocos2d::CCDouble *aDouble;

        ref = dict->objectForKey(CCLevelUpConsts::JSON_LU_SCORE_RANGE_LOW);
        aDouble = dynamic_cast<cocos2d::CCDouble *>(ref);
        if (aDouble) {
            this->mLow = aDouble->getValue();
        }
        else {
            this->mLow = 0.0;
        }

        ref = dict->objectForKey(CCLevelUpConsts::JSON_LU_SCORE_RANGE_HIGH);
        aDouble = dynamic_cast<cocos2d::CCDouble *>(ref);
        if (aDouble) {
            this->mHigh = aDouble->getValue();
        }
        else {
            this->mHigh = 0.0;
        }

        return true;
    }

    cocos2d::CCDictionary *CCSRange::toDictionary() {
        cocos2d::CCDictionary *dict = cocos2d::CCDictionary::create();

        dict->setObject(cocos2d::CCDouble::create(mLow), CCLevelUpConsts::JSON_LU_SCORE_RANGE_LOW);
        dict->setObject(cocos2d::CCDouble::create(mHigh), CCLevelUpConsts::JSON_LU_SCORE_RANGE_HIGH);

        return dict;
    }

    char const *CCRangeScore::getType() const {
        return CCLevelUpConsts::JSON_JSON_TYPE_RANGE_SCORE;
    }
}
