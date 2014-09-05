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
#include "CCLevel.h"
#include "CCScheduleGate.h"
#include "CCLevelUpConsts.h"

using namespace UnitTest;

TEST_FIXTURE(InitialWorldFixture, SanityCanStart) {
    CCScheduleGate *gate = CCScheduleGate::create(__String::create("unopened_gate"),
                                                  CCSchedule::createAnyTimeOnce());
    initialWorld->setGate(gate);
    
    CHECK(!initialWorld->canStart());
    
    gate->forceOpen(true);
    
    CHECK(handler->checkEventFired(CCLevelUpConsts::EVENT_GATE_OPENED));
    CHECK(initialWorld->canStart());
}

TEST_FIXTURE(InitialWorldFixture, SanityAddInnerWorld) {
    CCLevel *level = CCLevel::create(__String::create("test_level"));
    initialWorld->addInnerWorld(level);
    
    __Dictionary *innerWorlds = initialWorld->getInnerWorldsMap();
    innerWorlds->objectForKey("test_level");
    CCWorld *innerLevel = dynamic_cast<CCWorld *>(innerWorlds->objectForKey(level->getId()->getCString()));
    
    CHECK_EQUAL(1, innerWorlds->count());
    CHECK_EQUAL(level, innerLevel);
}