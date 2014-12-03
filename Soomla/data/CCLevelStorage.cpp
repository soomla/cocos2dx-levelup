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
#include "CCLevelUpService.h"

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
        CCLevelUpService::getInstance()->levelSetSlowestDurationMillis(level, duration);
    }

    long CCLevelStorage::getSlowestDurationMillis(CCLevel *level) {
        return CCLevelUpService::getInstance()->levelGetSlowestDurationMillis(level);
    }

    void CCLevelStorage::setFastestDurationMillis(CCLevel *level, long duration) {
        CCLevelUpService::getInstance()->levelSetFastestDurationMillis(level, duration);
    }

    long CCLevelStorage::getFastestDurationMillis(CCLevel *level) {
        return CCLevelUpService::getInstance()->levelGetFastestDurationMillis(level);
    }

    int CCLevelStorage::incTimesStarted(CCLevel *level) {
        return CCLevelUpService::getInstance()->levelIncTimesStarted(level);
    }

    int CCLevelStorage::decTimesStarted(CCLevel *level) {
        return CCLevelUpService::getInstance()->levelDecTimesStarted(level);
    }

    int CCLevelStorage::getTimesStarted(CCLevel *level) {
        return CCLevelUpService::getInstance()->levelGetTimesStarted(level);
    }

    int CCLevelStorage::getTimesPlayed(CCLevel *level) {
        return CCLevelUpService::getInstance()->levelGetTimesPlayed(level);
    }

    int CCLevelStorage::incTimesPlayed(CCLevel *level) {
        return CCLevelUpService::getInstance()->levelIncTimesPlayed(level);
    }

    int CCLevelStorage::decTimesPlayed(CCLevel *level) {
        return CCLevelUpService::getInstance()->levelDecTimesPlayed(level);
    }
}
