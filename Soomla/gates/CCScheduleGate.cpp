/*
 Copyright (C) 2012-2014 Soomla Inc.

 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at

 http://www.apache.org/licenses/LICENSE-2.0

 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.
 */



#include "CCScheduleGate.h"
#include "CCLevelUpConsts.h"
#include "CCDomainFactory.h"
#include "CCGateStorage.h"

namespace soomla {

#define TAG "SOOMLA ScheduleGate"

    CCScheduleGate *CCScheduleGate::create(cocos2d::__String *id, CCSchedule *schedule) {
        CCScheduleGate *ret = new CCScheduleGate();
        if (ret->init(id, schedule)) {
            ret->autorelease();
        }
        else {
            CC_SAFE_DELETE(ret);
        }

        return ret;
    }

    bool CCScheduleGate::init(cocos2d::__String *id, CCSchedule *schedule) {
        bool result = CCGate::init(id, NULL);
        if (result) {
            setSchedule(schedule);
            return true;
        }
        return result;
    }

    bool CCScheduleGate::initWithDictionary(cocos2d::__Dictionary *dict) {
        bool result = CCGate::initWithDictionary(dict);
        if (result) {
            Ref *ref = dict->objectForKey(CCCoreConsts::JSON_SCHEDULE);
            if (ref) {
                cocos2d::__Dictionary *scheduleDict = dynamic_cast<cocos2d::__Dictionary *>(ref);
                CC_ASSERT(scheduleDict);
                setSchedule((CCSchedule *) CCDomainFactory::getInstance()->createWithDictionary(scheduleDict));
            }

            return true;
        }
        return result;
    }

    cocos2d::__Dictionary *CCScheduleGate::toDictionary() {
        cocos2d::__Dictionary *dict = CCSoomlaEntity::toDictionary();

        if (mSchedule) {
            dict->setObject(mSchedule->toDictionary(), CCCoreConsts::JSON_SCHEDULE);
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
