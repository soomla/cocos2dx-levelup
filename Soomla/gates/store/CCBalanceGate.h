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


#ifndef __CCBalanceGate_H_
#define __CCBalanceGate_H_

#include "CCGate.h"
#include "CCLevelUpConsts.h"
#include "CCBalanceMission.h"
#include "CCVirtualCurrency.h"
#include "CCVirtualGood.h"
#include "CCSimpleStoreEventHandler.h"

namespace soomla {
    
    /**
     A specific type of `Gate` that has an associated virtual item and a desired
     balance. The `Gate` opens once the item's balance reaches the desired 
     balance.
     */
    class CCBalanceGate: public CCGate {
        friend class CCBalanceGateEventHandler;
        SL_SYNTHESIZE_RETAIN_WITH_DICT(cocos2d::CCString *, mAssociatedItemId, AssociatedItemId, CCLevelUpConsts::JSON_LU_ASSOCITEMID)
        SL_SYNTHESIZE_RETAIN_WITH_DICT(cocos2d::CCInteger *, mDesiredBalance, DesiredBalance, CCLevelUpConsts::JSON_LU_DESIRED_BALANCE);
        CC_SYNTHESIZE(CCStoreEventHandler *, mEventHandler, EventHandler);
    
    public:
        CCBalanceGate(): CCGate(), mAssociatedItemId(NULL), mDesiredBalance(NULL), mEventHandler(NULL) {
        }
        
        /**
         Creates an instance of `CCBalanceGate`.
         @param id ID.
         @param associatedItemId Associated item ID.
         @param desiredBalance Desired balance.
         */
        static CCBalanceGate *create(cocos2d::CCString *id, cocos2d::CCString *associatedItemId, cocos2d::CCInteger *desiredBalance);

        SL_CREATE_WITH_DICTIONARY(CCBalanceGate);

        virtual bool init(cocos2d::CCString *id, cocos2d::CCString *associatedItemId, cocos2d::CCInteger *desiredBalance);

        virtual bool initWithDictionary(cocos2d::CCDictionary* dict);

        virtual const char *getType() const;
        
        /**
         Converts this gate to a Dictionary.
         @param The Dictionary representation of this `CCBalanceGate`.
         */
        virtual cocos2d::CCDictionary *toDictionary();

        virtual ~CCBalanceGate();

    protected:
        
        /**
         Checks if this `Gate` meets its criteria for opening, by checking if 
         the item's balance has reached the desired balance.
         @return If the `Gate` meets the criteria to be opened returns `true`;
         otherwise `false`.
         */
        virtual bool canOpenInner();
        
        /**
         Opens the `Gate` if the criteria has been met.
         @return If the `Gate` is opened returns `true`; otherwise `false`.
         */
        virtual bool openInner();
        
        /**
         Registers relevant events: currency-balance and good-balance changed 
         events.
         */
        virtual void registerEvents();
        
        /**
         Unregisters relevant events: currency-balance and good-balance changed 
         events.
         */
        virtual void unregisterEvents();
    private:
        void checkItemIdBalance(cocos2d::CCString *itemId, int balance);;
    };

    class CCBalanceGateEventHandler: public CCSimpleStoreEventHandler {
        
    private:
        CCBalanceGate *mBalanceGate;
        
    public:
        
        /**
         Creates an instance of `CCBalanceGateEventHandler`. 
         @param balanceGate The `BalanceGate` that is associated with this 
         event handler.
         */
        static CCBalanceGateEventHandler *create(CCBalanceGate *balanceGate);
        
        /**
         Opens this `Gate` if the currency-balance changed event causes the `Gate`'s
         /// criteria to be met.
         @param virtualCurrency">Virtual currency whose balance changed.
         @param balance New balance.
         @param amountAdded Amount added.
         */
        virtual void onCurrencyBalanceChanged(CCVirtualCurrency *virtualCurrency, int balance, int amountAdded);
        
        /**
         Opens this `Gate` if the good-balance changed event causes the `Gate`'s
         criteria to be met.
         @param good Virtual good whose balance has changed.
         @param balance New balance.
         @param amountAdded Amount added.
         */
        virtual void onGoodBalanceChanged(CCVirtualGood *virtualGood, int balance, int amountAdded);
    };
}

#endif //__CCBalanceGate_H_
