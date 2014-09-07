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
 
#ifndef __TestingLevelUpEventHandler_H
#define __TestingLevelUpEventHandler_H

#include "CCLevelUpEventHandler.h"
#include "cocos2d.h"
#include "CCLevelUpConsts.h"
#include "BaseTestingEventHandler.h"

class TestingLevelUpEventHandler : public soomla::CCLevelUpEventHandler, public BaseTestingEventHandler {
    
public:
    
    void onLevelUpInitialized();
    
    void onScoreRecordReached(soomla::CCScore *score);
    void onScoreRecordChanged(soomla::CCScore *score);
    
    void onGateOpened(soomla::CCGate *gate);
    
    void onMissionCompleted(soomla::CCMission *mission);
    void onMissionCompletionRevoked(soomla::CCMission *mission);
    
    void onWorldCompleted(soomla::CCWorld *world);
    void onWorldRewardAssigned(soomla::CCWorld *world);
    
    void onLevelStarted(soomla::CCLevel *level);
    void onLevelEnded(soomla::CCLevel *level);
};

#endif // __TestingLevelUpEventHandler_H
