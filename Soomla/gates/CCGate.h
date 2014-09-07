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

        virtual bool init(cocos2d::CCString *id, cocos2d::CCString *name = NULL);

        virtual bool initWithDictionary(cocos2d::CCDictionary* dict);

        virtual const char *getType() const;

        virtual bool open();
        virtual void forceOpen(bool open);
        virtual bool isOpen();
        virtual bool canOpen();
    protected:
        virtual void registerEvents() = 0;
        virtual void unregisterEvents() = 0;
        virtual bool canOpenInner() = 0;
        virtual bool openInner() = 0;
    };
}

#endif //__CCGate_H_
