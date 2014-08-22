//
// Created by Shubin Fedor on 22/08/14.
// Copyright (c) 2014 SOOMLA. All rights reserved.
//

#include "ССRangeScore.h"

namespace soomla {

    ССRangeScore *ССRangeScore::create(cocos2d::__String *id, CCSRange *range) {
        return ССRangeScore::create(id, NULL, NULL, range);
    }

    ССRangeScore *ССRangeScore::create(cocos2d::__String *id, cocos2d::__String *name, cocos2d::__Bool *higherBetter, CCSRange *range) {
        ССRangeScore *ret = new ССRangeScore();
        if (ret->init(id, name, higherBetter, range)) {
            ret->autorelease();
        }
        else {
            CC_SAFE_DELETE(ret);
        }

        return ret;
    }

    bool ССRangeScore::init(cocos2d::__String *id, cocos2d::__String *name, cocos2d::__Bool *higherBetter, CCSRange *range) {
        bool result = CCScore::init(id, name, higherBetter);
        if (result) {
            setRange(range);
            return true;
        }
        return result;
    }

    bool ССRangeScore::initWithDictionary(cocos2d::__Dictionary *dict) {
        bool result = CCScore::initWithDictionary(dict);
        if (result) {
            cocos2d::__Dictionary *rangeDict = dynamic_cast<cocos2d::__Dictionary *>(
                    dict->objectForKey(CCLevelUpConsts::JSON_LU_SCORE_RANGE));
            if (rangeDict) {
                setRange(CCSRange::createWithDictionary(rangeDict));
            }
            return true;
        }
        return result;
    }

    cocos2d::__Dictionary *ССRangeScore::toDictionary() {
        cocos2d::__Dictionary *dict = CCScore::toDictionary();

        if (mRange) {
            dict->setObject(mRange->toDictionary(), CCLevelUpConsts::JSON_LU_SCORE_RANGE);
        }

        return dict;
    }


    void ССRangeScore::inc(double amount) {
        // Don't increment if we've hit the range's highest value
        if (mTempScore >= mRange->mHigh) {
            return;
        }

        if ((mTempScore+amount) > mRange->mHigh) {
            amount = mRange->mHigh - mTempScore;
        }

        CCScore::inc(amount);
    }

    void ССRangeScore::dec(double amount) {
        // Don't dencrement if we've hit the range's lowest value
        if (mTempScore <= mRange->mLow) {
            return;
        }

        if ((mTempScore-amount) < mRange->mLow) {
            amount = mTempScore - mRange->mLow;
        }

        CCScore::dec(amount);
    }

    void ССRangeScore::setTempScore(double score, bool onlyIfBetter) {
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

    bool CCSRange::initWithDictionary(cocos2d::__Dictionary *dict) {
        cocos2d::Ref *ref;
        cocos2d::__Double *aDouble;

        ref = dict->objectForKey(CCLevelUpConsts::JSON_LU_SCORE_RANGE_LOW);
        aDouble = dynamic_cast<cocos2d::__Double *>(ref);
        if (aDouble) {
            this->mLow = aDouble->getValue();
        }
        else {
            this->mLow = 0.0;
        }

        ref = dict->objectForKey(CCLevelUpConsts::JSON_LU_SCORE_RANGE_HIGH);
        aDouble = dynamic_cast<cocos2d::__Double *>(ref);
        if (aDouble) {
            this->mHigh = aDouble->getValue();
        }
        else {
            this->mHigh = 0.0;
        }

        return true;
    }

    cocos2d::__Dictionary *CCSRange::toDictionary() {
        cocos2d::__Dictionary *dict = cocos2d::__Dictionary::create();

        dict->setObject(cocos2d::__Double::create(mLow), CCLevelUpConsts::JSON_LU_SCORE_RANGE_LOW);
        dict->setObject(cocos2d::__Double::create(mHigh), CCLevelUpConsts::JSON_LU_SCORE_RANGE_HIGH);

        return dict;
    }
}
