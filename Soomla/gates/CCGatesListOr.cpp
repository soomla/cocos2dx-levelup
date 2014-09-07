//
// Created by Shubin Fedor on 20/08/14.
// Copyright (c) 2014 SOOMLA. All rights reserved.
//

#include "CCGatesListOr.h"

namespace soomla {

    USING_NS_CC;

    CCGatesListOr *CCGatesListOr::create(cocos2d::CCString *id, cocos2d::CCArray *gates) {
        CCGatesListOr *ret = new CCGatesListOr();
        if (ret->init(id, gates)) {
            ret->autorelease();
        }
        else {
            CC_SAFE_DELETE(ret);
        }

        return ret;
    }

    CCGatesListOr *CCGatesListOr::create(cocos2d::CCString *id, CCGate *singleGate) {
        CCGatesListOr *ret = new CCGatesListOr();
        if (ret->init(id, singleGate)) {
            ret->autorelease();
        }
        else {
            CC_SAFE_DELETE(ret);
        }

        return ret;
    }

    bool CCGatesListOr::canOpenInner() {
        CCObject *ref;
        CCGate *gate;
        CCARRAY_FOREACH(getGates(), ref) {
                gate = dynamic_cast<CCGate *>(ref);
                CC_ASSERT(gate);
                if (gate->isOpen()) {
                    return true;
                }
            }
        return false;
    }

    const char *CCGatesListOr::getType() const {
        return CCLevelUpConsts::JSON_JSON_TYPE_GATES_LIST_OR;
    }
}

