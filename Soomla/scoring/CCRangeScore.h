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

#ifndef __CCRangeScore_H_
#define __CCRangeScore_H_

#include "CCScore.h"

namespace soomla {
    
    /**
     Each `CCRangeScore` has a range (`CCSRange`).
     */
    class CCSRange: public cocos2d::CCObject {
    public:
        double mLow;
        double mHigh;
        CCSRange(): mLow(0.0), mHigh(0.0) {
        }

        static CCSRange *create(double low, double high);

        SL_CREATE_WITH_DICTIONARY(CCSRange);

        virtual bool init(double low, double high);

        virtual bool initWithDictionary(cocos2d::CCDictionary* dict);

        virtual cocos2d::CCDictionary *toDictionary();
    };


    /**
     A specific type of `Score` that has an associated range. The `Score`'s
     value can be only inside the range of values. For example, a shooting
     `Score` can be on a scale of 10 to 100 according to the user's performance
     in the game.
     */
    class CCRangeScore : public CCScore {
        CC_SYNTHESIZE_RETAIN(CCSRange *, mRange, Range);
    public:
        CCRangeScore(): CCScore(), mRange(NULL) {
        }

        /**
         Creates an instance of `CCRangeScore`.
         @param id ID.
         @param range Range that the `Score` value must reside in.
         */
        static CCRangeScore *create(cocos2d::CCString *id, CCSRange *range);

        /**
         Creates an instance of `CCRangeScore`.
         @param id ID of this `CCRangeScore`.
         @param name Name of this `CCRangeScore`.
         @param higherBetter If set to `true` then higher is better.
         @param range Range that the `Score` value must reside in.
         */
        static CCRangeScore *create(cocos2d::CCString *id, cocos2d::CCString *name, cocos2d::CCBool *higherBetter, CCSRange *range);

        SL_CREATE_WITH_DICTIONARY(CCRangeScore);

        virtual bool init(cocos2d::CCString *id, cocos2d::CCString *name, cocos2d::CCBool *higherBetter, CCSRange *range);

        virtual bool initWithDictionary(cocos2d::CCDictionary* dict);

        /**
         Converts this `Score` to a Dictionary.
         @return The Dictionary representation of this `CCRangeScore`.
         */
        virtual cocos2d::CCDictionary *toDictionary();

        /**
         Increases this `Score` by the given amount after checking that it will
         stay within the range.
         @param amount Amount to increase by.
         */
        virtual void inc(double amount);

        /**
         Decreases this `Score` by the given amount after checking that the
         `Score` will stay within the range.
         @param amount Amount to decrease by.
         */
        virtual void dec(double amount);

        /**
         Sets the temp score to be the given `score`, after making sure that the
         it will stay within the range.
         @param score Score.
         @param onlyIfBetter If `Score` is better than the given `score` then
         this value should be `true`.
         */
        virtual void setTempScore(double score, bool onlyIfBetter);

        char const *getType() const;
    };
}

#endif //__CCRangeScore_H_
