//
// Created by Shubin Fedor on 21/08/14.
// Copyright (c) 2014 SOOMLA. All rights reserved.
//

#include "CCScheduleGate.h"
#include "CCLevelUpConsts.h"
#include "CCDomainFactory.h"
#include "CCGateStorage.h"

namespace soomla {

#define TAG "SOOMLA ScheduleGate"

    CCScheduleGate *CCScheduleGate::create(cocos2d::CCString *id, CCSchedule *schedule) {
        CCScheduleGate *ret = new CCScheduleGate();
        if (ret->init(id, schedule)) {
            ret->autorelease();
        }
        else {
            CC_SAFE_DELETE(ret);
        }

        return ret;
    }

    bool CCScheduleGate::init(cocos2d::CCString *id, CCSchedule *schedule) {
        bool result = CCGate::init(id, NULL);
        if (result) {
            setSchedule(schedule);
            return true;
        }
        return result;
    }

    bool CCScheduleGate::initWithDictionary(cocos2d::CCDictionary *dict) {
        bool result = CCGate::initWithDictionary(dict);
        if (result) {
            CCObject *ref = dict->objectForKey(CCLevelUpConsts::JSON_SCHEDULE);
            if (ref) {
                cocos2d::CCDictionary *scheduleDict = dynamic_cast<cocos2d::CCDictionary *>(ref);
                CC_ASSERT(scheduleDict);
                setSchedule((CCSchedule *) CCDomainFactory::getInstance()->createWithDictionary(scheduleDict));
            }

            return true;
        }
        return result;
    }

    cocos2d::CCDictionary *CCScheduleGate::toDictionary() {
        cocos2d::CCDictionary *dict = CCSoomlaEntity::toDictionary();

        if (mSchedule) {
            dict->setObject(mSchedule->toDictionary(), CCLevelUpConsts::JSON_SCHEDULE);
        }

        return dict;
    }

    const char *CCScheduleGate::getType() const {
        return CCLevelUpConsts::JSON_JSON_TYPE_SCHEDULE_GATE;
    }

    CCScheduleGate::~CCScheduleGate() {
        CC_SAFE_RELEASE(mSchedule);
    }


    void CCScheduleGate::registerEvents() {
        // Not listening to any events
    }

    void CCScheduleGate::unregisterEvents() {
        // Not listening to any events
    }

    bool CCScheduleGate::canOpenInner() {
        // gates don't have activation times. they can only be activated once.
        // We kind of ignoring the activation limit of Schedule here.
        return mSchedule->approve(CCGateStorage::getInstance()->isOpen(this) ? 1 : 0);
    }

    bool CCScheduleGate::openInner() {
        if (canOpen()) {
            // There's nothing to do here... If the DesiredRecord was reached then the gate is just open.
            forceOpen(true);
            return true;
        }

        return false;
    }
}