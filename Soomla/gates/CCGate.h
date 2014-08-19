//
// Created by Shubin Fedor on 19/08/14.
// Copyright (c) 2014 SOOMLA. All rights reserved.
//

#ifndef __CCGate_H_
#define __CCGate_H_

#include "CCSoomlaEntity.h"

namespace soomla {
    class CCGate: public CCSoomlaEntity {
    public:
        SL_CREATE_WITH_DICTIONARY(CCGate);

        void forceOpen(bool b);

        bool open();

        bool canOpen();


        virtual char const *getType() const;
    };
}

#endif //__CCGate_H_
