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
 
#ifndef __TestingCoreEventHandler_H
#define __TestingCoreEventHandler_H

#include "cocos2d.h"
#include "BaseTestingEventHandler.h"
#include "CCReward.h"

class TestingCoreEventHandler : public BaseTestingEventHandler {
public:
    TestingCoreEventHandler();
    ~TestingCoreEventHandler();
    void onRewardGivenEvent(cocos2d::EventCustom *event);
    void onRewardTakenEvent(cocos2d::EventCustom *event);
};

#endif // __TestingCoreEventHandler_H
