//
// Created by Shubin Fedor on 20/08/14.
// Copyright (c) 2014 SOOMLA. All rights reserved.
//


#ifndef __CCPurchasableGate_H_
#define __CCPurchasableGate_H_

#include "CCGate.h"
#include "CCLevelUpConsts.h"
#include "CCSimpleStoreEventHandler.h"

namespace soomla {
    class CCPurchasableGate: public CCGate {
        friend class CCPurchasableGateEventHanler;
        SL_SYNTHESIZE_RETAIN_WITH_DICT(cocos2d::CCString *, mAssociatedItemId, AssociatedItemId, CCLevelUpConsts::JSON_LU_ASSOCITEMID)
        CC_SYNTHESIZE_RETAIN(CCStoreEventHandler *, mEventHandler, EventHandler);
    public:
        CCPurchasableGate(): CCGate(), mAssociatedItemId(NULL), mEventHandler(NULL) {
        }

        static CCPurchasableGate *create(cocos2d::CCString *id, cocos2d::CCString *associatedItemId);

        SL_CREATE_WITH_DICTIONARY(CCPurchasableGate);

        virtual bool init(cocos2d::CCString *id, cocos2d::CCString *associatedItemId);

        virtual bool initWithDictionary(cocos2d::CCDictionary* dict);

        virtual const char *getType() const;

        virtual cocos2d::CCDictionary *toDictionary();

        virtual ~CCPurchasableGate();

    protected:
        virtual void registerEvents();

        virtual void unregisterEvents();

        virtual bool canOpenInner();

        virtual bool openInner();
    };

    class CCPurchasableGateEventHanler: public CCSimpleStoreEventHandler {
    private:
        CCPurchasableGate *mPurchasableGate;
    public:
        CCPurchasableGateEventHanler(): mPurchasableGate(NULL) {
        }

        static CCPurchasableGateEventHanler *create(CCPurchasableGate *purchasableGate);

        virtual void onItemPurchased(CCPurchasableVirtualItem *purchasableVirtualItem);
    };
}


#endif //__CCPurchasableGate_H_
