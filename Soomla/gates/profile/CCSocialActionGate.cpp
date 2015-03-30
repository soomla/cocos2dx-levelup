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

    bool CCSocialActionGate::init(cocos2d::__String *id, CCProvider provider) {
        bool result = CCGate::init(id, NULL);
        if (result) {
            setProvider(provider);
            return true;
        }
        return result;
    }

    bool CCSocialActionGate::initWithDictionary(cocos2d::__Dictionary *dict) {
        bool result = CCGate::initWithDictionary(dict);
        if (result) {
            fillProviderFromDict(dict);
            return true;
        }
        return result;
    }

    cocos2d::__Dictionary *CCSocialActionGate::toDictionary() {
        cocos2d::__Dictionary *dict = CCGate::toDictionary();

        putProviderToDict(dict);

        return dict;
    }

    bool CCSocialActionGate::canOpenInner() {
        return true;
    }

    void CCSocialActionGate::registerEvents() {
        if (!isOpen()) {
            setEventListener(Director::getInstance()->getEventDispatcher()->addCustomEventListener(CCProfileConsts::EVENT_SOCIAL_ACTION_FINISHED,
                                                                                                  CC_CALLBACK_1(CCSocialActionGate::onSocialActionFinishedEvent, this)));
        }
    }

    void CCSocialActionGate::unregisterEvents() {
        if (mEventListener) {
            Director::getInstance()->getEventDispatcher()->removeEventListener(mEventListener);
            setEventListener(NULL);
        }
    }
    
    void CCSocialActionGate::onSocialActionFinishedEvent(cocos2d::EventCustom *event) {
        __Dictionary *eventData = (__Dictionary *)event->getUserData();
        __String *payload = dynamic_cast<__String *>(eventData->objectForKey(CCProfileConsts::DICT_ELEMENT_PAYLOAD));
        CC_ASSERT(payload);
        
        if (payload->isEqual(getId())) {
            forceOpen(true);
        }
    }

    CCSocialActionGate::~CCSocialActionGate() {
        CC_SAFE_RELEASE(mEventListener);
    }


    void CCSocialActionGate::fillProviderFromDict(cocos2d::__Dictionary *dict) {
        __String *val = dynamic_cast<__String *>(dict->objectForKey(CCLevelUpConsts::JSON_LU_SOCIAL_PROVIDER));
        CC_ASSERT(val);
        setProvider(CCUserProfileUtils::providerStringToEnum(val));
    }

    void CCSocialActionGate::putProviderToDict(cocos2d::__Dictionary *dict) {
        dict->setObject(CCUserProfileUtils::providerEnumToString(getProvider()),
                CCLevelUpConsts::JSON_LU_SOCIAL_PROVIDER);
    }
}
