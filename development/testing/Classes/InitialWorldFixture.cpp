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

#include "InitialWorldFixture.h"
#include "CCLevelUp.h"
#include "CCLevelUpEventDispatcher.h"
#include "CCCoreEventDispatcher.h"
#include "CCKeyValueStorage.h"

InitialWorldFixture::InitialWorldFixture() {
    initialWorld = CCWorld::create(__String::create("initial_world"),
                                   NULL,
                                   __Dictionary::create(),
                                   __Dictionary::create(),
                                   __Array::create());
    
    handler = new TestingLevelUpEventHandler();
    CCLevelUpEventDispatcher::getInstance()->addEventHandler(handler);
    coreHandler = new TestingCoreEventHandler();
    CCCoreEventDispatcher::getInstance()->addEventHandler(coreHandler);
    
    CCKeyValueStorage::getInstance()->purge();
}

InitialWorldFixture::~InitialWorldFixture() {
    CCLevelUpEventDispatcher::getInstance()->purge();
    CCCoreEventDispatcher::getInstance()->purge();
}

void InitialWorldFixture::reinitialize(__Array *rewards) {
    CCLevelUp::getInstance()->initialize(initialWorld, rewards);
}