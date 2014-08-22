//
// Created by Shubin Fedor on 22/08/14.
// Copyright (c) 2014 SOOMLA. All rights reserved.
//

#ifndef __ССRangeScore_H_
#define __ССRangeScore_H_

#include "CCScore.h"

namespace soomla {

    class CCSRange: public cocos2d::Ref {
    public:
        double mLow;
        double mHigh;
        CCSRange(): mLow(0.0), mHigh(0.0) {
        }

        static CCSRange *create(double low, double high);

        SL_CREATE_WITH_DICTIONARY(CCSRange);

        virtual bool init(double low, double high);

        virtual bool initWithDictionary(cocos2d::__Dictionary* dict);

        virtual cocos2d::__Dictionary *toDictionary();
    };

    class ССRangeScore: public CCScore {
        CC_SYNTHESIZE_RETAIN(CCSRange *, mRange, Range);
    public:
        ССRangeScore(): CCScore(), mRange(NULL) {
        }

        static ССRangeScore *create(cocos2d::__String *id, CCSRange *range);
        static ССRangeScore *create(cocos2d::__String *id, cocos2d::__String *name, cocos2d::__Bool *higherBetter, CCSRange *range);

        SL_CREATE_WITH_DICTIONARY(ССRangeScore);

        virtual bool init(cocos2d::__String *id, cocos2d::__String *name, cocos2d::__Bool *higherBetter, CCSRange *range);

        virtual bool initWithDictionary(cocos2d::__Dictionary* dict);

        virtual cocos2d::__Dictionary *toDictionary() override;

        virtual void inc(double amount) override;

        virtual void dec(double amount) override;

        virtual void setTempScore(double score, bool onlyIfBetter) override;
    };
}

#endif //__ССRangeScore_H_
