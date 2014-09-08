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
        SL_SYNTHESIZE_RETAIN_WITH_DICT(cocos2d::__String *, mStatus, Status, CCLevelUpConsts::JSON_LU_STATUS);
    public:
        CCSocialStatusGate(): CCSocialActionGate(), mStatus(NULL) {
        }

        static CCSocialStatusGate *create(cocos2d::__String *id, CCProvider provider, cocos2d::__String *status);

        SL_CREATE_WITH_DICTIONARY(CCSocialStatusGate)
        virtual bool init(cocos2d::__String *id, CCProvider provider, cocos2d::__String *status);

        virtual bool initWithDictionary(cocos2d::__Dictionary* dict);

        virtual const char *getType() const override;

        virtual cocos2d::__Dictionary *toDictionary();

        virtual ~CCSocialStatusGate();

    protected:
        virtual bool openInner();
    };

}

#endif //__CCSocialStatusGate_H_
