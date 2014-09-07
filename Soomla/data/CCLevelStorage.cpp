//
// Created by Shubin Fedor on 19/08/14.
// Copyright (c) 2014 SOOMLA. All rights reserved.
//

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
