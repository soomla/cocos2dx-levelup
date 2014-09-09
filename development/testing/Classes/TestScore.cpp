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

#include "UnitTestPP.h"
#include "ScoreFixture.h"

using namespace UnitTest;

SUITE(TestScore) {
    
    TEST_FIXTURE(ScoreFixture, SanityDefaultValues) {
        CHECK_EQUAL(0.0, score->getStartValue()->getValue());
        CHECK_EQUAL(true, score->getHigherBetter()->getValue());
    }
    
    TEST_FIXTURE(ScoreFixture, scoreIncrementDecrementTest) {
        double initialScore = score->getTempScore();
        score->inc(10);
        double latestScore = score->getTempScore();
        CHECK_EQUAL(latestScore, initialScore + 10);
        CHECK(score->hasTempReached(latestScore));
        
        score->dec(5);
        latestScore = score->getTempScore();
        CHECK_EQUAL(latestScore, initialScore + 5);
        CHECK(score->hasTempReached(latestScore));
    }
    
    TEST_FIXTURE(ScoreFixture, scoreResetTest) {
        double startValue = score->getStartValue()->getValue();
        score->reset(false);
        CHECK_EQUAL(startValue, score->getStartValue()->getValue());
        
        score->inc(10);
        score->reset(false);
        CHECK_EQUAL(startValue, score->getStartValue()->getValue());
    }
    
    TEST_FIXTURE(ScoreFixture, hasTempReached) {
        double startValue = score->getStartValue()->getValue();
        score->reset(false);
        CHECK_EQUAL(startValue, score->getStartValue()->getValue());
        
        //        CCLOG("%f", score->getTempScore());
        score->inc(10);
        score->reset(false);
        CHECK_EQUAL(startValue, score->getStartValue()->getValue());
    }
    
    TEST_FIXTURE(ScoreFixture, scoreLatestAndRecord) {
        
        registerScoreWithWorld();
        
        double startValue = score->getStartValue()->getValue();
        score->inc(10);
        score->reset(true);
        CHECK_EQUAL(startValue, score->getStartValue()->getValue());
        CHECK_EQUAL(10, score->getRecord());
        
        // Record is now 10
        score->inc(15);
        score->reset(false);
        CHECK_EQUAL(10  , score->getLatest());
        CHECK_EQUAL(10, score->getRecord());
        
        // Record is now 10
        score->inc(15);
        score->reset(true);
        CHECK_EQUAL(15  , score->getLatest());
        CHECK_EQUAL(15, score->getRecord());
        
        // Record is now 15
        score->inc(10);
        score->reset(true);
        CHECK_EQUAL(10  , score->getLatest());
        CHECK_EQUAL(15, score->getRecord());
    }

    
    TEST_FIXTURE(ScoreFixture, scoreHasMethods) {
        
        registerScoreWithWorld();
        
        score->inc(10);
        CHECK(score->hasTempReached(5));
        CHECK(score->hasTempReached(10));
        CHECK(!score->hasTempReached(15));
        
        score->reset(false);
        score->inc(10);
        CHECK(!score->hasRecordReached(5));
        
        score->reset(true);
        CCLOG("Record: %f", score->getRecord());
        CHECK(score->hasRecordReached(5));
        CHECK(score->hasRecordReached(10));
        CHECK(!score->hasRecordReached(15));
        CHECK(!score->hasTempReached(5));
    }

}

