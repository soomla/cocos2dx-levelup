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



#ifndef __CCBalanceGate_H_
#define __CCBalanceGate_H_

#include "CCGate.h"
#include "CCLevelUpConsts.h"
#include "CCBalanceMission.h"
#include "CCVirtualCurrency.h"
#include "CCVirtualGood.h"

namespace soomla {

    /**
     A specific type of `Gate` that has an associated virtual item and a desired
     balance. The `Gate` opens once the item's balance reaches the desired
     balance.
     */
    class CCBalanceGate: public CCGate {
        SL_SYNTHESIZE_RETAIN_WITH_DICT(cocos2d::__String *, mAssociatedItemId, AssociatedItemId, CCLevelUpConsts::JSON_LU_ASSOCITEMID)
        SL_SYNTHESIZE_RETAIN_WITH_DICT(cocos2d::__Integer *, mDesiredBalance, DesiredBalance, CCLevelUpConsts::JSON_LU_DESIRED_BALANCE);
        CC_SYNTHESIZE(cocos2d::EventListener *, mCurrencyBalanceChangedListener, CurrencyBalanceChangedListener);
        CC_SYNTHESIZE(cocos2d::EventListener *, mGoodBalanceChangedListener, GoodBalanceChangedListener);

    public:
        CCBalanceGate(): CCGate(), mAssociatedItemId(NULL), mDesiredBalance(NULL), mCurrencyBalanceChangedListener(NULL),
            mGoodBalanceChangedListener(NULL) {}

        /**
         Creates an instance of `CCBalanceGate`.
         @param id ID.
         @param associatedItemId Associated item ID.
         @param desiredBalance Desired balance.
         */
        static CCBalanceGate *create(cocos2d::__String *id, cocos2d::__String *associatedItemId, cocos2d::__Integer *desiredBalance);

        SL_CREATE_WITH_DICTIONARY(CCBalanceGate);

        virtual bool init(cocos2d::__String *id, cocos2d::__String *associatedItemId, cocos2d::__Integer *desiredBalance);

        virtual bool initWithDictionary(cocos2d::__Dictionary* dict);

        virtual const char *getType() const;

        /**
         Converts this gate to a Dictionary.
         @param The Dictionary representation of this `CCBalanceGate`.
         */
        virtual cocos2d::__Dictionary *toDictionary();

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
        
        /**
         Opens this `Gate` if the currency-balance changed event causes the `Gate`'s
         criteria to be met.
         */
        virtual void onCurrencyBalanceChanged(cocos2d::EventCustom *event);
        
        /**
         Opens this `Gate` if the good-balance changed event causes the `Gate`'s
         criteria to be met.
         */
        virtual void onGoodBalanceChanged(cocos2d::EventCustom *event);
    private:
        void checkItemIdBalance(cocos2d::__String *itemId, int balance);;
    };
}

#endif //__CCBalanceGate_H_
