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


#include "CCGate.h"
#include "CCLevelUpConsts.h"
#include "CCGateStorage.h"

namespace soomla {

#define TAG "SOOMLA Gate"

    bool CCGate::init(cocos2d::__String *id, cocos2d::__String *name) {
        if (!name) {
            name = cocos2d::__String::create("");
        }
        bool result = CCSoomlaEntity::init(id, name, NULL);

        if (result) {
            eventsRegistered = false;

            return true;
        }

        return result;
    }

    bool CCGate::initWithDictionary(cocos2d::__Dictionary *dict) {
        bool result = CCSoomlaEntity::initWithDictionary(dict);

        if (result) {
            eventsRegistered = false;

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
    
    void CCGate::onAttached() {
        if (eventsRegistered) {
            return;
        }
        
        registerEvents();
        eventsRegistered = true;
    }
    
    void CCGate::onDetached() {
        if (!eventsRegistered) {
            return;
        }
        
        unregisterEvents();
        eventsRegistered = false;
    }
}
