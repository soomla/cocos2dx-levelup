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

#include "CCLevelStorage.h"
#include "CCLevel.h"
#include "CCLevelUpBridge.h"

namespace soomla {
    static CCLevelStorage *sInstance = NULL;

    CCLevelStorage *soomla::CCLevelStorage::getInstance() {
        if (!sInstance)
        {
            sInstance = new CCLevelStorage();
            sInstance->retain();
        }
        return sInstance;
    }

    void CCLevelStorage::setSlowestDurationMillis(CCLevel *level, long duration) {
        CCLevelUpBridge::getInstance()->levelSetSlowestDurationMillis(level, duration);
    }

    long CCLevelStorage::getSlowestDurationMillis(CCLevel *level) {
        return CCLevelUpBridge::getInstance()->levelGetSlowestDurationMillis(level);
    }

    void CCLevelStorage::setFastestDurationMillis(CCLevel *level, long duration) {
        CCLevelUpBridge::getInstance()->levelSetFastestDurationMillis(level, duration);
    }

    long CCLevelStorage::getFastestDurationMillis(CCLevel *level) {
        return CCLevelUpBridge::getInstance()->levelGetFastestDurationMillis(level);
    }

    int CCLevelStorage::incTimesStarted(CCLevel *level) {
        return CCLevelUpBridge::getInstance()->levelIncTimesStarted(level);
    }

    int CCLevelStorage::decTimesStarted(CCLevel *level) {
        return CCLevelUpBridge::getInstance()->levelDecTimesStarted(level);
    }

    int CCLevelStorage::getTimesStarted(CCLevel *level) {
        return CCLevelUpBridge::getInstance()->levelGetTimesStarted(level);
    }

    int CCLevelStorage::getTimesPlayed(CCLevel *level) {
        return CCLevelUpBridge::getInstance()->levelGetTimesPlayed(level);
    }

    int CCLevelStorage::incTimesPlayed(CCLevel *level) {
        return CCLevelUpBridge::getInstance()->levelIncTimesPlayed(level);
    }

    int CCLevelStorage::decTimesPlayed(CCLevel *level) {
        return CCLevelUpBridge::getInstance()->levelDecTimesPlayed(level);
    }
    
    int CCLevelStorage::getTimesCompleted(CCLevel *level) {
        return CCLevelUpBridge::getInstance()->levelGetTimesCompleted(level);
    }
    
    int CCLevelStorage::incTimesCompleted(CCLevel *level) {
        return CCLevelUpBridge::getInstance()->levelIncTimesCompleted(level);
    }
    
    int CCLevelStorage::decTimesCompleted(CCLevel *level) {
        return CCLevelUpBridge::getInstance()->levelDecTimesCompleted(level);
    }
}
