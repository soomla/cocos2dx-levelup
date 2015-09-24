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


#include "CCGateStorage.h"
#include "CCNativeGateStorage.h"
#include "CCKeyValueStorage.h"
#include "CCLevelUpEventDispatcher.h"

namespace soomla {

    USING_NS_CC;

#define DB_GATE_KEY_PREFIX "soomla.levelup.gates."

    static CCGateStorage *sInstance = nullptr;

    CCGateStorage *soomla::CCGateStorage::getInstance() {
        if (!sInstance)
        {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) || (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
            sInstance = new CCNativeGateStorage();
#else
            sInstance = new CCGateStorage();
#endif
        }
        return sInstance;
    }

    bool CCGateStorage::isOpen(CCGate *gate) {
        const char *key = this->keyGateOpen(gate->getId()->getCString());
        const char *val = CCKeyValueStorage::getInstance()->getValue(key);
        return (val != NULL && strlen(val) > 0);
    }

    void CCGateStorage::setOpen(CCGate *gate, bool open) {
        setOpen(gate, open, true);
    }

    void CCGateStorage::setOpen(CCGate *gate, bool open, bool notify) {
        const char *key = this->keyGateOpen(gate->getId()->getCString());

        if (open) {
            CCKeyValueStorage::getInstance()->setValue(key, "yes");

            if (notify) {
                CCLevelUpEventDispatcher::getInstance()->onGateOpened(gate);
            }
        } else {
            CCKeyValueStorage::getInstance()->deleteKeyValue(key);

            if (notify) {
                CCLevelUpEventDispatcher::getInstance()->onGateClosed(gate);
            }
        }
    }

    const char *CCGateStorage::keyGatesWithGateId(const char *gateId, const char *postfix) {
        return __String::createWithFormat("%s%s.%s", DB_GATE_KEY_PREFIX, gateId, postfix)->getCString();
    }

    const char *CCGateStorage::keyGateOpen(const char *gateId) {
        return this->keyGatesWithGateId(gateId, "open");
    }

    char const *CCGateStorage::getKeyGatePrefix() {
        return DB_GATE_KEY_PREFIX;
    }
}
