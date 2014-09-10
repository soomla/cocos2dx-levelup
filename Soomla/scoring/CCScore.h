//
// Created by Shubin Fedor on 21/08/14.
// Copyright (c) 2014 SOOMLA. All rights reserved.
//

#ifndef __CCScore_H_
#define __CCScore_H_

#include "CCSoomlaEntity.h"
#include "CCLevelUpConsts.h"

namespace soomla {

    class CCScore: public CCSoomlaEntity {
        SL_SYNTHESIZE_DOUBLE_RETAIN_WITH_DICT( mStartValue, StartValue, CCLevelUpConsts::JSON_LU_SCORE_STARTVAL);
        SL_SYNTHESIZE_RETAIN_WITH_DICT(cocos2d::__Bool *, mHigherBetter, HigherBetter, CCLevelUpConsts::JSON_LU_SCORE_HIGHBETTER);
    protected:
        double mTempScore;
    private:
        bool mScoreRecordReachedSent;
    public:
        CCScore(): mStartValue(NULL), mHigherBetter(NULL), mTempScore(0), mScoreRecordReachedSent(false) {
        }

        static CCScore *create(cocos2d::__String *id, cocos2d::__String *name = NULL, cocos2d::__Bool *higherBetter = NULL);

        SL_CREATE_WITH_DICTIONARY(CCScore);

        virtual bool init(cocos2d::__String *id, cocos2d::__String *name = NULL, cocos2d::__Bool *higherBetter = NULL);

        virtual bool initWithDictionary(cocos2d::__Dictionary* dict);


        virtual cocos2d::__Dictionary *toDictionary() override;

        virtual char const *getType() const;

        virtual void inc(double amount);
        virtual void dec(double amount);
        virtual void reset(bool save);
        virtual bool hasTempReached(double scoreVal);
        virtual bool hasRecordReached(double scoreVal);
        virtual void setTempScore(double score);
        virtual void setTempScore(double score, bool onlyIfBetter);
        virtual double getTempScore();
        virtual double getRecord();
        virtual double getLatest();
    protected:
        virtual void performSaveActions();

    private:
        bool hasScoreReached(double score1, double score2);
    };

}

#endif //__CCScore_H_
