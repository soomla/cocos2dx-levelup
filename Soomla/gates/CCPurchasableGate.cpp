//
// Created by Shubin Fedor on 20/08/14.
// Copyright (c) 2014 SOOMLA. All rights reserved.
//

#include "CCPurchasableGate.h"
#include "CCStoreEventDispatcher.h"
#include "CCStoreInventory.h"
#include "CCSoomlaUtils.h"

namespace soomla {

    USING_NS_CC;

#define TAG "SOOMLA PurchasableGate"

    CCPurchasableGate *CCPurchasableGate::create(cocos2d::__String *id, cocos2d::__String *associatedItemId) {
        CCPurchasableGate *ret = new CCPurchasableGate();
        if (ret->init(id, associatedItemId)) {
            ret->autorelease();
        }
        else {
            CC_SAFE_DELETE(ret);
        }

        return ret;
    }

    bool CCPurchasableGate::init(cocos2d::__String *id, cocos2d::__String *associatedItemId) {
        bool result = CCGate::init(id, NULL);
        if (result) {
            setAssociatedItemId(associatedItemId);
            return true;
        }
        return result;
    }

    bool CCPurchasableGate::initWithDictionary(cocos2d::__Dictionary *dict) {
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

    cocos2d::__Dictionary *CCPurchasableGate::toDictionary() {
        cocos2d::__Dictionary *dict = CCGate::toDictionary();

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
            CCSoomlaUtils::logError(TAG, __String::createWithFormat("Cannot purchase this item. itemId: %s",
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

    void CCPurchasableGateEventHanler::onItemPurchased(CCPurchasableVirtualItem *purchasableVirtualItem) {
        // TODO: Implement payload onItemPurchased
        if (purchasableVirtualItem->getItemId()->compare(mPurchasableGate->getAssociatedItemId()->getCString()) == 0) {
//                && payload == this._id) {
            mPurchasableGate->forceOpen(true);
        }
    }
}

