//
// Created by Shubin Fedor on 19/08/14.
// Copyright (c) 2014 SOOMLA. All rights reserved.
//

#include "CCGateStorage.h"

namespace soomla {
    static CCGateStorage *sInstance = nullptr;

    CCGateStorage *soomla::CCGateStorage::getInstance() {
        if (!sInstance)
        {
            sInstance = new CCGateStorage();
            sInstance->retain();
        }
        return sInstance;
    }
}
