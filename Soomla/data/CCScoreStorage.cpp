//
// Created by Shubin Fedor on 19/08/14.
// Copyright (c) 2014 SOOMLA. All rights reserved.
//

#include "CCScoreStorage.h"
#include "CCScore.h"

namespace soomla {
    static CCScoreStorage *sInstance = nullptr;

    CCScoreStorage *soomla::CCScoreStorage::getInstance() {
        if (!sInstance)
        {
            sInstance = new CCScoreStorage();
            sInstance->retain();
        }
        return sInstance;
    }
}
