/*
 Copyright (C) 2012-2014 ; Inc.

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
#include "CCLevelUp.h"
#include "CCBadgeReward.h"
#include "CCLevel.h"
#include "CCWorldCompletionGate.h"

SUITE(TestLevelUp) {
    
    TEST_FIXTURE(InitialWorldFixture, SanityInitialize) {
        reinitialize();
        
        CHECK_EQUAL(initialWorld, CCLevelUp::getInstance()->getWorld(initialWorld->getId()->getCString()));
        // crashes
        // CHECK(CCLevelUp::getInstance()->getReward("reward") == NULL);
    }
    
    TEST_FIXTURE(InitialWorldFixture, SanityInitializeRewards) {
        CCBadgeReward *reward = CCBadgeReward::create(__String::create("test_badge_reward"),
                                                      __String::create("Test Badge Reward"));
        
        CCBadgeReward *secondReward = CCBadgeReward::create(__String::create("rsecond_test_badge_reward"),
                                                             __String::create("Second Test Badge Reward"));
        
        reinitialize(__Array::create(reward, secondReward, NULL));
        
        CHECK_EQUAL(initialWorld, CCLevelUp::getInstance()->getWorld(initialWorld->getId()->getCString()));
        CHECK_EQUAL(reward, CCLevelUp::getInstance()->getReward(reward->getId()->getCString()));
        CHECK_EQUAL(secondReward, CCLevelUp::getInstance()->getReward(secondReward->getId()->getCString()));
    }
    
    TEST_FIXTURE(InitialWorldFixture, TestGetWorld) {
        CCLevel *level = CCLevel::create(__String::create("test_level"));
        CCLevel *innerLevel = CCLevel::create(__String::create("test_inner_level"));
        level->addInnerWorld(innerLevel);
        initialWorld->addInnerWorld(level);
        
        reinitialize();
        
        CHECK_EQUAL(initialWorld, CCLevelUp::getInstance()->getWorld(initialWorld->getId()->getCString()));
        CHECK_EQUAL(level, CCLevelUp::getInstance()->getWorld(level->getId()->getCString()));
        CHECK_EQUAL(innerLevel, CCLevelUp::getInstance()->getWorld(innerLevel->getId()->getCString()));
    }
    
    TEST_FIXTURE(InitialWorldFixture, TestGetScore) {
        CCLevel *level = CCLevel::create(__String::create("test_level"));
        CCScore *score = CCScore::create(__String::create("test_score"));
        CCScore *innerScore = CCScore::create(__String::create("test_inner_score"));
        
        level->addScore(innerScore);
        initialWorld->addInnerWorld(level);
        initialWorld->addScore(score);
        
        reinitialize();
        
        CHECK_EQUAL(score, CCLevelUp::getInstance()->getScore(score->getId()->getCString()));
        CHECK_EQUAL(innerScore, CCLevelUp::getInstance()->getScore(innerScore->getId()->getCString()));
    }
    
    TEST_FIXTURE(InitialWorldFixture, TestGetGate) {
        
        CCLevel *level = CCLevel::create(__String::create("test_level"));
        CCWorldCompletionGate *gate = CCWorldCompletionGate::create(__String::create("test_level_complete_gate"),
                                                                    level->getId());
        CCLevel *secondLevel = CCLevel::create(__String::create("test_second_level"),
                                               gate, NULL, NULL);
        
        initialWorld->addInnerWorld(level);
        initialWorld->addInnerWorld(secondLevel);
        
        reinitialize();
        
        CHECK_EQUAL(gate, CCLevelUp::getInstance()->getGate(gate->getId()->getCString()));
    }
}