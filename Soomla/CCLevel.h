//
// Created by Shubin Fedor on 22/08/14.
// Copyright (c) 2014 SOOMLA. All rights reserved.
//


#ifndef __CCLevel_H_
#define __CCLevel_H_

#include "CCWorld.h"

namespace soomla {

    class CCLevel: public CCWorld {
    public:
        static CCLevel *create(cocos2d::__String *id);

    };

}

#endif //__CCLevel_H_
