//
// Created by Shubin Fedor on 19/08/14.
// Copyright (c) 2014 SOOMLA. All rights reserved.
//

#include "CCLevelStorage.h"
#include "CCWorld.h"
#include "CCLevel.h"

namespace soomla {
    static CCLevelStorage *sInstance = nullptr;

    CCLevelStorage *soomla::CCLevelStorage::getInstance() {
        if (!sInstance)
        {
            sInstance = new CCLevelStorage();
            sInstance->retain();
        }
        return sInstance;
    }

    int CCLevelStorage::getTimesStarted(CCLevel *level) {
        return 0;
    }
}
