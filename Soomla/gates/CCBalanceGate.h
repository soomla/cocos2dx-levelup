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
    class CCBalanceGate: public CCGate {
        friend class CCBalanceGateEventHandler;
        SL_SYNTHESIZE_RETAIN_WITH_DICT(cocos2d::CCString *, mAssociatedItemId, AssociatedItemId, CCLevelUpConsts::JSON_LU_ASSOCITEMID)
        SL_SYNTHESIZE_RETAIN_WITH_DICT(cocos2d::CCInteger *, mDesiredBalance, DesiredBalance, CCLevelUpConsts::JSON_LU_DESIRED_BALANCE);
        CC_SYNTHESIZE(CCStoreEventHandler *, mEventHandler, EventHandler);
    public:
        CCBalanceGate(): CCGate(), mAssociatedItemId(NULL), mDesiredBalance(NULL), mEventHandler(NULL) {
        }

        static CCBalanceGate *create(cocos2d::CCString *id, cocos2d::CCString *associatedItemId, cocos2d::CCInteger *desiredBalance);

        SL_CREATE_WITH_DICTIONARY(CCBalanceGate);

        virtual bool init(cocos2d::CCString *id, cocos2d::CCString *associatedItemId, cocos2d::CCInteger *desiredBalance);

        virtual bool initWithDictionary(cocos2d::CCDictionary* dict);

        virtual const char *getType() const;

        virtual cocos2d::CCDictionary *toDictionary();

        virtual ~CCBalanceGate();

    protected:
        virtual bool canOpenInner();

        virtual bool openInner();

        virtual void registerEvents();

        virtual void unregisterEvents();
    private:
        void checkItemIdBalance(cocos2d::CCString *itemId, int balance);;
    };

    class CCBalanceGateEventHandler: public CCSimpleStoreEventHandler {
    private:
        CCBalanceGate *mBalanceGate;
    public:
        static CCBalanceGateEventHandler *create(CCBalanceGate *balanceGate);

        virtual void onCurrencyBalanceChanged(CCVirtualCurrency *virtualCurrency, int balance, int amountAdded);
        virtual void onGoodBalanceChanged(CCVirtualGood *virtualGood, int balance, int amountAdded);
    };
}

#endif //__CCBalanceGate_H_
