//
// Created by Shubin Fedor on 20/08/14.
// Copyright (c) 2014 SOOMLA. All rights reserved.
//


#ifndef __CCGatesListAnd_H_
#define __CCGatesListAnd_H_

#include "CCGatesList.h"

namespace soomla {
    class CCGatesListAnd : public CCGatesList {
    public:
        static CCGatesListAnd *create(cocos2d::__String *id, cocos2d::__Array *gates = NULL);
        static CCGatesListAnd *create(cocos2d::__String *id, CCGate *singleGate);

        SL_CREATE_WITH_DICTIONARY(CCGatesListAnd);

        virtual const char *getType() const override;
    protected:
        virtual bool canOpenInner();
    };
}


#endif //__CCGatesListAnd_H_
