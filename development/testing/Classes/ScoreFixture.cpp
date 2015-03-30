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

#include "ScoreFixture.h"
#include "CCKeyValueStorage.h"
#include "CCWorld.h"
#include "CCSoomlaLevelUp.h"

ScoreFixture::ScoreFixture() {
    score = CCScore::create(__String::create("test_score"));
    CCKeyValueStorage::getInstance()->purge();
}

ScoreFixture::~ScoreFixture() {
}

/**
 Utility method
 */
void ScoreFixture::printDictionary() {
    CCLOG("======== SCORE ========");
    CCLOG("itemId: %s", score->getId()->getCString());
    CCLOG("jsonType: %s", score->getType());
    CCLOG("startValue: %f", score->getStartValue()->getValue());
    CCLOG("higherBetter: %d", score->getHigherBetter()->getValue());
}

/**
 Mental note: The score can't live in isolation,
 there has to be a created world has this score associated to it.
 */
void ScoreFixture::registerScoreWithWorld() {
    CCWorld *world = CCWorld::create(__String::create("initial_world"),
                                     NULL,
                                     __Dictionary::create(),
                                     __Dictionary::create(),
                                     __Array::create());
    world->addScore(score);
    CCSoomlaLevelUp::getInstance()->initialize(world, __Array::create());
};

