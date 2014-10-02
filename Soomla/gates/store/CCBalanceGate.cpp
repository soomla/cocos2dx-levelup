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
// Created by Shubin Fedor on 20/08/14.
// Copyright (c) 2014 SOOMLA. All rights reserved.
//

#include "CCBalanceGate.h"
#include "CCStoreInventory.h"
#include "CCSoomlaUtils.h"
#include "CCStoreEventDispatcher.h"

namespace soomla {

#define TAG "SOOMLA BalanceGate"

    soomla::CCBalanceGate *soomla::CCBalanceGate::create(cocos2d::CCString *id, cocos2d::CCString *associatedItemId, cocos2d::CCInteger *desiredBalance) {
        CCBalanceGate *ret = new CCBalanceGate();
        if (ret->init(id, associatedItemId, desiredBalance)) {
            ret->autorelease();
        }
        else {
            CC_SAFE_DELETE(ret);
        }

        return ret;
    }

    bool soomla::CCBalanceGate::init(cocos2d::CCString *id, cocos2d::CCString *associatedItemId, cocos2d::CCInteger *desiredBalance) {
        bool result = CCGate::init(id, NULL);
        if (result) {
            setAssociatedItemId(associatedItemId);
            setDesiredBalance(desiredBalance);
            return true;
        }
        return result;
    }

    bool soomla::CCBalanceGate::initWithDictionary(cocos2d::CCDictionary *dict) {
        bool result = CCGate::initWithDictionary(dict);
        if (result) {
            fillAssociatedItemIdFromDict(dict);
            fillDesiredBalanceFromDict(dict);
            return true;
        }
        return result;
    }

    const char *soomla::CCBalanceGate::getType() const {
        return CCLevelUpConsts::JSON_JSON_TYPE_BALANCE_GATE;
    }

    cocos2d::CCDictionary *soomla::CCBalanceGate::toDictionary() {
        cocos2d::CCDictionary *dict = CCGate::toDictionary();

        putAssociatedItemIdToDict(dict);
        putDesiredBalanceToDict(dict);

        return dict;
    }

    soomla::CCBalanceGate::~CCBalanceGate() {
        CC_SAFE_RELEASE(mAssociatedItemId);
        CC_SAFE_RELEASE(mDesiredBalance);
        CC_SAFE_RELEASE(mEventHandler);
    }

    bool CCBalanceGate::canOpenInner() {
        CCError *error = NULL;
        int balance = CCStoreInventory::sharedStoreInventory()->getItemBalance(mAssociatedItemId->getCString(), &error);
        if (error) {
            CCSoomlaUtils::logError(TAG, cocos2d::CCString::createWithFormat(
                    "(canOpenInner) Couldn't find itemId. itemId: %s", mAssociatedItemId->getCString())->getCString());
            CCSoomlaUtils::logError(TAG, error->getInfo());
            return false;
        }
        return (balance >= mDesiredBalance->getValue());
    }


    bool CCBalanceGate::openInner() {
        if (canOpen()) {
            // There's nothing to do here... If the DesiredBalance was reached then the gate is just open.
            forceOpen(true);
            return true;
        }

        return false;
    }


    void CCBalanceGate::registerEvents() {
        if (!isOpen()) {
            setEventHandler(CCBalanceGateEventHandler::create(this));
            CCStoreEventDispatcher::getInstance()->addEventHandler(getEventHandler());
        }
    }

    void CCBalanceGate::unregisterEvents() {
        CCStoreEventHandler *eventHandler = getEventHandler();
        if (eventHandler) {
            CCStoreEventDispatcher::getInstance()->removeEventHandler(eventHandler);
            setEventHandler(NULL);
        }
    }

    void CCBalanceGate::checkItemIdBalance(cocos2d::CCString *itemId, int balance) {
        if (mAssociatedItemId->compare(itemId->getCString()) == 0 && balance >= mDesiredBalance->getValue()) {
            forceOpen(true);
        }
    }

    CCBalanceGateEventHandler *CCBalanceGateEventHandler::create(CCBalanceGate *balanceGate) {
        CCBalanceGateEventHandler *ret = new CCBalanceGateEventHandler();
        ret->autorelease();

        ret->mBalanceGate = balanceGate;

        return ret;
    }

    void CCBalanceGateEventHandler::onCurrencyBalanceChanged(CCVirtualCurrency *virtualCurrency, int balance, int amountAdded) {
        mBalanceGate->checkItemIdBalance(virtualCurrency->getItemId(), balance);
    }

    void CCBalanceGateEventHandler::onGoodBalanceChanged(CCVirtualGood *virtualGood, int balance, int amountAdded) {
        mBalanceGate->checkItemIdBalance(virtualGood->getItemId(), balance);
    }

}
