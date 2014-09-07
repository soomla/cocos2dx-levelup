//
// Created by Shubin Fedor on 19/08/14.
// Copyright (c) 2014 SOOMLA. All rights reserved.
//

#include "CCGateStorage.h"
#include "CCLevelUpService.h"

namespace soomla {
    static CCGateStorage *sInstance = NULL;

    CCGateStorage *soomla::CCGateStorage::getInstance() {
        if (!sInstance)
        {
            sInstance = new CCGateStorage();
            sInstance->retain();
        }
        return sInstance;
    }

    bool CCGateStorage::isOpen(CCGate *gate) {
        return CCLevelUpService::getInstance()->gateIsOpen(gate);
    }

    void CCGateStorage::setOpen(CCGate *gate, bool open) {
        setOpen(gate, open, true);
    }

    void CCGateStorage::setOpen(CCGate *gate, bool open, bool notify) {
        CCLevelUpService::getInstance()->gateSetOpen(gate, open, notify);
    }
}
