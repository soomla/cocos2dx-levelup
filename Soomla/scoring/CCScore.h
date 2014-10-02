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

//
// Created by Shubin Fedor on 21/08/14.
// Copyright (c) 2014 SOOMLA. All rights reserved.
//

#ifndef __CCScore_H_
#define __CCScore_H_

#include "CCSoomlaEntity.h"
#include "CCLevelUpConsts.h"

namespace soomla {

    /**
     Represents a score in the game. A simple game usually has one generic 
     numeric score which grows as the user progresses in the game. A game can 
     also have multiple scores for different aspects such as time, speed, 
     points etc. A `Score` can be ascending in nature such as regular points 
     (higher is better) or can be descending such as time-to-complete level 
     (lower is better).
     */
    class CCScore: public CCSoomlaEntity {

        SL_SYNTHESIZE_DOUBLE_RETAIN_WITH_DICT(mStartValue, StartValue, CCLevelUpConsts::JSON_LU_SCORE_STARTVAL);
        SL_SYNTHESIZE_RETAIN_WITH_DICT(cocos2d::CCBool *, mHigherBetter, HigherBetter, CCLevelUpConsts::JSON_LU_SCORE_HIGHBETTER);
    
    protected:
        double mTempScore;
    
    private:
        bool mScoreRecordReachedSent;
    
    public:
        CCScore(): mStartValue(NULL), mHigherBetter(NULL), mTempScore(0), mScoreRecordReachedSent(false) {
        }
        
        /**
         Creates an instance of `CCScore`.
         @param id ID of this `CCScore`.
         @param name Name of this `CCScore`.
         @param higherBetter If `true` then the higher the score the better.
         */
        static CCScore *create(cocos2d::CCString *id, cocos2d::CCString *name = NULL, cocos2d::CCBool *higherBetter = NULL);

        SL_CREATE_WITH_DICTIONARY(CCScore);

        virtual bool init(cocos2d::CCString *id, cocos2d::CCString *name = NULL, cocos2d::CCBool *higherBetter = NULL);

        virtual bool initWithDictionary(cocos2d::CCDictionary* dict);
        
        /**
         Converts this `CCScore` into a Dictionary.
         @return The Dictionary representation of this `CCScore`.
         */
        virtual cocos2d::CCDictionary *toDictionary() override;

        virtual char const *getType() const;
        
        /**
         Increases this `Score` by the given amount.
         @param amount Amount to increase by.
         */
        virtual void inc(double amount);
        
        /**
         Decreases this `Score` by the given amount.
         @param amount Amount to decrease by.
         */
        virtual void dec(double amount);
        
        /**
         Saves the current `Score` (and record if reached) and resets the score
         to its initial value. Use this method for example when a user restarts 
         a level with a fresh score of 0.
         @param save If set to `true` save.
         */
        virtual void reset(bool save);
        
        /**
         Checks if the `Score` in the current game session has reached the given 
         value.
         @return If this `Score` has reached the given scoreVal returns `true`;
         otherwise `false`.
         @param scoreVal numeric score value.
         */
        virtual bool hasTempReached(double scoreVal);
        
        /**
         Determines if this `Score` has reached a record value of the given 
         `scoreVal`.
         @return If this score has reached the given record returns `true`;
         otherwise `false`.
         @param scoreVal numeric score value.
         */
        virtual bool hasRecordReached(double scoreVal);
        
        /**
         Sets the temp score to be the given `score`, and checks if the given 
         `score` breaks a record - if so, triggers the score-record-reached 
         event.
         @param score Score to compare to temp score.
         */
        virtual void setTempScore(double score, bool onlyIfBetter);
        virtual void setTempScore(double score);
        
        /**
         Retrieves the temp `Score`.
         @return The temp `Score`.
         */
        virtual double getTempScore();
        
        /**
         Retrieves the record of this `Score`.
         @return The record.
         */
        virtual double getRecord();
        
        /**
         Retrieves the most recently saved value of this `Score`.
         @return The latest score.
         */
        virtual double getLatest();
        
    protected:
        
        /**
         `Score` can sometimes have additional actions associated with 
         reaching/saving it. Override this method to add specific `Score` 
         behavior.
         */
        virtual void performSaveActions();

    private:
        bool hasScoreReached(double score1, double score2);
    };

}

#endif //__CCScore_H_
