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
#include "InitialWorldFixture.h"
#include "CCScheduleGate.h"
#include "CCLevelUpConsts.h"
#include "CCCoreConsts.h"
#include "CCRecordMission.h"
#include "CCBadgeReward.h"
#include "CCLevel.h"
#include "CCWorldCompletionGate.h"
#include "CCLevelUp.h"
#include "CCLevelUpEventDispatcher.h"
#include "CCWorldCompletionMission.h"
#include "CCVirtualItemReward.h"
#include "MuffinRushAssets.h"

using namespace UnitTest;

SUITE(TestWorld)
{

    TEST_FIXTURE(InitialWorldFixture, SanityCanStart) {
        reinitialize();
        
        CCScheduleGate *gate = CCScheduleGate::create(__String::create("unopened_gate"),
                                                  CCSchedule::createAnyTimeOnce());
        initialWorld->setGate(gate);
    
        CHECK(!initialWorld->canStart());
    
        gate->forceOpen(true);
    
        CHECK(handler->checkEventFired(CCLevelUpConsts::EVENT_GATE_OPENED));
        CHECK(initialWorld->canStart());
    }

    TEST_FIXTURE(InitialWorldFixture, SanityAddInnerWorld) {
        reinitialize();
        
        CCLevel *level = CCLevel::create(__String::create("test_level"));
        initialWorld->addInnerWorld(level);
    
        __Dictionary *innerWorlds = initialWorld->getInnerWorldsMap();
        CCWorld *innerLevel = dynamic_cast<CCWorld *>(innerWorlds->objectForKey(level->getId()->getCString()));
    
        CHECK_EQUAL(1, innerWorlds->count());
        CHECK_EQUAL(level, innerLevel);
    }
    
    TEST_FIXTURE(InitialWorldFixture, SanityAddScore) {
        reinitialize();
        
        CCScore *score = CCScore::create(__String::create("test_score"));
        initialWorld->addScore(score);
        
        __Dictionary *innerScores = initialWorld->getScores();
        CCScore *innerScore = dynamic_cast<CCScore *>(innerScores->objectForKey(score->getId()->getCString()));
        
        CHECK_EQUAL(1, innerScores->count());
        CHECK_EQUAL(score, innerScore);
        
        CCScore *singleScore  = initialWorld->getSingleScore();
        CHECK_EQUAL(singleScore, innerScore);
    }
    
    TEST_FIXTURE(InitialWorldFixture, SanityResetScores) {
        reinitialize();
        
        CCScore *score = CCScore::create(__String::create("test_score"));
        initialWorld->addScore(score);
        
        initialWorld->incSingleScore(2.0);
        
        CHECK_EQUAL(2.0, score->getTempScore());
        
        initialWorld->resetScores(false);
        CHECK(score->getTempScore() != 2.0);
        
        initialWorld->setSingleScoreValue(2.0);
        
        CHECK_EQUAL(2.0, score->getTempScore());
        
        initialWorld->resetScores(true);
        CHECK(score->getTempScore() != 2.0);
        CHECK(score->getLatest() == 2.0);
    }
    
    TEST_FIXTURE(InitialWorldFixture, SanityComplete) {
        reinitialize();
        
        CCLevel *level = CCLevel::create(__String::create("test_level"));
        initialWorld->addInnerWorld(level);
        
        CHECK(!initialWorld->isCompleted());
        initialWorld->setCompleted(true);
        CHECK(initialWorld->isCompleted());
        CHECK(handler->checkEventFiredWith(CCLevelUpConsts::EVENT_WORLD_COMPLETED, initialWorld));
        
        CHECK(!level->isCompleted());
        CHECK(!handler->checkEventFiredWith(CCLevelUpConsts::EVENT_WORLD_COMPLETED, level));
    }
    
    TEST_FIXTURE(InitialWorldFixture, SanityCompleteRecursive) {
        reinitialize();
        
        CCLevel *level = CCLevel::create(__String::create("test_level"));
        initialWorld->addInnerWorld(level);
        
        CHECK(!initialWorld->isCompleted());
        CHECK(!level->isCompleted());
        
        initialWorld->setCompleted(true, true);
        CHECK(initialWorld->isCompleted());
        CHECK(handler->checkEventFiredWith(CCLevelUpConsts::EVENT_WORLD_COMPLETED, initialWorld));
        
        CHECK(level->isCompleted());
        CHECK(handler->checkEventFiredWith(CCLevelUpConsts::EVENT_WORLD_COMPLETED, level));
    }
    
    TEST_FIXTURE(InitialWorldFixture, FullSingleScore) {
        reinitialize();
        
        double initialRecord = 2.0;
        
        CCScore *score = CCScore::create(__String::create("test_score"));
        initialWorld->addScore(score);
        
        // Test increase score
        initialWorld->incSingleScore(initialRecord);
        
        // Not saved yet should be in temp
        CHECK_EQUAL(initialRecord, initialWorld->getSingleScore()->getTempScore());
        
        // Saving score
        initialWorld->resetScores(true);
        
        // Should be the new record and latest score
        CHECK_EQUAL(initialRecord, initialWorld->getSingleScore()->getRecord());
        CHECK_EQUAL(initialRecord, initialWorld->getSingleScore()->getLatest());
        CHECK(handler->checkEventFiredWith(CCLevelUpConsts::EVENT_SCORE_RECORD_CHANGED, score));
        
        // Create new lower score
        
        handler->clearEventStack();
        initialWorld->incSingleScore(3.0);
        // Testing decrease
        initialWorld->decSingleScore(2.0);
        // Saving lower score
        initialWorld->resetScores(true);
        
        // Record should still remain
        CHECK_EQUAL(initialRecord, initialWorld->getSingleScore()->getRecord());
        // Latest score is the new score
        CHECK_EQUAL(1.0, initialWorld->getSingleScore()->getLatest());
        // No record broken
        CHECK(!handler->checkEventFired(CCLevelUpConsts::EVENT_SCORE_RECORD_CHANGED));
        
        // Creating a new record
        double newRecord = 3.0;
        handler->clearEventStack();
        initialWorld->setSingleScoreValue(newRecord);
        initialWorld->resetScores(true);
        
        // Record was broken
        CHECK_EQUAL(newRecord, initialWorld->getSingleScore()->getRecord());
        CHECK_EQUAL(newRecord, initialWorld->getSingleScore()->getLatest());
        CHECK(handler->checkEventFiredWith(CCLevelUpConsts::EVENT_SCORE_RECORD_CHANGED, score));
    }
    
    TEST_FIXTURE(InitialWorldFixture, FullMultipleScores) {
        reinitialize();
        
        // Adding two differnt scores
        CCScore *score = CCScore::create(__String::create("test_score"));
        initialWorld->addScore(score);
        double scoreRecord = 2.0;
        
        CCScore *secondScore = CCScore::create(__String::create("test_score_2"));
        initialWorld->addScore(secondScore);
        double secondScoreRecord = 4.0;
        
        // Check increasing one does not affect the other
        initialWorld->incScore(score->getId()->getCString(), scoreRecord);
        CHECK_EQUAL(scoreRecord, score->getTempScore());
        CHECK(secondScore->getTempScore() != scoreRecord);
        
        // Save score
        initialWorld->resetScores(true);
        // New record was broken in one score
        CHECK_EQUAL(scoreRecord, score->getRecord());
        CHECK_EQUAL(scoreRecord, score->getLatest());
        CHECK(handler->checkEventFiredWith(CCLevelUpConsts::EVENT_SCORE_RECORD_CHANGED, score));
        
        // Clear to isolate next events
        handler->clearEventStack();
        
        // Check increasing second does not affect the first
        initialWorld->incScore(secondScore->getId()->getCString(), secondScoreRecord);
        CHECK_EQUAL(secondScoreRecord, secondScore->getTempScore());
        CHECK(score->getTempScore() != secondScoreRecord);
        
        // Save score
        initialWorld->resetScores(true);
        // New record was broken in second score
        CHECK_EQUAL(secondScoreRecord, secondScore->getRecord());
        CHECK_EQUAL(secondScoreRecord, secondScore->getLatest());
        CHECK(handler->checkEventFiredWith(CCLevelUpConsts::EVENT_SCORE_RECORD_CHANGED, secondScore));
        
        handler->clearEventStack();
        
        // Check breaking two scores in parallel
        
        double newScoreRecord = scoreRecord + 1.0;
        double newSecondScoreRecord = secondScoreRecord + 1.0;
        
        initialWorld->incScore(score->getId()->getCString(), newScoreRecord);
        initialWorld->incScore(secondScore->getId()->getCString(), newSecondScoreRecord);
        initialWorld->resetScores(true);
        
        CHECK_EQUAL(newScoreRecord, score->getRecord());
        CHECK_EQUAL(newSecondScoreRecord, secondScore->getRecord());
        CHECK(handler->checkEventFiredWith(CCLevelUpConsts::EVENT_SCORE_RECORD_CHANGED, secondScore));
        CHECK(handler->checkEventFiredWith(CCLevelUpConsts::EVENT_SCORE_RECORD_CHANGED, score));
        
        // Testing if getting the records table works
        __Dictionary *records = initialWorld->getRecordScores();
        __Double *scoreRecordInner = dynamic_cast<__Double *>(records->objectForKey(score->getId()->getCString()));
        __Double *secondScoreRecordInner = dynamic_cast<__Double *>(records->objectForKey(secondScore->getId()->getCString()));
        
        // Test if the records are correct
        CHECK(scoreRecordInner != NULL);
        CHECK(secondScoreRecordInner != NULL);
        
        CHECK_EQUAL(newScoreRecord, scoreRecordInner->getValue());
        CHECK_EQUAL(newSecondScoreRecord, secondScoreRecordInner->getValue());
        
        handler->clearEventStack();
        
        // Check applying new non-record scores
        
        double latestScore = 1.0;
        double latestSecondScore = 1.5;
        
        initialWorld->setScoreValue(score->getId()->getCString(), latestScore);
        initialWorld->setScoreValue(secondScore->getId()->getCString(), latestSecondScore);
        initialWorld->resetScores(true);
        
        // Test that the records remain and events were not sent
        CHECK_EQUAL(newScoreRecord, score->getRecord());
        CHECK_EQUAL(newSecondScoreRecord, secondScore->getRecord());
        CHECK(!handler->checkEventFiredWith(CCLevelUpConsts::EVENT_SCORE_RECORD_CHANGED, secondScore));
        CHECK(!handler->checkEventFiredWith(CCLevelUpConsts::EVENT_SCORE_RECORD_CHANGED, score));
        
        // Test the records table still with old records
        records = initialWorld->getRecordScores();
        scoreRecordInner = dynamic_cast<__Double *>(records->objectForKey(score->getId()->getCString()));
        secondScoreRecordInner = dynamic_cast<__Double *>(records->objectForKey(secondScore->getId()->getCString()));
        
        // Check if the latest scores are the new lower scores
        __Dictionary *latest = initialWorld->getLatestScores();
        __Double *scoreLatestInner = dynamic_cast<__Double *>(latest->objectForKey(score->getId()->getCString()));
        __Double *secondScoreLatestInner = dynamic_cast<__Double *>(latest->objectForKey(secondScore->getId()->getCString()));
        
        CHECK(scoreLatestInner != NULL);
        CHECK(secondScoreLatestInner != NULL);
        
        CHECK_EQUAL(latestScore, scoreLatestInner->getValue());
        CHECK_EQUAL(latestSecondScore, secondScoreLatestInner->getValue());
        
        CHECK_EQUAL(newScoreRecord, scoreRecordInner->getValue());
        CHECK_EQUAL(newSecondScoreRecord, secondScoreRecordInner->getValue());
    }
    
    TEST_FIXTURE(InitialWorldFixture, SanityAddMission) {
        reinitialize();
        
        CCScore *score = CCScore::create(__String::create("test_score"));
        initialWorld->addScore(score);
        
        CCRecordMission *mission = CCRecordMission::create(__String::create("test_record_mission"),
                                                           __String::create("Test Record Mission"),
                                                           score->getId(),
                                                           __Double::create(20.0));
        CHECK(!mission->isCompleted());
        CHECK(!mission->isAvailable());
        initialWorld->addMission(mission);
        
        __Array *missions = initialWorld->getMissions();
        bool found = false;
        Ref *object = NULL;
        CCARRAY_FOREACH(missions, object) {
            if (object == mission) {
                found = true;
            }
        }
        
        CHECK_EQUAL(1, missions->count());
        CHECK(found);
    }
    
    TEST_FIXTURE(InitialWorldFixture, SanityMission) {
        reinitialize();
        
        CCScore *score = CCScore::create(__String::create("test_score"));
        initialWorld->addScore(score);
        
        CCBadgeReward *reward = CCBadgeReward::create(__String::create("test_badge_reward"),
                                                      __String::create("Test Badge Reward"));
        
        CCRecordMission *mission = CCRecordMission::create(__String::create("test_record_mission"),
                                                           __String::create("Test Record Mission"),
                                                           __Array::create(reward, NULL),
                                                           score->getId(),
                                                           __Double::create(20.0));
        CHECK(!mission->isCompleted());
        initialWorld->addMission(mission);
        
        CHECK(!reward->isOwned());
        
        initialWorld->setSingleScoreValue(35.0);
        CHECK(!mission->isCompleted());
        
        initialWorld->resetScores(true);
        CHECK(mission->isCompleted());
        
        CHECK(handler->checkEventFiredWith(CCLevelUpConsts::EVENT_GATE_OPENED, mission->getGate()));
        CHECK(handler->checkEventFiredWith(CCLevelUpConsts::EVENT_MISSION_COMPLETED, mission));
        
        CHECK(coreHandler->checkEventFiredWithById(CCCoreConsts::EVENT_REWARD_GIVEN, reward));
        CHECK(reward->isOwned());
    }
    
    TEST_FIXTURE(InitialWorldFixture, SanityAssignReward) {
        reinitialize();
        
        CCBadgeReward *reward = CCBadgeReward::create(__String::create("test_badge_reward"),
                                                      __String::create("Test Badge Reward"));
        
        initialWorld->assignReward(reward);
        
        CHECK(coreHandler->checkEventFiredWithById(CCCoreConsts::EVENT_REWARD_GIVEN, reward));
        CHECK(reward->isOwned());
    }
    
    TEST_FIXTURE(InitialWorldFixture, SanityReplaceReward) {
        reinitialize();
        
        CCBadgeReward *reward = CCBadgeReward::create(__String::create("test_badge_reward"),
                                                      __String::create("Test Badge Reward"));
        
        CCBadgeReward *replaceReward = CCBadgeReward::create(__String::create("replace_test_badge_reward"),
                                                             __String::create("Replace Test Badge Reward"));
        
        // replacing takes LevelUp rewards dependency
        this->reinitialize(__Array::create(reward, replaceReward, NULL));
        
        initialWorld->assignReward(reward);
        
        CHECK(coreHandler->checkEventFiredWithById(CCCoreConsts::EVENT_REWARD_GIVEN, reward));
        CHECK(reward->isOwned());
        
        initialWorld->assignReward(replaceReward);
        
        CHECK(coreHandler->checkEventFiredWithById(CCCoreConsts::EVENT_REWARD_TAKEN, reward));
        CHECK(!reward->isOwned());
        CHECK(coreHandler->checkEventFiredWithById(CCCoreConsts::EVENT_REWARD_GIVEN, replaceReward));
        CHECK(replaceReward->isOwned());
    }
    
    TEST_FIXTURE(InitialWorldFixture, SanityBatchAddLevelsTemplateNull) {
        reinitialize();
        
        int levelCount = 5;
        
        initialWorld->batchAddLevelsWithTemplates(levelCount, NULL, (CCScore *)NULL, NULL);
        __Dictionary *innerWolds = initialWorld->getInnerWorldsMap();
        
        CHECK_EQUAL(levelCount, innerWolds->count());
        
        DictElement *element = NULL;
        CCDICT_FOREACH(innerWolds, element) {
            CCLevel *level = dynamic_cast<CCLevel *>(element->getObject());
            
            __Dictionary *innerMap = level->getInnerWorldsMap();
            CHECK_EQUAL(0, innerMap->count());
            
            CHECK(level->getGate() == NULL);
            
            __Array *missions = level->getMissions();
            CHECK_EQUAL(0, missions->count());
            
            __Dictionary *scores = level->getScores();
            CHECK_EQUAL(0, scores->count());
        }
    }
    
    TEST_FIXTURE(InitialWorldFixture, SanityBatchAddLevelsTemplatesNull) {
        reinitialize();
        
        int levelCount = 5;
        
        initialWorld->batchAddLevelsWithTemplates(levelCount, NULL, (CCScore *)NULL, NULL);
        __Dictionary *innerWolds = initialWorld->getInnerWorldsMap();
        
        CHECK_EQUAL(levelCount, innerWolds->count());
        
        DictElement *element = NULL;
        CCDICT_FOREACH(innerWolds, element) {
            CCLevel *level = dynamic_cast<CCLevel *>(element->getObject());
            
            __Dictionary *innerMap = level->getInnerWorldsMap();
            CHECK_EQUAL(0, innerMap->count());
            
            CHECK(level->getGate() == NULL);
            
            __Array *missions = level->getMissions();
            CHECK_EQUAL(0, missions->count());
            
            __Dictionary *scores = level->getScores();
            CHECK_EQUAL(0, scores->count());
        }
    }
    
    TEST_FIXTURE(InitialWorldFixture, SanityBatchAddDependentLevels) {
        reinitialize();
        
        int levelCount = 5;
        
        initialWorld->batchAddDependentLevelsWithTemplates(levelCount, (CCScore *)NULL, NULL);
        __Dictionary *innerWolds = initialWorld->getInnerWorldsMap();
        
        CHECK_EQUAL(levelCount, innerWolds->count());
        
        DictElement *element = NULL;
        int i = 0;
        CCDICT_FOREACH(innerWolds, element) {
            CCLevel *level = dynamic_cast<CCLevel *>(element->getObject());
            
            __Dictionary *innerMap = level->getInnerWorldsMap();
            CHECK_EQUAL(0, innerMap->count());
            
            __Array *missions = level->getMissions();
            CHECK_EQUAL(0, missions->count());
            
            __Dictionary *scores = level->getScores();
            CHECK_EQUAL(0, scores->count());
            
            if (i == 0) {
                CHECK(level->canStart());
            }
            else {
                CHECK(!level->canStart());
            }
            i++;
        }
        
        for (i = 0; i < levelCount - 1; i++) {
            CCWorld *innerWorld = initialWorld->getInnerWorldAt(i);
            CCWorld *nextWorld = initialWorld->getInnerWorldAt(i + 1);
            
            innerWorld->setCompleted(true);
            CHECK(nextWorld->canStart());
        }
    }
    
    TEST_FIXTURE(InitialWorldFixture, SanityBatchAddLevels) {
        reinitialize();
        
        int levelCount = 5;
        
        CCScore *testScore = CCScore::create(__String::create("test_score"));
        CCRecordMission *recordMission = CCRecordMission::create(__String::create("test_record_mission"),
                                                           __String::create("Test Record Mission"),
                                                           NULL,
                                                           testScore->getId(),
                                                           __Double::create(20.0));
        CCScheduleGate *testGate = CCScheduleGate::create(__String::create("unopened_gate"),
                                                      CCSchedule::createAnyTimeOnce());
        
        initialWorld->batchAddLevelsWithTemplates(levelCount, testGate, testScore, recordMission);
        __Dictionary *innerWolds = initialWorld->getInnerWorldsMap();
        
        CHECK_EQUAL(levelCount, innerWolds->count());
        
        DictElement *element = NULL;
        CCDICT_FOREACH(innerWolds, element) {
            CCLevel *level = dynamic_cast<CCLevel *>(element->getObject());
            
            __Dictionary *innerMap = level->getInnerWorldsMap();
            CHECK_EQUAL(0, innerMap->count());
            
            CHECK_EQUAL(testGate->getType(), level->getGate()->getType());
            CHECK(!testGate->getId()->isEqual(level->getId()));
            CHECK_EQUAL(testGate->isOpen(), level->getGate()->isOpen());
            CHECK(testGate != level->getGate());
            
            __Array *missions = level->getMissions();
            CHECK_EQUAL(1, missions->count());
            
            Ref *missionObject = NULL;
            CCARRAY_FOREACH(missions, missionObject) {
                CCMission *mission = dynamic_cast<CCMission *>(missionObject);
                CHECK_EQUAL(mission->getType(), recordMission->getType());
                CHECK(!mission->getId()->isEqual(recordMission->getId()));
                CHECK(mission != recordMission);
            }
            
            __Dictionary *scores = level->getScores();
            CHECK_EQUAL(1, scores->count());
            
            DictElement *scoreElement = NULL;
            CCDICT_FOREACH(scores, scoreElement) {
                CCScore *score = dynamic_cast<CCScore *>(scoreElement->getObject());
                CHECK_EQUAL(score->getType(), testScore->getType());
                CHECK(!score->getId()->isEqual(testScore->getId()));
                CHECK(score != testScore);
            }
        }
    }
}