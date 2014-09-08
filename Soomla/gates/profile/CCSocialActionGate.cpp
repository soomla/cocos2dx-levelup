//
// Created by Shubin Fedor on 20/08/14.
// Copyright (c) 2014 SOOMLA. All rights reserved.
//

#include "CCSocialActionGate.h"
#include "CCLevelUpEventDispatcher.h"
#include "CCLevelUp.h"
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


    void CCSocialActionGate::fillProviderFromDict(cocos2d::__Dictionary *dict) {
        __String *val = dynamic_cast<__String *>(dict->objectForKey(CCLevelUpConsts::JSON_LU_SOCIAL_PROVIDER));
        CC_ASSERT(val);
        setProvider(CCUserProfileUtils::providerStringToEnum(val));
    }

    void CCSocialActionGate::putProviderToDict(cocos2d::__Dictionary *dict) {
        dict->setObject(CCUserProfileUtils::providerEnumToString(getProvider()),
                CCLevelUpConsts::JSON_LU_SOCIAL_PROVIDER);
    }

    CCSocialActionGateEventHandler *CCSocialActionGateEventHandler::create(CCSocialActionGate *socialActionGate) {
        CCSocialActionGateEventHandler *ret = new CCSocialActionGateEventHandler();
        ret->autorelease();

        ret->mSocialActionGate = socialActionGate;

        return ret;
    }

    void CCSocialActionGateEventHandler::onSocialActionFinishedEvent(CCProvider provider, CCSocialActionType socialActionType) {
//        TODO: Add payload: if (payload == this.ID) {
            mSocialActionGate->forceOpen(true);
//        }
    }
}
