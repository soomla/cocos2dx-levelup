//
// Created by Shubin Fedor on 20/08/14.
// Copyright (c) 2014 SOOMLA. All rights reserved.
//


#ifndef __CCWorldCompletionGate_H_
#define __CCWorldCompletionGate_H_

#include "CCGate.h"
#include "CCLevelUpConsts.h"
#include "CCSimpleStoreEventHandler.h"
#include "CCSimpleLevelUpEventHandler.h"
#include "CCWorld.h"

namespace soomla {
    class CCWorldCompletionGate: public CCGate {
        friend class CCWorldCompletionGateEventHanler;
        SL_SYNTHESIZE_RETAIN_WITH_DICT(cocos2d::CCString *, mAssociatedWorldId, AssociatedWorldId, CCLevelUpConsts::JSON_LU_ASSOCWORLDID)
        CC_SYNTHESIZE_RETAIN(CCLevelUpEventHandler *, mEventHandler, EventHandler);
    public:
        CCWorldCompletionGate(): CCGate(), mAssociatedWorldId(NULL), mEventHandler(NULL) {
        }

        static CCWorldCompletionGate *create(cocos2d::CCString *id, cocos2d::CCString *associatedWorldId);

        SL_CREATE_WITH_DICTIONARY(CCWorldCompletionGate)
        bool init(cocos2d::CCString *id, cocos2d::CCString *associatedWorldId);

        virtual bool initWithDictionary(cocos2d::CCDictionary* dict);

        virtual const char *getType() const;

        virtual cocos2d::CCDictionary *toDictionary();

        virtual ~CCWorldCompletionGate();

    protected:
        virtual void registerEvents();

        virtual void unregisterEvents();

        virtual bool canOpenInner();

        virtual bool openInner();
    };

    class CCWorldCompletionGateEventHanler: public CCSimpleLevelUpEventHandler {
    private:
        CCWorldCompletionGate *mWorldCompletionGate;
    public:
        CCWorldCompletionGateEventHanler(): mWorldCompletionGate(NULL) {
        }

        static CCWorldCompletionGateEventHanler *create(CCWorldCompletionGate *worldCompletionGate);

        void onWorldCompleted(CCWorld *world);
    };
}

#endif //__CCWorldCompletionGate_H_
