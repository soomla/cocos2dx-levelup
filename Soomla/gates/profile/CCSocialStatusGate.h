//
// Created by Shubin Fedor on 21/08/14.
// Copyright (c) 2014 SOOMLA. All rights reserved.
//


#ifndef __CCSocialStatusGate_H_
#define __CCSocialStatusGate_H_

#include "CCGate.h"
#include "CCSocialActionGate.h"


namespace soomla {

    class CCSocialStatusGate: public CCSocialActionGate {
        SL_SYNTHESIZE_RETAIN_WITH_DICT(cocos2d::CCString *, mStatus, Status, CCLevelUpConsts::JSON_LU_STATUS);
    public:
        CCSocialStatusGate(): CCSocialActionGate(), mStatus(NULL) {
        }

        static CCSocialStatusGate *create(cocos2d::CCString *id, CCProvider provider, cocos2d::CCString *status);

        SL_CREATE_WITH_DICTIONARY(CCSocialStatusGate)
        virtual bool init(cocos2d::CCString *id, CCProvider provider, cocos2d::CCString *status);

        virtual bool initWithDictionary(cocos2d::CCDictionary* dict);

        virtual const char *getType() const override;

        virtual cocos2d::CCDictionary *toDictionary();

        virtual ~CCSocialStatusGate();

    protected:
        virtual bool openInner();
    };

}

#endif //__CCSocialStatusGate_H_
