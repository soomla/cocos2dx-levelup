//
// Created by Shubin Fedor on 20/08/14.
// Copyright (c) 2014 SOOMLA. All rights reserved.
//

#include "CCGatesListAnd.h"

namespace soomla {

    USING_NS_CC;

    CCGatesListAnd *CCGatesListAnd::create(cocos2d::CCString *id, cocos2d::CCArray *gates) {
        CCGatesListAnd *ret = new CCGatesListAnd();
        if (ret->init(id, gates)) {
            ret->autorelease();
        }
        else {
            CC_SAFE_DELETE(ret);
        }

        return ret;
    }

    CCGatesListAnd *CCGatesListAnd::create(cocos2d::CCString *id, CCGate *singleGate) {
        CCGatesListAnd *ret = new CCGatesListAnd();
        if (ret->init(id, singleGate)) {
            ret->autorelease();
        }
        else {
            CC_SAFE_DELETE(ret);
        }

        return ret;
    }

    bool CCGatesListAnd::canOpenInner() {
        CCObject *ref;
        CCGate *gate;
        CCARRAY_FOREACH(getGates(), ref) {
                gate = dynamic_cast<CCGate *>(ref);
                CC_ASSERT(gate);
                if (!gate->isOpen()) {
                    return false;
                }
            }
        return true;
    }

    const char *CCGatesListAnd::getType() const {
        return CCLevelUpConsts::JSON_JSON_TYPE_GATES_LIST_AND;
    }
}

