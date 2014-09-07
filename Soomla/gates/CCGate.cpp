//
// Created by Shubin Fedor on 19/08/14.
// Copyright (c) 2014 SOOMLA. All rights reserved.
//

#include "CCGate.h"
#include "CCLevelUpConsts.h"
#include "CCGateStorage.h"
#include "cocos2d.h"

namespace soomla {

#define TAG "SOOMLA Gate"

    bool CCGate::init(cocos2d::CCString *id, cocos2d::CCString *name) {
        if (!name) {
            name = cocos2d::CCString::create("");
        }
        bool result = CCSoomlaEntity::init(id, name, NULL);

        if (result) {
            registerEvents();

            return true;
        }

        return result;
    }

    bool CCGate::initWithDictionary(cocos2d::CCDictionary *dict) {
        bool result = CCSoomlaEntity::initWithDictionary(dict);

        if (result) {
            registerEvents();

            return true;
        }

        return result;
    }

    char const *CCGate::getType() const {
        return CCLevelUpConsts::JSON_JSON_TYPE_GATE;
    }

    bool CCGate::open() {
        //  check in gate storage if it's already open
        if (CCGateStorage::getInstance()->isOpen(this)) {
            return true;
        }
        return openInner();
    }

    void CCGate::forceOpen(bool open) {
        if (isOpen() == open) {
            // if it's already open why open it again?
            return;
        }

        CCGateStorage::getInstance()->setOpen(this, open);
        if (open) {
            unregisterEvents();
        } else {
            // we can do this here ONLY becasue we check 'isOpen == open' a few lines above.
            registerEvents();
        }
    }

    bool CCGate::isOpen() {
        return CCGateStorage::getInstance()->isOpen(this);
    }

    bool CCGate::canOpen() {
        // check in gate storage if the gate is open
        if (CCGateStorage::getInstance()->isOpen(this)) {
            return false;
        }

        return canOpenInner();
    }

}
