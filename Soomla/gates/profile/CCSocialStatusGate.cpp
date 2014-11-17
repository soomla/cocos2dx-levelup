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


#include "CCSocialStatusGate.h"
#include "CCGateStorage.h"
#include "CCSoomlaProfile.h"

namespace soomla {

#define TAG "SOOMLA SocialStatusGate"

    CCSocialStatusGate *CCSocialStatusGate::create(cocos2d::__String *id, CCProvider provider, cocos2d::__String *pageName) {
        CCSocialStatusGate *ret = new CCSocialStatusGate();
        if (ret->init(id, provider, pageName)) {
            ret->autorelease();
        }
        else {
            CC_SAFE_DELETE(ret);
        }

        return ret;
    }

    bool CCSocialStatusGate::init(cocos2d::__String *id, CCProvider provider, cocos2d::__String *pageName) {
        bool result = CCSocialActionGate::init(id, provider);
        if (result) {

            setStatus(pageName);

            return true;
        }
        return result;
    }

    bool CCSocialStatusGate::initWithDictionary(cocos2d::__Dictionary *dict) {
        bool result = CCGate::initWithDictionary(dict);
        if (result) {

            fillStatusFromDict(dict);

            return true;
        }
        return result;
    }

    cocos2d::__Dictionary *CCSocialStatusGate::toDictionary() {
        cocos2d::__Dictionary *dict = CCSoomlaEntity::toDictionary();

        putStatusToDict(dict);

        return dict;
    }

    const char *CCSocialStatusGate::getType() const {
        return CCLevelUpConsts::JSON_JSON_TYPE_SOCIAL_STATUS_GATE;
    }

    CCSocialStatusGate::~CCSocialStatusGate() {
        CC_SAFE_RELEASE(mStatus);
    }

    bool CCSocialStatusGate::openInner() {
        if (canOpen()) {

            CCSoomlaProfile::getInstance()->updateStatus(getProvider(), getId()->getCString(), getStatus()->getCString(), NULL, NULL);

            return true;
        }

        return false;
    }

}
