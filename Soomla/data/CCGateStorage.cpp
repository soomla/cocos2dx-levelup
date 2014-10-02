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
