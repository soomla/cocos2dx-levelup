//
// Created by Shubin Fedor on 20/08/14.
// Copyright (c) 2014 SOOMLA. All rights reserved.
//

#ifndef __CCSocialActionGate_H_
#define __CCSocialActionGate_H_

#include "CCGate.h"
#include "CCLevelUpConsts.h"
#include "CCSimpleProfileEventHandler.h"
#include "CCUserProfileUtils.h"

namespace soomla {
    class CCSocialActionGate: public CCGate {
        friend class CCRecordGateEventHandler;
        CC_SYNTHESIZE(CCProfileEventHandler *, mEventHandler, EventHandler);
        CC_SYNTHESIZE(CCProvider, mProvider, Provider);
    public:
        CCSocialActionGate(): CCGate(), mProvider(FACEBOOK), mEventHandler(NULL) {
        }

        virtual bool init(cocos2d::CCString *id, CCProvider provider);

        virtual bool initWithDictionary(cocos2d::CCDictionary* dict);

        virtual cocos2d::CCDictionary *toDictionary();

        virtual ~CCSocialActionGate();

    protected:
        virtual bool canOpenInner();

        virtual void registerEvents();

        virtual void unregisterEvents();
    private:
        void fillProviderFromDict(cocos2d::CCDictionary *dict);
        void putProviderToDict(cocos2d::CCDictionary *dict);
    };

    class CCSocialActionGateEventHandler: public CCSimpleProfileEventHandler {
    private:
        CCSocialActionGate *mSocialActionGate;
    public:
        static CCSocialActionGateEventHandler *create(CCSocialActionGate *socialActionGate);

        virtual void onSocialActionFinishedEvent(CCProvider provider, CCSocialActionType socialActionType);
    };
}

#endif //__CCSocialActionGate_H_
