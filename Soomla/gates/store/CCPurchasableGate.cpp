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


#include "CCPurchasableGate.h"
#include "CCStoreEventDispatcher.h"
#include "CCStoreInventory.h"
#include "CCSoomlaUtils.h"

namespace soomla {

    USING_NS_CC;

#define TAG "SOOMLA PurchasableGate"

    CCPurchasableGate *CCPurchasableGate::create(cocos2d::CCString *id, cocos2d::CCString *associatedItemId) {
        CCPurchasableGate *ret = new CCPurchasableGate();
        if (ret->init(id, associatedItemId)) {
            ret->autorelease();
        }
        else {
            CC_SAFE_DELETE(ret);
        }

        return ret;
    }

    bool CCPurchasableGate::init(cocos2d::CCString *id, cocos2d::CCString *associatedItemId) {
        bool result = CCGate::init(id, NULL);
        if (result) {
            setAssociatedItemId(associatedItemId);
            return true;
        }
        return result;
    }

    bool CCPurchasableGate::initWithDictionary(cocos2d::CCDictionary *dict) {
        bool result = CCGate::initWithDictionary(dict);
        if (result) {
            fillAssociatedItemIdFromDict(dict);
            return true;
        }
        return result;
    }

    const char *CCPurchasableGate::getType() const {
        return CCLevelUpConsts::JSON_JSON_TYPE_PURCHASABLE_GATE;
    }

    cocos2d::CCDictionary *CCPurchasableGate::toDictionary() {
        cocos2d::CCDictionary *dict = CCGate::toDictionary();

        putAssociatedItemIdToDict(dict);

        return dict;
    }

    CCPurchasableGate::~CCPurchasableGate() {
        CC_SAFE_RELEASE(mAssociatedItemId);
    }


    void CCPurchasableGate::registerEvents() {
        if (!isOpen()) {
            setEventHandler(CCPurchasableGateEventHanler::create(this));
            CCStoreEventDispatcher::getInstance()->addEventHandler(getEventHandler());
        }
    }

    void CCPurchasableGate::unregisterEvents() {
        CCStoreEventHandler *eventHandler = getEventHandler();
        if (eventHandler) {
            CCStoreEventDispatcher::getInstance()->removeEventHandler(eventHandler);
            setEventHandler(NULL);
        }
    }

    bool CCPurchasableGate::canOpenInner() {
        return true;
    }

    bool CCPurchasableGate::openInner() {
        CCError *error = NULL;
        CCStoreInventory::sharedStoreInventory()->buyItem(mAssociatedItemId->getCString(), this->getId()->getCString(), &error);
        if (error) {
            if (error->getInfo())
            CCSoomlaUtils::logError(TAG, CCString::createWithFormat("Cannot purchase this item. itemId: %s",
                    mAssociatedItemId->getCString())->getCString());
            CCSoomlaUtils::logError(TAG, error->getInfo());
            return false;
        }
        return true;
    }

    CCPurchasableGateEventHanler *CCPurchasableGateEventHanler::create(CCPurchasableGate *purchasableGate) {
        CCPurchasableGateEventHanler *ret = new CCPurchasableGateEventHanler();
        ret->autorelease();

        ret->mPurchasableGate = purchasableGate;

        return ret;
    }

    void CCPurchasableGateEventHanler::onItemPurchased(CCPurchasableVirtualItem *purchasableVirtualItem, cocos2d::CCString *payload) {
        if ((purchasableVirtualItem->getItemId()->compare(mPurchasableGate->getAssociatedItemId()->getCString()) == 0)
                && payload->isEqual(mPurchasableGate->getId())) {
            mPurchasableGate->forceOpen(true);
        }
    }
}
