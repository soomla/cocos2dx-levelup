//
// Created by Shubin Fedor on 19/08/14.
// Copyright (c) 2014 SOOMLA. All rights reserved.
//

#include "CCMissionStorage.h"

namespace soomla {
    static CCMissionStorage *sInstance = nullptr;

    CCMissionStorage *soomla::CCMissionStorage::getInstance() {
        if (!sInstance)
        {
            sInstance = new CCMissionStorage();
            sInstance->retain();
        }
        return sInstance;
    }
}
