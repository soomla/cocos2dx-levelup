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

#include "CCNativeLevelStorage.h"
#include "CCLevelUpBridge.h"

namespace soomla {

    void CCNativeLevelStorage::setSlowestDurationMillis(CCLevel *level, long duration) {
        CCLevelUpBridge::getInstance()->levelSetSlowestDurationMillis(level, duration);
    }

    long CCNativeLevelStorage::getSlowestDurationMillis(CCLevel *level) {
        return CCLevelUpBridge::getInstance()->levelGetSlowestDurationMillis(level);
    }

    void CCNativeLevelStorage::setFastestDurationMillis(CCLevel *level, long duration) {
        CCLevelUpBridge::getInstance()->levelSetFastestDurationMillis(level, duration);
    }

    long CCNativeLevelStorage::getFastestDurationMillis(CCLevel *level) {
        return CCLevelUpBridge::getInstance()->levelGetFastestDurationMillis(level);
    }

    int CCNativeLevelStorage::incTimesStarted(CCLevel *level) {
        return CCLevelUpBridge::getInstance()->levelIncTimesStarted(level);
    }

    int CCNativeLevelStorage::decTimesStarted(CCLevel *level) {
        return CCLevelUpBridge::getInstance()->levelDecTimesStarted(level);
    }

    int CCNativeLevelStorage::getTimesStarted(CCLevel *level) {
        return CCLevelUpBridge::getInstance()->levelGetTimesStarted(level);
    }

    int CCNativeLevelStorage::getTimesPlayed(CCLevel *level) {
        return CCLevelUpBridge::getInstance()->levelGetTimesPlayed(level);
    }

    int CCNativeLevelStorage::incTimesPlayed(CCLevel *level) {
        return CCLevelUpBridge::getInstance()->levelIncTimesPlayed(level);
    }

    int CCNativeLevelStorage::decTimesPlayed(CCLevel *level) {
        return CCLevelUpBridge::getInstance()->levelDecTimesPlayed(level);
    }
    
    int CCNativeLevelStorage::getTimesCompleted(CCLevel *level) {
        return CCLevelUpBridge::getInstance()->levelGetTimesCompleted(level);
    }
    
    int CCNativeLevelStorage::incTimesCompleted(CCLevel *level) {
        return CCLevelUpBridge::getInstance()->levelIncTimesCompleted(level);
    }
    
    int CCNativeLevelStorage::decTimesCompleted(CCLevel *level) {
        return CCLevelUpBridge::getInstance()->levelDecTimesCompleted(level);
    }
}
