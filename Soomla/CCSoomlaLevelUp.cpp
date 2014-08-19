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

// Created by Fedor Shubin on 5/20/13.

#include "CCSoomlaLevelUp.h"
#include "CCNdkBridge.h"

using namespace cocos2d;

namespace soomla {
    #define TAG "SOOMLA SoomlaStore"

    USING_NS_CC;

    static CCSoomlaLevelUp *s_SharedSoomlaStore = NULL;

    CCSoomlaLevelUp *CCSoomlaLevelUp::getInstance() {
        if (!s_SharedSoomlaStore)
        {
            s_SharedSoomlaStore = new CCSoomlaLevelUp();
            s_SharedSoomlaStore->retain();
        }
        return s_SharedSoomlaStore;
    }

    CCSoomlaLevelUp::CCSoomlaLevelUp() {
    }

    CCSoomlaLevelUp::~CCSoomlaLevelUp() {

    }

    void CCSoomlaLevelUp::buyMarketItem(const char *productId, const char *payload, CCError **error) {
        __Dictionary *params = __Dictionary::create();
        params->setObject(__String::create("CCSoomlaLevelUp::buyMarketItem"), "method");
        params->setObject(__String::create(productId), "productId");
        params->setObject(__String::create(payload), "payload");
        CCNdkBridge::callNative (params, error);
    }

    void CCSoomlaLevelUp::restoreTransactions() {
        __Dictionary *params = __Dictionary::create();
        params->setObject(__String::create("CCSoomlaLevelUp::restoreTransactions"), "method");
        CCNdkBridge::callNative (params, NULL);
    }

    void CCSoomlaLevelUp::refreshInventory() {
        __Dictionary *params = __Dictionary::create();
        params->setObject(__String::create("CCSoomlaLevelUp::refreshInventory"), "method");
        CCNdkBridge::callNative (params, NULL);
    }

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    bool CCSoomlaLevelUp::transactionsAlreadyRestored() {
        __Dictionary *params = __Dictionary::create();
        params->setObject(__String::create("CCSoomlaLevelUp::transactionsAlreadyRestored"), "method");
        __Dictionary *retParams = (__Dictionary *) CCNdkBridge::callNative (params, NULL);
        __Bool *retValue = (__Bool *) retParams->objectForKey("return");
        return retValue->getValue();
    }

    void CCSoomlaLevelUp::refreshMarketItemsDetails(CCError **error) {
        __Dictionary *params = __Dictionary::create();
        params->setObject(__String::create("CCSoomlaLevelUp::refreshMarketItemsDetails"), "method");
        CCNdkBridge::callNative (params, error);
    }
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    void CCSoomlaStore::startIabServiceInBg() {
        __Dictionary *params = __Dictionary::create();
        params->setObject(__String::create("CCSoomlaStore::startIabServiceInBg"), "method");
        CCNdkBridge::callNative (params, NULL);
    }

    void CCSoomlaStore::stopIabServiceInBg() {
        __Dictionary *params = __Dictionary::create();
        params->setObject(__String::create("CCSoomlaStore::stopIabServiceInBg"), "method");
        CCNdkBridge::callNative (params, NULL);
    }
#endif
}
