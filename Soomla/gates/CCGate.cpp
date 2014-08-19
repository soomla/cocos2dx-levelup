//
// Created by Shubin Fedor on 19/08/14.
// Copyright (c) 2014 SOOMLA. All rights reserved.
//

#include "CCGate.h"
#include "CCLevelUpConsts.h"

void soomla::CCGate::forceOpen(bool b) {

}

bool soomla::CCGate::open() {
    return false;
}

bool soomla::CCGate::canOpen() {
    return false;
}

char const *soomla::CCGate::getType() const {
    return CCLevelUpConsts::JSON_JSON_TYPE_GATE;
}
