//
// Created by Shubin Fedor on 20/08/14.
// Copyright (c) 2014 SOOMLA. All rights reserved.
//

#ifndef __CCRecordGate_H_
#define __CCRecordGate_H_

#include "CCGate.h"
#include "CCLevelUpConsts.h"
#include "CCSimpleLevelUpEventHandler.h"

namespace soomla {
    class CCRecordGate: public CCGate {
        friend class CCRecordGateEventHandler;
        SL_SYNTHESIZE_RETAIN_WITH_DICT(cocos2d::CCString *, mAssociatedScoreId, AssociatedScoreId, CCLevelUpConsts::JSON_LU_ASSOCSCOREID)
    SL_SYNTHESIZE_DOUBLE_RETAIN_WITH_DICT(mDesiredRecord, DesiredRecord, CCLevelUpConsts::JSON_LU_DESIRED_RECORD);
        CC_SYNTHESIZE(CCLevelUpEventHandler *, mEventHandler, EventHandler);
    public:
        CCRecordGate(): CCGate(), mAssociatedScoreId(NULL), mDesiredRecord(NULL), mEventHandler(NULL) {
        }

        static CCRecordGate *create(cocos2d::CCString *id, cocos2d::CCString *associatedScoreId, cocos2d::CCDouble *desiredRecord);

        SL_CREATE_WITH_DICTIONARY(CCRecordGate);

        virtual bool init(cocos2d::CCString *id, cocos2d::CCString *associatedScoreId, cocos2d::CCDouble *desiredRecord);

        virtual bool initWithDictionary(cocos2d::CCDictionary* dict);

        virtual const char *getType() const;

        virtual cocos2d::CCDictionary *toDictionary();

        virtual ~CCRecordGate();

    protected:
        virtual bool canOpenInner();

        virtual bool openInner();

        virtual void registerEvents();

        virtual void unregisterEvents();
    };

    class CCRecordGateEventHandler: public CCSimpleLevelUpEventHandler {
    private:
        CCRecordGate *mRecordGate;
    public:
        static CCRecordGateEventHandler *create(CCRecordGate *recordGate);

        void onScoreRecordChanged(CCScore *score);
    };
}

#endif //__CCRecordGate_H_
