//
// Created by Shubin Fedor on 22/08/14.
// Copyright (c) 2014 SOOMLA. All rights reserved.
//

#ifndef __CCRangeScore_H_
#define __CCRangeScore_H_

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

    class CCRangeScore : public CCScore {
        CC_SYNTHESIZE_RETAIN(CCSRange *, mRange, Range);
    public:
        CCRangeScore(): CCScore(), mRange(NULL) {
        }

        static CCRangeScore *create(cocos2d::__String *id, CCSRange *range);
        static CCRangeScore *create(cocos2d::__String *id, cocos2d::__String *name, cocos2d::__Bool *higherBetter, CCSRange *range);

        SL_CREATE_WITH_DICTIONARY(CCRangeScore);

        virtual bool init(cocos2d::__String *id, cocos2d::__String *name, cocos2d::__Bool *higherBetter, CCSRange *range);

        virtual bool initWithDictionary(cocos2d::__Dictionary* dict);

        virtual cocos2d::__Dictionary *toDictionary() override;

        virtual void inc(double amount) override;

        virtual void dec(double amount) override;

        virtual void setTempScore(double score, bool onlyIfBetter) override;

        char const *getType() const;
    };
}

#endif //__CCRangeScore_H_
