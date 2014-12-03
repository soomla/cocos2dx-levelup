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



#include "CCSocialActionGate.h"
#include "CCLevelUpEventDispatcher.h"
#include "CCProfileEventDispatcher.h"

namespace soomla {

#define TAG "SOOMLA SocialActionGate"

    bool CCSocialActionGate::init(cocos2d::CCString *id, CCProvider provider) {
        bool result = CCGate::init(id, NULL);
        if (result) {
            setProvider(provider);
            return true;
        }
        return result;
    }

    bool CCSocialActionGate::initWithDictionary(cocos2d::CCDictionary *dict) {
        bool result = CCGate::initWithDictionary(dict);
        if (result) {
            fillProviderFromDict(dict);
            return true;
        }
        return result;
    }

    cocos2d::CCDictionary *CCSocialActionGate::toDictionary() {
        cocos2d::CCDictionary *dict = CCGate::toDictionary();

        putProviderToDict(dict);

        return dict;
    }

    bool CCSocialActionGate::canOpenInner() {
        return true;
    }

    void CCSocialActionGate::registerEvents() {
        if (!isOpen()) {
            setEventHandler(CCSocialActionGateEventHandler::create(this));
            CCProfileEventDispatcher::getInstance()->addEventHandler(getEventHandler());
        }
    }

    void CCSocialActionGate::unregisterEvents() {
        CCProfileEventHandler *eventHandler = getEventHandler();
        if (eventHandler) {
            CCProfileEventDispatcher::getInstance()->removeEventHandler(eventHandler);
            setEventHandler(NULL);
        }
    }

    CCSocialActionGate::~CCSocialActionGate() {
        CC_SAFE_RELEASE(mEventHandler);
    }


    void CCSocialActionGate::fillProviderFromDict(cocos2d::CCDictionary *dict) {
        CCString *val = dynamic_cast<CCString *>(dict->objectForKey(CCLevelUpConsts::JSON_LU_SOCIAL_PROVIDER));
        CC_ASSERT(val);
        setProvider(CCUserProfileUtils::providerStringToEnum(val));
    }

    void CCSocialActionGate::putProviderToDict(cocos2d::CCDictionary *dict) {
        dict->setObject(CCUserProfileUtils::providerEnumToString(getProvider()),
                CCLevelUpConsts::JSON_LU_SOCIAL_PROVIDER);
    }

    CCSocialActionGateEventHandler *CCSocialActionGateEventHandler::create(CCSocialActionGate *socialActionGate) {
        CCSocialActionGateEventHandler *ret = new CCSocialActionGateEventHandler();
        ret->autorelease();

        ret->mSocialActionGate = socialActionGate;

        return ret;
    }

    void CCSocialActionGateEventHandler::onSocialActionFinishedEvent(CCProvider provider, CCSocialActionType socialActionType, cocos2d::CCString *payload) {
        if (payload->isEqual(this->mSocialActionGate->getId())) {
            mSocialActionGate->forceOpen(true);
        }
    }
}
