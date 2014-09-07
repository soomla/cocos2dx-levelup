//
// Created by Shubin Fedor on 20/08/14.
// Copyright (c) 2014 SOOMLA. All rights reserved.
//


#ifndef __CCGatesListOr_H_
#define __CCGatesListOr_H_

#include "CCGatesList.h"

namespace soomla {
    class CCGatesListOr : public CCGatesList {
    public:
        static CCGatesListOr *create(cocos2d::CCString *id, cocos2d::CCArray *gates = NULL);
        static CCGatesListOr *create(cocos2d::CCString *id, CCGate *singleGate);

        SL_CREATE_WITH_DICTIONARY(CCGatesListOr);

        virtual const char *getType() const;
    protected:
        virtual bool canOpenInner();
    };
}


#endif //__CCGatesListAnd_H_
