//
// Created by Shubin Fedor on 19/08/14.
// Copyright (c) 2014 SOOMLA. All rights reserved.
//

#include "CCScoreStorage.h"
#include "CCScore.h"
#include "CCLevelUpService.h"

namespace soomla {
    static CCScoreStorage *sInstance = NULL;

    CCScoreStorage *soomla::CCScoreStorage::getInstance() {
        if (!sInstance)
        {
            sInstance = new CCScoreStorage();
            sInstance->retain();
        }
        return sInstance;
    }

    void CCScoreStorage::setLatestScore(CCScore *score, double newValue) {
        CCLevelUpService::getInstance()->scoreSetLatestScore(score, newValue);
    }

    double CCScoreStorage::getLatestScore(CCScore *score) {
        return CCLevelUpService::getInstance()->scoreGetLatestScore(score);
    }

    void CCScoreStorage::setRecordScore(CCScore *score, double newValue) {
        CCLevelUpService::getInstance()->scoreSetRecordScore(score, newValue);
    }

    double CCScoreStorage::getRecordScore(CCScore *score) {
        return CCLevelUpService::getInstance()->scoreGetRecordScore(score);
    }
}
