//
// Created by Shubin Fedor on 20/08/14.
// Copyright (c) 2014 SOOMLA. All rights reserved.
//


#ifndef __CCGatesList_H_
#define __CCGatesList_H_

#include "CCGate.h"
#include "CCLevelUpConsts.h"
#include "CCBalanceMission.h"
#include "CCVirtualCurrency.h"
#include "CCVirtualGood.h"

namespace soomla {

    class CCGatesList: public CCGate {
        friend class CCGateListEventHandler;
        CC_SYNTHESIZE(cocos2d::CCArray *, mGates, Gates);
        CC_SYNTHESIZE(CCLevelUpEventHandler *, mEventHandler, EventHandler);
    public:
        CCGatesList(): CCGate(), mGates(NULL), mEventHandler(NULL) {
        }

        bool init(cocos2d::CCString *id, cocos2d::CCArray *gates = NULL);
        bool init(cocos2d::CCString *id, CCGate *gate);

        virtual bool initWithDictionary(cocos2d::CCDictionary* dict);

        virtual cocos2d::CCDictionary *toDictionary();

        virtual ~CCGatesList();

        unsigned int count();
        void add(CCGate *gate);
        void remove(CCGate *gate);
    protected:
        virtual bool openInner();

        virtual void registerEvents();

        virtual void unregisterEvents();
    };

    class CCGateListEventHandler: public CCSimpleLevelUpEventHandler {
    private:
        CCGatesList *mGatesList;
    public:
        static CCGateListEventHandler *create(CCGatesList *gatesList);

        virtual void onGateOpened(CCGate *gate);
    };
}

#endif //__CCGatesList_H_
